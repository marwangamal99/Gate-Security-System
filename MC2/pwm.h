/*--------------------------------------------------------------------------
 * [FILE NAME]:		<pwm.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<20/10/2021>
 *
 * [DESCRIPTION]:	<A header file for AVR PWM driver>
 ---------------------------------------------------------------------------*/

#ifndef PWM_H_
#define PWM_H_

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*-----------------------------FUNCTIONS PROTOTYPES---------------------------*/
/*
 * Description:
 * This Function is used to initialize the DC motor
 */
void PWM_Timer0_Start(uint8 duty_cycle);


/*
 * Description:
 * This Function is used to de-initialize the PWM driver
 */
void PWM_Timer0_Stop(void);

#endif /* PWM_H_ */
