#include "temperature.h"

void InitTemperatureSensor() {
	if(TEMPERATURE_SENSOR == "BMP180") {
		InitTemperatureSensorBMP();
	}
	else if(TEMPERATURE_SENSOR == "DHT11") {
		InitTemperatureDHT();
	}
}

double GetTemperature() {
	if(TEMPERATURE_SENSOR == "BMP180") {
		return GetTemperatureBMP();
	}
	else if(TEMPERATURE_SENSOR == "DHT11") {
		return GetTemperatureDHT();
	}
}
