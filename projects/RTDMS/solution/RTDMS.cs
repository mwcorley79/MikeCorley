using System;
using System.Device.Gpio;
using System.Device.I2c;
using System.Text;
using System.Text.Json;
using Iot.Device.Bmxx80;
using Iot.Device.Bmxx80.ReadResult;
using Microsoft.Azure.Devices.Client;
using Microsoft.Extensions.Configuration;

namespace viceroy
{
    public class RTDMS_Driver : IDisposable
    {
        public bool HVAC_On = false;
        private I2cConnectionSettings i2cSettings;
        private I2cDevice i2cDevice;
        private GpioController gpio;
        private Bme280 bme280;
        private LCDWriter lcd_writer;
        private IotHubClient hub_client;
        private Task driverTask;
        private Task transmitTask;
        private object transmitLockObj;
        private CancellationTokenSource ctsTransmitTelem;
        public RDTMS_Settings Settings { get; set; }
        public int HVAC_Pin { get; set; }
        public int LED_Pin { get; set; }
        public int TransmitInterval;

        int transmitCount = 0;

        public RTDMS_Driver()
        {
            try
            {
                // Build a configuration object, using JSON providers.
                // https://learn.microsoft.com/en-us/dotnet/core/extensions/configuration
                IConfiguration config = new ConfigurationBuilder()
                   .AddJsonFile("appsettings.json")
                   .Build();

                // Get values from the apppsettings configuration given their key and target value type.
                Settings = config.GetRequiredSection("Settings").Get<RDTMS_Settings>();

                HVAC_Pin = Settings.HVACPin;
                LED_Pin = Settings.LEDPin;

                // Get a reference to a device on the I2C bus
                i2cSettings = new I2cConnectionSettings(1, Bme280.DefaultI2cAddress);

                // initialize the device (instance) using, the BME280 default bus address
                i2cDevice = I2cDevice.Create(i2cSettings);

                // Finally, create an instance of BME280, using device settings configured above)
                bme280 = new Bme280(i2cDevice);

                // Initialize the GPIO controller for communication with Rasspberry Pi, using logical pin numbering scheme
                gpio = new GpioController(PinNumberingScheme.Logical);

                // Open the HVAC pin for output, set to off (low voltage)
                gpio.OpenPin(Settings.HVACPin, PinMode.Output);
                gpio.Write(Settings.HVACPin, PinValue.Low);

                // Open the transmit LED indicator pin for output, set to off (low voltage)
                gpio.OpenPin(Settings.LEDPin, PinMode.Output);
                gpio.Write(Settings.LEDPin, PinValue.Low);

                //construct an instance of the LCD_writer (MaxLines, and LineLen are set in appsettings.json)
                lcd_writer = new LCDWriter(1, 0x27, Settings.LCDMaxLines, Settings.LCDLineLen);
                lcd_writer.On(true); // turn the display on

                // construct an instance of the IoTHub to enable dbidirectional MQTT communication the Azure Iot hub service
                // depends on Microsoft.Azure.Devices.Client package
                hub_client = new IotHubClient(Settings, TransportType.Mqtt, this);

                // cancelation token for stopping the transmit task
                ctsTransmitTelem = new CancellationTokenSource();

                // critical section (lock) for setting the interval rate
                transmitLockObj = new Object();

                // set the default transmit interval 
                TransmitInterval = 1000;

                // trap ctrl-c press
                Console.CancelKeyPress += (s, e) =>
                {
                    Console.WriteLine("Choose menu option \"X\" to exit the program");
                    e.Cancel = true;
                };
            }
            catch (Exception ex)
            {
                Console.Error.WriteLine($"{ex}");
            }
        }

        public (double, double, double) ReadBME280()
        {
            // Read the BME280
            Bme280ReadResult output = bme280.Read();
            double temperatureF = output.Temperature.Value.DegreesFahrenheit;
            double humidityPercent = output.Humidity.Value.Percent;
            double decapascals = output.Pressure.Value.Decapascals;
            return (temperatureF, humidityPercent, decapascals);
        }

