#ifndef _TASKS_H_
#define _TASKS_H_

#include <Arduino.h>
#include "light.h"
#include "format_data.h"
#include "mqtt.h"
#include "MQ2.h"
#include "temperature.h"

void CreateTasks();

//Tasks:
void readLightTask( void * parameter );
void readGasTask( void * parameter );
void sendDataTask(void *parameter);
void readTemperatureTask( void * parameter );

#endif
