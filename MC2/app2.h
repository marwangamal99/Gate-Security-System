/*--------------------------------------------------------------------------
 * [FILE NAME]:		<app2.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<4/11/2021>
 *
 * [DESCRIPTION]:	<A header file for the Application Layer for mC2>
 ---------------------------------------------------------------------------*/

#ifndef APP2_H_
#define APP2_H_

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*------------------------DEFINITIONS AND CONFIGURATIONS----------------------*/

#define PASSWORD_SIZE		7
#define EEPROM_START_BYTE	0x3E8

/*----------------------------------EXTERNS-----------------------------------*/

extern uint8 g_pass_check;
extern uint8 password_size;
extern uint8 TIMER1_flagComplete;

/*-----------------------------FUNCTIONS PROTOTYPES---------------------------*/

/*
 * Description:
 * This Function is used to initialize the Application layer which contains
 * HAL, UART Drivers
 */
void APP2_init(void);


/*
 * Description:
 * This Function is used to check if the entered password is for the first
 * time or not.
 */
void APP2_checkForFirstTime(void);



/*
 * Description:
 * This Function is used to receive password sent from mC1
 */
void APP2_receivePassword(void);


/*
 * Description:
 * This Function is used to receive commands sent from mC1
 */
uint8 APP2_receiveCommand(void);


/*
 * Description:
 * This Function is used to check the validity of the re-entered password
 * by comparing it to the saved password in EEPROM
 */
uint8 APP2_checkPassword(void);


/*
 * Description:
 * This Function is used to receive and check for the validity of the entered
 * password for the first time
 */
void APP2_receiveAndCheckPassword(void);


/*
 * Description:
 * This Function is used to receive and check for the validity of the entered
 * password for the second time
 */
void APP2_receiveAndCheckPassword2(void);


/*
 * Description:
 * This Function is used to receive and check for the validity of the entered
 * password for the third time
 */
void APP2_receiveAndCheckPassword3(void);


/*
 * Description:
 * This Function is used to receive and check for the validity of the entered
 * password in the main menu in the Door open option for the first time
 */
void APP2_receiveAndCheckPassword_mainMenu(void);


/*
 * Description:
 * This Function is used to receive and check for the validity of the entered
 * password in the main menu in the Door open option for the second time
 */
void APP2_receiveAndCheckPassword2_mainMenu(void);


/*
 * Description:
 * This Function is used to receive and check for the validity of the entered
 * password in the main menu in the Door open option for the third time
 */
void APP2_receiveAndCheckPassword3_mainMenu(void);


/*
 * Description:
 * This Function is used to open the door by operating the motor in CW
 * direction
 */
void APP2_openDoor(void);


/*
 * Description:
 * This Function is used to stop motor operation
 */
void APP2_doorStop(void);


/*
 * Description:
 * This Function is used to close the door by operating the motor in CCW
 * direction
 */
void APP2_closeDoor(void);


/*
 * Description:
 * This Function is used set the ALARM on
 */
void APP2_setAlarmON(void);


/*
 * Description:
 * This Function is used to count ticks for Timer1 driver, the function
 * will set the Timer1 flag to 1 if the ticks are equal to the input
 * milliseconds
 */
void TIMER1_countProcessing(uint16 g_msec1);


/*
 * Description:
 * This Function is used to give a delay process according to the give
 * milliseconds
 */
void TIMER1_delay_ms(uint16 seconds);

#endif /* APP_H_ */
