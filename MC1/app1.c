/*--------------------------------------------------------------------------------------
 * [FILE NAME]:		<app1.c>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<2/11/2021>
 *
 * [DESCRIPTION]:	<A source file for the Application Layer for mC1>
 --------------------------------------------------------------------------------------*/

/*----------------------------------------INCLUDES-------------------------------------*/

#include "app1.h"

#include "uart.h"
#include <util/delay.h>
#include "timer.h"

#include "keypad.h"
#include "lcd.h"

#include "uart_commands.h"

/*------------------------------------GLOBAL VARIABLES----------------------------------*/

/* A flag used for the Timer1 */
uint8 TIMER1_flagComplete = 0;

/*---------------------------------FUNCTIONS DEFINITIONS--------------------------------*/
/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP1_init
 * [DESCRIPTION]:	This Function is used to initialize the Application layer which contains
 * 					HAL, Timer, UART Drivers
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP1_init(void)
{
	/* As we're using a prescalar of 64, then every count takes 8 u.sec,
	 * so we need 125 counts to get 1 millisecond */

	TIMER_ConfigType TIMER1_config = {TIMER1,0,0,CTC_T1,CHANNEL_A,FCPU_64_T1,0,0,0,125};
	TIMER_init(&TIMER1_config);
	TIMER1_setCallBack(TIMER1_countProcessing);

	/*
	 * UART configuration :
	 * Parity bits: No bits
	 * Data length: 8 bits
	 * Number of stop bits: 1
	 * Baud Rate: 19200
	 */
	UART_configType UART_config = {OFF, EIGHT, ONE, 19200};
	UART_init(&UART_config);

	/* Initializing the LCD driver */
	LCD_init();
}


/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP1_enterNewPassword
 * [DESCRIPTION]:	This Function is used to get the Newest password from the user and send
 * 					it to mC2
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP1_enterNewPassword(void)
{
	LCD_clearScreen();
	LCD_displayString("Enter New Pass:");
	LCD_moveCursor(1,0);

	/*
	 * Get the password entered until the user press Enter key
	 * if Enter key is pressed, set a # symbol at the end the
	 * send it by UART
	 */
	uint8 password[PASSWORD_SIZE];
	for(uint8 i=0; i<PASSWORD_SIZE; i++)
	{
		_delay_ms(KEYPAD_DELAY);
		if(KEYPAD_getPressedKey() != ENTER_KEY)
		{
			password[i] = KEYPAD_getPressedKey();
			/* delay function for the keypad */
			_delay_ms(KEYPAD_DELAY);
			LCD_displayCharacter('*');
		}
		else if(KEYPAD_getPressedKey() == ENTER_KEY)
		{
			password[i] = '#';
			UART_sendString(password);
			break;
		}
	}
	UART_sendString(password);
}


/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP1_stateCheck
 * [DESCRIPTION]:	This Function is used to check for the state received from mC2
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
uint8 APP1_stateCheck(void)
{
	/* Receive states from mC2 */
	return UART_receiveByte();
}


/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP1_sendCommand
 * [DESCRIPTION]:	This Function is used to send commands to mC2 from mC1
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP1_sendCommand(uint8 command)
{
	/* Send Commands to mC2 */
	UART_sendByte(command);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP1_re_enterPassword
 * [DESCRIPTION]:	This Function is used to get the re-entered password from the user and
 * 					send it to mC2
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP1_re_enterPassword(void)
{
	LCD_clearScreen();
	LCD_displayString("Re-enter Pass:");
	LCD_moveCursor(1,0);

	/*
	 * Get the re-entered password entered until the user press Enter key
	 * if Enter key is pressed, set a # symbol at the end the
	 * send it by UART
	 */
	uint8 re_password[PASSWORD_SIZE];
	for(uint8 i=0; i<PASSWORD_SIZE; i++)
	{
		_delay_ms(KEYPAD_DELAY);
		if(KEYPAD_getPressedKey() != ENTER_KEY)
		{
			re_password[i] = KEYPAD_getPressedKey();
			_delay_ms(KEYPAD_DELAY);
			LCD_displayCharacter('*');
		}
		else if(KEYPAD_getPressedKey() == ENTER_KEY)
		{
			re_password[i] = '#';
			UART_sendString(re_password);
			break;
		}
	}
	UART_sendString(re_password);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP1_mainOptionMenu
 * [DESCRIPTION]:	This Function is used to display the main menu to the user and receive
 * 					the choice of the user to send it by UART to mC2
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
uint8 APP1_mainOptionMenu(void)
{
	uint8 choice = 0;
	LCD_clearScreen();
	LCD_displayStringRowColumn("+: Open Door",0 ,0);
	LCD_displayStringRowColumn("-: Change Pass",1 ,0);
	_delay_ms(KEYPAD_DELAY);
	choice = KEYPAD_getPressedKey();
	_delay_ms(KEYPAD_DELAY);
	return choice;
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP1_mainOptionMenu
 * [DESCRIPTION]:	This Function is used to display that the Door is opening
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP1_openDoor(void)
{
	LCD_clearScreen();
	LCD_displayString("Door OPENING...");
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP1_doorIsOpened
 * [DESCRIPTION]:	This Function is used to display that the Door is opened successfully
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP1_doorIsOpened(void)
{
	LCD_clearScreen();
	LCD_displayString(" Door is OPENED");
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP1_closeDoor
 * [DESCRIPTION]:	This Function is used to display that the Door is closing
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP1_closeDoor(void)
{
	LCD_clearScreen();
	LCD_displayString("Door CLOSING...");
}


/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP1_setAlarmON
 * [DESCRIPTION]:	This Function is used to display that the Alarm is sent off
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP1_setAlarmON(void)
{
	LCD_clearScreen();
	LCD_displayString("WARNING !!");
}


/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP1_displayCorrect
 * [DESCRIPTION]:	This Function is used to display that the Password sent is correct
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP1_displayCorrect(void)
{
	LCD_clearScreen();
	LCD_displayString("Password Correct");
	_delay_ms(5000);
	UART_sendByte(SEND_CORRECT);
}


/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP1_displayWrong
 * [DESCRIPTION]:	This Function is used to display that the Password sent is correct
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP1_displayWrong(void)
{
	LCD_clearScreen();
	LCD_displayString("Password Wrong!");
	_delay_ms(5000);
	UART_sendByte(SEND_WRONG);
}
/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TIMER1_countProcessing
 * [DESCRIPTION]:	This Function is used to count ticks for Timer1 driver, the function
 * 					will set the Timer1 flag to 1 if the ticks are equal to the input
 * 					milliseconds
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void TIMER1_countProcessing(uint16 g_msec1)
{
	g_tick1++;
	if(g_tick1 == g_msec1)
	{
		TIMER1_flagComplete = 1;
		g_tick1 = 0;
	}
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TIMER1_delay_ms
 * [DESCRIPTION]:	This Function is used to give a delay process according to the give
 * 					milliseconds
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void TIMER1_delay_ms(uint16 seconds)
{
	g_tick1 = 0;
	g_msec1 = seconds;

	while(TIMER1_flagComplete != 1){}
	TIMER1_flagComplete = 0;
}
