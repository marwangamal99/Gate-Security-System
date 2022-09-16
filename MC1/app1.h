/*--------------------------------------------------------------------------
 * [FILE NAME]:		<app1.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<2/11/2021>
 *
 * [DESCRIPTION]:	<A header file for the Application Layer for mC1>
 -----------------------------------------------------------------------------*/

#ifndef APP1_H_
#define APP1_H_

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*------------------------------------EXTERNS---------------------------------*/

extern uint8 TIMER1_flagComplete;

/*------------------------DEFINITIONS AND CONFIGURATIONS----------------------*/

#define PASSWORD_SIZE		7

/*----------------------------FUNCTIONS PROTOTYPES----------------------------*/
/*
 * Description:
 * This Function is used to initialize the Application layer which contains
 * HAL, Timer, UART Drivers
 */
void APP1_init(void);


/*
 * Description:
 * This Function is used to get the Newest password from the user and send
 * it to mC2
 */
void APP1_enterNewPassword(void);


/*
 * Description:
 * This Function is used to check for the state received from mC2
 */
uint8 APP1_stateCheck(void);


/*
 * Description:
 * This Function is used to send commands to mC2 from mC1
 */
void APP1_sendCommand(uint8 command);


/*
 * Description:
 * This Function is used to get the re-entered password from the user and
 * send it to mC2
 */
void APP1_re_enterPassword(void);


/*
 * Description:
 * This Function is used to display the main menu to the user and receive
 * the choice of the user to send it by UART to mC2
 */
uint8 APP1_mainOptionMenu(void);


/*
 * Description:
 * This Function is used to display that the Door is opening
 */
void APP1_openDoor(void);


/*
 * Description:
 * This Function is used to display that the Door is opened successfully
 */
void APP1_doorIsOpened(void);


/*
 * Description:
 * This Function is used to display that the Door is closing
 */
void APP1_closeDoor(void);


/*
 * Description:
 * This Function is used to display that the Alarm is sent off
 */
void APP1_setAlarmON(void);


/*
 * Description:
 * This Function is used to display that the Password sent is correct
 */
void APP1_displayCorrect(void);


/*
 * Description:
 * This Function is used to display that the Password sent is wrong
 */
void APP1_displayWrong(void);


/*
 * Description:
 * This Function is used to count ticks for Timer1 driver, the function
 * will set the Timer1 flag to 1 if the ticks are equal to the input
 * milliseconds
 */
void TIMER1_countProcessing(uint16 g_seconds1);


/*
 * Description:
 * This Function is used to give a delay process according to the give
 * milliseconds
 */
void TIMER1_delay_ms(uint16 seconds);

#endif /* APP_H_ */
