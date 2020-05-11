#include "temperatureDHT.h"


DHT dht(DHTPIN, DHTTYPE);


void InitTemperatureDHT() {
    dht.begin();
}

float GetTemperatureDHT() {
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
