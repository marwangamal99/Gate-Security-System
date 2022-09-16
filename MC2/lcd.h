/*--------------------------------------------------------------------------
 * [FILE NAME]:		<lcd.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<4/10/2021>
 *
 * [DESCRIPTION]:	<A header file for AVR LCD>
 ---------------------------------------------------------------------------*/

#ifndef LCD_H_
#define LCD_H_

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*------------------------DEFINITIONS AND CONFIGURATIONS----------------------*/

#define NUM_OF_COLS		16
#define NUM_OF_ROWS		2

#define LCD_PORT		PORTD_ID
#define LCD_RS_PIN		PIN2_ID
#define	LCD_RW_PIN		PIN3_ID
#define LCD_E_PIN		PIN4_ID

#define LCD_DB_PORT		PORTC_ID

#define LCD_2LINES_8BITS_MODE	0x38
#define	LCD_CURSOR_OFF			0x0C
#define LCD_CLEAR_SCREEN		0x01
#define LCD_SET_CURSOR_AT_BEGIN	0x80

/*-----------------------------FUNCTIONS PROTOTYPES---------------------------*/
/*
 * Description:
 * This function is used for sending commands. it helps in other functions as
 * initializing and displaying characters on LCD
 */
void LCD_sendCommand(uint8 command);


/*
 * Description:
 * This function is used in displaying a character on LCD
 */
void LCD_displayCharacter(uint8 character);


/*
 * Description:
 * This function is used in initializing LCD Driver
 */
void LCD_init(void);

/*
 * Description:
 * This function is used in displaying a string on LCD
 */
void LCD_displayString(const char *str);

/*
 * Description:
 * This function is used to move the cursor to a specific location on LCD
 */
void LCD_moveCursor(uint8 row, uint8 column);


/*
 * Description:
 * This function is used in displaying a string and begin it from a certain location
 */
void LCD_displayStringRowColumn(const char *str, uint8 row, uint8 column);


/*
 * Description:
 * This function is used in clearing LCD display
 */
void LCD_clearScreen(void);


/*
 * Description:
 * This function is used in displaying a variable on LCD
 */
void LCD_integerToString(uint32 integer);

#endif /* LCD_H_ */
