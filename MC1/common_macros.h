/*--------------------------------------------------------------------------
 * [FILE NAME]:		<common_macros.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<4/10/2021>
 *
 * [DESCRIPTION]:	<Commonly used Macros in AVR>
 ---------------------------------------------------------------------------*/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_		/* For file guarding */

/*--------------------------------------------------------------------------
 * [MACRO NAME]:	SET_BIT
 * [DESCRIPTION]:	This Macro is used for setting a bit in a register
 * [ARGS]:
 * [in]		uint8 REG:
 * 				This Arg shall indicate the register
 * 			uint8 BIT:
 *				This Arg shall indicate the bit
 ---------------------------------------------------------------------------*/
#define SET_BIT(REG,BIT) ( REG |= (1<<BIT) )

/* Clear a bit from any register */
#define CLEAR_BIT(REG,BIT) ( REG &= (~(1<<BIT)) )

/* Toggling any bit */
#define TOGGLE_BIT(REG,BIT) ( REG ^= (1<<BIT) )

/* Check if the bet is set in a certain register bit and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if the bet is cleared in a certain register bit and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !( REG & (1<<BIT) ) )

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

#endif	/* COMMON_MACROS_H_ */
