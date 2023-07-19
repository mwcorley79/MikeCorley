using Iot.Device.CharacterLcd;
using Iot.Device.Pcx857x;
using System;
using System.Device.Gpio;
using System.Device.I2c;

namespace viceroy
{
    public class LCDWriter : IDisposable
    {
        I2cDevice i2c;
        Pcf8574 driver;
        Lcd2004 lcd;

        int line_len_;
        int max_lines_; 

        public LCDWriter(int busId, int deviceAddress, int maxLines, int lineLen)
        {
            i2c = I2cDevice.Create(new I2cConnectionSettings(busId, deviceAddress));
            driver = new Pcf8574(i2c);
            lcd = new Lcd2004(registerSelectPin: 0,
                                    enablePin: 2,
                                    dataPins: new int[] { 4, 5, 6, 7 },
                                    backlightPin: 3,
                                    backlightBrightness: 0.1f,
                                    readWritePin: 1,
                                    controller: new GpioController(PinNumberingScheme.Logical, driver));
        
            line_len_ = lineLen;
            max_lines_ = maxLines;
        }


        public void WriteMessage(string message)
        {

            Clear();
            int numLines = (int)Math.Ceiling((double)message.Length / line_len_);

            int line_num = 0;
            int startPos = 0;
            for (line_num = 0; ((line_num < numLines - 1) && (line_num < max_lines_)); ++line_num)
            {
                WriteMessageLine(message.Substring(startPos,line_len_), line_num);
                startPos += line_len_;
            }

            WriteMessageLine(message.Substring(startPos, message.Length-startPos), line_num);
        }


        public void WriteMessageLine(string message, int lineNum, int startPos = 0)
        {
            lcd.SetCursorPosition(startPos, lineNum);
            lcd.Write(message);
        }

        public void Clear()
        {
            lcd.Clear();
        }

        public void On(bool on = false)
        {
            lcd.BacklightOn = on;
        }

        public void Dispose()
        {
            lcd.Dispose();
            driver.Dispose();
            i2c.Dispose();
        }

#if TEST_LCD_WRITER
        static void Main(string[] args)
        {
            Console.WriteLine("*** Test LCD Writer *** ");
            LCDWriter lcd_writer = new LCDWriter(1, 0x27);
            lcd_writer.On(true);

            int currentLine = 0;

            while (currentLine < 4)
            {

                lcd_writer.Clear();
                lcd_writer.WriteMessage(DateTime.Now.ToShortTimeString(), currentLine);

                currentLine++;
                Thread.Sleep(1000);
            }

            lcd_writer.On(false);
        }
#endif

    }
}