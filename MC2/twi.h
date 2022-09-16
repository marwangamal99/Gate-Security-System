/*--------------------------------------------------------------------------
 * [FILE NAME]:		<twi.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<25/10/2021>
 *
 * [DESCRIPTION]:	<A header file for AVR TWI "I2C" driver>
 ---------------------------------------------------------------------------*/

#ifndef TWI_H_
#define TWI_H_

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*-----------------------------TYPES DECLEARATION-----------------------------*/

typedef enum{
	NORMAL=100000, FAST=400000, FAST_PLUS=1000000, HIGH_SPEED=3400000
}TWI_SCLmode;

typedef enum{
	NO_PRESCALAR,FCPU_4,FCPU_16,FCPU_64
}TWI_prescalar;

typedef struct{
	TWI_SCLmode modeFreq;
	TWI_prescalar prescalar;
	uint8 address;
}TWI_ConfigType;

/*-----------------------------PREPROCESSOR MACROS----------------------------*/

#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*-----------------------------FUNCTIONS PROTOTYPES---------------------------*/
/*
 * Description:
 * This Function is used to initiate the TWI module
 */
void TWI_init(const TWI_ConfigType *a_configPtr);


/*
 * Description:
 * This Function is used to send the start bit to start the TWI operation
 */
void TWI_start(void);


/*
 * Description:
 * This Function is used to send the stop bit to finish the TWI operation
 */
void TWI_stop(void);


/*
 * Description:
 * This Function is used to send the data bits to the SDA bus
 */
void TWI_writeByte(uint8 data);


/*
 * Description:
 * This Function is used to read the data sent on The SDA bus then sending
 * an ACK bit after finishing this process
 */
uint8 TWI_readWithACK(void);


/*
 * Description:
 * This Function is used to read the data sent on The SDA bus then sending
 * an NACK bit or sending nothing after finishing this process.
 * This will indicate that the whole operation is finished to stop the
 * communication
 */
uint8 TWI_readWithNACK(void);


/*
 * Description:
 * This Function is used to read the status of TWI module, the status code
 * is described in the DATASHEET
 */
uint8 TWI_getStatus(void);

#endif /* TWI_H_ */
