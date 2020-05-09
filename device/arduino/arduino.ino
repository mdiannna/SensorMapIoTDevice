#include <timer-api.h>
#include <timer_setup.h>

#include "os.h"
#include "tasks.h"
#include "communication.h"
#include "led.h"

#define DEVICE_ID 1

int connection_established_esp = 0;

OS_TaskDescriptor_t tasks[NR_TASKS];
int32_t taskRecurrences[5] = {1000, 1010, 1020, 1030, 1040};
int (*fp[NR_TASKS])() = { 
                    TaskGetTemperature, 
                    TaskGetHumidity,
                    TaskGetDustValue,
                    TaskGetLightValue,
                    TaskGetGasValue
                };


void timer_handle_interrupts(int timer) {
	OS_Scheduler();
}

void SerialInit() {
	Serial.begin(9600);
}


void TasksInit() {
   for(int i=0; i<NR_TASKS; i++) {
    tasks[i] =  OS_TaskDescriptorDefault();
    tasks[i].recurrence = taskRecurrences[i];

    OS_TaskInit( (*fp[i]), &(tasks[i]) );
   }
}

void setup() {
	//SerialInit();
  CommunicationInit();
  LED_Init();

  // TODO: 
  // TemperatureInit()
  // HumidityInit();
  // DustInit();
  // LightInit();
  // GasInit();

  TasksInit();

  timer_init_ISR_1KHz(TIMER_DEFAULT);
}

// String CreateJSONItem(double temperature, double humidity, double light, double gas, double dust) {
//   String result = " { \"boxID\": "+ DEVICE_ID + ", \"temperature\": " + temperature + "\"humidity\": " 
//   + humidity + ", \"light\": " + light +
//    ", \"gas\": " +gas + ", \"dust\": " + dust + "}";
//   return result;
// }

String CreateJSONItem(String sensorType, double value) {
  String result = " { \"boxID\": "+ String(DEVICE_ID)
  + ", \"sensorType\": \"" + String(sensorType) +"\" " +
  + ",\"value\": " + String(value) + "}"; 
 
  return result;
}


void SendDataJSON() {
  String result = "[" 
  + CreateJSONItem("temperature", temperature) + "," 
  + CreateJSONItem("humidity", humidity)+ ","
  + CreateJSONItem("light", light) + ","
  + CreateJSONItem("gas", gas) + ","
  + CreateJSONItem("dust", dust) + ","
  + "]";

  SendPacket(result, TYPE_SEND_DATA);
}

void loop() {
//  LED_Off();
  int command_type = ReceivePacket();
  Serial.println("Received command_type:");
  Serial.println(command_type);
//  LED_On();       
  
 
      SendDataJSON();
      
  delay(1000);
}
