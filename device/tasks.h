
#ifndef TASKS_H_
#define TASKS_H_

#include <Arduino.h>

#define NR_TASKS 5

 
extern double temperature;
extern double humidity;
extern double dust;
extern double light;
extern double gas;

int TaskGetTemperature();
int TaskGetHumidity();
int TaskGetDustValue();
int TaskGetLightValue();
int TaskGetGasValue();


#endif
