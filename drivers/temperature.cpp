#include "temperature.h"


DHT dht(DHTPIN, DHTTYPE);


void InitTemperature() {
    dht.begin();
}

float GetTemperature() {
  // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // for humidity:
     // float h = dht.readHumidity();
    if (isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return -1;
    }
    // else
  return t;
}
