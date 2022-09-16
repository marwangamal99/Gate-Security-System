/*--------------------------------------------------------------------------
 * [FILE NAME]:		<uart_commands.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<6/11/2021>
 *
 * [DESCRIPTION]:	<A header file for commands sent or received from mC1>
 ---------------------------------------------------------------------------*/

#ifndef UART_COMMANDS_H_
#define UART_COMMANDS_H_

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*------------------------DEFINITIONS AND CONFIGURATIONS----------------------*/

#define	MC2_READY							0x01

#define	ASK_FOR_NEW_PASSWORD				'{'
#define	ASK_FOR_PASSWORD					'}'
#define RECEIVE_NEWEST_PASSWORD				'~'
#define NEWEST_PASSWORD_RECEIVED			'!'
#define RE_ENTER_PASSWORD					':'
#define RECEIVE_RE_ENTERED_PASSWORD			'@'
#define OPEN_MAIN_MENU						'#'
#define	ENTER_PASSWORD_AGAIN				'$'
#define RECEIVE_PASSWORD_2					'%'
#define ENTER_PASSWORD2_AGAIN				'^'
#define RECEIVE_PASSWORD_3					'&'
#define RECEIVE_PASSWORD_IN_MAIN_MENU		'*'
#define ENTER_PASSWORD_AGAIN_MAIN_MENU		'('
#define RECEIVE_PASSWORD_2_MAIN_MENU		')'
#define ENTER_PASSWORD2_AGAIN_MAIN_MENU		'/'
#define RECEIVE_PASSWORD_3_MAIN_MENU		'|'
#define OPEN_DOOR							'['
#define DOOR_IS_OPENED						'.'
#define CLOSE_DOOR							';'
#define ALARM_ON							']'
#define SEND_CORRECT						'>'
#define SEND_WRONG							'<'


#endif /* UART_COMMANDS_H_ */
