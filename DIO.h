/******************************************************************************
 *
 * Module: DIO
 *
 * File Name: Dio.h
 *
 * Description: Dio header file
 *
 * Author: Ahmed Wael
 *
 *******************************************************************************/

#ifndef DIO_H_
#define DIO_H_

#include "Dio_confg.h"

typedef enum{
	N_OK,O_K
}STD_Fun;

#define MAX_NUM_PINS (uint8 )32

extern STD_Fun DIO_Init(void);
extern STD_Fun DIO_Write(PINS_t pin , uint8 value);
extern STD_Fun DIO_Read( PINS_t pin ,uint8 *PVal);


#endif /* DIO_H_ */
