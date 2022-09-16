#include "app2.h"
#include "uart_commands.h"

/* Define the CPU frequency to 8MHz as a confirmation */
#define F_CPU 8000000UL

int main(void)
{
	uint8 command = 0;

	APP2_init();

	/* Check for password existence in the EEPROM or not */
	APP2_checkForFirstTime();

	while(1)
	{
		/* Receive commands from mC1 */
		command = APP2_receiveCommand();

		switch(command)
		{
		case RECEIVE_NEWEST_PASSWORD :
			APP2_receivePassword();
			break;

		case RECEIVE_RE_ENTERED_PASSWORD :
			/* Take the re-entered password and check it if it's valid or not and continue the operation */
			APP2_receiveAndCheckPassword();
			break;

		case RECEIVE_PASSWORD_2 :
			/* Receive the password given for the second time and check its validity */
			APP2_receiveAndCheckPassword2();
			break;

		case RECEIVE_PASSWORD_3 :
			/* Receive the password given for the Third time and check its validity,
			 * this is the function that will operate the BUZZER is wrong pass is given */
			APP2_receiveAndCheckPassword3();
			break;

		case RECEIVE_PASSWORD_IN_MAIN_MENU :
			APP2_receiveAndCheckPassword_mainMenu();
			break;

		case RECEIVE_PASSWORD_2_MAIN_MENU:
			APP2_receiveAndCheckPassword2_mainMenu();
			break;

		case RECEIVE_PASSWORD_3_MAIN_MENU :
			APP2_receiveAndCheckPassword3_mainMenu();
			break;

		case OPEN_DOOR :
			APP2_openDoor();
			break;

		case CLOSE_DOOR :
			APP2_closeDoor();
			break;
		}
	}
}
