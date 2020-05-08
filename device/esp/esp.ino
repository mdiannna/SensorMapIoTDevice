
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
  String message  = ReceivePacket();
  Serial.println("---=====Received command:=====---");
  Serial.println(message);
	delay(5000);
}
