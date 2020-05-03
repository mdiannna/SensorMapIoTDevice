#include "os.h"
#include "timer-api.h"
#include "tasks.h"


OS_TaskDescriptor_t tasks[NR_TASKS];
int32_t taskRecurrences[5] = {1000, 1010, 1020, 1030, 1040};
void (*fp[NR_TASKS])() = { 
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
	SerialInit();
  // TODO: 
  // TemperatureInit()
  // HumidityInit();
  // DustInit();
  // LightInit();
  // GasInit();

  TasksInit();

  timer_init_ISR_1KHz(TIMER_DEFAULT);
}

void loop() {
  	Serial.println(":)");
    delay(1000);
    Serial.println("^^^^^");
    delay(2000);
}
