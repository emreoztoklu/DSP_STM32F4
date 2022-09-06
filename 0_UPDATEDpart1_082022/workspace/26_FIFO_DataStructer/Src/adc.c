/****************************************************************
 * Project_Name: 24_ADC_Driver_LIVE_EXAMPLE
 * File_name   : adc.c
 *
 *  Created on: Sep 1, 2022
 *      Author: Eng.Emre ÖZTOKLU
 *
 *****************************************************************/

#include <stdio.h>
#include <stdint.h>

/*
 * AHB1-> APB2 -> ADC1  or Temp_Sen.
 *
 * PA0 --> ADC1_0
 * PA1 --> ADC1_1
 * PA4 --> ADC1_4
 * PB0 --> ADC1_8
 * PC1 or PB9  --> ADC1_11 or I2C1_SDA
 * PC0 or PB8  --> ADC1_10 or I2C1_SCL
*/
#include "adc.h"

/* RCC REGISTER*/
#define GPIOAEN 		(1U << 0)
#define ADC1EN			(1U << 8)

/*CONTROL REGISTER*/
#define CR2_ADCON 		(1U << 0)
#define CR2_CONT    	(1U << 1)
#define CR2_SWSTART 	(1U << 30)

/*STATUS REGISTER*/
#define SR_EOC          (1U << 1)



void PA1_ADC_init(void){

/*Configure the ADC GPIO Pin*/
	/*Enable Clock Access to GPIOA*/
		//RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)  _GPIOAEN [0]
	RCC->AHB1ENR |= GPIOAEN;

/*Set PA1 mode to Analog mode*/
		//GPIO port mode register (GPIOx_MODER) (x = A..E and H)
		//_MODER1  Bit [2:3] Analog Mode 0011
	GPIOA->MODER |= (1U<< 2);
	GPIOA->MODER |= (1U<< 3);

/******************************/
/*Configure ADC module*/
/*Enable clock access to the ADC Module*/
		//RCC APB2 peripheral clock enable register (RCC_APB2ENR)   _ADC1EN [8]
	RCC->APB2ENR |= ADC1EN;

/*Set start of conversion sequence*/
		// ADC regular sequence register 3 (ADC_SQR3)  _SQ1[4:0]
	ADC1->SQR3 = (1U<<0);

/*Set conversion sequence length*/
		// ADC regular sequence register 1 (ADC_SQR1)  _L[20:23]
	ADC1->SQR1 = 0x00;
		/*Regular channel sequence length
			These bits are written by software to define the total number of conversions
			in the regular
				channel conversion sequence.
					0000: 1 conversion
					0001: 2 conversions
					...
					1111: 16 conversions*/

/*Enable ADC Module*/
		//ADC control register 2 (ADC_CR2)  _ADON [0]
	ADC1->CR2 |= CR2_ADCON;
}


void Start_Conversion(void){

/*Enable Continuous Conversion */
		//ADC control register 2 (ADC_CR2)  _CONT [1]
	ADC1->CR2 |= CR2_CONT;
			/*Bit 1 CONT: Continuous conversion
				This bit is set and cleared by software. If it is set, conversion takes place continuously until it
				is cleared.
				0: Single conversion mode
			->	1: Continuous conversion mode*/


/*Start ADC conversion*/
	//ADC control register 2 (ADC_CR2)  _SWSTART [30]
	ADC1->CR2 |= CR2_SWSTART;
			/* Start conversion of regular channels
				This bit is set by software to start conversion and cleared by hardware as soon as the conversion starts.
				0: Reset state
				1: Starts conversion of regular channels
				Note: This bit can be set only when ADON = 1 otherwise no conversion is launched.*/
}


uint32_t Read_ADC(void){
/*Wait for conversion to be complete*/
		//ADC status register (ADC_SR)    EOC flag [1]

	while(!(ADC1->SR & SR_EOC))
		;
		/*EOC:Regular channel end of conversion
		This bit is set by hardware at the end of the conversion of a regular group of channels. It is
		cleared by software or by reading the ADC_DR register.
		0: Conversion not complete (EOCS=0), or sequence of conversions not complete (EOCS=1)
		1: Conversion complete (EOCS=0), or sequence of conversions complete (EOCS=1)*/

/*Read Converted results*/
		//ADC regular data register (ADC_DR)	DATA[15:0]: Regular data These bits are read-only.
	return (uint32_t)(ADC1->DR);
}
