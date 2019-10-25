/******************************************************************************
 *
 * Module: Keypad
 *
 * File Name: keypad.h
 *
 * Description: header file of Keypad static code
 *
 * Author: Ahmed Wael
 *
 *******************************************************************************/

#ifndef KEYPAD_HEADER
#define KEYPAD_HEADER

#ifndef F_CPU
#define F_CPU   8000000ul
#endif

#include "Dio.h"

#define READY 1
#define NOT_READY 0

typedef enum{
	PENDING,FINISHED
}Enum_KEYPADState;

// Locate your keypad at which port does it exist
#define KEYPAD_PORT_OUT  PORTC
#define KEYPAD_PORT_DDR  DDRC
#define KEYPAD_PIN_IN   PINC

// Determine your Keypad Dimension
#define N_COL  3
#define N_ROW  3

#define YES	   1
#define NO     0

// Determine whether you need to return Integer Numbers from keypad or Ascii Value (Characters) from KeyPad
#define PRINT_NUMBERS_From_KEYPAD YES


//----------------------- Section of Public Function Prototype of Keypad API's -----------------//
extern void KEYPAD_Init(void);
extern Enum_KEYPADState KEYPAD_getPressedKey(uint8 *key);


#endif /* KEYPAD_HEADER */
