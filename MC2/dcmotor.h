/*--------------------------------------------------------------------------
 * [FILE NAME]:		<dcmotor.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<10/10/2021>
 *
 * [DESCRIPTION]:	<A header file for DC Motor driver>
 ---------------------------------------------------------------------------*/

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*------------------------DEFINITIONS AND CONFIGURATIONS----------------------*/

#define IN1_PORT_ID		PORTB_ID
#define IN1_PIN_ID		PIN0_ID

#define	IN2_PORT_ID		PORTB_ID
#define IN2_PIN_ID		PIN1_ID

/*-----------------------------TYPES DECLEARATION-----------------------------*/

typedef enum
{
	STOP,CW,CCW
}DcMotor_State;

/*-----------------------------FUNCTIONS PROTOTYPES---------------------------*/
/*
 * Description:
 * This Function is used to initialize the DC motor
 */
void DcMotor_Init(void);


/*
 * Description:
 * This Function is used to set the state and the speed to rotate the motor
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed);


/*
 * Description:
 * This Function is used to de-initialize the motor by de-initializing
 * the PWM driver
 */
void DcMotor_deInit(void);

#endif /* DCMOTOR_H_ */
