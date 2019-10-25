

#include "timer_conf.h"


//  TIMER , MODE, COMP_PIN, CHANNAL,  COMP_REG,  TOP_VALUE, PRESCALER, INTERRUPT, STATE

TIMER_Conf_t TIMER_Array[NUM_TIMER_STATES] = {

	{TIMER_0 , CTC , Disconnect , NA_T , NA_T , NA_T, No_Clock , Enable, Not_Running},
	{TIMER_1 , CTC , Disconnect , NA_T , NA_T , NA_T, No_Clock , Enable, Not_Running},
	{TIMER_2 , CTC , Disconnect , NA_T , NA_T , NA_T, No_Clock , Enable, Not_Running} };
