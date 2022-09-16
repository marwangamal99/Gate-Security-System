/*--------------------------------------------------------------------------------------
 * [FILE NAME]:		<app2.c>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<4/11/2021>
 *
 * [DESCRIPTION]:	<A source file for the Application Layer for mC2>
 --------------------------------------------------------------------------------------*/

/*----------------------------------------INCLUDES-------------------------------------*/

#include "app2.h"

#include "uart.h"
#include "timer.h"
#include <util/delay.h>

#include "eeprom.h"
#include "buzzer.h"
#include "dcmotor.h"

#include "uart_commands.h"

/*------------------------------------GLOBAL VARIABLES----------------------------------*/

static volatile uint8 password[PASSWORD_SIZE];
static volatile uint8 re_password[PASSWORD_SIZE];

uint8 g_pass_check = PASSWORD_FIRST_TIME;
uint8 password_size = 0;
uint8 re_password_size = 0;

uint8 TIMER1_flagComplete = 0;
/*---------------------------------FUNCTIONS DEFINITIONS-------------------------------*/
/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP2_init
 * [DESCRIPTION]:	This Function is used to initialize the Application layer which contains
 * 					HAL, UART Drivers
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP2_init(void)
{
	/*
	 * UART configuration :
	 * Parity bits: No bits
	 * Data length: 8 bits
	 * Number of stop bits: 1
	 * Baud Rate: 19200
	 */
	UART_configType UART_config = {OFF, EIGHT, ONE, 19200};
	UART_init(&UART_config);

	/* Initializing the hardware drivers */
	EEPROM_init();
	BUZZER_init();
	DcMotor_Init();
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP2_checkForFirstTime
 * [DESCRIPTION]:	This Function is used to check if the entered password is for the first
 * 					time or not.
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP2_checkForFirstTime(void)
{
	uint8 i = 0;

	/* Read the EEPROM password check flag whether it's 0 or 1
	 * 0: It's the first time for the user to enter the password in EEPROM
	 * 1: The user entered a password in EEPROM before */
	EEPROM_readByte(EEPROM_ADDRESS_FLAG, &g_pass_check);
	_delay_ms(EEPROM_FRAME_DELAY);

	/* if the user is entering the password for the first time, the flag
	 * would by 0. Else if the user entered the password before, the flag
	 * will be 1 */
	if(g_pass_check == PASSWORD_FIRST_TIME)
	{
		UART_sendByte(ASK_FOR_NEW_PASSWORD);
	}
	else
	{
		/*
		 * If the password is entered in the EEPROM before, enter EEPROM
		 * to get password, password size, and send a confirmation
		 */
		EEPROM_readByte(EEPROM_PASS_SIZE, &password_size);
		_delay_ms(EEPROM_FRAME_DELAY);
		do
		{
			EEPROM_readByte(EEPROM_PASS_ADDRESS+i,&password[i]);
			_delay_ms(EEPROM_FRAME_DELAY);
			i++;
		}while(i<password_size);
		UART_sendByte(RE_ENTER_PASSWORD);
	}
}


/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP2_receivePassword
 * [DESCRIPTION]:	This Function is used to receive password sent from mC1
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP2_receivePassword(void)
{
	uint8 i = 0;
	/* Set the password check flag to (NOT FIRST TIME) to describe that the password
	 * is set before for further accessing */
	g_pass_check = PASSWORD_NOT_FIRST_TIME;
	EEPROM_writeByte(EEPROM_ADDRESS_FLAG, g_pass_check);
	_delay_ms(EEPROM_FRAME_DELAY);

	UART_receiveString(password);

	while(password[i] != '\0')
	{
		EEPROM_writeByte( EEPROM_START_BYTE+i , password[i]);
		_delay_ms(EEPROM_FRAME_DELAY);
		i++;
	}
	/* Set the given password size in a global variable called password_size */
	password_size = i;

	/* Write the password size in EEPROM_PASS_SIZE location */
	EEPROM_writeByte(EEPROM_PASS_SIZE, i);
	_delay_ms(EEPROM_FRAME_DELAY);

	/* Send UART command to tell mC1 that the new password is received to initiate
	 * further processes */
	UART_sendByte(NEWEST_PASSWORD_RECEIVED);
}


/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP2_receiveCommand
 * [DESCRIPTION]:	This Function is used to receive commands sent from mC1
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
uint8 APP2_receiveCommand(void)
{
	return UART_receiveByte();
}


/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP2_receiveCommand
 * [DESCRIPTION]:	This Function is used to check the validity of the re-entered password
 * 					by comparing it to the saved password in EEPROM
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
uint8 APP2_checkPassword(void)
{
	uint8 flag = TRUE;
	uint8 i = 0;
	if(re_password_size != password_size)
	{
		flag = FALSE;
	}
	else
	{
		while(password[i] != '\0')
		{
			if(re_password[i] != password[i])
			{
				flag = FALSE;
				break;
			}
			i++;
		}
	}
	return flag;
}


/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP2_receiveAndCheckPassword
 * [DESCRIPTION]:	This Function is used to receive and check for the validity of the entered
 * 					password for the first time
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP2_receiveAndCheckPassword(void)
{
	uint8 counter = 0;

	UART_receiveString(re_password);

	/* A loop to get the size of the re-entered password to use it in
	 * checking for re-password validity */
	while(re_password[counter] != '\0')
	{
		counter++;
	}
	re_password_size = counter;

	switch(APP2_checkPassword())
	{
	case TRUE :
		/* Hand shaking method is used to send a command to mC1 that the password
		 * is correct to display on LCD screen then wait mC1 to send that it finished
		 * displaying the message. Also same goes for wrong password */
		UART_sendByte(SEND_CORRECT);
		while(UART_receiveByte() != SEND_CORRECT){}
		UART_sendByte(OPEN_MAIN_MENU);
		break;
	case FALSE :
		UART_sendByte(SEND_WRONG);
		while(UART_receiveByte() != SEND_WRONG){}
		UART_sendByte(ENTER_PASSWORD_AGAIN);
		break;
	}
}


/*-----------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP2_receiveAndCheckPassword2
 * [DESCRIPTION]:	This Function is used to receive and check for the validity of the entered
 * 					password for the second time
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP2_receiveAndCheckPassword2(void)
{
	uint8 counter = 0;
	UART_receiveString(re_password);

	while(re_password[counter] != '\0')
	{
		counter++;
	}
	re_password_size = counter;

	switch(APP2_checkPassword())
	{
	case TRUE :
		UART_sendByte(SEND_CORRECT);
		while(UART_receiveByte() != SEND_CORRECT){}
		UART_sendByte(OPEN_MAIN_MENU);
		break;
	case FALSE :
		UART_sendByte(SEND_WRONG);
		while(UART_receiveByte() != SEND_WRONG){}
		UART_sendByte(ENTER_PASSWORD2_AGAIN);
		break;
	}
}


/*-----------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP2_receiveAndCheckPassword3
 * [DESCRIPTION]:	This Function is used to receive and check for the validity of the entered
 * 					password for the third time
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP2_receiveAndCheckPassword3(void)
{
	uint8 counter = 0;
	UART_receiveString(re_password);

	while(re_password[counter] != '\0')
	{
		counter++;
	}
	re_password_size = counter;

	switch(APP2_checkPassword())
	{
	case TRUE :
		UART_sendByte(SEND_CORRECT);
		while(UART_receiveByte() != SEND_CORRECT){}
		UART_sendByte(OPEN_MAIN_MENU);
		break;
	case FALSE :
		APP2_setAlarmON();
		break;
	}
}


/*-----------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP2_receiveAndCheckPassword_mainMenu
 * [DESCRIPTION]:	This Function is used to receive and check for the validity of the entered
 * 					password in the main menu in the Door open option for the first time
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP2_receiveAndCheckPassword_mainMenu(void)
{
	UART_receiveString(re_password);

	switch(APP2_checkPassword())
	{
	case TRUE :
		UART_sendByte(SEND_CORRECT);
		while(UART_receiveByte() != SEND_CORRECT){}
		APP2_openDoor();
		APP2_doorStop();
		APP2_closeDoor();
		break;
	case FALSE :
		UART_sendByte(SEND_WRONG);
		while(UART_receiveByte() != SEND_WRONG){}
		UART_sendByte(ENTER_PASSWORD_AGAIN_MAIN_MENU);
		break;
	}
}


/*-----------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP2_receiveAndCheckPassword2_mainMenu
 * [DESCRIPTION]:	This Function is used to receive and check for the validity of the entered
 * 					password in the main menu in the Door open option for the second time
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP2_receiveAndCheckPassword2_mainMenu(void)
{
	UART_receiveString(re_password);

	switch(APP2_checkPassword())
	{
	case TRUE :
		UART_sendByte(SEND_CORRECT);
		while(UART_receiveByte() != SEND_CORRECT){}
		APP2_openDoor();
		APP2_doorStop();
		APP2_closeDoor();
		break;
	case FALSE :
		UART_sendByte(SEND_WRONG);
		while(UART_receiveByte() != SEND_WRONG){}
		UART_sendByte(ENTER_PASSWORD2_AGAIN_MAIN_MENU);
		break;
	}
}


/*-----------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP2_receiveAndCheckPassword3_mainMenu
 * [DESCRIPTION]:	This Function is used to receive and check for the validity of the entered
 * 					password in the main menu in the Door open option for the third time
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP2_receiveAndCheckPassword3_mainMenu(void)
{
	UART_receiveString(re_password);

	switch(APP2_checkPassword())
	{
	case TRUE :
		UART_sendByte(SEND_CORRECT);
		while(UART_receiveByte() != SEND_CORRECT){}
		APP2_openDoor();
		APP2_doorStop();
		APP2_closeDoor();
		break;
	case FALSE :
		APP2_setAlarmON();
		break;
	}
}


/*-----------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP2_openDoor
 * [DESCRIPTION]:	This Function is used to open the door by operating the motor in CW
 * 					direction
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP2_openDoor(void)
{
	UART_sendByte(OPEN_DOOR);

	/* Open Door process */
	DcMotor_Rotate(CW,75);
	TIMER1_delay_ms(15000);
	DcMotor_deInit();
}