        public void HandleCloseCommmand()
        {
            if (HVAC_On)
            {
                Console.WriteLine("Shuting down HVAC unit ");
                gpio.Write(HVAC_Pin, PinValue.Low);
            }

            if (gpio.Read(LED_Pin) == PinValue.High)
            {
                gpio.Write(LED_Pin, PinValue.Low);
            }

            // Close the pin before exit
            gpio.ClosePin(HVAC_Pin);
            gpio.ClosePin(LED_Pin);

            // turn off lcd display
            lcd_writer.On(false);
        }

        void UpdateSendInterval()
        {
            lock (transmitLockObj)
            {
                Console.Write("Enter new send interval rate (ms): ");
                string interval = Console.ReadLine();
                if (int.TryParse(interval, out TransmitInterval))
                    Console.WriteLine($"Send interval rate (ms): {TransmitInterval}");
                else
                    Console.WriteLine($"input error, interval not set: {TransmitInterval}");
            }
        }

        void SendAzureCompatibleTempHumMessage(string device_id, double temp, double hum)
        {
            /* var telemetryDataPoint = new
             {
                 deviceId = device_id,
                 temperature = temp,
                 humidity = hum,
             };
            */

            Telem telemetryDataPoint = new Telem
            {
                deviceId = device_id,
                temperature = temp,
                humidity = hum,
                messageId = transmitCount++
            };
           
             var telemetryDataString = JsonSerializer.Serialize(telemetryDataPoint);

            // serialize the telemetry data and convert it to JSON.
            //var telemetryDataString = JsonConvert.SerializeObject(telemetryDataPoint);

            // Encode the serialized object using UTF-8 so it can be parsed by IoT Hub when
            // processing messaging rules.
            var message = new Message(Encoding.UTF8.GetBytes(telemetryDataString))
            {
                ContentEncoding = "utf-8",
                ContentType = "application/json",
            };

            Console.WriteLine(string.Format("[{0}] {1}", transmitCount, telemetryDataString));

            // Submit the message to the hub.
            hub_client.SendDeviceToCloudMessagesAsync(message).Wait();

            /* string message_template = string.Format("{\"messageId\":{0},\"deviceId\":\"{1}\",\"temperature\":{2},\"humidity\":{3}}", ++msgCount, device_id,  temp, hum );
            Microsoft.Azure.Devices.Client.Message m = new Microsoft.Azure.Devices.Client.Message(Encoding.ASCII.GetBytes(message_template));
            iotClient.SendDeviceToCloudMessagesAsync(m).Wait();
            Debug.WriteLine(message_template);
            */
        }

        public void TransmitTelemety()
        {
            transmitTask = Task.Run(() =>
            {
                while (!ctsTransmitTelem.IsCancellationRequested)
                {
                    var telem = ReadBME280();
                    gpio.Write(LED_Pin, PinValue.High);

                    SendAzureCompatibleTempHumMessage(Settings.DeviceId, telem.Item1, telem.Item2);

                    lock (transmitLockObj)
                    {
                        gpio.Write(LED_Pin, PinValue.Low);
                        Thread.Sleep(TransmitInterval);
                    }

                    gpio.Write(LED_Pin, PinValue.Low);
                }

                // dispose of cancelation token, and instiate a new for next time the function runs
                ctsTransmitTelem.Dispose();
                ctsTransmitTelem = new CancellationTokenSource();
            });
        }

        bool IsTransmiting()
        {
            if(transmitTask != null)
               return !transmitTask.IsCompleted;
            return false;
        }

        public void External_HVAC(bool onoff, string LCD_message)
        {
            HVAC_On = onoff;
            if(HVAC_On)
            {
                 gpio.Write(HVAC_Pin, PinValue.High);
            }
            else
            {
                 gpio.Write(HVAC_Pin, PinValue.Low);
            }

            Console.WriteLine($"{LCD_message}");
            lcd_writer.WriteMessage(LCD_message);
        }

