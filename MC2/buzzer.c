/*--------------------------------------------------------------------------------------
 * [FILE NAME]:		<buzzer.c>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<1/11/2021>
 *
 * [DESCRIPTION]:	<A source file for buzzer driver>
 --------------------------------------------------------------------------------------*/

/*----------------------------------------INCLUDES-------------------------------------*/

#include "buzzer.h"
#include "gpio.h"

/*---------------------------------FUNCTIONS DEFINITIONS-------------------------------*/
/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	BUZZER_init
 * [DESCRIPTION]:	This Function is used to initialize the buzzer
 * [ARGS]:			No Arguments
 * [RETURNS]:		No Returns
 ----------------------------------------------------------------------------------------*/
void BUZZER_init(void)
{
	GPIO_setPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
}


/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	BUZZER_ON
 * [DESCRIPTION]:	This Function is used to set the buzzer on
 * [ARGS]:			No Arguments
 * [RETURNS]:		No Returns
 ----------------------------------------------------------------------------------------*/
void BUZZER_ON(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);
}


/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	BUZZER_OFF
 * [DESCRIPTION]:	This Function is used to set the buzzer off
 * [ARGS]:			No Arguments
 * [RETURNS]:		No Returns
 ----------------------------------------------------------------------------------------*/
void BUZZER_OFF(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}
