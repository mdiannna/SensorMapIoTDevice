#include "humidity.h"

void SerialInit() {
  Serial.begin(9600);
}

void setup() {
  SerialInit();
  Serial.println(F("DHTxx test!"));

  InitHumidity();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  float humidity = GetHumidity();

  Serial.println("humidity: ");
  Serial.println(humidity);
}