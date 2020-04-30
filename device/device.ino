#include "os.h"

OS_TaskDescriptor_t task1;


void SerialInit() {
	Serial.begin(9600);
}

void PrintHello() {
	Serial.println("Hello!");
}

void setup() {
	SerialInit();

	task1.recurrence = 1000; //1 second
	task1.recurrenceCnt = 500;
	task1.startupTimeout = 1000;  // 1 second
	task1.timeout = 1000;
	task1.priorty = 1;

	// int32_t (*task) ();
	task1.task = PrintHello;
	task1.task_state = ENABLE;


	OS_TaskInit( PrintHello, &task1 );

}

void loop() {
//	Serial.println(":)");
}
