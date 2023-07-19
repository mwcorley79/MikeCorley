/* notes: 

For the azure function
1. use azure functions extenstion to Iot Hub tiggered function
2.  choose .net LTS (not isolated)
3. update Microsoft.Azure.WebJobs.Extensions.EventHubs      4.2.0  to the latest 5.3.0
      commmand: dotnet add package Microsoft.Azure.WebJobs.Extensions.EventHubs -v 5.3.0

4.create a corresponding function app using the Azure Portal.  
5. the azure extension in vscode to the deploy the function to the app.
*
https://ardalis.com/how-do-i-update-a-nuget-package-using-dotnet-cli/

For cloud to device use the following package:
Add the NuGet package for the c2d communication to function project: dotnet add package Microsoft.Azure.Devices

Add a reference to TelemetryModel class lib project:
	dotnet add AzTelemFunc.csproj reference ../TelemModel/TelemModel.csproj

*/


using IoTHubTrigger = Microsoft.Azure.WebJobs.EventHubTriggerAttribute;
using System;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
// using Microsoft.Azure.EventHubs;
using Azure.Messaging.EventHubs;

using System.Text;
using System.Text.Json;
using System.Net.Http;
using Microsoft.Extensions.Logging;

using System.Threading.Tasks;
using System.Threading;


using Microsoft.Azure.Devices;

namespace viceroy.TelemFunc
{
    public class IoTHub_EventHubFunc
    {
        private static HttpClient client = new HttpClient();
        private static bool status = false;
        public string IOTHUB_CONNECT_STRING { get; set; } = "HostName=QSI-IoT-hub-1.azure example example"
        private int instance_count = 0;
        private static int static_count = 0; 

        public IoTHub_EventHubFunc()
        {
            instance_count++;
            static_count++;

        }
        
        public async Task Generic_Device_Controller(string dev_name, string deviceId, bool onoff)
        {
            var methodInvocation = new CloudToDeviceMethod(dev_name) { ResponseTimeout = TimeSpan.FromSeconds(30) };
            var messag = new { onoff = onoff };

            // newtonsoft json library use
            //string messageString = JsonConvert.SerializeObject(messag);

            // native .Net json library use
            string messageString = System.Text.Json.JsonSerializer.Serialize(messag);

            methodInvocation.SetPayloadJson(messageString);
            ServiceClient serviceClient = ServiceClient.CreateFromConnectionString(IOTHUB_CONNECT_STRING);
            var response = await serviceClient.InvokeDeviceMethodAsync(deviceId, methodInvocation);
        }

        [FunctionName("IoTHub_EventHubFunc")]
        public void Run([IoTHubTrigger("messages/events", Connection = "HubConnection")] EventData message, ILogger log)
        {
            // log.LogInformation($"C# IoT Hub trigger function processed a message: {Encoding.UTF8.GetString(message.Body.Array)}");
            string deserialized_message = Encoding.UTF8.GetString(message.Body.ToArray());
            // log.LogInformation($"C# IoT Hub trigger function processed a message: {deserialized_message}");

            // native .Net json library use
            Telem telemMsg = JsonSerializer.Deserialize<Telem>(deserialized_message);

            // Newtonsoft JSON library example
            // Telem telemMsg = JsonConvert.DeserializeObject<Telem>(telem_input, new JsonSerializerSettings
            // {
            //    Error = HandleDeserializationError
            // });

           // log.LogInformation("Instance: " + instance_count);
            log.LogInformation("Run Count     : " +  static_count);
            log.LogInformation("Humidity Telem: " + telemMsg.humidity);

            if(telemMsg.humidity >= 70)
            {
                if(status == false)
                {
                    Generic_Device_Controller("ControlRelay", telemMsg.deviceId, true).Wait();
                    
                    //  still need IFTTT integration, not shown.
                    status = true;       
                }
            }
            else
            {
                if(status == true)
                {
                    Thread.Sleep(3000);
                    Generic_Device_Controller("ControlRelay", telemMsg.deviceId, false).Wait();
                    status = false;
                }
            }

        }
    }
}
