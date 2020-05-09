#ifndef _TASKS_H_
#define _TASKS_H_

#include "light.h"
#include "format_data.h"

//Data_t GenericData_t;

//extern GenericData_t data;

void CreateTasks();
void readLightTask( void * parameter );
void sendDataTask(void *parameter);

#endif
