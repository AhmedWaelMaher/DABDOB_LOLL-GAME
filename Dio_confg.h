/******************************************************************************
 *
 * Module: DIO
 *
 * File Name: Dio_confg.h
 *
 * Description: Dio configuration header file
 *
 * Author: Ahmed Wael
 *
 *******************************************************************************/

#ifndef DIO_CONF_H_
#define DIO_CONF_H_

#include "STD_Types.h"

typedef enum {KEYPAD_1,KEYPAD_2,KEYPAD_3,KEYPAD_4,KEYPAD_5,KEYPAD_6,KEYPAD_7,KEYPAD_8,LCD_D4,LCD_D5,LCD_D6,LCD_D7,LCD_EN,RS,RW,BUZZER,LED_1,LED_2,LED_3,LED_4,NUM_PINS }PINS_t ;

#define PORT_A		0
#define PORT_B		1
#define PORT_C		2
#define PORT_D		3

#define KEYPAD		PORT_C
#define BUZZER 		PORT_B
#define LED			PORT_B

#define PIN0		0
#define PIN1		1
#define PIN2		2
#define PIN3		3
#define PIN4		4
#define PIN5		5
#define PIN6		6
#define PIN7		7

#define OUTPUT		1
#define INPUT		0

#ifndef HIGH
#define HIGH		1
#endif
#ifndef LOW
#define LOW			0
#endif

#define PULLUP		1
#define EXTRES		0

#define INITIALIZED			1
#define NOT_INITIALIZED		0

#define NA			0xff


typedef struct {

	uint8 PORT;
	uint8 PIN;
	uint8 Dir;
	uint8 Val;
	uint8 Res;
	uint8 IS_Init;

}DIO_Conf_t;


extern DIO_Conf_t DIO_Array[NUM_PINS];


#endif  DIO_CONF_H_

