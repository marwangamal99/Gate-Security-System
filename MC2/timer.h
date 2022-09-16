/*--------------------------------------------------------------------------
 * [FILE NAME]:		<timer.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<31/10/2021>
 *
 * [DESCRIPTION]:	<A header file for AVR timer driver>
 ---------------------------------------------------------------------------*/

#ifndef TIMER_H_
#define TIMER_H_

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*------------------------------------EXTERNS---------------------------------*/

extern uint8 g_tick0;
extern uint16 g_tick1;
extern uint8 g_tick2;

extern uint16 g_msec0;
extern uint16 g_msec1;
extern uint16 g_msec2;

/*-----------------------------TYPES DECLEARATION-----------------------------*/
typedef enum{
	TIMER0,TIMER1,TIMER2
}TIMER_SELECT;

typedef enum{
	NORMAL_T0, CTC_T0 = 2
}TIMER0_MODE;
typedef enum{
	NO_CLOCK_T0, FCPU_1_T0, FCPU_8_T0, FCPU_64_T0, FCPU_256_T0, FCPU_1024_T0, EXTERNAL_FALLING_T0, EXTERNAL_RISING_T0
}TIMER0_PRESCALAR;


typedef enum{
	NORMAL_T1,CTC_T1=4
}TIMER1_MODE;
typedef enum{
	NO_CLOCK_T1, FCPU_1_T1, FCPU_8_T1, FCPU_64_T1, FCPU_256_T1, FCPU_1024_T1, EXTERNAL_FALLING_T1, EXTERNAL_RISING_T1
}TIMER1_PRESCALAR;
typedef enum{
	CHANNEL_A,CHANNEL_B
}TIMER1_CHANNEL;


typedef enum{
	NORMAL_T2, CTC_T2=2
}TIMER2_MODE;
typedef enum{
	NO_CLOCK_T2, FCPU_1_T2, FCPU_8_T2, FCPU_32_T2, FCPU_64_T2, FCPU_128_T2, FCPU_256_T2, FCPU_1024_T2
}TIMER2_PRESCALAR;


typedef struct{
	TIMER_SELECT timer;

	TIMER0_MODE mode0;
	TIMER0_PRESCALAR prescalar0;

	TIMER1_MODE mode1;
	TIMER1_CHANNEL channel1;
	TIMER1_PRESCALAR prescalar1;

	TIMER2_MODE mode2;
	TIMER2_PRESCALAR prescalar2;

	uint16 initial_value;
	uint16 compare_value;
}TIMER_ConfigType;

/*-----------------------------FUNCTIONS PROTOTYPES---------------------------*/
/*
 * Description:
 * A function used for initializing the AVR Timer Driver
 */
void TIMER_init(const TIMER_ConfigType *a_configPtr);


/*
 * Description:
 * A Call back function for Timer0 driver
 */
void TIMER0_setCallBack(void(*a_ptr)(uint16));


/*
 * Description:
 * A Call back function for Timer1 driver
 */
void TIMER1_setCallBack(void(*a_ptr)(uint16));


/*
 * Description:
 * A Call back function for Timer2 driver
 */
void TIMER2_setCallBack(void(*a_ptr)(uint16));


/*
 * Description:
 * A function used for de-initing Timer0 Driver
 */
void TIMER0_deInit(void);


/*
 * Description:
 * A function used for de-initing Timer1 Driver
 */
void TIMER1_deInit(void);


/*
 * Description:
 * A function used for de-initing Timer2 Driver
 */
void TIMER2_deInit(void);

#endif /* TIMER_H_ */
