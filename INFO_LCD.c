
#include "INFO_LCD.h"

volatile static uint8 g_CMND_Flag = CMD_FREE;

volatile static uint8 g_Data_Flag = DATA_FREE;

static volatile uint8 g_InitFlag = LCD_UNINTAILIZED ;

Enum_LCDState LCD_sendCommand(uint8 COPY_CMND)
{
	static uint8 LOC_CMNDSTATE = 0;
	Enum_LCDState LOC_CMNDStatus = LCD_Pending;

	switch(LOC_CMNDSTATE)
	{
	case 0:
		DIO_Write(RS , LOW);
		DIO_Write(RW , LOW);

		DIO_Write(LCD_D4 , (COPY_CMND >> 4) &1);
		DIO_Write(LCD_D5 , (COPY_CMND >> 5) &1);
		DIO_Write(LCD_D6 , (COPY_CMND >> 6) &1);
		DIO_Write(LCD_D7 , (COPY_CMND >> 7) &1);

		DIO_Write( LCD_EN , HIGH);
		LOC_CMNDSTATE++;

		break;
	case 1:
		DIO_Write(LCD_EN , LOW);

		DIO_Write(LCD_D4 , (COPY_CMND >> 0) &1);
		DIO_Write(LCD_D5 , (COPY_CMND >> 1) &1);
		DIO_Write(LCD_D6 , (COPY_CMND >> 2) &1);
		DIO_Write(LCD_D7 , (COPY_CMND >> 3) &1);

		DIO_Write( LCD_EN , HIGH);
		LOC_CMNDSTATE++;

		break;
	case 2:
		DIO_Write(LCD_EN , LOW);
		LOC_CMNDSTATE=0;
		LOC_CMNDStatus = LCD_Finished;
		break;
	}

	return LOC_CMNDStatus;
}


Enum_LCDState LCD_DataWr(uint8 COPY_Data)
{
	static uint8 LOC_DataWrState = 0;
	Enum_LCDState LOC_DataWrStatus = LCD_Pending;

	if( LCD_INITALIZED == g_InitFlag )
	{
		switch (LOC_DataWrState)
		{
		case 0:
			DIO_Write(RS , HIGH);
			DIO_Write(RW , LOW);

			DIO_Write(LCD_D4 , (COPY_Data >> 4) &1 );
			DIO_Write(LCD_D5 , (COPY_Data >> 5) &1 );
			DIO_Write(LCD_D6 , (COPY_Data >> 6) &1 );
			DIO_Write(LCD_D7 , (COPY_Data >> 7) &1 );

			DIO_Write( LCD_EN , HIGH);
			LOC_DataWrState++;
			break;
		case 1:
			DIO_Write(LCD_EN , LOW);

			DIO_Write(LCD_D4 , (COPY_Data >> 0) &1);
			DIO_Write(LCD_D5 , (COPY_Data >> 1) &1);
			DIO_Write(LCD_D6 , (COPY_Data >> 2) &1);
			DIO_Write(LCD_D7 , (COPY_Data >> 3) &1);

			DIO_Write( LCD_EN , HIGH);
			LOC_DataWrState++;
			break;
		case 2:
			DIO_Write(LCD_EN , LOW);
			LOC_DataWrState=0;
			LOC_DataWrStatus = LCD_Finished;
			break;
		}
	}
	return LOC_DataWrStatus;
}


Enum_LCDState LCD_DispChar(uint8 COPY_Data)
{
	static uint8 LOC_CurrentTaskAquiringData = 0;
	Enum_LCDState LOC_LCDStatus = LCD_Pending;
	if( (LCD_INITALIZED == g_InitFlag) && (g_CMND_Flag == CMD_FREE) )
	{
		if ( (g_Data_Flag == DATA_FREE) || (LOC_CurrentTaskAquiringData == 1) )
		{
			LOC_LCDStatus = LCD_DataWr(COPY_Data);
			g_Data_Flag = DATA_ACUIRED;
			LOC_CurrentTaskAquiringData = 1;
			if (LOC_LCDStatus == LCD_Finished)
			{
				g_Data_Flag = DATA_FREE;
				LOC_CurrentTaskAquiringData = 0;
				LOC_LCDStatus = LCD_Finished;
			}
		}
	}
	return LOC_LCDStatus;
}

