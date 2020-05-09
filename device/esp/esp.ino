double lightLevel = 0.0;
 
#define SEND_DATA_DELAY 5000

#include "led.h"
#include "mqtt.h"
#include "tasks.h"

void setup() {
  Serial.begin(112500);
  InitMQTT();
  delay(1000);
  CreateTasks();
}

void loop() {
  client.loop();
  // delay(1000);
}
 
 
