
#include "timer.h"

void (*Ptr_Timer0_OV) (void) = ((void *) 0);
void (*Ptr_Timer0_CM) (void) = ((void *) 0);

void (*Ptr_Timer2_OV) (void) = ((void *) 0);
void (*Ptr_Timer2_CM) (void) = ((void *) 0);

void (*Ptr_Timer1_OV) (void) = ((void *) 0);
void (*Ptr_Timer1_CM) (void) = ((void *) 0);


STD_Fun_t TIMER_Init(uint8 TimerSpecs)
{
    STD_Fun_t StateVar = OK;
    // check if the timer exists in Array or not 
    if (TimerSpecs < NUM_TIMER_STATES)  
    {
        // at which timer user wants to operate 

		/************************************************************************/
		  /*                            Timer 0								*/			           
		/************************************************************************/
        if (TIMER_Array[TimerSpecs].TIMER == TIMER_0)
        {
			
            switch(TIMER_Array[TimerSpecs].MODE)
            {
			                /*      Normal mode           */
                            
            case Normal:
                TCCR0 &= ~(1u<<WGM00);
                TCCR0 &= ~(1u<<WGM01);
                // check the interrupt
                switch (TIMER_Array[TimerSpecs].INTERRUPT){
                    case Enable:
                        // enable interrupt overflow for timer 0 normal mode
                        TIMSK |= (1u<<TOIE0);
                        SREG |= (1u << 7);
                    break;
                    case Disable:
                        TIMSK &= ~(1u<<TOIE0);
                    break;
                    default:
                    StateVar = NOK;
                    break;
                    }
                    // compare reg value 
                    OCR0 = TIMER_Array[TimerSpecs].COMP_REG;
                    // check the pin 
                switch(TIMER_Array[TimerSpecs].COMP_PIN){
                    case Set:
                    TCCR0 |= (1u << COM00);
                    TCCR0 |= (1u << COM01);
                    DDRB |= (1u << OC0);
                    break;
                    case Clear:
                    TCCR0 &= ~(1u << COM00);
                    TCCR0 |= (1u << COM01);        
                    break;
                    case Toggle:
                    TCCR0 |= (1u << COM00);
                    TCCR0 &= ~(1u << COM01);
                    DDRB |= (1u << OC0);  
                    break;
                    default:
                    TCCR0 &= ~(1u << COM00);
                    TCCR0 &= ~(1u << COM01);  
                    break;
                    } 
                break;
				                /*            CTC mode	        */
            case CTC:
                TCCR0 &= ~(1u<<WGM00);
                TCCR0 |= (1u<<WGM01);
                switch (TIMER_Array[TimerSpecs].INTERRUPT){
                    case Enable:
                        // enable interrupt overflow for timer 0 normal mode
                        TIMSK |= (1u<<OCIE0);
                        SREG |= (1u << 7);
                    break;
                    case Disable:
                        TIMSK &= ~(1u<<OCIE0);
                    break;
                    default:
                    StateVar = NOK;
                    break;
                    }
				    OCR0 = TIMER_Array[TimerSpecs].COMP_REG;
                    switch(TIMER_Array[TimerSpecs].COMP_PIN){
                    case Set:
                    TCCR0 |= (1u << COM00);
                    TCCR0 |= (1u << COM01);
                    DDRB |= (1u << OC0);
                    break;
                    case Clear:
                    TCCR0 &= ~(1u << COM00);
                    TCCR0 |= (1u << COM01);        
                    break;
                    case Toggle:
                    TCCR0 |= (1u << COM00);
                    TCCR0 &= ~(1u << COM01);
                    DDRB |= (1u << OC0);  
                    break;
                    default:
                    TCCR0 &= ~(1u << COM00);
                    TCCR0 &= ~(1u << COM01);  
                    break;
                    }
                break;
             default:
                    StateVar = NOK;
             break;
                }

            switch (TIMER_Array[TimerSpecs].PRESCALER)
            {
            case No_Clock:
                TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                TIMER_Array[TimerSpecs].STATE = Not_Running;
                break;
            case No_Prescaler:
                TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                TCCR0 |= (1<<CS00);
                TIMER_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_8:
                TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                TCCR0 |=(1<<CS01);
                TIMER_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_64:
                TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                TCCR0 |=(1<<CS00)|(1<<CS01);
                TIMER_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_256:
                TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                TCCR0 |=(1<<CS02);
                TIMER_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_1024:
                TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                TCCR0 |=(1<<CS00) | (1<<CS02);
                TIMER_Array[TimerSpecs].STATE = Running;
                break;
            default:
				StateVar = NOK;
                break;
            }
        }
	
		/************************************************************************/
		    /* 			        	TIMER 1								   */
		/************************************************************************/
        else if (TIMER_Array[TimerSpecs].TIMER == TIMER_1)
        {
            /*                    NORAML MODE                   */
            if (TIMER_Array[TimerSpecs].MODE == Normal)
            {
				TCCR1A = (~(1<<WGM10)) &(~(1<<WGM11));
				TCCR1B = (~(1<<WGM13)) &(~(1<<WGM12));
				switch(TIMER_Array[TimerSpecs].CHANNAL)
				{
					case Channel_A:
						
						OCR1AH = (uint8) (TIMER_Array[TimerSpecs].COMP_REG >> 8);
                        OCR1AL = (uint8) ((TIMER_Array[TimerSpecs].COMP_REG) & 0x00FF);
						switch(TIMER_Array[TimerSpecs].COMP_PIN)
						{
							case Disconnect:
								TCCR1A &= (~(1<<COM1A0)) & (~(1<<COM1A1));
								break;
							case Toggle:
								TCCR1A &= (~(1<<COM1A0)) & (~(1<<COM1A1));
								TCCR1A |= (1<<COM1A0);
                                DDRD|= (1<<OC1A);
								break;
							case Clear:
								TCCR1A &= (~(1<<COM1A0)) & (~(1<<COM1A1));
								TCCR1A |= (1<<COM1A1);
                                DDRD|= (1<<OC1A);
								break;
							case Set:
								TCCR1A &= (~(1<<COM1A0)) & (~(1<<COM1A1));
								TCCR1A |= (1<<COM1A0) | (1<<COM1A1);
                                DDRD|= (1<<OC1A);
								break;
							default:
								StateVar = NOK;
								break;
						}
						break;
						
					case Channel_B:
						
						OCR1BH = (uint8) (TIMER_Array[TimerSpecs].COMP_REG >> 8);
                        OCR1BL = (uint8) ((TIMER_Array[TimerSpecs].COMP_REG) & 0x00FF);
					switch(TIMER_Array[TimerSpecs].COMP_PIN)
					{
						case Disconnect:
							TCCR1A &= (~(1<<COM1B0)) & (~(1<<COM1B1));
							break;
						case Toggle:
							TCCR1A &= (~(1<<COM1B0)) & (~(1<<COM1B1));
							TCCR1A |= (1<<COM1B0);
                            DDRD|= (1<<OC1B);
							break;
						case Clear:
							TCCR1A &= (~(1<<COM1B0)) & (~(1<<COM1B1));
							TCCR1A |= (1<<COM1B1);
                            DDRD|= (1<<OC1B);
							break;
						case Set:
							TCCR1A &= (~(1<<COM1B0)) & (~(1<<COM1B1));
							TCCR1A |= (1<<COM1B0) | (1<<COM1B1);
                            DDRD|= (1<<OC1B);
							break;
						default:
							StateVar = NOK;
							break;
					}
					break;
                    default:
						StateVar = NOK;
						break;					
				}
                switch(TIMER_Array[TimerSpecs].INTERRUPT)
                {
                    case Enable:
                        TIMSK |= (1<<TOIE1);
                        SREG|= (1<<7);
                        break;
                    case Disable:
                        TIMSK &= ~(1<<TOIE1);
                        break;
                    default:
                        StateVar = NOK;
                        break;
                }
            }
			/* CTC mode													            */
            else if (TIMER_Array[TimerSpecs].MODE == CTC)
            {
				TCCR1A = (~(1<<WGM10)) &(~(1<<WGM11));
				TCCR1B = (1<<WGM12);

				switch(TIMER_Array[TimerSpecs].CHANNAL)
				{
				//	Channel A
					case Channel_A:
						OCR1AH =  (TIMER_Array[TimerSpecs].COMP_REG >> 8);
						OCR1AL =  ((TIMER_Array[TimerSpecs].COMP_REG) & 0x00FF);
						switch(TIMER_Array[TimerSpecs].COMP_PIN)
						{
							case Disconnect:
							TCCR1A &= (~(1<<COM1A0)) & (~(1<<COM1A1));
								break;
							case Toggle:
								TCCR1A &= (~(1<<COM1A0)) & (~(1<<COM1A1));
								TCCR1A |= (1<<COM1A0);
                                DDRD|= (1<<OC1A);
								break;
							case Clear:
								TCCR1A &= (~(1<<COM1A0)) & (~(1<<COM1A1));
								TCCR1A |= (1<<COM1A1);
                                DDRD|= (1<<OC1A);
								break;
							case Set:
								TCCR1A &= (~(1<<COM1A0)) & (~(1<<COM1A1));
								TCCR1A |= (1<<COM1A0) | (1<<COM1A1);
                                DDRD|= (1<<OC1A);
								break;
							default:
								StateVar = NOK;
								break;
						}
						switch(TIMER_Array[TimerSpecs].INTERRUPT)
						{
							case Enable:
								TIMSK|= (1<<OCIE1A);
                                SREG|= (1<<7);
								break;
							case Disable:
								TIMSK&=~(1<<OCIE1A);
								break;
							default:
								StateVar = NOK;
								break;
						}

						break;

					// Channel B
					case Channel_B:
					OCR1AH =  (TIMER_Array[TimerSpecs].COMP_REG >> 8);
					OCR1AL =  ((TIMER_Array[TimerSpecs].COMP_REG) & 0x00FF);
					switch(TIMER_Array[TimerSpecs].COMP_PIN)
					{
						case Disconnect:
							TCCR1A &= (~(1<<COM1B0)) & (~(1<<COM1B1));
							break;
						case Toggle:
							TCCR1A &= (~(1<<COM1B0)) & (~(1<<COM1B1));
							TCCR1A |= (1<<COM1B0);
                            DDRD|= (1<<OC1B);
							break;
						case Clear:
							TCCR1A &= (~(1<<COM1B0)) & (~(1<<COM1B1));
							TCCR1A |= (1<<COM1B1);
                            DDRD|= (1<<OC1B);
							break;
						case Set:
							TCCR1A &= (~(1<<COM1B0)) & (~(1<<COM1B1));
							TCCR1A |= (1<<COM1B0) | (1<<COM1B1);
                            DDRD|= (1<<OC1B);
							break;
						default:
							StateVar = NOK;
							break;
					}
					switch(TIMER_Array[TimerSpecs].INTERRUPT)
					{
						case Enable:
							TIMSK|= (1<<OCIE1B);
                            SREG |= (1<<7);
							break;
						case Disable:
							TIMSK&=~(1<<OCIE1B);
							break;
						default:
							StateVar = NOK;
							break;
					}
					
					break;

				default:
					StateVar = NOK;
					break;
				}
            }
            /*                        Prescaler Conf                             */
            switch (TIMER_Array[TimerSpecs].PRESCALER){
            case No_Clock:
                TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
                TIMER_Array[TimerSpecs].STATE = Not_Running; 
                break;
            case No_Prescaler:
				TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
                TCCR1B |= (1u << CS10);
                TIMER_Array[TimerSpecs].STATE = Running;
                break;        
            case CLK_8:
                TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
				TCCR1B |= (1u << CS11);
                TIMER_Array[TimerSpecs].STATE = Running; 
                break;
            case CLK_64:
                TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
				TCCR1B |=(1u << CS10) | (1u << CS11);
                TIMER_Array[TimerSpecs].STATE = Running; 
                break;        
            case CLK_256:
                TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
				TCCR1B |=(1<<CS12);
                TIMER_Array[TimerSpecs].STATE = Running; 
                break;
            case CLK_1024:
                TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
				TCCR1B |=(1<<CS10) | (1<<CS12);
                TIMER_Array[TimerSpecs].STATE = Running; 
                break;
            default:
				StateVar = NOK;
                break;
            }
        }

		/************************************************************************/
		          /*                     TIMER 2						     */
		/************************************************************************/

        else if (TIMER_Array[TimerSpecs].TIMER == TIMER_2)
        {
           switch(TIMER_Array[TimerSpecs].MODE)
            {
		      /*                    NORMAL MODE						  */
                case Normal:
                TCCR2 &= ~(1u<<WGM20);
                TCCR2 &= ~(1u<<WGM21);
                // check the interrupt
                switch (TIMER_Array[TimerSpecs].INTERRUPT){
                    case Enable:
                        // enable interrupt overflow for timer 0 normal mode
                        TIMSK |= (1u<<TOIE2);
                        SREG |= (1u << 7);
                    break;
                    case Disable:
                        TIMSK &= ~(1u<<TOIE2);
                    break;
                    default:
                    StateVar = NOK;
                    break;
                    }
                // compare reg value 
                OCR2 = TIMER_Array[TimerSpecs].COMP_REG;
                // check the pin 
                switch(TIMER_Array[TimerSpecs].COMP_PIN){
                    case Set:
                    TCCR2 |= (1u << COM20);
                    TCCR2 |= (1u << COM21);
                    DDRD |= (1u << OC2);
                    break;
                    case Clear:
                    TCCR2 &= ~(1u << COM20);
                    TCCR2 |= (1u << COM21);        
                    break;
                    case Toggle:
                    TCCR2 |= (1u << COM20);
                    TCCR2 &= ~(1u << COM21);
                    DDRD |= (1u << OC2);  
                    break;
                    default:
                    TCCR2 &= ~(1u << COM20);
                    TCCR2 &= ~(1u << COM21);  
                    break;
                     } 
                break;
		        /*                    CTC					  */
                case CTC:
                TCCR2 &= ~(1u<<WGM20);
                TCCR2 |= (1u<<WGM21);
                switch (TIMER_Array[TimerSpecs].INTERRUPT){
                    case Enable:
                        // enable interrupt overflow for timer 0 normal mode
                        TIMSK |= (1u<<OCIE2);
                        SREG |= (1u << 7);
                    break;
                    case Disable:
                        TIMSK &= ~(1u<<OCIE2);
                    break;
                    default:
                    StateVar = NOK;
                    break;
                    }
                switch(TIMER_Array[TimerSpecs].COMP_PIN){
                    case Set:
                    TCCR2 |= (1u << COM20);
                    TCCR2 |= (1u << COM21);
                    DDRD |= (1u << OC2);
                    break;
                    case Clear:
                    TCCR2 &= ~(1u << COM20);
                    TCCR2 |= (1u << COM21);        
                    break;
                    case Toggle:
                    TCCR2 |= (1u << COM20);
                    TCCR2 &= ~(1u << COM21);
                    DDRD |= (1u << OC2);  
                    break;
                    default:
                    TCCR2 &= ~(1u << COM20);
                    TCCR2 &= ~(1u << COM21);  
                    break;
                    } 
                OCR2 = TIMER_Array[TimerSpecs].COMP_REG;  
                break;
                default:
                    StateVar = NOK;
                    break;
            }
            switch (TIMER_Array[TimerSpecs].PRESCALER)
            {
            case No_Clock:
                TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                TIMER_Array[TimerSpecs].STATE = Not_Running;
                break;
            case No_Prescaler:
                TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                TCCR2 |= (1<<CS20);
                TIMER_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_8:
                TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                TCCR2 |=(1<<CS21);
                TIMER_Array[TimerSpecs].STATE = Running;
                break;

            case CLK_32:
                TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                TCCR2 |=(1<<CS20) | (1<<CS21);
                TIMER_Array[TimerSpecs].STATE = Running;
                break;
				
			case CLK_64:
				 TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
				 TCCR2 |=(1<<CS22);
                TIMER_Array[TimerSpecs].STATE = Running;
				 break;
            
            case CLK_256:
                TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                TCCR2 |=(1<<CS22) | (1<<CS21);
                TIMER_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_1024:
                TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                TCCR2 |=(1<<CS20) | (1<<CS22) | (1<<CS21);
                TIMER_Array[TimerSpecs].STATE = Running;
                break;
            default:
            StateVar = NOK;
                break;
            }
        }

        else 
        {
            // wrong info
            StateVar = NOK;
        }
    }
    else 
    {
        StateVar = NOK;
    }
    return StateVar;
}

