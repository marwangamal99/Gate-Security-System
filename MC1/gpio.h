/*--------------------------------------------------------------------------
 * [FILE NAME]:		<gpio.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<4/10/2021>
 *
 * [DESCRIPTION]:	<A header file for AVR gpio driver>
 ---------------------------------------------------------------------------*/

#ifndef GPIO_H_
#define GPIO_H_

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*------------------------DEFINITIONS AND CONFIGURATIONS----------------------*/

#define NUM_OF_PORTS			4
#define NUM_OF_PINS_PER_PORT	8

#define PORTA_ID				0
#define PORTB_ID				1
#define PORTC_ID				2
#define PORTD_ID				3

#define PIN0_ID					0
#define PIN1_ID					1
#define PIN2_ID					2
#define PIN3_ID					3
#define PIN4_ID					4
#define PIN5_ID					5
#define PIN6_ID					6
#define PIN7_ID					7

/*-----------------------------TYPES DECLEARATION-----------------------------*/

typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/*-----------------------------FUNCTIONS PROTOTYPES---------------------------*/
/*
 * Description:
 * This function is used to set the direction on a specific pin (i/p or o/p)
 */
void GPIO_setPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);


/*
 * Description:
 * This function is used to write on a specific pin (HIGH or LOW)
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);


/*
 * Description:
 * This function is used to read a specific pin value
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);


/*
 * Description:
 * This function is used to set the direction on a specific PORT (i/p or o/p)
 */
void GPIO_setPortDirection(uint8 port_num, GPIO_PortDirectionType direction);


/*
 * Description:
 * This function is used to write on a specific PORT (HIGH or LOW)
 */
void GPIO_writePort(uint8 port_num, uint8 value);


/*
 * Description:
 * This function is used to read a specific PORT value
 */
uint8 GPIO_readPort(uint8 port_num);

#endif /* GPIO_H_ */
