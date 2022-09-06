/*
 * clock.c
 *
 *  Created on: Aug 25, 2022
 *      Author: Eng.Emre ÖZTOKLU
 *
 *NOTES:
 *	RM0383 Reference manual STM32F411xC/E advanced Arm®-based 32-bit MCUs
 *  6 Reset and clock control (RCC) for STM32F411xC/E  page:93/844
 *  6.2 Clocks
 *
 *  Check        : https://www.udemy.com/course/arm-cortex-dsp/learn/lecture/33396332#questions/18142862
 */



#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "clock.h"

		/*8MHz     25MHz Crystal*/
#define PLL_M 4		//12
#define PLL_N 200	//96
#define PLL_P 4		//2
#define PLL_Q 9		//4
/*
 This register is used to configure
 the PLL clock outputs according to the formulas:
 	f(VCO clock) = f(PLL clock input) × (PLLN / PLLM)
	f(PLL general clock output) = f(VCO clock) / PLLP
	f(USB OTG FS, SDIO) = f(VCO clock) / PLLQ
*/

/*
	00: PLLP = 2		2 >> 1 = 1, 1-1 = 0 = 0x00 ==> 2
	01: PLLP = 4		4 >> 1 = 2, 2-1 = 1 = 0x01 ==> 4
	10: PLLP = 6		6 >> 1 = 3, 3-1 = 2 = 0x10 ==> 6
	11: PLLP = 8		8 >> 1 = 4, 4-1 = 3 = 0x11 ==> 8
 * */

/*
 * System Clock Source   ==>  HSE
 * SYSCLK				 ==>  100Hz
 * HCLK					 ==>  100Hz   //Hardware Clock
 *
 * AHB   Prescaler		 ==>  1 (divide)
 * APB1  Prescaler	     ==>  4
*  APB2  Prescaler	     ==>  1
*  HSE 					 ==>  25MHz
 * */


void clock_100MHz_config(void){

	/*Enable HSE Oscillator*/
	//RCC clock control register (RCC_CR)
	RCC->CR |= RCC_CR_HSEON;
	/**********************************************************/
	/*Wait till HSE ready goes low -- HSERDY */
	//RCC clock control register (RCC_CR)
	while (!(RCC->CR & RCC_CR_HSERDY));
	/**********************************************************/
	/*Set HCLK Prescaler this will depend AHB scaling*/
	/*Set AHB  Prescaler  = 1  it means zero configuration*/
	//RCC clock configuration register (RCC_CFGR) HPRE:
	RCC->CFGR &= ~(RCC_CFGR_HPRE);
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	/**********************************************************/
	/*Set APB1 Prescaler  = 4  APB1 peripheral 25Mhz, APB1 Timer clocks 50Mhz*/
	//RCC clock configuration register (RCC_CFGR) PPRE1:
	RCC->CFGR &= ~(RCC_CFGR_PPRE1);
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
	/**********************************************************/
	/*Set APB2 Prescaler*/
	//RCC clock configuration register (RCC_CFGR) PPRE2:
	RCC->CFGR &= ~(RCC_CFGR_PPRE2);
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
	/**********************************************************/
	/*Configure PLL*/
	//RCC PLL configuration register (RCC_PLLCFGR)
	// M N P Q R etc.
	RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1)-1)<<16) \
					| (RCC_PLLCFGR_PLLSRC_HSE) |(PLL_Q<<24);
	/**********************************************************/
	/*Turn PLL ON*/
	//RCC clock control register (RCC_CR)  PLLON:
	RCC->CR |= RCC_CR_PLLON;
	/**********************************************************/
	/*Wait for PLL to come on*/
	//RCC clock control register (RCC_CR)  PLLRDY:
	while ((RCC->CR & RCC_CR_PLLRDY) == 0)
		;
	/*PLLRDY: Main PLL (PLL) clock ready flag
		Set by hardware to indicate that PLL is locked.
		0: PLL unlocked
		1: PLL locked*/

/**********************************************************/
/*NOTES*/
	/*STM32F411xC STM32F411xE data sheet*/
	/*page 64 Table 15: Features depending on the operating power supply range*/
	/*VDD = 2.7 to 3.6 V Maximum Flash memory access frequency with wait states (1)( */
	/*100 MHz with 3 wait states*/
	/*
	 *
	*/
	/*Set Flash Latency*/
	//Flash access control register (FLASH_ACR)  LATENCY:
	FLASH->ACR &= ~(FLASH_ACR_LATENCY);
	FLASH->ACR |= FLASH_ACR_LATENCY_3WS;

/**********************************************************/
	/*Select the main PLL as the clock source*/
	//RCC clock configuration register (RCC_CFGR)  SW: System clock switch
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	/*Wait for main PLL to be used as the clock source*/
	//RCC clock configuration register (RCC_CFGR)  SWS: System clock switch status
	//10: PLL used as the system clock
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
		;
}












