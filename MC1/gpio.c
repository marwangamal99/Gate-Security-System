/*--------------------------------------------------------------------------------------
 * [FILE NAME]:		<gpio.c>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<4/10/2021>
 *
 * [DESCRIPTION]:	<A source file for AVR gpio driver>
 --------------------------------------------------------------------------------------*/

/*----------------------------------------INCLUDES-------------------------------------*/
#include "gpio.h"
#include "common_macros.h"
#include <avr/io.h>

/*---------------------------------FUNCTIONS DEFINITIONS-------------------------------*/

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	GPIO_setPinDirection
 * [DESCRIPTION]:	This Function is used to set the direction of pin whether it's input
 * 					or output
 * [ARGS]:
 * [in]		uint8 port_num :	This Arg shall indicate the register port number
 * 			uint8 pin_num : 	This Arg shall indicate the register pin number in the
 * 							    specified port
 * 			GPIO_PinDirectionType direction :	This Arg shall indicate the direction of
 * 												the pin
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void GPIO_setPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
	if((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT))
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRA,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRA,pin_num);
			}
			break;
		case PORTB_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRB,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRB,pin_num);
			}
			break;
		case PORTC_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRC,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRC,pin_num);
			}
			break;
		case PORTD_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRD,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRD,pin_num);
			}
			break;
		}
	}
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	GPIO_writePin
 * [DESCRIPTION]:	This Function is used to write in the pin HIGH or LOW
 * [ARGS]:
 * [in]		uint8 port_num :	This Arg shall indicate the register port number
 * 			uint8 pin_num : 	This Arg shall indicate the register pin number in the
 * 							    specified port
 * 			uint8 value :		This Arg shall indicate the value of the pin
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	if((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT))
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTA,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTA,pin_num);
			}
			break;
		case PORTB_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTB,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTB,pin_num);
			}
			break;
		case PORTC_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTC,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTC,pin_num);
			}
			break;
		case PORTD_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTD,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTD,pin_num);
			}
			break;
		}
	}
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	GPIO_readPin
 * [DESCRIPTION]:	This Function is used to read from the pin
 * [ARGS]:
 * [in]		uint8 port_num :	This Arg shall indicate the register port number
 * 			uint8 pin_num : 	This Arg shall indicate the register pin number in the
 * 							    specified port
 *	[RETURNS]:	The function returns the value on the pin (High or Low)
 ----------------------------------------------------------------------------------------*/
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	uint8 pinValue = LOGIC_LOW;
	if((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT))
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(BIT_IS_SET(PINA,pin_num))
			{
				pinValue = LOGIC_HIGH;
			}
			else
			{
				pinValue = LOGIC_LOW;
			}
			break;
		case PORTB_ID:
			if(BIT_IS_SET(PINB,pin_num))
			{
				pinValue = LOGIC_HIGH;
			}
			else
			{
				pinValue = LOGIC_LOW;
			}
			break;
		case PORTC_ID:
			if(BIT_IS_SET(PINC,pin_num))
			{
				pinValue = LOGIC_HIGH;
			}
			else
			{
				pinValue = LOGIC_LOW;
			}
			break;
		case PORTD_ID:
			if(BIT_IS_SET(PIND,pin_num))
			{
				pinValue = LOGIC_HIGH;
			}
			else
			{
				pinValue = LOGIC_LOW;
			}
			break;
		}
	}
	return pinValue;
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	GPIO_setPortDirection
 * [DESCRIPTION]:	This Function is used to set the direction of port whether it's all
 * 					input or output
 * [ARGS]:
 * [in]		uint8 port_num :	This Arg shall indicate the register port number
 * 			GPIO_PinDirectionType direction :	This Arg shall indicate the direction of
 * 												the pin
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void GPIO_setPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	GPIO_writePort
 * [DESCRIPTION]:	This Function is used to write in the PORT
 * [ARGS]:
 * [in]		uint8 port_num :	This Arg shall indicate the register port number
 * 			uint8 value :		This Arg shall indicate the value to write in port
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void GPIO_writePort(uint8 port_num, uint8 value)
{
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	GPIO_readPort
 * [DESCRIPTION]:	This Function is used to read from the port
 * [ARGS]:
 * [in]		uint8 port_num :	This Arg shall indicate the register port number
 *	[RETURNS]:	The function returns the value on the port
 ----------------------------------------------------------------------------------------*/
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 portValue = 0x00;
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			portValue = PINA;
			break;
		case PORTB_ID:
			portValue = PINB;
			break;
		case PORTC_ID:
			portValue = PINC;
			break;
		case PORTD_ID:
			portValue = PIND;
			break;
		}
	}
	return portValue;
}
