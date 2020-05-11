#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

#include "temperatureDHT.h"
#include "temperatureBMP.h"

// #define TEMPERATURE_SENSOR "DHT11"
#define TEMPERATURE_SENSOR "BMP180"


void InitTemperatureSensor();
double GetTemperature();

#endif