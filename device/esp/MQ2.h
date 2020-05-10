#ifndef _MQ2_H_
#define _MQ2_H_

#include <Arduino.h>

#define GAS_SENSOR_PIN A0

void InitGasSensor();
double GetGasSensorValue();

#endif
