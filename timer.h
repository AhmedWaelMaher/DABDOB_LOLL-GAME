#ifndef TIMER_H_
#define TIMER_H_

#include "STD_Types.h"
#include "avr_reg.h"
#include "timer_conf.h"


//#define TIMER_0         0
//#define TIMER_1         1
//#define TIMER_2         2

#define Normal                  0
#define CTC                     1


#define Disconnect      0
#define Toggle          1
#define Set             2
#define Clear           3
#define Inverted        4
#define Non_Inverted    5

#define No_Clock        0
#define No_Prescaler    1
#define CLK_8           2
#define CLK_32			6
#define CLK_64          3
#define CLK_256         4
#define CLK_1024        5

#define Disable         0
#define Enable          1

#define Channel_A       1
#define Channel_B       0

#define NA_T            0


/* TCCR0 */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

/* TCCR1A */
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

/* TCCR2 */
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0

/* TCCR1B */
#define ICNC1   7
#define ICES1   6
/* bit 5 reserved */
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0


/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

/* TIFR */
#define OCF2    7
#define TOV2    6
#define ICF1    5
#define OCF1A   4
#define OCF1B   3
#define TOV1    2
#define OCF0    1
#define TOV0    0


#define OC0		3
#define OC2     7
#define OC1A    5
#define OC1B    4


#define Not_Running     0
#define Running         1

#define NULL		( (void*) 0)





#define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
    void vector (void)

#define SIGNAL(vector)					\
    void vector (void) __attribute__ ((signal, __INTR_ATTRS));		\
    void vector (void)

#define _VECTOR(N) __vector_ ## N


#define TIMER0_OV		_VECTOR(11)
#define	TIMER0_COMP		_VECTOR(10)
#define TIMER2_COMP		_VECTOR(4)
#define TIMER2_OV		_VECTOR(5)
#define TIMER1_OV		_VECTOR(9)
#define TIMER1_COMPB	_VECTOR(8)
#define TIMER1_COMPA	_VECTOR(7)



STD_Fun_t TIMER_Init (uint8 TimerSpecs);
STD_Fun_t TIMER_Start (uint8 TimerName, uint8 Prescaler_Conf);
STD_Fun_t TIMER_Stop (uint8 TimerName);
STD_Fun_t Timer_CreateTick(uint8 TimerID , uint16 resolution_ms);

void TIMER0_SetOV(void (*Ptr_ISR) (void));
void TIMER0_SetCM(void (*Ptr_ISR) (void));

void TIMER2_SetOV(void (*Ptr_ISR) (void));
void TIMER2_SetCM(void (*Ptr_ISR) (void));

void TIMER1_SetOV(void (*Ptr_ISR) (void));
void TIMER1_SetCM(void (*Ptr_ISR) (void));


#endif /* TIMER_H_*/
