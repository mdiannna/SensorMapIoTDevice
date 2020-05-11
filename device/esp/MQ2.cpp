#include "MQ2.h"

void InitGasSensor() {
  pinMode(GAS_SENSOR_PIN, INPUT);  
}


double GetGasSensorValue() {
  int sensorValue = analogRead(GAS_SENSOR_PIN);
  return sensorValue/100 + 0.0;
}
