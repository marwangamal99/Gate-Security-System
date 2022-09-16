/*--------------------------------------------------------------------------------------
 * [FILE NAME]:		<keypad.c>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<4/10/2021>
 *
 * [DESCRIPTION]:	<A source file for AVR Keypad in HAL "Hardware Abstract Layer">
 --------------------------------------------------------------------------------------*/

/*----------------------------------------INCLUDES-------------------------------------*/
#include "keypad.h"
#include "gpio.h"
#include "common_macros.h"

/*------------------------------FUNCTIONS PROTOTYPES(PRIVATE)----------------------------*/
/* This function is used for declaration whether the used keypad is 4x3 or 4x4 */
#if (KEYPAD_NUM_OF_COLS == 3)

static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);

#elif (KEYPAD_NUM_OF_COLS == 4)

static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);

#endif

/*---------------------------------FUNCTIONS DEFINITIONS-------------------------------*/

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	KEYPAD_getPressedKey
 * [DESCRIPTION]:	This Function is used to get the button number of the pressed button.
 * 					at first, it set all columns as input the change each tick only one column
 * 					as an output and read its value, if the button is pressed then the
 * 					function will return the number order of this pressed button
 * [ARGS]:			No Arguments
 *	[RETURNS]:		The function return the value of the pressed button
 ----------------------------------------------------------------------------------------*/
uint8 KEYPAD_getPressedKey(void)
{
	uint8 row, col, value = 0;
	while(1)
	{
		for(col=0; col<KEYPAD_NUM_OF_COLS; col++)
		{
			/* First, set all the port as an Input port */
			GPIO_setPortDirection(KEYPAD_PORT_ID, PORT_INPUT);

			/* Then, begin to set each pin in the port as an output */
			GPIO_setPinDirection(KEYPAD_PORT_ID, (col+KEYPAD_FIRST_COL_PIN_ID), PIN_OUTPUT);

#if (KEYPAD_BUTTON_PRESSED == LOGIC_LOW)
			/* Put the value of the PORT in a variable as all 1 and the only pressed one is 0 */
			value = ~(1<<(col+KEYPAD_FIRST_COL_PIN_ID));
#elif (KEYPAD_BUTTON_PRESSED == LOGIC_HIGH)
			/* Put the value of the PORT in a variable as all 0 and the only pressed one is 1 */
			value = 1<<(col+KEYPAD_FIRST_COL_PIN_ID);
#endif

			/*  */
			GPIO_writePort(KEYPAD_PORT_ID, value);

			for(row=0; row<KEYPAD_NUM_OF_ROWS; row++)
			{
				if((GPIO_readPin(KEYPAD_PORT_ID,row)) == KEYPAD_BUTTON_PRESSED)
				{
#if (KEYPAD_NUM_OF_COLS == 3)
					return KEYPAD_4x3_adjustKeyNumber((row * KEYPAD_NUM_OF_COLS) + col + 1);
					/* An empirical equation used to get the button number */
#elif (KEYPAD_NUM_OF_COLS == 4)
					return KEYPAD_4x4_adjustKeyNumber((row * KEYPAD_NUM_OF_COLS) + col + 1);
#endif
				}
			}
		}
	}
}
#if (KEYPAD_NUM_OF_COLS == 3)

static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
	case 10:
		keypad_button = '*';
		break;
	case 11:
		keypad_button = 0;
		break;
	case 12:
		keypad_button = '#';
		break;
	}
	return keypad_button;
}

#elif (KEYPAD_NUM_OF_COLS == 4)

static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
	case 1:
		keypad_button = 7;
		break;
	case 2:
		keypad_button = 8;
		break;
	case 3:
		keypad_button = 9;
		break;
	case 4:
		keypad_button = '%';
		break;
	case 5:
		keypad_button = 4;
		break;
	case 6:
		keypad_button = 5;
		break;
	case 7:
		keypad_button = 6;
		break;
	case 8:
		keypad_button = 'x';
		break;
	case 9:
		keypad_button = 1;
		break;
	case 10:
		keypad_button = 2;
		break;
	case 11:
		keypad_button = 3;
		break;
	case 12:
		keypad_button = '-';
		break;
	case 13:
		keypad_button = 13;		/* ASCII code of Enter is 13 */
		break;
	case 14:
		keypad_button = 0;
		break;
	case 15:
		keypad_button = '=';
		break;
	case 16:
		keypad_button = '+';
		break;
	}
	return keypad_button;
}
#endif	/* KEYPAD_NUM_OF_COLS */
