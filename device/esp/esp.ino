double lightLevel = 0.0;
 
#define SEND_DATA_DELAY 5000

#include "led.h"
#include "mqtt.h"
#include "tasks.h"
#include "light.h"

void setup() {
  Serial.begin(112500);
  InitMQTT();
  InitLight();
  delay(1000);
  CreateTasks();
}

void loop() {
  client.loop();
  // delay(1000);
}
 
 
