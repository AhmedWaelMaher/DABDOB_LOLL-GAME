/*
 * SOS.c
 *
 * Created: 10/22/2019 2:03:42 PM
 * Author : minam
 */ 

#include "SOS.h"
#include "INFO_LCD.h"
#include "keypad.h"

#define NUMBEROFQUESTIONS 6

typedef enum {
	APP_NO = 2,
	APP_YES = 1,
	APP_SKIP = 3,
}answers_t;
static answers_t answers[NUMBEROFQUESTIONS] = {APP_YES, APP_YES, APP_NO, APP_NO, APP_NO};
static uint8 g_key = 0;
static uint8 question_ptr = 0;
static uint8 score = 0;
typedef enum{
	ON,
	OFF,
	STOP,
}Flag_t;
static Flag_t next_question = ON;
static Flag_t get_answer = OFF;
static Flag_t answer_ready = OFF;


static uint8 questions[NUMBEROFQUESTIONS][17] = {"Do you love me ?","Do you need me ?", "mn 2albak?", "b 2mana?","akid?", "Score: "};


void QuestionDisplayTask(void)
{
	Enum_LCDState LCD_Status = LCD_Pending;
	static uint8 LOC_ClearStatus=0;
	static uint8 Question_Disp = 0;
	if(next_question == ON)
	{

		if(LOC_ClearStatus==0)
		{
			LCD_Status=LCD_Clear();
			if(LCD_Status==LCD_Finished)
			{
				LOC_ClearStatus=1;
			}
		}
		if(LOC_ClearStatus==1)
		{

			if(Question_Disp == 0)
			{
				LCD_Status= LCD_displayStringRowColumn(questions[question_ptr],0,0);
				if(LCD_Status == LCD_Finished)
				{
					Question_Disp = 1;

				}

			}
			if(Question_Disp == 1)
			{
				LCD_Status = LCD_displayStringRowColumn("1.Yes 2.No 3.Skp", 1u, 0u);
				if(LCD_Status == LCD_Finished)
				{
					question_ptr++;
					next_question = OFF;
					get_answer = ON;
					Question_Disp = 0;
					LOC_ClearStatus=0;
					if(question_ptr == 6){
						question_ptr =0;
						get_answer = STOP;
					}
				}

			}
		}
	}

}
void GetAnswerTask(void){

	Enum_KEYPADState state = PENDING;
	if(get_answer == ON)
	{
		state = KEYPAD_getPressedKey(&g_key);
		if(state == FINISHED)
		{
			answer_ready = ON;
			/*next_question = ON;
			get_answer = OFF;*/
		}
	}
}

void AnswerCheckTask(void)
{
	if (answer_ready == ON)
	{
		DDRB |= (1<<6);
		PORTB |= (1<<6);
		answer_ready = OFF;
		get_answer = OFF;
		if (answers[question_ptr-1] == g_key)
		{
			score++;
		}
		next_question = ON;
	}
}

void ScoreDisplay(void){
	static uint8 status = PENDING;
	static uint8 LCD_gotoState = 0;
	if(get_answer == STOP){
		if(LCD_gotoState == 0)
		{
			status = LCD_gotoRowColumn(0, 7);
			if(status == LCD_Finished)
			{
				LCD_gotoState = 1;
			}
		}
		else if(LCD_gotoState == 1)
		{
			//Score
/*			PORTB ^= (1<<4);*/
			status =LCD_DispChar(score +48);
			if(status == LCD_Finished){
				get_answer = OFF;
				LCD_gotoState = 0;
			}
		}


	}
}

int main(void)
{
	SOS_Init();
	StrTask_t KEYPAD_initTask = {KEYPAD_Init,0,2};
	StrTask_t LCD_initTask={LCD_init,0,2};
	StrTask_t Display_Question = {QuestionDisplayTask,0,2};
	StrTask_t Get_Answer={GetAnswerTask,0,200};
	StrTask_t Score_Update={AnswerCheckTask,0,20};
	StrTask_t Score_Display={ScoreDisplay,0,2};

	SOS_CreateTask(&KEYPAD_initTask);
	SOS_CreateTask(&LCD_initTask);
	SOS_CreateTask(&Display_Question);
	SOS_CreateTask(&Get_Answer);
	SOS_CreateTask(&Score_Update);
	SOS_CreateTask(&Score_Display);

	SOS_Scheduler();
}
