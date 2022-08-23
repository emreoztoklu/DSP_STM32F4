/*
 * https://www.keil.com/pack/doc/CMSIS/DSP/html/index.html
 *
 * */

#include <stdio.h>

#include "stm32f4xx.h"
#include "signals.h"
#include "uart.h"
#include "filters.h"



/*data types*/
float g_input_SigSample;
float g_impluse_rsp_Sample;


/******************************************/
/*Function prototypes */

/*Input Signal*/
static void plot_input_signal(void);
static void serial_plot_input_signal(void);

/*Impulse Responce of the System*/
static void plot_impulse_response(void);
static void serial_plot_impulse_response(void);


/******************************************/
static void FPU_enable_Init(void);
static void pseudo_delay(int delay);
/***********************
 *
 *
************************/
int main (){
	/*Init Float point*/
	FPU_enable_Init();

	/*Initialize the uart*/
	Uart2_Tx_Init(UART_BAUDRATE_115200);

/******************************************************************/

/******************************************************************/

	/*Test2*/serial_plot_impulse_response();
/******************************************************************/

	while(1){
		/*Test1*/plot_impulse_response();

	} //while loop
} //main

/***********************
*
*
************************/

static void FPU_enable_Init(void){
	/*Enable Floating point unit*/
	/*Doc: Cortex™-M4 Devices Generic User Guide*/
	/*System Control Block (SCB)*/
	/*Coprocessor Access Control Register*/
		/*0b11 = Full access.  (3UL)*/

#define CP10  (2*10)   /*21 20*/
#define CP11  (2*11)   /*23 22*/

	SCB->CPACR |= ((3UL << CP10) | (3UL << CP11));
}

/*
 * The signal is 1Khz -- 15Khz Mixed Sin. signal
 * */

static void plot_input_signal(void){
	for ( int i = 0; i < INPUT_SIGNAL_LEN_KHZ_1_15; i++){
		g_input_SigSample = inputSignal_f32_1kHz_15kHz[i];
		pseudo_delay(9000);
	}
}

static void plot_impulse_response(void){
	for ( int i = 0; i < IMPULSE_SIG_LENGTH; i++){
		g_impluse_rsp_Sample = impulse_response[i];
		pseudo_delay(9000);
	}
}

static void serial_plot_input_signal(void){
	for ( int i = 0; i < INPUT_SIGNAL_LEN_KHZ_1_15; i++){
		printf("%f\r\n", inputSignal_f32_1kHz_15kHz[i]);
		pseudo_delay(9000);
	}
}

static void serial_plot_impulse_response(void){
	for ( int i = 0; i < IMPULSE_SIG_LENGTH; i++){
		printf("%f\r\n", impulse_response[i]);
		pseudo_delay(9000);
	}
}


static void pseudo_delay(int delay){
	for(int i = 0; i < delay; i++)
		;
}
