/*--------------------------------------------------------------------------------------
 * [FILE NAME]:		<keypad.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<4/10/2021>
 *
 * [DESCRIPTION]:	<A header file for AVR Keypad in HAL "Hardware Abstract Layer">
 --------------------------------------------------------------------------------------*/

#ifndef KEYPAD_H_
#define KEYPAD_H_

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*------------------------DEFINITIONS AND CONFIGURATIONS----------------------*/

#define KEYPAD_NUM_OF_ROWS			4
#define KEYPAD_NUM_OF_COLS			4

#define KEYPAD_PORT_ID				PORTA_ID	/* Used port for the Keypad */

#define	KEYPAD_FIRST_ROW_PIN_ID		PIN0_ID		/* The used pin for the first row in keypad */
#define KEYPAD_FIRST_COL_PIN_ID		PIN4_ID		/* The used pin for the first column in keypad */

#define KEYPAD_BUTTON_PRESSED		LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED		LOGIC_HIGH

#define ENTER_KEY					13
#define KEYPAD_DELAY				2000	//was 300 in 1MHz
/*-----------------------------FUNCTIONS PROTOTYPES---------------------------*/
/*
 * Description:
 * This function is used to get the number of the pressed key in KEYPAD
 */
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
