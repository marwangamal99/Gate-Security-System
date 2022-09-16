/*--------------------------------------------------------------------------
 * [FILE NAME]:		<eeprom.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<25/10/2021>
 *
 * [DESCRIPTION]:	<A header file for 24C16 EEPROM driver>
 ---------------------------------------------------------------------------*/

#ifndef EEPROM_H_
#define EEPROM_H_

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*-----------------------------PREPROCESSOR MACROS----------------------------*/

#define ERROR	    0
#define SUCCESS		1

#define EEPROM_FRAME_DELAY					500

#define PASSWORD_FIRST_TIME					255
#define PASSWORD_NOT_FIRST_TIME				0
#define	EEPROM_PASS_SIZE					0x1F4
#define	EEPROM_PASS_ADDRESS					0x3E8	/* Set an adress of 1000 as an Example */
#define EEPROM_ADDRESS_FLAG					0x0C8

/*-----------------------------FUNCTIONS PROTOTYPES---------------------------*/
/*
 * Description:
 * This Function is used to initialize external 24C16 EEPROM by initializing
 * TWI "I2C" module.
 */
void EEPROM_init(void);


/*
 * Description:
 * This Function is used to write a data byte in EEPROM
 */
uint8 EEPROM_writeByte(uint16 u16address,uint8 u8data);


/*
 * Description:
 * This Function is used to write a data byte in EEPROM
 */
uint8 EEPROM_readByte(uint16 u16address, uint8 *u8data);

#endif /* EEPROM_H_ */
