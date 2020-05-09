
#include <Arduino.h>
#include "communication.h"
#include <Wire.h>

void setup() {
	CommunicationInit();

	Serial.println("Init done MCU2");
	delay(1000);
	SendHello();
}


void loop() {
  SendHello();
	delay(5000);
}
