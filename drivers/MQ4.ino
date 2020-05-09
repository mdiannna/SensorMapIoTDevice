#include "MQ4.h"

void SerialInit() {
  Serial.begin(9600);
}

void setup(){ 
	  SerialInit();
  	Serial.println(F("DHTxx test!"));

  	InitMQ4();

}


void loop(){
	delay(2000);
  	float gas = GetMQ4();

  	Serial.println("gas: ");
  	Serial.println(gas);
  
}
