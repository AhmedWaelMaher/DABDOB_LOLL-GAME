/******************************************************************************
 *
 * Module: Keypad
 *
 * File Name: keypad.c
 *
 * Description: source file of Keypad static code
 *
 * Author: Ahmed Wael
 *
 *******************************************************************************/

#include "Keypad.h"
#include "SOS.h"

/*static uint8 KEYPAD_Button(uint8);*/
static uint8 INIT_flag =NOT_READY;


Enum_KEYPADState KEYPAD_Init(void)
{
	Enum_KEYPADState status = PENDING;
	if(NOT_READY == INIT_flag)
		DIO_Init();
#if((3 == N_ROW) && (3 == N_COL))
	{
		DIO_Write(PIN4, HIGH);
		DIO_Write(PIN5, HIGH);
		DIO_Write(PIN6, HIGH);
		DIO_Write(PIN7, HIGH);
		DIO_Write(PIN2, HIGH);
		DIO_Write(PIN3, HIGH);
		INIT_flag =READY;
		status = FINISHED;
	}
#elif((4 == N_ROW) && (4 == N_COL) )
	{
		KEYPAD_PORT_DDR = 0x0F ;              // high significant nibble is input which is indicating to columns and Least significant nibble is output which is indicating to Rows
		KEYPAD_PORT_OUT= 0xFF;	              // Write ones to the all pins in the port to activate pull-up resistors in the input nibble
	}
}
#endif
SOS_DeleteTask(KEYPAD_Init);
return status;

}

Enum_KEYPADState KEYPAD_getPressedKey(uint8 *key)
{
	Enum_KEYPADState state = PENDING;
	if(READY == INIT_flag){
		uint8 row,col;
		uint8 val =0;
#if((N_ROW == 3) && (N_COL == 3))
		{
			for(row=0;row<N_ROW;row++)  // rows for the output pins ( LSB of the port)
			{
				switch(row){
				case 0 :
					DIO_Write(PIN0, HIGH);
					DIO_Write(PIN2, LOW);
					DIO_Write(PIN1, HIGH);
					DIO_Write(PIN3, HIGH);
					DIO_Write(PIN4, HIGH);
					DIO_Write(PIN5, HIGH);
					DIO_Write(PIN6, HIGH);
					DIO_Write(PIN7, HIGH);
					break;
				case 1 :
					DIO_Write(PIN0, HIGH);
					DIO_Write(PIN2, HIGH);
					DIO_Write(PIN1, HIGH);
					DIO_Write(PIN3, LOW);
					DIO_Write(PIN4, HIGH);
					DIO_Write(PIN5, HIGH);
					DIO_Write(PIN6, HIGH);
					DIO_Write(PIN7, HIGH);
					break;
				case 2 :
					DIO_Write(PIN0, HIGH);
					DIO_Write(PIN2, HIGH);
					DIO_Write(PIN1, HIGH);
					DIO_Write(PIN3, HIGH);
					DIO_Write(PIN4, LOW);
					DIO_Write(PIN5, HIGH);
					DIO_Write(PIN6, HIGH);
					DIO_Write(PIN7, HIGH);
					break;
				}
				for(col=0;col<N_COL;col++) // this loop reads the status of each column in that row.
				{
					switch(col){
					case 0 :
						DIO_Read(PIN5, &val);
						if(!(val)){
							*key = (row*N_COL)+col+1;
							state = FINISHED;
						}
						break;
					case 1 :
						DIO_Read(PIN6, &val);
						if(!(val)){
							*key = (row*N_COL)+col+1;
							state = FINISHED;
						}
						break;
					case 2 :
						DIO_Read(PIN7, &val);
						if(!(val)){
							*key = (row*N_COL)+col+1;
							state = FINISHED;
						}
						break;
					}
				}
			}
		}
	}
#elif((N_ROW == 4) && (N_COL == 4) )
	{
		_delay_ms(200);
		while(1)
		{
			for(row=0;row<N_ROW;row++)  // rows for the output pins ( LSB of the port)
			{
				KEYPAD_PORT_OUT = (~(0b00000001<<row));			//clear this row pin and set all pins
				for(col=0;col<N_COL;col++) // this loop reads the status of each column in that row.
				{
					if ( ! ( KEYPAD_PIN_IN & (0b00010000<<col) ) )		//Column Detected means that there is a single 0 in that row.
					{
						key = KEYPAD_Button ((row*N_COL)+col+1) ;
						Number = Number*10;
						j++;
						return  (key);

					}
				}
			}

		}
	}

}
#endif
return state;

}

