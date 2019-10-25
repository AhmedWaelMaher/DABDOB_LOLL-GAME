

#ifndef QUEUE_H_
#define QUEUE_H_

#include "STD_Types.h"
#include "SOS_CNFG.h"
#include "SOS.h"

typedef struct Queue{
    StrTask_t *arr;
    uint8 Size;
    uint8 Front;
    uint8 Rear;
    uint8 Numb_of_elements;

}ST_queueInfo;

extern ST_queueInfo ST_ArrayOfReadyTasks [MAX_PRIORITY_LEVEL];
extern StrTask_t QueueOfTasks [MAX_PRIORITY_LEVEL][MAX_TASKS_NUMB];

void createQueues(void);
void enqueue(uint8 QueueIndex, StrTask_t TaskStr);
void dequeue(uint8 QueueIndex, StrTask_t *PtrToTaskStr);


#endif // QUEUE_H_
