
#include "SOS.h"
#include "timer.h"
#include "Queue.h"
#include <avr/sleep.h>

// array of pointers which points to certain number of queues based on their priority
ST_queueInfo ST_ArrayOfReadyTasks [MAX_PRIORITY_LEVEL];

// 2-D array as a queue for each priority level which includes the tasks that have the same priority.
StrTask_t QueueOfTasks [MAX_PRIORITY_LEVEL][MAX_TASKS_NUMB];

// An array to store the blocked (waiting) tasks.
StrTask_t WaitingList[MAX_TASKS_NUMB];

// number of system ticks which increments every ISR
static volatile uint16 Systick = 1;




// call back function to count system ticks
static void TimerSysticCallback(void)
{
	Systick++;
	if (Systick == 65000u)
	{
		Systick = 1;
	}
}

// function to initialize the os
EnumSOSError_t SOS_Init(void)
{
	EnumSOSError_t StateVal = SOS_OK;
	// initiate array of queues based on the number of priorities.
	createQueues();
	// set up the timer to create a system tick at certain resolution
	Timer_CreateTick(OS_TIMER , SYSTEM_TICK_MS);
	switch(OS_TIMER)
	{
		case TIMER_0:
			TIMER0_SetCM( TimerSysticCallback );
		break;
		case TIMER_1:
			TIMER1_SetCM( TimerSysticCallback );
		break;
		case TIMER_2:
			TIMER2_SetCM( TimerSysticCallback );
		break;
		default:
			StateVal = SOS_InCorrectInput;
		break;
	}
	
	TIMER_Init(OS_TIMER);
	return StateVal;
}

// function to create task which takes pointer to the task.
EnumSOSError_t SOS_CreateTask (StrTask_t *PtrStrTask)
{
	EnumSOSError_t StateVal = SOS_OK;
	static uint8 LocalIterator = 0;
	
	// check if i passed the max predefined number of tasks.
	if (LocalIterator == MAX_TASKS_NUMB)
	{
		// loop to check if there is a deleted task and over write on it.
		for (uint8 LocalLoop = 0 ; LocalLoop < MAX_TASKS_NUMB ; LocalLoop++)
		{
			if (WaitingList[LocalLoop].TaskState == TaskDeleted)
			{
				WaitingList[LocalLoop] = *(PtrStrTask);
				WaitingList[LocalLoop].TaskState = TaskActive;
				LocalLoop = MAX_TASKS_NUMB;
				StateVal = SOS_OK;
			}
			else
			{
				// no place available. 
				StateVal = SOS_MaxNumbOfTasksReached;
			}
		}
		
	}
	else
	{
		// add the function into waitinglist buffer.
		WaitingList[LocalIterator] = *(PtrStrTask);
		WaitingList[LocalIterator].TaskState = TaskActive;
		LocalIterator++;
	}
	return StateVal;	
}


// function to run the scheduler
void SOS_Scheduler(void)
{
	uint8 LocalIterator = 0;
	StrTask_t CurrentTask;
	
	while(1)
	{
			// check on the tasks to make sure its time to run
			for (LocalIterator = 0; LocalIterator < MAX_TASKS_NUMB ; LocalIterator++ )
			{
				if (  (WaitingList[LocalIterator].TaskState == TaskActive) && (Systick % WaitingList[LocalIterator].Periodicity) == 0 )
				{
					// enqueue the tasks into a certain buffer based on its priority
					enqueue(WaitingList[LocalIterator].Priority , WaitingList[LocalIterator]);
				}
			}
			// loop to execute the functions ready in the priority buffers.
			for (LocalIterator = 0 ; LocalIterator < MAX_PRIORITY_LEVEL ; LocalIterator++)
			{
				
				if (ST_ArrayOfReadyTasks[LocalIterator].Numb_of_elements > 0)
				{
					dequeue(LocalIterator , &CurrentTask);
					CurrentTask.PtrTask();
					LocalIterator = MAX_PRIORITY_LEVEL;
				}
				
			}
		sleep_mode();
	}
}

// function to delete a certain task
EnumSOSError_t SOS_DeleteTask( PtrVfunctionV PtrTaskFunction )
{
	EnumSOSError_t StateVal = SOS_OK;
	uint8 LocalIterator = 0;
	// check if the pointer is not a null pointer
	if (PtrTaskFunction != NULL)
	{
		// loop to get the function index in the waitinglist buffer
		for (LocalIterator = 0 ; LocalIterator < MAX_TASKS_NUMB ; LocalIterator++)
		{
			if (WaitingList[LocalIterator].PtrTask == PtrTaskFunction)
			{
				WaitingList[LocalIterator].TaskState = TaskDeleted;
				LocalIterator = MAX_TASKS_NUMB;
			}
		}
	}
	else
	{
		StateVal = SOS_NULLPtr;
	}
	
	return StateVal;	
}