        bool ExecuteCommand(string commandText)
        {
            switch (commandText.ToLower())
            {
                case "x":
                    Console.WriteLine("Exiting RTDMS...");
                    HandleCloseCommmand();
                    return true;

                case "h":
                    {
                        string HVAC_msg = "HVAC Off";
                        if (HVAC_On = !HVAC_On)
                        {
                           HVAC_msg = "HVAC On";
                        }
                       
                        External_HVAC(HVAC_On, HVAC_msg);    
                    }
                    break;
                case "t":
                    {
                        if (IsTransmiting())
                        {
                            ctsTransmitTelem.Cancel();
                            transmitTask.Wait();
                        }
                        else
                        {
                            TransmitTelemety();
                        }
                    }
                    break;
                case "i":
                    UpdateSendInterval();
                    break;
                case "s":
                    {
                        var output = ReadBME280();
                        Console.WriteLine("DEVICE STATUS");
                        Console.WriteLine("-------------");
                        Console.WriteLine($"HVAC: {(HVAC_On ? "ON" : "OFF")}");
                        Console.WriteLine($"Temperature: {output.Item1:0.#}dF");
                        Console.WriteLine($"Relative humidity: {output.Item2:#.##}%");
                        string lcd_msg = $"T:{output.Item1:0.#}dF " + $"H:{output.Item2:#.#}%";

                        lcd_writer.WriteMessage(lcd_msg);
                    }
                    break;
                default:
                    Console.WriteLine("Unknown command");
                    break;
            }
            return false;
        }

        void DisplayMenu()
        {
            string hvac_status = HVAC_On ? "Off" : "On";
            string transmit_status = (!IsTransmiting()) ? "Transmit" : "Stop Transmiting";
            Console.WriteLine("---------------");
            Console.WriteLine("RDTMS v1.0 Menu");
            Console.WriteLine("---------------");
            Console.WriteLine("\"S\": - display current temperature/humidity");
            Console.WriteLine($"\"H\": - turn HVAC {hvac_status}");
            Console.WriteLine($"\"T\": - {transmit_status} Telemetry To Azure IoT Hub service");
            Console.WriteLine("\"I\": - Change telemetry transmit interval (1000ms -default )");
            Console.WriteLine("\"X:\" - Close the  RDTMS driver");
            Console.Write("Command:-> ");
        }

        public void Start()
        {
            driverTask = Task.Run(() =>
            {
                // prior to displaying the menu for the first time connect, established TLS connection to Azure IoT Cloud 
                hub_client.Start();

                if (hub_client.Connected)
                {
                    Console.WriteLine("Using Shared Access Signature (SAS - connectionString) to authenticate with Azure IoT service, please wait...");
                    Console.WriteLine("Successfully Connected To Azure Cloud (IoT Hub) Service, using MQTT over TLS.");
                }
                else
                {
                    Console.WriteLine("Error connecting (or already connected) to the Azure Cloud");
                }

                bool exit = false;
                while (!exit)
                {
                    DisplayMenu();
                    string commandText = Console.ReadLine();
                    exit = ExecuteCommand(commandText);
                }

                Console.WriteLine("Closing Azure IoT Connection...");
                hub_client.Close();
                if (!hub_client.Connected)
                    Console.WriteLine("Disconnected from Azure Cloud");
                else
                    Console.WriteLine("Eror disconnecting from the Azure Cloud");
            });
        }

        public void Stop()
        {
            driverTask.Wait();
        }

        // free any platform (non CLR managed) resources
        public void Dispose()
        {
            if (bme280 != null)
                bme280.Dispose();

            if (lcd_writer != null)
                lcd_writer.Dispose();

            if (i2cDevice != null)
                i2cDevice.Dispose();

            if (gpio != null)
                gpio.Dispose();

            if (hub_client != null)
                hub_client.Dispose();

            if (ctsTransmitTelem != null)
                ctsTransmitTelem.Dispose();

            Console.WriteLine("Disposed");
        }
    }
}
