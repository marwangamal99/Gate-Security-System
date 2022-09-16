#include "app1.h"
#include "uart_commands.h"

/* Define the CPU frequency to 8MHz as a confirmation */
#define F_CPU 8000000UL

int main(void)
{
	uint8 state = 0;
	uint8 choice = 0;

	/* Initializing all drivers used in mC1 */
	APP1_init();

	while(1)
	{
		/* Get the state send from mC2, and according to each case
		 * a specific function will be operated */
		state = APP1_stateCheck();
		switch(state)
		{
		case ASK_FOR_NEW_PASSWORD :
			APP1_sendCommand(RECEIVE_NEWEST_PASSWORD);
			APP1_enterNewPassword();
			break;
		case NEWEST_PASSWORD_RECEIVED :
			/* Send Command to mC2 to be ready to receive re-entered password */
			APP1_sendCommand(RECEIVE_RE_ENTERED_PASSWORD);
			APP1_re_enterPassword();
			break;

		case RE_ENTER_PASSWORD :
			/* If the re-entered password is wrong, send it for the first time */
			APP1_sendCommand(RECEIVE_RE_ENTERED_PASSWORD);
			APP1_re_enterPassword();
			break;

		case ENTER_PASSWORD_AGAIN :
			/* If the re-entered password is wrong, send it for the second time */
			APP1_sendCommand(RECEIVE_PASSWORD_2);
			APP1_re_enterPassword();
			break;

		case ENTER_PASSWORD2_AGAIN :
			/* If the re-entered password is wrong again, send it for the third time */
			APP1_sendCommand(RECEIVE_PASSWORD_3);
			APP1_re_enterPassword();
			break;

		case OPEN_MAIN_MENU :
			choice = APP1_mainOptionMenu();
			switch(choice)
			{
			case '+' :
				/* If the user chose '+', start the password enter and check process again */
				APP1_sendCommand(RECEIVE_PASSWORD_IN_MAIN_MENU);
				APP1_re_enterPassword();
				break;
			case '-' :
				/* If the user chose '-', we will repeat the process from the very beginning */
				APP1_sendCommand(RECEIVE_NEWEST_PASSWORD);
				APP1_enterNewPassword();
				break;
			}
			break;

		case ENTER_PASSWORD_AGAIN_MAIN_MENU :
			APP1_sendCommand(RECEIVE_PASSWORD_2_MAIN_MENU);
			APP1_re_enterPassword();
			break;

		case ENTER_PASSWORD2_AGAIN_MAIN_MENU :
			APP1_sendCommand(RECEIVE_PASSWORD_3_MAIN_MENU);
			APP1_re_enterPassword();
			break;

		case OPEN_DOOR :
			APP1_openDoor();
			break;

		case DOOR_IS_OPENED :
			APP1_doorIsOpened();
			break;

		case CLOSE_DOOR :
			APP1_closeDoor();
			break;

		case ALARM_ON :
			APP1_setAlarmON();
			break;

		case SEND_CORRECT :
			APP1_displayCorrect();
			break;

		case SEND_WRONG :
			APP1_displayWrong();
			break;

		}
	}
}