STD_Fun_t TIMER_Start (uint8 TimerName, uint8 Prescaler_Conf)
{
    uint8 LoopIndex ;
    STD_Fun_t StateVar = OK;
    for(LoopIndex=0; LoopIndex<NUM_TIMER_STATES; LoopIndex++)
    {
        if (TIMER_Array[LoopIndex].TIMER == TimerName)
        {
            if (TIMER_Array[LoopIndex].STATE != Running)
            {
                if (TimerName == TIMER_0)
                {
                    switch(Prescaler_Conf)
                    {
                        case No_Prescaler:
							TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
							TCCR0 |= (1<<CS00);
							TIMER_Array[LoopIndex].STATE = Running;
                        break;
                        case CLK_8:
							TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
							TCCR0 |=(1<<CS01);
							TIMER_Array[LoopIndex].STATE = Running;
                        break;
							case CLK_64:
							TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
							TCCR0 |=(1<<CS00) | (1<<CS01);
							TIMER_Array[LoopIndex].STATE = Running;
                        break;       
                        case CLK_256:
							TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
							TCCR0 |=(1<<CS02);
							TIMER_Array[LoopIndex].STATE = Running;
                        break;
                        case CLK_1024:
							TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
							TCCR0 |=(1<<CS00) | (1<<CS02);
							TIMER_Array[LoopIndex].STATE = Running;
                        break;
                        default:
							StateVar = NOK;
                        break;
                    }
                }
                else if (TimerName == TIMER_1)
                {
                    switch (Prescaler_Conf)
                    {
                        case No_Prescaler:
								TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
								TCCR1B |= (1u << CS10);
								TIMER_Array[LoopIndex].STATE = Running;
                            break;        
                        case CLK_8:
								TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
								TCCR1B |= (1u << CS11);
								TIMER_Array[LoopIndex].STATE = Running;
                            break;
                        case CLK_64:
								TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
								TCCR1B |=(1u << CS10) | (1u << CS11);
								TIMER_Array[LoopIndex].STATE = Running;
                            break;        
                        case CLK_256:
								TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
								TCCR1B |=(1<<CS12);
								TIMER_Array[LoopIndex].STATE = Running;
                            break;
                        case CLK_1024:
								TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
								TCCR1B |=(1<<CS10) | (1<<CS12);
								TIMER_Array[LoopIndex].STATE = Running;
                            break;
                        default:
                            StateVar = NOK;
                            break;
                        }
                }
                else if (TimerName == TIMER_2)
                {
                    switch(Prescaler_Conf)
                    {
                        case No_Prescaler:
							TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
							TCCR2 |= (1<<CS20);
							TIMER_Array[LoopIndex].STATE = Running;
                        break;
                        case CLK_8:
							TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
							TCCR2 |=(1<<CS21);
							TIMER_Array[LoopIndex].STATE = Running;
                        break;
                        case CLK_32:
							TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
							TCCR2 |=(1<<CS20) | (1<<CS21);
							TIMER_Array[LoopIndex].STATE = Running;
                        break;                    
                        case CLK_64:
							TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
							TCCR2 |=(1<<CS22);
							TIMER_Array[LoopIndex].STATE = Running;
                        break;
                        case CLK_256:
							TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
							TCCR2 |=(1<<CS22) | (1<<CS21);
							TIMER_Array[LoopIndex].STATE = Running;
                        break;
                        case CLK_1024:
							TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
							TCCR2 |=(1<<CS20) | (1<<CS22) | (1<<CS21);
							TIMER_Array[LoopIndex].STATE = Running;
                        break;
                        default:
							StateVar = NOK;
                        break;
                    }
                }
            }
            else 
            {
                StateVar = NOK;
            }
        }
    }
    return StateVar;
}

