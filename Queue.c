

#include "Queue.h"


void createQueues()
{
    for(uint8 i = 0 ; i < MAX_PRIORITY_LEVEL ; i++)
    {
        ST_ArrayOfReadyTasks[i].arr = QueueOfTasks[i];
        ST_ArrayOfReadyTasks[i].Size = MAX_TASKS_NUMB;
        ST_ArrayOfReadyTasks[i].Front = 0;
        ST_ArrayOfReadyTasks[i].Rear = 0;
        ST_ArrayOfReadyTasks[i].Numb_of_elements = 0;
    }
}


void enqueue(uint8 QueueIndex, StrTask_t TaskStr)
{
    if(ST_ArrayOfReadyTasks[QueueIndex].Numb_of_elements == ST_ArrayOfReadyTasks[QueueIndex].Size)
    {
        return;
    }
    ST_ArrayOfReadyTasks[QueueIndex].arr[ST_ArrayOfReadyTasks[QueueIndex].Rear] = TaskStr;
    ST_ArrayOfReadyTasks[QueueIndex].Rear = ( ST_ArrayOfReadyTasks[QueueIndex].Rear + 1 ) % ST_ArrayOfReadyTasks[QueueIndex].Size;
    ST_ArrayOfReadyTasks[QueueIndex].Numb_of_elements++;
}

void dequeue(uint8 QueueIndex, StrTask_t *PtrToTaskStr)
{
    if(ST_ArrayOfReadyTasks[QueueIndex].Numb_of_elements == 0)
    {
        return;
    }
   *PtrToTaskStr = ST_ArrayOfReadyTasks[QueueIndex].arr[ST_ArrayOfReadyTasks[QueueIndex].Front];
    ST_ArrayOfReadyTasks[QueueIndex].Front = (ST_ArrayOfReadyTasks[QueueIndex].Front + 1) % ST_ArrayOfReadyTasks[QueueIndex].Size;
    ST_ArrayOfReadyTasks[QueueIndex].Numb_of_elements--;

}


