/*
 * sys_tick.c
 *
 *  Created on: Aug 23, 2022
 *      Author: Eng.Emre ÖZTOKLU
 */



#include <stdio.h>
#include <stdint.h>
#include <string.h>


#include "sys_tick.h"



/*NOTES:
 Cortex™-M4 Devices Generic User Guide / 4.4 System timer, SysTick The processor has
 */

#define CTRL_ENABLE  	(1U << 0)		//0 = counter disabled, 1 = counter enabled.
#define CTRL_CLKSOURCE  (1U << 2)		//0 = external clock , 1 = processor clock.

#define SYSTEM_FREQUENCE  (16000000)
#define SINGLE_CYCLE      (1/SYSTEM_FREQUENCE)  //  62.5 x 10^-9 ==> 0,0000000625

#define SEC_TO_MSEC		(1000)



void Systick_Init(void){
	/*SysTick Control and Status Register:
	 *Disable systick before config*/
	SysTick->CTRL = 0x00;

	/*SysTick Reload Value Register :
	 *Load systick reload value register with maximum value*/
	SysTick->LOAD = 0x00FFFFFF;		// 16Mhz

	/*SysTick Current Value Register:
	 *Clear systick current value register*/
	SysTick->VAL = 0x00;

	/*SysTick Control and Status Register:
	 *Select internal clock source*/
	SysTick->CTRL |= CTRL_CLKSOURCE;

	/*SysTick Control and Status Register:
	 *Enable systick*/
	SysTick->CTRL |= CTRL_ENABLE;

}

float32_t second(uint32_t val){
	return (float32_t)((val) * SINGLE_CYCLE);

}

float32_t milli_second(uint32_t val){
	return (float32_t)(second(val) * SEC_TO_MSEC);
}
