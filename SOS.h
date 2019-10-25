
#ifndef SOS_H_
#define SOS_H_

#include "SOS_CNFG.h"
#include "STD_Types.h"

typedef void(*PtrVfunctionV)(void);


typedef enum { SOS_MaxNumbOfTasksReached , SOS_OK , SOS_NULLPtr, SOS_InCorrectInput} EnumSOSError_t;
typedef enum { TaskDeleted , TaskActive  } EnumTaskState_t;
	
typedef struct {
	
	PtrVfunctionV PtrTask;
	uint8 Priority;
	uint16 Periodicity;
	uint8 TaskState;

} StrTask_t;


EnumSOSError_t SOS_Init(void);
EnumSOSError_t SOS_CreateTask (StrTask_t *PtrStrTask);
void SOS_Scheduler(void);
EnumSOSError_t SOS_DeleteTask( PtrVfunctionV PtrTaskFunction );


#endif