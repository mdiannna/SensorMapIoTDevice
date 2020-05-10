double lightLevel = 0.0;
 
#define SEND_DATA_DELAY 5000

#include "led.h"
#include "mqtt.h"
#include "tasks.h"
#include "light.h"
#include "MQ2.h"

void InitSerial() {
  Serial.begin(112500);
}

void setup() {
  InitSerial();
  InitMQTT();
  InitLight();
  InitGasSensor();
  
  delay(1000);
  
  CreateTasks();
}

void loop() {
  client.loop();
  // delay(1000);
}
 
 
