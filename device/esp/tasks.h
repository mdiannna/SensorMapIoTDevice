#ifndef _TASKS_H_
#define _TASKS_H_

#include "light.h"

typedef struct Data_t
{
    // uint32_t ucData;
    // char id;
    double light;
    double temperature;
    double humidity;
    double dust;
    double gas;
} GenericData_t;

extern GenericData_t data;

void CreateTasks();
void readLightTask( void * parameter );
void sendDataTask(void *parameter);

#endif
