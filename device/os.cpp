/*
 * os.c
 *
 *  Created on: 11 ����. 2013 �.
 *      Author: admin
 */

#include "os.h"



OS_TaskDescriptor_t* taskList[MAX_NR_OF_TASKS];

int32_t nrOfTasks   = 0;	//  nr of existing tasks
int32_t currentTask = 0;    //  current executing task number


void OS_Scheduler(void) {

#ifdef WATCHDOG_ENABLE
	WatchdogReloadSet(WATCHDOG0_BASE, 0xFEEFEE);
#endif
	for (currentTask = 0; currentTask < nrOfTasks; currentTask++) {

		// the startup offset is set as a timeout on startup
		// evaluate timeout and recurrence
		// also evaluate if the task is enable
		if (OS_TaskEvalState() == ENABLE && OS_TaskEvalTimeout() == TIME_FINISHED &&
			OS_EvalRecurrence()  == ENABLE)  {

			if (taskList[currentTask]->task)
				(*(taskList[currentTask]->task))();
		}

	}

}


int32_t OS_TaskInit( int32_t (*task)(void),  OS_TaskDescriptor_t* taskDescriptor  ){

	if(nrOfTasks < MAX_NR_OF_TASKS-1){
		taskDescriptor->task = task;
		taskDescriptor->timeout = taskDescriptor->startupTimeout;
		taskList[nrOfTasks++] = taskDescriptor;

	}
	else{
		return -1;
	}

	return nrOfTasks-1;

}

/*
 * A default initialization template for tasks
 */

OS_TaskDescriptor_t OS_TaskDescriptorDefault(void){

	OS_TaskDescriptor_t taskDescriptor;
	taskDescriptor.task           = 0;
	taskDescriptor.recurrence     = 1;
	taskDescriptor.recurrenceCnt  = 0;
	taskDescriptor.timeout        = 0;
	taskDescriptor.startupTimeout = 0;
	taskDescriptor.priorty        = 1;
	taskDescriptor.task_state     = ENABLE;

	return taskDescriptor;
}


/*
 * Evaluate recurrence of the task , to see if
 * we should let it execute in the current sys tick or no
 */
FunctionalState OS_EvalRecurrence(void) {

	FunctionalState result = DISABLE;
	if (taskList[currentTask]->recurrence) {

		if (++taskList[currentTask]->recurrenceCnt >= taskList[currentTask]->recurrence) {
			taskList[currentTask]->recurrenceCnt = 0;
			result = ENABLE;
		}

	}else{
		taskList[currentTask]->recurrenceCnt = 0;
	}
	return result;
}


void OS_TaskSetTimeout( timeout_t time){
	taskList[currentTask]->timeout = time;
}

timeout_t OS_TaskEvalTimeout(void){
	return OS_EvalTimeout(&(taskList[currentTask]->timeout));
}

FunctionalState OS_TaskEvalState(void)
{
	return taskList[currentTask]->task_state;
}

timeout_t OS_EvalTimeout( timeout_t * time){
	if(*time>0)
		(*time)--;
	else
		(*time)=0;
	return *time;
}
