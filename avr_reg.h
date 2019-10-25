/*
 * avr_reg.h
 *
 *  Created on: Sep 20, 2019
 *      Author: abdelqader
 */

#ifndef AVR_REG_H_
#define AVR_REG_H_

/* Group A Registers */
#define PORTA  *((volatile uint8*)0x3B)
#define DDRA   *((volatile uint8*)0x3A)
#define PINA   *((volatile uint8*)0x39)

/* Group B Registers */
#define PORTB  *((volatile uint8*)0x38)
#define DDRB   *((volatile uint8*)0x37)
#define PINB   *((volatile uint8*)0x36)

/* Group C Registers */
#define PORTC *((volatile uint8*)0x35)
#define DDRC   *((volatile uint8*)0x34)
#define PINC  *((volatile uint8*)0x33)

/* Group D Registers */
#define PORTD *((volatile uint8*)0x32)
#define DDRD  *((volatile uint8*)0x31)
#define PIND  *((volatile uint8*)0x30)

/* SREG Register */
#define SREG  *((volatile uint8*)0x5F)


/* TIMER 0 AND TIMER 2 */
#define TCCR0	(* (volatile uint8 *) 0x53)
#define TCNT0	(* (volatile uint8 *) 0x52)
#define OCR0	(* (volatile uint8 *) 0x5C)
#define TIMSK	(* (volatile uint8 *) 0x59)
#define TIFR	(* (volatile uint8 *) 0x58)
#define	TCCR2	(* (volatile uint8 *) 0x45)
#define	TCNT2	(* (volatile uint8 *) 0x44)
#define	OCR2	(* (volatile uint8 *) 0x43)
#define	ASSR	(* (volatile uint8 *) 0x42)

/* TIMER 1 */
#define	TCCR1A	(* (volatile uint8 *) 0x4F)
#define	TCCR1B	(* (volatile uint8 *) 0x4E)
#define	TCNT1L	(* (volatile uint8 *) 0x4C)
#define	TCNT1H	(* (volatile uint8 *) 0x4D)
#define	OCR1AH	(* (volatile uint8 *) 0x4B)
#define	OCR1AL	(* (volatile uint8 *) 0x4A)
#define	OCR1BH	(* (volatile uint8 *) 0x49)
#define	OCR1BL	(* (volatile uint8 *) 0x48)
#define	ICR1H	(* (volatile uint8 *) 0x47)
#define	ICR1L	(* (volatile uint8 *) 0x46)



//ADDRESS OF GICR "GLOBAL INTERRUPT CONTROL REGISTER"
#define GICR_ADDRESS 0x5B
#define GICR (*(volatile uint8 *) GICR_ADDRESS)

//ADDRESS OF MCUCR "MCU CONTROL REGISTER"
#define MCUCR_ADDRESS 0x55
#define MCUCR (*(volatile uint8 *) MCUCR_ADDRESS)

//ADDRESS OF MCUCSR "MCU CONTROL SENSE REGISTER"
#define MCUCSR_ADDRESS 0x54
#define MCUCSR (*(volatile uint8 *) MCUCSR_ADDRESS)



#endif /* AVR_REG_H_ */
