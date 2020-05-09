

#ifndef OS_H_
#define OS_H_

#include <stdint.h>
//#include "mcal_config.h"


#ifndef MAX_NR_OF_TASKS
#define MAX_NR_OF_TASKS 20
#endif

#ifndef TIME_FINISHED
#define TIME_FINISHED 0
#endif



///****************************************************************************
//	** Operating system execution control
//	*/
//
//	/* Type and constant definitions */
//	typedef U32 AppModeType;
//
//	extern const AppModeType OSDEFAULTAPPMODE;
//
//	/* Constructional Elements */
//
//	/* System Services */
//	AppModeType GetActiveApplicationMode( void );
//	void StartOS( AppModeType Mode );
//	void ShutdownOS( StatusType error );
//
//
//	/* System Services */
//	void ErrorHook( StatusType error );
//	void PreTaskHook( void );
//	void PostTaskHook( void );
//	void StartupHook( void );
//	void ShutdownHook( StatusType error );
//



typedef enum {RESET = 0, SET = !RESET}        FlagStatus, ITStatus;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
typedef enum {ERROR = 0, SUCCESS = !ERROR}    ErrorStatus;

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef unsigned char OS_StatusType;
#define OS_E_OK 0


#define TASKNAME(TaskName)      _##TaskName##_func
#define TASK(TaskName)          OS_StatusType TASKNAME(TaskName)(void)


typedef int64_t timeout_t;

typedef struct OS_TaskDescriptor{
	int32_t recurrence;
	int32_t recurrenceCnt;
	int32_t startupTimeout;
	timeout_t timeout;
	int32_t priorty;
	int32_t (*task) ();
	FunctionalState task_state;
} OS_TaskDescriptor_t;

OS_TaskDescriptor_t OS_TaskDescriptorDefault(void);
int32_t OS_TaskInit( int32_t (*task)(void), OS_TaskDescriptor_t* taskDescriptor );

FunctionalState OS_EvalRecurrence(void);

void OS_TaskSetTimeout( timeout_t time);
timeout_t OS_EvalTimeout( timeout_t * time);
timeout_t OS_TaskEvalTimeout(void);
FunctionalState OS_TaskEvalState(void);

void OS_Scheduler(void);

#endif /* OS_H_ */
