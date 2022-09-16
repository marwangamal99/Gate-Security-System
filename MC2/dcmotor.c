/*--------------------------------------------------------------------------------------
 * [FILE NAME]:		<dcmotor.c>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<10/10/2021>
 *
 * [DESCRIPTION]:	<A source file for DC motor driver>
 --------------------------------------------------------------------------------------*/

/*----------------------------------------INCLUDES-------------------------------------*/

#include "dcmotor.h"
#include "gpio.h"
#include "pwm.h"

/*---------------------------------FUNCTIONS DEFINITIONS-------------------------------*/

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	DcMotor_Init
 * [DESCRIPTION]:	This Function is used to initialize the DC motor
 * [ARGS]:		No Arguments
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void DcMotor_Init(void)
{
	GPIO_setPinDirection(IN1_PORT_ID, IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setPinDirection(IN2_PORT_ID, IN2_PIN_ID, PIN_OUTPUT);

	GPIO_writePin(IN1_PORT_ID, IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(IN2_PORT_ID, IN2_PIN_ID, LOGIC_LOW);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	DcMotor_Rotate
 * [DESCRIPTION]:	This Function is used to set the state and the speed to rotate the motor
 * [ARGS]:
 * [in]		DcMotor_State state :	This Arg shall indicate the state of the motor (STOP,CW,CCW)
 * 			uint8 speed : 			This Arg shall indicate the motor speed in percentage (%)
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void DcMotor_Rotate(DcMotor_State state, uint8 speed)	//uint8 speed
{
	uint8 duty_cycle = 0;

	/*
	 * Equation to convert speed percentage (0->100)
	 * into duty cycle range (0->255)
	 */
	duty_cycle = (uint8) ( ((uint16)speed * 255) / 100 );
	PWM_Timer0_Start(duty_cycle);

	if(state == STOP)
	{
		GPIO_writePin(IN1_PORT_ID, IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(IN2_PORT_ID, IN2_PIN_ID, LOGIC_LOW);
	}
	else if(state == CW)
	{
		GPIO_writePin(IN1_PORT_ID, IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(IN2_PORT_ID, IN2_PIN_ID, LOGIC_LOW);
	}
	else if(state == CCW)
	{
		GPIO_writePin(IN1_PORT_ID, IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(IN2_PORT_ID, IN2_PIN_ID, LOGIC_HIGH);
	}
}


/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	DcMotor_deInit
 * [DESCRIPTION]:	This Function is used to de-initialize the motor by de-initializing
 * 					the PWM driver
 * [ARGS]:		No Arguments
 *[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void DcMotor_deInit(void)
{
	PWM_Timer0_Stop();
}
