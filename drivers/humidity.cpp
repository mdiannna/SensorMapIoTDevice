#include "humidity.h"


DHT dht(DHTPIN, DHTTYPE);


void InitHumidity() {
  	dht.begin();
}

float GetHumidity() {
	// Read humidity:
  	float h = dht.readHumidity();
  	if (isnan(h)) {
    	Serial.println(F("Failed to read from DHT sensor!"));
    	return -1;
    }
  	// else
 	return h;
}