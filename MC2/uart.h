/*--------------------------------------------------------------------------
 * [FILE NAME]:		<uart.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<21/10/2021>
 *
 * [DESCRIPTION]:	<A header file for AVR UART driver>
 ---------------------------------------------------------------------------*/

#ifndef UART_H_
#define UART_H_

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*-----------------------------TYPES DECLEARATION-----------------------------*/
typedef enum{
	OFF,RESERVED,EVEN,ODD
}UART_parityMode;

typedef enum{
	FIVE,SIX,SEVEN,EIGHT,RESERVED1,RESERVED2,RESERVED3,NINE
}UART_dataLength;

typedef enum{
	ONE,TWO
}UART_stopBit;

typedef struct{
	UART_parityMode parityBit;
	UART_dataLength bitLength;
	UART_stopBit stopBit;
	uint16 baudRate;
}UART_configType;

/*-----------------------------FUNCTIONS PROTOTYPES---------------------------*/
/*
 * Description:
 * A function responsible for UART driver initialization
 */
void UART_init(UART_configType *configPtr);


/*
 * Description:
 * A function responsible for sending a byte using UART
 */
void UART_sendByte(uint8 byte);


/*
 * Description:
 * A function responsible for receiving a byte using UART
 */
uint8 UART_receiveByte(void);


/*
 * Description:
 * A function responsible for sending a string of bytes using UART
 */
void UART_sendString(const uint8 *str);


/*
 * Description:
 * A function responsible for receiving a string of bytes using UART
 */
void UART_receiveString(uint8 *str);

#endif /* UART_H_ */
