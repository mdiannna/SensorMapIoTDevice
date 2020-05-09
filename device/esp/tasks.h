#ifndef _TASKS_H_
#define _TASKS_H_

extern double lightLevel;

void CreateTasks();
void readLightTask( void * parameter );
void sendDataTask(void *parameter);

#endif
