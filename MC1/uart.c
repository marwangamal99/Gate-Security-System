/*--------------------------------------------------------------------------------------
 * [FILE NAME]:		<uart.c>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<21/10/2021>
 *
 * [DESCRIPTION]:	<A source file for AVR UART driver>
 --------------------------------------------------------------------------------------*/
/*----------------------------------------INCLUDES-------------------------------------*/

#include "uart.h"
#include "common_macros.h"
#include <avr/io.h>

/*---------------------------------FUNCTIONS DEFINITIONS-------------------------------*/
/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	UART_init
 * [DESCRIPTION]:	This Function is used to initialize the UART module
 * [ARGS]:		UART_configuration *configPtr: 	a pointer to struct to pass over the struct
 * 												variables for UART module.
 * 				uint16 baud_rate: This Argument shall indicate the baud rate of UART module.
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void UART_init(UART_configType *configPtr)
{
	uint32 ubrr_value = 0;

	/* Set the U2X bit to 1 to double the transmission speed */
	SET_BIT(UCSRA,U2X);

	/* Set the Receive and Transmit Enable bits to 1 */
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);

	UCSRC = (UCSRC & 0xCF) | ((configPtr->parityBit)<<4);
	UCSRC = (UCSRC & 0xF7) | ((configPtr->stopBit)<<3);

	/* The bitLength consists of 3 bits, 2 in UCSRC register "UCSZ0,UCSZ1"
	 * and the third bit is in UCSRB register "UCSZ2" */
	UCSRC = (UCSRC & 0xF9) | ((configPtr->bitLength)<<2);
	UCSRB = (UCSRB & 0xFB) | (((configPtr->bitLength) & 0x04)<<2);

	/* Calculate the baud rate and set it in the UBRR registers */
	ubrr_value =(( (F_CPU / ( 8 * (configPtr->baudRate) )) ) - 1);
	UBRRH = (uint8) (ubrr_value>>8);
	UBRRL = (uint8) (ubrr_value);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	UART_sendByte
 * [DESCRIPTION]:	This Function is used to send data bytes
 * [ARGS]:		uint8 byte:	This Argument shall indicate the data byte to be sent
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void UART_sendByte(uint8 byte)
{
	/* Wait until the UART data register empty flag bit "UDRE" = 0,
	 * this bit is set to one when the transmit buffer is ready to receive
	 * new data  */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	UDR = byte;
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	UART_receiveByte
 * [DESCRIPTION]:	This Function is used to receive data bytes
 * [ARGS]:		No Arguments
 * [RETURNS]:	The return shall indicates the received data byte
 ----------------------------------------------------------------------------------------*/
uint8 UART_receiveByte(void)
{
	/* Wait until the UART receive complete flag bit "RXC" = 1,
	* this bit is set to one when the UART finish receiving data */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	return UDR;
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	UART_sendString
 * [DESCRIPTION]:	This Function is used to send strings, character by character
 * [ARGS]:		const uint8 *str: 	This Argument shall indicates a pointer to character
 * 									that will pass over each character in the string and
 * 									send it.
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void UART_sendString(const uint8 *str)
{
	uint8 i = 0;
	while(str[i] != '\0')
	{
		UART_sendByte(str[i]);
		i++;
	}
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	UART_receiveString
 * [DESCRIPTION]:	This Function is used to receive strings, character by character
 * [ARGS]:		const uint8 *str: 	This Argument shall indicates a pointer to character
 * 									that will pass over each character in the string and
 * 									receive it until it reaches the # character.
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void UART_receiveString(uint8 *str)
{
	uint8 i = 0;
	str[i] = UART_receiveByte();

	while(str[i] != '#')
	{
		i++;
		str[i] = UART_receiveByte();
	}

	str[i] = '\0';
}
