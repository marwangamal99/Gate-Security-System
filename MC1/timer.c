/*--------------------------------------------------------------------------------------
 * [FILE NAME]:		<timer.c>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<16/10/2021>
 *
 * [DESCRIPTION]:	<A source file for AVR timer driver>
 --------------------------------------------------------------------------------------*/

/*----------------------------------------INCLUDES-------------------------------------*/

#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*------------------------------------GLOBAL VARIABLES----------------------------------*/

static volatile void(*g_TIMER0_callBackPtr)(uint16) = NULL_PTR;
static volatile void(*g_TIMER1_callBackPtr)(uint16) = NULL_PTR;
static volatile void(*g_TIMER2_callBackPtr)(uint16) = NULL_PTR;

uint8 g_tick0 = 0;
uint16 g_tick1 = 0;
uint8 g_tick2 = 0;

uint16 g_msec0 = 0;
uint16 g_msec1 = 0;
uint16 g_msec2 = 0;

/*---------------------------------FUNCTIONS DEFINITIONS-------------------------------*/
/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TIMER_init
 * [DESCRIPTION]:	This Function is used to initialize the AVR TIMER Driver
 * [ARGS]:	const TIMER_ConfigType *a_configPtr : This Argument is a pointer to struct,
 * 			it will indicate the struct input for this function
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void TIMER_init(const TIMER_ConfigType *a_configPtr)
{
	/* Switching for each TIMER exist */
	switch(a_configPtr->timer)
	{
	case TIMER0 :
		/* Force Output Compare bit (FOC0) */
		TCCR0 |= (1<<FOC0);

		/* WaveForm Generation Mode (WGM00, WGM01) */
		TCCR0 = (TCCR0 & 0xBF) | (((a_configPtr->mode0) & 0x01) << 6);
		TCCR0 = (TCCR0 & 0xF7) | (((a_configPtr->mode0) & 0x02) << 3);

		/* Clock Select bits (CS02,CS01,CS00) */
		TCCR0 = (TCCR0 & 0xF8) | (a_configPtr->prescalar0);

		/* Set the initial value of timer here */
		TCNT0 = (a_configPtr->initial_value);

		/* Set the compare value of timer here */
		OCR0 = (a_configPtr->compare_value);

		/* Module interrupt enable select (CompareMatch or OverFlow) */
		if((a_configPtr->mode0) == CTC_T0)
		{
			TIMSK |= (1<<OCIE0);
		}
		else if((a_configPtr->mode0) == NORMAL_T0)
		{
			TIMSK |= (1<<TOIE0);
		}
		break;
/*******************************************************************************************/
	case TIMER1 :
		/* Set the initial value of timer in TCNT1 register */
		TCNT1 = (a_configPtr->initial_value);

		/* Force Output Compare bit (FOC1A,FOC1B)
		 * Set the compare value of timer in OCR1A and OCR1B */
		switch(a_configPtr->channel1)
		{
		case CHANNEL_A :
			TCCR1A |= (1<<FOC1A);
			OCR1A = (a_configPtr->compare_value);
			break;

		case CHANNEL_B :
			TCCR1A |= (1<<FOC1B);
			OCR1B = (a_configPtr->compare_value);
			break;
		}

		/* Set the module interrupt bit according to the mode we are using */
		switch(a_configPtr->mode1)
		{
		case CTC_T1 :
			if((a_configPtr->channel1) == CHANNEL_A)
			{
				TIMSK |= (1<<OCIE1A);
			}
			else if((a_configPtr->channel1) == CHANNEL_B)
			{
				TIMSK |= (1<<OCIE1B);
			}
			break;

		case NORMAL_T1 :
			TIMSK |= (1<<TOIE1);
			break;
		}

		/* WaveForm Generation Mode (WGM10, WGM11) in TCCR1A & (WGM12,WGM13) in TCCR1B
		 * as it controls the mode we are using */
		TCCR1A = (TCCR1A & 0xFC) | ((a_configPtr->mode1) & 0x03);
		TCCR1B = (TCCR1B & 0xE7) | ( ((a_configPtr->mode1) & 0x0C) << 1 );

		/* Clock Select bits "Prescalar" (CS02,CS01,CS00) */
		TCCR1B = (TCCR1B & 0xF8) | (a_configPtr->prescalar1);
		break;
/*******************************************************************************************/
		case TIMER2 :
			/* Force Output Compare bit (FOC0) */
			TCCR2 |= (1<<FOC0);

			/* WaveForm Generation Mode (WGM00, WGM01) */
			TCCR2 = (TCCR2 & 0xBF) | (((a_configPtr->mode2) & 0x01) << 6);
			TCCR2 = (TCCR2 & 0xF7) | (((a_configPtr->mode2) & 0x02) << 3);

			/* Clock Select bits (CS02,CS01,CS00) */
			TCCR2 = (TCCR0 & 0xF8) | (a_configPtr->prescalar2);

			/* Set the initial value of timer here */
			TCNT2 = (a_configPtr->initial_value);

			/* Set the compare value of timer here */
			OCR2 = (a_configPtr->compare_value);

			if((a_configPtr->mode2) == CTC_T2)
			{
				TIMSK |= (1<<OCIE2);
			}
			else if(((a_configPtr->mode2) == NORMAL_T2))
			{
				TIMSK |= (1<<TOIE2);
			}
			break;
	}
	/* Set the global interrupt bit */
	SREG |= (1<<7);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TIMER0_setCallBack
 * [DESCRIPTION]:	This Function is used to assign the specific function used to the
 * 					global pointer to function of TIMER0 to use it in the ISR
 * [ARGS]:	void(*a_ptr)(uint16) :	This Argument is a pointer to function, indicating the
 * 								 	function called in the call back function
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void TIMER0_setCallBack(void(*a_ptr)(uint16))
{
	g_TIMER0_callBackPtr = a_ptr;
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TIMER1_setCallBack
 * [DESCRIPTION]:	This Function is used to assign the specific function used to the
 * 					global pointer to function of TIMER1 to use it in the ISR
 * [ARGS]:	void(*a_ptr)(uint16) :	This Argument is a pointer to function, indicating the
 * 								 	function called in the call back function
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void TIMER1_setCallBack(void(*a_ptr)(uint16))
{
	g_TIMER1_callBackPtr = a_ptr;
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TIMER2_setCallBack
 * [DESCRIPTION]:	This Function is used to assign the specific function used to the
 * 					global pointer to function of TIMER2 to use it in the ISR
 * [ARGS]:	void(*a_ptr)(uint16) :	This Argument is a pointer to function, indicating the
 * 								 	function called in the call back function
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void TIMER2_setCallBack(void(*a_ptr)(uint16))
{
	g_TIMER2_callBackPtr = a_ptr;
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TIMER0_deInit
 * [DESCRIPTION]:	This Function is used to de-initialize the TIMER0 driver, used when
 * 					finishing using the driver in a specific function
 * [ARGS]:	No Argument
 *	[RETURNS]:	No Return
 ----------------------------------------------------------------------------------------*/
void TIMER0_deInit(void)
{
	/* Clear all TIMER0 registers */
	TCCR0 = 0;
	TCNT0 = 0;
	OCR0 = 0;

	/* Disable all interrupt mask registers (OCIE,TOIE0) */
	TIMSK &= ~(0x03);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TIMER1_deInit
 * [DESCRIPTION]:	This Function is used to de-initialize the TIMER1 driver, used when
 * 					finishing using the driver in a specific function
 * [ARGS]:	No Argument
 *	[RETURNS]:	No Return
 ----------------------------------------------------------------------------------------*/
void TIMER1_deInit(void)
{
	/* Clear all TIMER1 registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 0;
	OCR1B = 0;
	ICR1 = 0;

	/* Disable all interrupt mask registers (OCIE1A,OCIE1B,TOIE1) */
	TIMSK &= ~(0x3C);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TIMER2_deInit
 * [DESCRIPTION]:	This Function is used to de-initialize the TIMER2 driver, used when
 * 					finishing using the driver in a specific function
 * [ARGS]:	No Argument
 *	[RETURNS]:	No Return
 ----------------------------------------------------------------------------------------*/
void TIMER2_deInit(void)
{
	/* Clear all TIMER2 registers */
	TCCR2 = 0;
	TCNT2 = 0;
	OCR2 = 0;

	/* Disable all interrupt mask registers (OCIE2,TOIE2) */
	TIMSK &= ~(0xC0);
}

/*--------------------------------INTERRUPT SERVICE ROUTINES-----------------------------*/
/*---------------------------------------------------------------------------------------
 * [ISR NAME]:		TIMER0_OVF_vect
 * [DESCRIPTION]:	This ISR will trigger the call back function when using overflow mode
 * 					in TIMER0
 ----------------------------------------------------------------------------------------*/
ISR(TIMER0_OVF_vect)
{
	if(g_TIMER0_callBackPtr != NULL_PTR)
	{
		(*g_TIMER0_callBackPtr)(g_msec0);
	}
}


/*---------------------------------------------------------------------------------------
 * [ISR NAME]:		TIMER0_COMP_vect
 * [DESCRIPTION]:	This ISR will trigger the call back function when using compare match
 * 					mode in TIMER0
 ----------------------------------------------------------------------------------------*/
ISR(TIMER0_COMP_vect)
{
	if(g_TIMER0_callBackPtr != NULL_PTR)
	{
		(*g_TIMER0_callBackPtr)(g_msec0);
	}
}


/*---------------------------------------------------------------------------------------
 * [ISR NAME]:		TIMER1_OVF_vect
 * [DESCRIPTION]:	This ISR will trigger the call back function when using overflow mode
 * 					in TIMER1
 ----------------------------------------------------------------------------------------*/
ISR(TIMER1_OVF_vect)
{
	if(g_TIMER1_callBackPtr != NULL_PTR)
	{
		(*g_TIMER1_callBackPtr)(g_msec1);
	}
}


/*---------------------------------------------------------------------------------------
 * [ISR NAME]:		TIMER1_COMPA_vect
 * [DESCRIPTION]:	This ISR will trigger the call back function when using compare match
 * 					mode in TIMER1 - Channel A
 ----------------------------------------------------------------------------------------*/
ISR(TIMER1_COMPA_vect)
{
	if(g_TIMER1_callBackPtr != NULL_PTR)
	{
		(*g_TIMER1_callBackPtr)(g_msec1);
	}
}


/*---------------------------------------------------------------------------------------
 * [ISR NAME]:		TIMER1_COMPB_vect
 * [DESCRIPTION]:	This ISR will trigger the call back function when using compare match
 * 					mode in TIMER1 - Channel B
 ----------------------------------------------------------------------------------------*/
ISR(TIMER1_COMPB_vect)
{
	if(g_TIMER1_callBackPtr != NULL_PTR)
	{
		(*g_TIMER1_callBackPtr)(g_msec1);
	}
}

/*---------------------------------------------------------------------------------------
 * [ISR NAME]:		TIMER2_OVF_vect
 * [DESCRIPTION]:	This ISR will trigger the call back function when using overflow mode
 * 					in TIMER2
 ----------------------------------------------------------------------------------------*/
ISR(TIMER2_OVF_vect)
{
	if(g_TIMER2_callBackPtr != NULL_PTR)
	{
		(*g_TIMER2_callBackPtr)(g_msec2);
	}
}

/*---------------------------------------------------------------------------------------
 * [ISR NAME]:		TIMER2_COMP_vect
 * [DESCRIPTION]:	This ISR will trigger the call back function when using compare match
 * 					mode in TIMER2
 ----------------------------------------------------------------------------------------*/
ISR(TIMER2_COMP_vect)
{
	if(g_TIMER2_callBackPtr != NULL_PTR)
	{
		(*g_TIMER2_callBackPtr)(g_msec2);
	}
}
