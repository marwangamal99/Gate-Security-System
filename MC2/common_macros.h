#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H		/* For file guarding */

/* Set a bit from any register */
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

#endif	/* COMMON_MACROS_H */
