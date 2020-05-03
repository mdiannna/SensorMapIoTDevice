 #include "os.h"
#include "timer-api.h"

OS_TaskDescriptor_t task1;


void timer_handle_interrupts(int timer) {
	OS_Scheduler();
}

void SerialInit() {
	Serial.begin(9600);
}

int PrintHelloTaskRun() {
	Serial.println("Hello!");
  return 0;
}



void setup() {
	SerialInit();

  task1 = OS_TaskDescriptorDefault();
	task1.recurrence = 1000; //1 second

	OS_TaskInit( PrintHelloTaskRun, &task1 );

  timer_init_ISR_1KHz(TIMER_DEFAULT);
}

void loop() {
//	Serial.println(":)");
}