STD_Fun_t TIMER_Stop (uint8 TimerName)
{
    uint8 LoopIndex ;
    STD_Fun_t StateVar = OK;
    for(LoopIndex=0; LoopIndex<NUM_TIMER_STATES; LoopIndex++)
    {
        if (TIMER_Array[LoopIndex].TIMER == TimerName)
        {
            if (TIMER_Array[LoopIndex].STATE == Running)
            {
                if (TimerName == TIMER_0)
                {
                TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                TIMER_Array[LoopIndex].STATE = Not_Running;
                }
                else if (TimerName == TIMER_1)
                {
                TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
                TIMER_Array[LoopIndex].STATE = Not_Running; 
                }
                else if (TimerName == TIMER_2)
                {
                TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                TIMER_Array[LoopIndex].STATE = Not_Running;
                }
            }
            else 
            {
                StateVar = NOK;
            }
        }
    }
    return StateVar;
}


STD_Fun_t Timer_CreateTick(uint8 timer_id , uint16 resolution_ms)
{
	uint8 Loop_index;
	if ( (resolution_ms > 30) && ( (timer_id == TIMER_0) || (timer_id == TIMER_2) ) ){
			// return error
		}
	else if ((resolution_ms > 8000) &&  (timer_id == TIMER_1)){
			// return error
		}
	else {
		for(Loop_index=0; Loop_index<NUM_TIMER_STATES; Loop_index++){

			if (TIMER_Array[Loop_index].TIMER == timer_id){

				if(TIMER_Array[Loop_index].STATE == Not_Running){
					TIMER_Array[Loop_index].MODE = CTC;
					TIMER_Array[Loop_index].COMP_PIN = Disconnect;
					TIMER_Array[Loop_index].CHANNAL = NA_T;
					TIMER_Array[Loop_index].COMP_REG =  ( (float32)resolution_ms / 0.128f );
					TIMER_Array[Loop_index].TOP_VALUE = NA_T;
					TIMER_Array[Loop_index].PRESCALER = CLK_1024;
					TIMER_Array[Loop_index].INTERRUPT = Enable;	
					}

					else{
						//return error
					}
				Loop_index = NUM_TIMER_STATES;
				}
			}
		}
}


