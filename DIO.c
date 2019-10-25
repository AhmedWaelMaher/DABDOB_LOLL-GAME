/******************************************************************************
 *
 * Module: DIO
 *
 * File Name: Dio.c
 *
 * Description: Dio source file
 *
 * Author: Ahmed Wael
 *
 *******************************************************************************/

#include "Dio.h"

STD_Fun DIO_Init(void) {

	STD_Fun RetVal = O_K;
	uint8 LoopIndex;

	if (NUM_PINS <= MAX_NUM_PINS) {

		for (LoopIndex = 0; LoopIndex < NUM_PINS; LoopIndex++) {
			DIO_Array[LoopIndex].IS_Init = INITIALIZED;

			switch (DIO_Array[LoopIndex].PORT) {

			case PORT_A:

				if (DIO_Array[LoopIndex].Dir == OUTPUT) {
					DDRA |= (1u << DIO_Array[LoopIndex].PIN);
					if (DIO_Array[LoopIndex].Val == HIGH) {
						PORTA |= (1u << DIO_Array[LoopIndex].PIN);
					} else if (DIO_Array[LoopIndex].Val == LOW) {
						PORTA &= ~(1u << DIO_Array[LoopIndex].PIN);
					} else {
						DIO_Array[LoopIndex].IS_Init = NOT_INITIALIZED;
						RetVal = N_OK;
					}
				} else if (DIO_Array[LoopIndex].Dir == INPUT) {
					DDRA &= ~(1u << DIO_Array[LoopIndex].PIN);
					if (DIO_Array[LoopIndex].Res == PULLUP) {
						PORTA |= (1u << DIO_Array[LoopIndex].PIN);
					} else if (DIO_Array[LoopIndex].Res == EXTRES) {
						PORTA &= ~(1u << DIO_Array[LoopIndex].PIN);
					} else {
						DIO_Array[LoopIndex].IS_Init = NOT_INITIALIZED;
						RetVal = N_OK;
					}
				} else {
					DIO_Array[LoopIndex].IS_Init = NOT_INITIALIZED;
					RetVal = N_OK;
				}

				break;
			case PORT_B:

				if (DIO_Array[LoopIndex].Dir == OUTPUT) {
					DDRB |= (1u << DIO_Array[LoopIndex].PIN);
					if (DIO_Array[LoopIndex].Val == HIGH) {
						PORTB |= (1u << DIO_Array[LoopIndex].PIN);
					} else if (DIO_Array[LoopIndex].Val == LOW) {
						PORTB &= ~(1u << DIO_Array[LoopIndex].PIN);
					} else {
						DIO_Array[LoopIndex].IS_Init = NOT_INITIALIZED;
						RetVal = N_OK;
					}
				} else if (DIO_Array[LoopIndex].Dir == INPUT) {
					DDRB &= ~(1u << DIO_Array[LoopIndex].PIN);
					if (DIO_Array[LoopIndex].Res == PULLUP) {
						PORTB |= (1u << DIO_Array[LoopIndex].PIN);
					} else if (DIO_Array[LoopIndex].Res == EXTRES) {
						PORTB &= ~(1u << DIO_Array[LoopIndex].PIN);
					} else {
						DIO_Array[LoopIndex].IS_Init = NOT_INITIALIZED;
						RetVal = N_OK;
					}
				} else {
					DIO_Array[LoopIndex].IS_Init = NOT_INITIALIZED;
					RetVal = N_OK;
				}
				break;
			case PORT_C:

				if (DIO_Array[LoopIndex].Dir == OUTPUT) {
					DDRC |= (1u << DIO_Array[LoopIndex].PIN);
					if (DIO_Array[LoopIndex].Val == HIGH) {
						PORTC |= (1u << DIO_Array[LoopIndex].PIN);
					} else if (DIO_Array[LoopIndex].Val == LOW) {
						PORTC &= ~(1u << DIO_Array[LoopIndex].PIN);
					} else {
						DIO_Array[LoopIndex].IS_Init = NOT_INITIALIZED;
						RetVal = N_OK;
					}
				} else if (DIO_Array[LoopIndex].Dir == INPUT) {
					DDRC &= ~(1u << DIO_Array[LoopIndex].PIN);
					if (DIO_Array[LoopIndex].Res == PULLUP) {
						PORTC |= (1u << DIO_Array[LoopIndex].PIN);
					} else if (DIO_Array[LoopIndex].Res == EXTRES) {
						PORTC &= ~(1u << DIO_Array[LoopIndex].PIN);
					} else {
						DIO_Array[LoopIndex].IS_Init = NOT_INITIALIZED;
						RetVal = N_OK;
					}
				} else {
					DIO_Array[LoopIndex].IS_Init = NOT_INITIALIZED;
					RetVal = N_OK;
				}
				break;
			case PORT_D:

				if (DIO_Array[LoopIndex].Dir == OUTPUT) {
					DDRD |= (1u << DIO_Array[LoopIndex].PIN);
					if (DIO_Array[LoopIndex].Val == HIGH) {
						PORTD |= (1u << DIO_Array[LoopIndex].PIN);
					} else if (DIO_Array[LoopIndex].Val == LOW) {
						PORTD &= ~(1u << DIO_Array[LoopIndex].PIN);
					} else {
						DIO_Array[LoopIndex].IS_Init = NOT_INITIALIZED;
						RetVal = N_OK;
					}
				} else if (DIO_Array[LoopIndex].Dir == INPUT) {
					DDRD &= ~(1u << DIO_Array[LoopIndex].PIN);
					if (DIO_Array[LoopIndex].Res == PULLUP) {
						PORTD |= (1u << DIO_Array[LoopIndex].PIN);
					} else if (DIO_Array[LoopIndex].Res == EXTRES) {
						PORTD &= ~(1u << DIO_Array[LoopIndex].PIN);
					} else {
						DIO_Array[LoopIndex].IS_Init = NOT_INITIALIZED;
						RetVal = N_OK;
					}
				} else {
					DIO_Array[LoopIndex].IS_Init = NOT_INITIALIZED;
					RetVal = N_OK;
				}
				break;
			default:
				DIO_Array[LoopIndex].IS_Init = NOT_INITIALIZED;
				RetVal = N_OK;
				break;
			}
		}
	} else {
		for (LoopIndex = 0; LoopIndex < NUM_PINS; LoopIndex++) {
			DIO_Array[LoopIndex].IS_Init = NOT_INITIALIZED;
		}

		RetVal = N_OK;
	}
	return RetVal;
}


