/*--------------------------------------------------------------------------------------
 * [FILE NAME]:		<lcd.c>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<4/10/2021>
 *
 * [DESCRIPTION]:	<A source file for AVR LCD in HAL "Hardware Abstract Layer">
 --------------------------------------------------------------------------------------*/

/*----------------------------------------INCLUDES-------------------------------------*/

#include "lcd.h"
#include "gpio.h"
#include <util/delay.h>
#include <stdlib.h>

/*---------------------------------FUNCTIONS DEFINITIONS-------------------------------*/

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	LCD_sendCommand
 * [DESCRIPTION]:	This Function is used to send commands to the LCD mC
 * [ARGS]:
 * [in]		uint8 command :		This Arg shall indicate the sent command
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void LCD_sendCommand(uint8 command)
{
	/* At first we must send some commands to run the lcd
	 * as initiating the mode, turning cursor off, ...
	 * This sequence is known from data sheet (Timing Graph)
	 * 1. RS = 0	(As we transfer command data)
	 * 2. R/W = 0
	 * 3. delay t(as) = 50 ns	~1ms
	 * 4. E = 1
	 * 5. delay t(pw)-t(dsw) = 290-100 = 190 ns	~1ms
	 * 6. send the command
	 * 7. delay t(dsw) = 100 ns	~1ms
	 * 8. E = 0
	 * 9. delay t(h) = 13 ns 	~1ms */
	GPIO_writePin(LCD_PORT, LCD_RS_PIN, LOGIC_LOW);
	GPIO_writePin(LCD_PORT, LCD_RW_PIN, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_PORT, LCD_E_PIN, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePort(LCD_DB_PORT, command);
	_delay_ms(1);
	GPIO_writePin(LCD_PORT, LCD_E_PIN, LOGIC_LOW);
	_delay_ms(1);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	LCD_displayCharacter
 * [DESCRIPTION]:	This Function is used to display a character on the LCD
 * [ARGS]:
 * [in]		uint8 character :	This Arg shall indicate the sent character to display on LCD
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void LCD_displayCharacter(uint8 character)
{
	/* This function sequence is as sendCommand function
	 * except we make RS = 1
	 * This sequence is known from data sheet (Timing Graph)
	 * 1. RS = 1	(As we transfer display data)
	 * 2. R/W = 0
	 * 3. delay t(as) = 50 ns	~1ms
	 * 4. E = 1
	 * 5. delay t(pw)-t(dsw) = 290-100 = 190 ns	~1ms
	 * 6. send the command
	 * 7. delay t(dsw) = 100 ns	~1ms
	 * 8. E = 0
	 * 9. delay t(h) = 13 ns 	~1ms */
	GPIO_writePin(LCD_PORT, LCD_RS_PIN, LOGIC_HIGH);
	GPIO_writePin(LCD_PORT, LCD_RW_PIN, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_PORT, LCD_E_PIN, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePort(LCD_DB_PORT, character);
	_delay_ms(1);
	GPIO_writePin(LCD_PORT, LCD_E_PIN, LOGIC_LOW);
	_delay_ms(1);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	LCD_init
 * [DESCRIPTION]:	This Function is used to initiate the LCD
 * [ARGS]:		No Arguments
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void LCD_init(void)
{
	/* There are some initialization needed for LCD
	 * 1. Set RS, R/W, E pins as output pins
	 * 2. Set DB port as output port
	 * 3. Send command to initiate 2-lines,8-bit mode
	 * 4. Send command to set cursor off
	 * 5. Send command to clear The screen */
	GPIO_setPinDirection(LCD_PORT, LCD_RS_PIN, PIN_OUTPUT);
	GPIO_setPinDirection(LCD_PORT, LCD_RW_PIN, PIN_OUTPUT);
	GPIO_setPinDirection(LCD_PORT, LCD_E_PIN, PIN_OUTPUT);
	GPIO_setPortDirection(LCD_DB_PORT, PORT_OUTPUT);
	LCD_sendCommand(LCD_2LINES_8BITS_MODE);
	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_SCREEN);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	LCD_displayString
 * [DESCRIPTION]:	This Function is used to display a string on the LCD
 * [ARGS]:
 * [in]		uint8 *str :	This Arg shall indicate the sent string to display on LCD
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void LCD_displayString(const char *str)
{
	uint8 i = 0;
	while(str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	LCD_moveCursor
 * [DESCRIPTION]:	This Function is used to move the cursor of the LCD to a specific
 * 					place according to the given row and column from the user
 * [ARGS]:
 * [in]		uint8 row :	This Arg shall indicate the specified row
 * 			uint8 column :	This Arg shall indicate the specified column
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void LCD_moveCursor(uint8 row, uint8 column)
{
	uint8 location;
	/* If the user entered any value bigger than the number of rows or columns */
	if((row >= NUM_OF_ROWS) || (column >= NUM_OF_COLS))
	{
		/* Do Nothing */
	}
	else
	{
		/*
		 * first get into the specified row. then, add the given column number
		 * to the DDRAM address of the LCD to get the location address of the
		 * wanted location. Finally we send command to for the cursor to the beginning
		 * of the first line and add the location to it.
		 */
		switch(row)
		{
		case 0:
			location = column + 0x00;
			break;
		case 1:
			location = column + 0x40;
			break;
		case 2:
			location = column + 0x10;
			break;
		case 3:
			location = column + 0x50;
			break;
		}
		LCD_sendCommand(LCD_SET_CURSOR_AT_BEGIN | location);
	}
}

void LCD_displayStringRowColumn(const char *str, uint8 row, uint8 column)
{
	LCD_moveCursor(row,column);
	LCD_displayString(str);
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_SCREEN);
}

void LCD_integerToString(uint32 integer)
{
	char buffer[16];
	itoa(integer, buffer, 10);
	LCD_displayString(buffer);
}