void TIMER0_SetOV(void (*Ptr_ISR) (void))
{
	Ptr_Timer0_OV = Ptr_ISR;
}

void TIMER0_SetCM(void (*Ptr_ISR) (void))
{
	Ptr_Timer0_CM = Ptr_ISR;
}

void TIMER2_SetOV(void (*Ptr_ISR) (void))
{
	Ptr_Timer2_OV = Ptr_ISR;
}

void TIMER2_SetCM(void (*Ptr_ISR) (void))
{
	Ptr_Timer2_CM = Ptr_ISR;
}

void TIMER1_SetOV(void (*Ptr_ISR) (void))
{
	Ptr_Timer1_OV = Ptr_ISR;
}

void TIMER1_SetCM(void (*Ptr_ISR) (void))
{
	Ptr_Timer1_CM = Ptr_ISR;
}


ISR(TIMER0_OV)
{
	if (Ptr_Timer0_OV != NULL)
	{
		Ptr_Timer0_OV();
	}
	
}

ISR(TIMER0_COMP)
{
	if(Ptr_Timer0_CM != NULL)
	{
		Ptr_Timer0_CM();
	}
	
}

ISR(TIMER2_OV)
{
	if (Ptr_Timer2_OV != NULL)
	{
		Ptr_Timer2_OV();
	}
	
}

ISR(TIMER2_COMP)
{
	if (Ptr_Timer2_CM != NULL)
	{
		Ptr_Timer2_CM();
	}
	
}

ISR(TIMER1_OV)
{
	if (Ptr_Timer1_OV != NULL)
	{
		Ptr_Timer1_OV();
	}
	
}

ISR(TIMER1_COMPA)
{
	if (Ptr_Timer1_CM != NULL)
	{
		Ptr_Timer1_CM();
	}
	
}

ISR(TIMER1_COMPB)
{
	if (Ptr_Timer1_CM != NULL)
	{
		Ptr_Timer1_CM();
	}
	
}
