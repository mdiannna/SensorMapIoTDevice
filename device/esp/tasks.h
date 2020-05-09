#ifndef _TASKS_H_
#define _TASKS_H_

extern double lightLevel;

typedef struct Data_t
{
    // uint32_t ucData;
    // char id;
    double light;
    double temperature;
} GenericData_t;

extern GenericData_t data;

void CreateTasks();
void readLightTask( void * parameter );
void sendDataTask(void *parameter);

#endif
