/****************************************************************
 * Project_Name: 27_BackgroundThread
 * File_name   : tim.c
 *
 *  Created on: Sep 2, 2022
 *      Author: Eng.Emre ÖZTOKLU
 *
 *	Check: https://www.udemy.com/course/arm-cortex-dsp/learn/lecture/33453112#questions/18142862
 *	or earlier videos
 *****************************************************************/

/*********************  INCLUDES *********************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "tim.h"

#include "adc.h"
#include "fifo.h"


/*********************  DEFINES ******************* **/
#define TIM2EN 		(1U << 0)		//RCC APB1 peripheral clock enable register (RCC_APB1ENR)  _TIM2EN
#define CR1_CEN		(1U << 0)		//TIMx control register 1 (TIMx_CR1)  _CEN
#define DIER_UIE    (1U << 0)		//TIMx DMA/Interrupt enable register (TIMx_DIER)
/********************   TYPEDEF   ********************/

/********************  DATA_TYPES ********************/

/********************    MACRO    ********************/

/********************  FUNCTIONS  ********************/

/* AHB1-> APB1 -> TIM2 (32bit) 4 channels , ETR as AF
 *
 * *****TIM2/TIM5********
 * Counter_resolution: 	32-bit
 * Counter_type: 		Up,Down, Up/down
 * Prescaler_factor:	Any integer between 1 and 65536
 * DMA request_generation : Yes,  Capture/compare_channels : 4, Complementary_output: No
 * Max.interface_clock 	(MHz)	50
 * Max.timer_clock 		(MHz) 	100
 *
 * PA0-WKUP & PA15 	--> TIM2_CH1/TIM2_ET,
 * PA1 & PB3		--> TIM2_CH2,
 * PA2 & PB10 		--> TIM2_CH3,
 * PA3 & PB11 		--> TIM2_CH4,
 *******************************************/

/*
 * APB1 CLOCK = 50Mhz after Clock tree update
 * fCK_PSC = 50Mhz
 * 50000000/ 5000 = 10000
 * PSC = 5000
 *
 * 1Hz --> T = 1/1Hz = 1sn
 *
 * if ARR = 10000  ==> PSC/ARR = 1sn
 * */


void TIM2_1kHz_interrupt_init(void){
/*1. Enable Clock access to TIM2*/
	//RCC APB1 peripheral clock enable register (RCC_APB1ENR)  _TIM2EN
	RCC->APB1ENR |= TIM2EN;

/*2. Set the prescaler value*/
	//TIMx prescaler (TIMx_PSC)

	//TIM2->PSC = (5000 - 1);		//50000000/ 5000 = 10000		Period: 1sn   1Hz
	TIM2->PSC = (10000 - 1);		//50000000/ 10000 = 5000		Period: 2sn   500mHz=0.5hz

	/* The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1).
		PSC contains the value to be loaded in the active prescaler register at each update event
		(including when the counter is cleared through UG bit of TIMx_EGR register or through
		trigger controller when configured in “reset mode”).*/

/*3. Set auto-reload value*/
	//TIMx auto-reload register (TIMx_ARR)
	TIM2->ARR = 10 - 1;					//  * if ARR = 10  ==> PSC/ARR = 1000Hz=1KHz =1ms

/*4. Clear counter*/
	//TIMx counter (TIMx_CNT)
	TIM2->CNT = 0;

/*5. Enable Timer*/
	//TIMx control register 1 (TIMx_CR1)  _CEN
	TIM2->CR1 = CR1_CEN;

/*6. Enable Timer Interrupt*/
	//TIMx DMA/Interrupt enable register (TIMx_DIER)
	TIM2->DIER |= DIER_UIE;

/*7. Enable Timer Interrupt in NVIC*/
	// #define NVIC_EnableIRQ              __NVIC_EnableIRQ
	NVIC_EnableIRQ(TIM2_IRQn);
}


static void TIM2_callback(void){
	extern uint8_t g_fifo_full_Flag, g_process_Flag;

	/*Check if fifo is not full*/
	if(g_fifo_full_Flag == 1) {  /*1 is not full*/
		g_fifo_full_Flag = put_data_RX_FIFO(Read_ADC());
	}
	else{						/* 0 is  full*/
		g_process_Flag = 1;
	}

}


//startup_stm32f411ceux.s
void TIM2_IRQHandler (void){
/*1. Clear update interrupt flag*/
	//TIMx status register (TIMx_SR)  _UIF [0]
	TIM2->SR &= ~(SR_UIF);

	/*Do something*/
	TIM2_callback();

}











