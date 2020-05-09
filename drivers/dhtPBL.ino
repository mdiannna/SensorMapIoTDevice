#include "temperature.h"


void SerialInit() {
  Serial.begin(9600);
}

void setup() {
  SerialInit();
  Serial.println(F("DHTxx test!"));

  InitTemperature();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  float temperature = GetTemperature();

  Serial.println("temperature: ");
  Serial.println(temperature);
}
