/*--------------------------------------------------------------------------
 * [FILE NAME]:		<buzzer.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<1/11/2021>
 *
 * [DESCRIPTION]:	<A header file for buzzer driver>
 ---------------------------------------------------------------------------*/

#ifndef BUZZER_H_
#define BUZZER_H_

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*------------------------DEFINITIONS AND CONFIGURATIONS----------------------*/

#define BUZZER_PORT_ID		PORTC_ID
#define BUZZER_PIN_ID		PIN2_ID

/*-----------------------------FUNCTIONS PROTOTYPES---------------------------*/
/*
 * Description:
 * This Function is used to initialize the buzzer
 */
void BUZZER_init(void);


/*
 * Description:
 * This Function is used to set the buzzer on
 */
void BUZZER_ON(void);


/*
 * Description:
 * This Function is used to set the buzzer off
 */
void BUZZER_OFF(void);

#endif /* BUZZER_H_ */
