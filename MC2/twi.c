/*--------------------------------------------------------------------------------------
 * [FILE NAME]:		<twi.c>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<25/10/2021>
 *
 * [DESCRIPTION]:	<A source file for AVR TWI "I2C" driver>
 --------------------------------------------------------------------------------------*/

/*----------------------------------------INCLUDES-------------------------------------*/
#include "twi.h"
#include "common_macros.h"
#include <avr/io.h>

/*---------------------------------FUNCTIONS DEFINITIONS-------------------------------*/

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TWI_init
 * [DESCRIPTION]:	This Function is used to initiate the TWI module
 * [ARGS]:		const TWI_ConfigType *a_configPtr : This Argument is a pointer to struct,
 * 				it will indicate the struct input for the function
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void TWI_init(const TWI_ConfigType *a_configPtr)
{
	/*
	 * To get the TWI bit rate, apply this equation on TWBR register:
	 * F_SCL = F_CPU / (16 + 2(TWBR) * 4^TWPS
	 * then,
	 * TWBR = ( ((F_CPU/F_SCL) - 16) / (2 * (4^TWPS)) )
	 */
	TWBR = ( ((F_CPU/(a_configPtr->modeFreq)) - 16) / (2 * (4^(a_configPtr->prescalar))) );

	/* Set the prescalar in TWSR register */
	TWSR = (TWSR & 0xFC) | ((a_configPtr->prescalar) & 0x03);

	TWCR = (1<<TWEN);	/* Enable TWI module */

	TWAR = (a_configPtr->address); /* Give the user an address to be able to be called if it's initiated as a slave any time */
	/* <<1 test */
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TWI_start
 * [DESCRIPTION]:	This Function is used to send the start bit to start the TWI operation
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void TWI_start(void)
{
	/*
	 * 1. Clear TWI interrupt flag at first by set a 1 in it
	 * 2. Set TWI START condition bit
	 * 3. Set the TWI enable bit
	 */
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	/* Wait until the Flag is set to 1 as it indicates the the START operation is finished */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TWI_stop
 * [DESCRIPTION]:	This Function is used to send the stop bit to finish the TWI operation
 * [ARGS]:		No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void TWI_stop(void)
{
	/*
	 * 1. Clear TWI interrupt flag at first by set a 1 in it
	 * 2. Set TWI STOP condition bit
	 * 3. Set the TWI enable bit
	 */
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TWI_writeByte
 * [DESCRIPTION]:	This Function is used to send the data bits to the SDA bus
 * [ARGS]:		uint8 data: This Argument indicates the data sent to the SDA bus
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void TWI_writeByte(uint8 data)
{
	TWDR = data;

	/*
	 * 1. Clear TWI interrupt flag at first by set a 1 in it
	 * 2. Set the TWI enable bit
	 */
	TWCR = (1<<TWINT) | (1<<TWEN);

	/* Wait until the Flag is set to 1 as it indicates that the WRITE operation is finished */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TWI_readWithACK
 * [DESCRIPTION]:	This Function is used to read the data sent on The SDA bus then sending
 * 					an ACK bit after finishing this process
 * [ARGS]:		No Arguments
 * [RETURNS]:	This Return indicates the data read from TWI data register
 ----------------------------------------------------------------------------------------*/
uint8 TWI_readWithACK(void)
{
	/*
	 * 1. Clear TWI interrupt flag at first by set a 1 in it
	 * 2. Set TWI enable Acknowledge bit that will enable TWI to send ACK after reading
	 * 	  or receiving data
	 * 3. Set the TWI enable bit
	 */
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);

	/* Wait until the Flag is set to 1 as it indicates that the RECEIVING operation is completed */
	while(BIT_IS_CLEAR(TWCR,TWINT));

	return TWDR;
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TWI_readWithNACK
 * [DESCRIPTION]:	This Function is used to read the data sent on The SDA bus then sending
 * 					an NACK bit or sending nothing after finishing this process.
 * 					This will indicate that the whole operation is finished to stop the
 * 					communication
 * [ARGS]:		No Arguments
 * [RETURNS]:	This Return indicates the data read from TWI data register
 ----------------------------------------------------------------------------------------*/
uint8 TWI_readWithNACK(void)
{
	/*
	 * 1. Clear TWI interrupt flag at first by set a 1 in it
	 * 2. Set TWI enable Acknowledge bit that will enable TWI to send ACK after reading
	 * 	  or receiving data
	 * 3. Set the TWI enable bit
	 */
	TWCR = (1<<TWINT) | (1<<TWEN);

	/* Wait until the Flag is set to 1 as it indicates that the RECEIVING operation is completed */
	while(BIT_IS_CLEAR(TWCR,TWINT));

	return TWDR;
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	TWI_readWithNACK
 * [DESCRIPTION]:	This Function is used to read the status of TWI module, the status code
 * 					is described in the DATASHEET
 * [ARGS]:		No Arguments
 * [RETURNS]:	This Return indicates the status code read from TWI data register
 ----------------------------------------------------------------------------------------*/
uint8 TWI_getStatus(void)
{
	uint8 status;
	/* Mask the status register TWSR with 0b11111000 to eliminate the first 3 bits as we don't need them */
	status = TWSR & 0xF8;

	return status;
}
