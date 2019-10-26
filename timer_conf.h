#ifndef TIMER_CONF_H_
#define TIMER_CONF_H_

#include "STD_Types.h"
#include "timer.h"

typedef enum { TIMER_0, TIMER_1, TIMER_2, NUM_TIMER_STATES} TIMER_t;


typedef struct {
	uint8 TIMER;
	uint8 MODE;
	uint8 COMP_PIN;
	uint8 CHANNAL;
	uint16 COMP_REG;
	uint16 TOP_VALUE;
	uint8 PRESCALER;
	uint8 INTERRUPT;
	uint8 STATE;

} TIMER_Conf_t;



extern TIMER_Conf_t TIMER_Array[NUM_TIMER_STATES];



#endif /* TIMER_CONF_H_ */
