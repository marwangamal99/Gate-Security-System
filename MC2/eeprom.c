/*--------------------------------------------------------------------------------------
 * [FILE NAME]:		<eeprom.c>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<25/10/2021>
 *
 * [DESCRIPTION]:	<A source file for 24C16 EEPROM driver>
 --------------------------------------------------------------------------------------*/

/*----------------------------------------INCLUDES-------------------------------------*/

#include "eeprom.h"
#include "twi.h"

/*---------------------------------FUNCTIONS DEFINITIONS-------------------------------*/
/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	EEPROM_init
 * [DESCRIPTION]:	This Function is used to initialize external 24C16 EEPROM by initializing
 * 					TWI "I2C" module.
 * [ARGS]:	No Arguments
 * [RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void EEPROM_init(void)
{
	TWI_ConfigType TWI_configuration = {FAST,NO_PRESCALAR,0X01};
	TWI_init(&TWI_configuration);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	EEPROM_writeByte
 * [DESCRIPTION]:	This Function is used to write a data byte in EEPROM.
 * [ARGS]:		uint16 u16address:	This Argument shall indicate the address of location in
 * 									EEPROM we want to write in it.
 * 				uint8 u8data:	This Argument shall indicate the data we want to write in
 * 								EEPROM.
 *	[RETURNS]:	This Return shall indicate the TWI status for every command used
 ----------------------------------------------------------------------------------------*/
uint8 EEPROM_writeByte(uint16 u16address,uint8 u8data)
{
	/*
	 * EEPROM write frame:-
	 * [ S - DeviceAddress - W - ACK - LocationAddress - ACK - Data - ACK - P ]
	 */

	/* Send a start bit then check for the TWI status */
	TWI_start();
	if(TWI_getStatus() != TWI_START)
		return ERROR;

	/* Send the device address bits + Write bit, then check for the TWI status. it will return
	 * ACK bit */
	TWI_writeByte((uint8)((u16address & 0x0700) >> 7) | 0xA0);
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return ERROR;

	/* Send the location address bits, then check for the TWI status. it will return ACK bit */
	TWI_writeByte((uint8)(u16address));
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	/* Send the data bits, then check for the TWI status. it will return ACK bit */
	TWI_writeByte(u8data);
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	/* Send the stop bit to finish the process */
	TWI_stop();

	return SUCCESS;
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	EEPROM_readByte
 * [DESCRIPTION]:	This Function is used to write a data byte in EEPROM.
 * [ARGS]:		uint16 u16address:	This Argument shall indicate the address of location in
 * 									EEPROM we want to read from it.
 * 				uint8 *u8data:	This Argument shall indicate a pointer to character that will
 * 								point to the value we want to read from EEPROM.
 *	[RETURNS]:	This Return shall indicate the TWI status for every command used
 ----------------------------------------------------------------------------------------*/
uint8 EEPROM_readByte(uint16 u16address, uint8 *u8data)
{
	/*
	 * EEPROM write frame:-
	 * [ S - DeviceAddress - W - ACK - LocationAddress - ACK - Sr - DeviceAddress - R - ACK - ReadData - NACK - P ]
	 */

	/* Send a start bit then check for the TWI status */
	TWI_start();
	if(TWI_getStatus() != TWI_START)
		return ERROR;

	/* Send the device address bits + Write bit, then check for the TWI status. it will return
	 * ACK bit */
	TWI_writeByte((uint8)(((u16address & 0x0700) >> 7) | 0xA0));
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return ERROR;

	/* Send the location address bits, then check for the TWI status. it will return ACK bit */
	TWI_writeByte((uint8)(u16address));
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	/* Send the repeated start bit, then check for the TWI status */
	TWI_start();
	if(TWI_getStatus() != TWI_REP_START)
		return ERROR;

	/* Send the device address bits + Read bit, then check for the TWI status. it will return
	 * ACK bit */
	TWI_writeByte((uint8)((((u16address & 0x0700) >> 7) | 1) | 0xA0));
	if(TWI_getStatus() != TWI_MT_SLA_R_ACK)
		return ERROR;

	/* Read the data on the specified memory location, then check for the TWI status. It will finally
	 * return a NACK bit */
	*u8data = TWI_readWithNACK();
	if(TWI_getStatus() != TWI_MR_DATA_NACK)
		return ERROR;

	/* Send the stop bit to finish the process */
	TWI_stop();

	return SUCCESS;
}