/*
uint8 KEYPAD_Button(uint8 button_number)
{
#if(PRINT_NUMBERS_From_KEYPAD)
	{
		switch(button_number)
		{
		case 1: return 7 ; break;		 // position of (1) is located at top left of the keypad which is corresponding to button no. 7
		case 2: return 2 ; break;
		case 3: return 3 ; break;
		case 4: return 1 ; break;
		case 5: return 5 ; break;
		case 6: return 6 ; break;
		case 7: return 4 ; break;
		case 8: return 8 ; break;
		case 9: return 9 ; break;
		case 10: return -1 ; break;
		case 11: return -1 ; break;
		case 12: return -1 ; break;
		case 13: return -1 ; break;
		case 14: return 0 ; break;
		case 15: return -1; break;
		case 16: return -1 ; break;
		default: return button_number;
		}
	}
	// or to print the numbers in terms of ascii value
#elif(! PRINT_NUMBERS_From_KEYPAD )
	{
		switch(button_number)
		{
		case 1: return '1' ; break;			 // position of (1) is located at top left of the keypad which is corresponding to button no. 7
		case 2: return '2' ; break;
		case 3: return '3' ; break;
		case 4: return '4' ; break;
		case 5: return '5' ; break;
		case 6: return '6' ; break;
		case 7: return '7' ; break;
		case 8: return '8' ; break;
		case 9: return  '9' ; break;
		case 10: return 'A' ; break;
		case 11: return 'B' ; break;
		case 12: return 'C' ; break;
		case 13: return 'D' ; break;
		case 14: return '0' ; break;
		case 15: return 'E'; break;
		case 16: return 'F' ; break;
		default: return button_number;
		}
	}

#endif
}
 */

//it's used for Keypad 4x4 like Calculator

/*char KEYPAD_Button (unsigned button_number)
{
#if(PRINT_NUMBERS_From_KEYPAD)
	{
		switch(button_number)
		{
		case 1: return 7 ; break;		 // position of (1) is located at top left of the keypad which is corresponding to button no. 7
		case 2: return 8 ; break;
		case 3: return 9 ; break;
		case 4: return 10 ; break;
		case 5: return 4 ; break;
		case 6: return 5 ; break;
		case 7: return 6 ; break;
		case 8: return 11 ; break;
		case 9: return 1 ; break;
		case 10: return 2 ; break;
		case 11: return 3 ; break;
		case 12: return 12 ; break;
		case 13: return 13 ; break;
		case 14: return 0 ; break;
		case 15: return 14; break;
		case 16: return 15 ; break;
		default: return button_number;
		}
	}

	// or to print the numbers in terms of ascii value

#elif(! PRINT_NUMBERS_From_KEYPAD )
	{

		switch(button_number)
		{
		case 1: return '7' ; break;			 // position of (1) is located at top left of the keypad which is corresponding to button no. 7
		case 2: return '8' ; break;
		case 3: return '9' ; break;
		case 4: return 'A' ; break;
		case 5: return '4' ; break;
		case 6: return '5' ; break;
		case 7: return '6' ; break;
		case 8: return 'B' ; break;
		case 9: return '1' ; break;
		case 10: return '2' ; break;
		case 11: return '3' ; break;
		case 12: return 'C' ; break;
		case 13: return 'D' ; break;
		case 14: return '0' ; break;
		case 15: return 'E'; break;
		case 16: return 'F' ; break;
		default: return button_number;
		}
	}

#endif
}*/