/*-----------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP2_doorStop
 * [DESCRIPTION]:	This Function is used to stop motor operation
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP2_doorStop(void)
{
	UART_sendByte(DOOR_IS_OPENED);

	/* Stop Door process */
	DcMotor_Rotate(STOP,0);
	TIMER1_delay_ms(3000);
	DcMotor_deInit();
}


/*-----------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP2_closeDoor
 * [DESCRIPTION]:	This Function is used to close the door by operating the motor in CCW
 * 					direction
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP2_closeDoor(void)
{
	UART_sendByte(CLOSE_DOOR);

	/* Close Door process */
	DcMotor_Rotate(CCW,75);
	TIMER1_delay_ms(15000);
	DcMotor_deInit();

	UART_sendByte(OPEN_MAIN_MENU);
}


/*-----------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	APP2_closeDoor
 * [DESCRIPTION]:	This Function is used set the ALARM on
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void APP2_setAlarmON(void)
{
	UART_sendByte(ALARM_ON);

	/* ALARM ON process */
	BUZZER_ON();
	TIMER1_delay_ms(60000);
	BUZZER_OFF();

	UART_sendByte(NEWEST_PASSWORD_RECEIVED);
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
	/*
	 * Timer is initialized here because we need to init then de-init it
	 * after each function.
	 * As we're using a prescalar of 64, then every count takes 8 u.sec,
	 * so we need 125 counts to get 1 m.sec
	 */
	TIMER_ConfigType TIMER1_config = {TIMER1,0,0,CTC_T1,CHANNEL_A,FCPU_64_T1,0,0,0,125};
	TIMER_init(&TIMER1_config);
	TIMER1_setCallBack(TIMER1_countProcessing);

	g_tick1 = 0;
	g_msec1 = seconds;

	while(TIMER1_flagComplete != 1){}
	TIMER1_flagComplete = 0;

	TIMER1_deInit();
}
