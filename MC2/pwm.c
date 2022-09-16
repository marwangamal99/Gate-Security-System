/*--------------------------------------------------------------------------------------
 * [FILE NAME]:		<pwm.c>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<20/10/2021>
 *
 * [DESCRIPTION]:	<A source file for AVR PWM driver>
 --------------------------------------------------------------------------------------*/

/*----------------------------------------INCLUDES-------------------------------------*/

#include "pwm.h"
#include "common_macros.h"
#include <avr/io.h>

/*---------------------------------FUNCTIONS DEFINITIONS-------------------------------*/

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	DcMotor_Init
 * [DESCRIPTION]:	This Function is used to initialize the DC motor
 * [ARGS]:		No Arguments
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCNT0 = 0;
	OCR0 = duty_cycle;

	SET_BIT(DDRB,PB3);	/* Set PB3/OC0 pin as output */

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}



/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	PWM_Timer0_Stop
 * [DESCRIPTION]:	This Function is used to de-initialize the PWM driver
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void PWM_Timer0_Stop(void)
{
	TCNT0 = 0;
	OCR0 = 0;
	TCCR0 = 0;
}