void LCD_init(void)
	static uint8 LOC_InitState=0;
	Enum_LCDState LOC_LCDState = LCD_Pending;
	static uint8 LOC_CurrentTaskAquiringCMD = 0;

	if (LCD_UNINTAILIZED == g_InitFlag)
	{

		switch(LOC_InitState)
		{
		case 0:
			if ( (g_CMND_Flag == CMD_FREE) || (LOC_CurrentTaskAquiringCMD == 1) )
			{
				LOC_LCDState = LCD_sendCommand(LCD_CursorHome);
				g_CMND_Flag = CMD_ACUIRED;
				LOC_CurrentTaskAquiringCMD = 1;
				if (LOC_LCDState == LCD_Finished)
				{
					LOC_InitState++;
					g_CMND_Flag = CMD_FREE;
					LOC_CurrentTaskAquiringCMD = 0;
				}
			}

			break;
		case 1:
			if ( (g_CMND_Flag == CMD_FREE) || (LOC_CurrentTaskAquiringCMD == 1) )
			{
				LOC_LCDState = LCD_sendCommand(LCD_Set4Bit2Lin);
				g_CMND_Flag = CMD_ACUIRED;
				LOC_CurrentTaskAquiringCMD = 1;
				if (LOC_LCDState == LCD_Finished)
				{
					LOC_InitState++;
					g_CMND_Flag = CMD_FREE;
					LOC_CurrentTaskAquiringCMD = 0;
				}
			}


			break;
		case 2:
			if ( (g_CMND_Flag == CMD_FREE) || (LOC_CurrentTaskAquiringCMD == 1) )
			{
				LOC_LCDState = LCD_sendCommand(LCD_DisOnCurOnBliOff);
				g_CMND_Flag = CMD_ACUIRED;
				LOC_CurrentTaskAquiringCMD = 1;
				if (LOC_LCDState == LCD_Finished)
				{
					LOC_InitState++;
					g_CMND_Flag = CMD_FREE;
					LOC_CurrentTaskAquiringCMD = 0;
				}
			}

			break;
		case 3:
			if ( (g_CMND_Flag == CMD_FREE) || (LOC_CurrentTaskAquiringCMD == 1) )
			{
				LOC_LCDState = LCD_sendCommand(LCD_IncOnShiOff);
				g_CMND_Flag = CMD_ACUIRED;
				LOC_CurrentTaskAquiringCMD = 1;
				if (LOC_LCDState == LCD_Finished)
				{
					LOC_InitState++;
					g_CMND_Flag = CMD_FREE;
					LOC_CurrentTaskAquiringCMD = 0;
				}
			}
			break;
		case 4:
			if ( (g_CMND_Flag == CMD_FREE) || (LOC_CurrentTaskAquiringCMD == 1) )
			{
				LOC_LCDState = LCD_sendCommand(LCD_ClearScreen);
				g_CMND_Flag = CMD_ACUIRED;
				LOC_CurrentTaskAquiringCMD = 1;
				if (LOC_LCDState == LCD_Finished)
				{
					LOC_InitState++;
					g_CMND_Flag = CMD_FREE;
					LOC_CurrentTaskAquiringCMD = 0;
				}
			}

			break;
		case 5:
			LOC_InitState=0;
			g_InitFlag = LCD_INITALIZED;
			SOS_DeleteTask(LCD_init);
			break;

		}
	{
		if ( (DATA_FREE == g_Data_Flag) || (1 == LOC_CurrentTaskAquiringCMND) )
		{
			LCD_Status = LCD_DataWr(COPY_ptrString[LOC_LocalIterator]);
			g_Data_Flag = DATA_ACUIRED;
			LOC_CurrentTaskAquiringCMND = 1;
			if ( LCD_Finished == LCD_Status )
			{
				LOC_LocalIterator++;
				LCD_Status = LCD_Pending;
				if (COPY_ptrString[LOC_LocalIterator] == 0)
				{
					g_Data_Flag = DATA_FREE;
					LOC_CurrentTaskAquiringCMND = 0;
					LCD_State = 0;
					LCD_Status = LCD_Finished;
				}
			}
		}
		{
			if ( (CMD_FREE == g_CMND_Flag) || (1 == LOC_CurrentTaskAquiringCMND) )
			{
				LCD_Status = LCD_gotoRowColumn(COPY_Row,COPY_Column);
				g_CMND_Flag = CMD_ACUIRED;
				LOC_CurrentTaskAquiringCMND = 1;
				if ( LCD_Finished == LCD_Status)
				{
					g_CMND_Flag = CMD_FREE;
					LOC_CurrentTaskAquiringCMND = 0;
					LCD_State = 1;
					LCD_Status = LCD_Pending;
				}
			}
		}

		{
			if ( (DATA_FREE == g_Data_Flag) || (1 == LOC_CurrentTaskAquiringCMND) )
			{
				LCD_Status = LCD_DataWr(COPY_ptrString[LOC_LocalIterator]);
				g_Data_Flag = DATA_ACUIRED;
				LOC_CurrentTaskAquiringCMND = 1;
				if ( LCD_Finished == LCD_Status )
				{
					LOC_LocalIterator++;
					LCD_Status = LCD_Pending;
					if (COPY_ptrString[LOC_LocalIterator] == 0)
					{
						g_Data_Flag = DATA_FREE;
						LOC_CurrentTaskAquiringCMND = 0;
						LCD_State = 0;
						LCD_Status = LCD_Finished;
						LOC_LocalIterator =0;
					}
				}
			}
		}
	{
		if ( (CMD_FREE == g_CMND_Flag) || ( 1 == LOC_CurrentTaskAquiringCMND ))
		{
			LOC_LCDStatus =  LCD_sendCommand((0x80)|(COPY_u8Column+(0x40*COPY_u8Row)));
			g_CMND_Flag = CMD_ACUIRED;
			LOC_CurrentTaskAquiringCMND = 1;

			if ( LCD_Finished == LOC_LCDStatus)
			{
				g_CMND_Flag = CMD_FREE;
				LOC_CurrentTaskAquiringCMND = 0;
				LOC_LCDStatus = LCD_Finished;

			}
		}
	}


Enum_LCDState LCD_Clear(void)
{
	uint8 LOC_CurrentTaskAquiringCMD=1;
	Enum_LCDState LOC_LCDState=LCD_Pending;
	if ( ((g_Data_Flag==DATA_FREE && g_CMND_Flag == CMD_FREE) )|| (LOC_CurrentTaskAquiringCMD == 1) )
				{
					LOC_LCDState = LCD_sendCommand(LCD_ClearScreen);
					g_CMND_Flag = CMD_ACUIRED;
					LOC_CurrentTaskAquiringCMD = 1;
					if (LOC_LCDState == LCD_Finished)
					{
						g_CMND_Flag = CMD_FREE;
						LOC_CurrentTaskAquiringCMD = 0;
					}
				}
	return LOC_LCDState;
}
//{
	//LCD_gotoRowColumn(COPY_u8Row,COPY_u8Column);
	//if (0<=COPY_u16num)
		//{
		//if (COPY_u16num<=9) LCD_DataWr(COPY_u16num+0x30);
//else if(COPY_u16num<=99)
//{
//LCD_DataWr((COPY_u16num/10)+0x30);
//LCD_DataWr((COPY_u16num%10)+0x30);
//}
//else if(COPY_u16num<=999)
//{
//LCD_DataWr((COPY_u16num/100)+0x30);
//LCD_DataWr(((COPY_u16num/10)%10)+0x30);
//LCD_DataWr((COPY_u16num%10)+0x30);
//}
//else if (COPY_u16num<=9999)
//{
//LCD_DataWr((COPY_u16num/1000)+0x30);
//LCD_DataWr(((COPY_u16num/100)%10)+0x30);
//LCD_DataWr(((COPY_u16num/10)%10)+0x30);
//LCD_DataWr((COPY_u16num%10)+0x30);
//}
//else if (COPY_u16num<=99999)
//{
//LCD_DataWr((COPY_u16num/10000)+0x30);
//LCD_DataWr(((COPY_u16num/1000)%10)+0x30);
//LCD_DataWr(((COPY_u16num/100)%10)+0x30);
//LCD_DataWr(((COPY_u16num/10)%10)+0x30);
//LCD_DataWr((COPY_u16num%10)+0x30);
//}
//}
//
//if (0>COPY_u16num)
//{
//COPY_u16num = -1*COPY_u16num;
//
//if (COPY_u16num<=9)
//{
//LCD_DataWr(0x2d);
//LCD_DataWr(COPY_u16num+0x30);
//}
//else if(COPY_u16num<=99)
//{
//LCD_DataWr(0x2d);
//LCD_DataWr((COPY_u16num/10)+0x30);
//LCD_DataWr((COPY_u16num%10)+0x30);
//}
//else if(COPY_u16num<=999)
//{
//LCD_DataWr(0x2d);
//LCD_DataWr((COPY_u16num/100)+0x30);
//LCD_DataWr(((COPY_u16num/10)%10)+0x30);
//LCD_DataWr((COPY_u16num%10)+0x30);
//}
//
//}
//
//}
//
//