STD_Fun DIO_Write(PINS_t pin , uint8 value)
{
	STD_Fun state_val = O_K;
	if (pin <= NUM_PINS - 1)
	{
		if (DIO_Array[pin].IS_Init == INITIALIZED && DIO_Array[pin].Dir == OUTPUT)
		{
			switch(DIO_Array[pin].PORT)
			{
			case PORT_A:
				if (value == HIGH)
				{
					PORTA |=(1u<<DIO_Array[pin].PIN);
				}
				else
				{
					PORTA &=~(1u<<DIO_Array[pin].PIN);
				}
				break;
			case PORT_B:
				if (value == HIGH)
				{
					PORTB |=(1u<<DIO_Array[pin].PIN);
				}
				else
				{
					PORTB &=~(1u<<DIO_Array[pin].PIN);
				}
				break;
			case PORT_C:
				if (value == HIGH)
				{
					PORTC |=(1u<<DIO_Array[pin].PIN);
				}
				else
				{
					PORTC &=~(1u<<DIO_Array[pin].PIN);
				}
				break;
			case PORT_D:
				if (value == HIGH)
				{
					PORTD |=(1u<<DIO_Array[pin].PIN);
				}
				else
				{
					PORTD &=~(1u<<DIO_Array[pin].PIN);
				}
				break;
			}
		}
		else
		{
			state_val = N_OK;
		}
	}
	else
	{
		state_val = N_OK;
	}
	return state_val;
}



STD_Fun DIO_Read( PINS_t pin ,uint8 *PVal)
{
	STD_Fun stat_val = O_K;
	if (pin <= NUM_PINS - 1)
	{
		if (DIO_Array[pin].IS_Init == INITIALIZED && DIO_Array[pin].Dir == INPUT)
		{
			switch(DIO_Array[pin].PORT)
			{
			case PORT_A:
				*PVal = ((PINA >> DIO_Array[pin].PIN) & 1u);
				break;
			case PORT_B:
				*PVal = ((PINB >> DIO_Array[pin].PIN) & 1u);
				break;
			case PORT_C:
				*PVal = ((PINC >> DIO_Array[pin].PIN) & 1u);
				break;
			case PORT_D:
				*PVal = ((PIND >> DIO_Array[pin].PIN) & 1u);
				break;
			}
		}
		else
		{
			stat_val = N_OK;
		}
	}
	else
	{
		stat_val = N_OK;
	}

	return stat_val;
}
