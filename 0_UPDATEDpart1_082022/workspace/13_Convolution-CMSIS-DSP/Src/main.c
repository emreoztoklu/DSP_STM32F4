/*
 * https://www.keil.com/pack/doc/CMSIS/DSP/html/index.html
 *
 * */

#include <stdio.h>

#include "stm32f4xx.h"
#include "signals.h"
#include "uart.h"
//#include "filters.h"
//#include "algorithm.h"


/* OFFSET SIGNAL*/
#define OFFSET1  5
#define OFFSET2  10

/*data types*/
float g_input_SigSample;
float g_impluse_rsp_Sample;  //6kHz Cutt-off frequence of Low-pass filter
float g_output_Sample;

/*********************************/
/*1Khz & 15Khz Mixed Signal*/
extern float32_t inputSignal_f32_1kHz_15kHz[INPUT_SIGNAL_LEN_KHZ_1_15];

/*6Khz Low-pass filter Impulse Response*/
extern const float32_t  impulse_response[IMPULSE_SIG_LENGTH];

/*this array will keep it output signal*/
float32_t g_output_signal_arr[INPUT_SIGNAL_LEN_KHZ_1_15 + IMPULSE_SIG_LENGTH - 1];


/******************************************/
/*Function prototypes */

/*Input Signal*/
static void plot_input_signal(void);
static void serial_plot_input_signal(void);

/*Impulse Responce of the System*/
static void plot_impulse_response(void);
static void serial_plot_impulse_response(void);

/*Output Signal*/
static void plot_output_signal(void);
static void serial_plot_output_signal(void);

void serial_plot_all(void);
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
		// TESTING MY owm implementation
		/*
		convolution((float32_t*) inputSignal_f32_1kHz_15kHz, (float32_t*) impulse_response, (float32_t*) g_output_signal_arr,
				    (uint32_t) INPUT_SIGNAL_LEN_KHZ_1_15, (uint32_t) IMPULSE_SIG_LENGTH);

		*/

		//////////////////////////////////////////////////////////
		// TESTING CMSIS-DSP Convolution
		// https://www.keil.com/pack/doc/CMSIS/DSP/html/group__Conv.html#ga2e977f76e873bd47c6c41c7d940fdf7e
		/*
			void arm_conv_f32(const float32_t * pSrcA,uint32_t srcALen, const float32_t* pSrcB, uint32_t srcBLen, float32_t* pDst )
			[in]	pSrcA	points to the first input sequence
			[in]	srcALen	length of the first input sequence
			[in]	pSrcB	points to the second input sequence
			[in]	srcBLen	length of the second input sequence
			[out]	pDst	points to the location where the output result is written. Length srcALen+srcBLen-1.
		*/

		arm_conv_f32((float32_t*)inputSignal_f32_1kHz_15kHz, (uint32_t)INPUT_SIGNAL_LEN_KHZ_1_15,
				     (float32_t*)impulse_response, (uint32_t)IMPULSE_SIG_LENGTH,
					 (float32_t*)g_output_signal_arr);


	/******************************************************************/
	while(1){
		serial_plot_all();

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

static void plot_output_signal(void){

	uint32_t output_sig_lenght = (INPUT_SIGNAL_LEN_KHZ_1_15 + IMPULSE_SIG_LENGTH - 1);

	for ( int i = 0; i < output_sig_lenght; i++){
		g_output_Sample = g_output_signal_arr[i];
		pseudo_delay(9000);
	}
}
/*********************************************/
void serial_plot_all(void){
	//NOTE: https://www.udemy.com/course/arm-cortex-dsp/learn/lecture/33309590#reviews
	uint32_t i,j,k;
	i = j = 0;

	for( k = 0; k < (INPUT_SIGNAL_LEN_KHZ_1_15 + IMPULSE_SIG_LENGTH - 1); k++){

		(i==INPUT_SIGNAL_LEN_KHZ_1_15) ? i=0 : printf("%f,",OFFSET1 +inputSignal_f32_1kHz_15kHz[i++]);
		(j==IMPULSE_SIG_LENGTH) ? j=0 : printf("%f,",OFFSET2 + impulse_response[j++]);

		printf("%f\n\r",g_output_signal_arr[k]);

		pseudo_delay(9000);
	}
}

/*********************************************/

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

static void serial_plot_output_signal(void){
	uint32_t output_sig_lenght = (INPUT_SIGNAL_LEN_KHZ_1_15 + IMPULSE_SIG_LENGTH - 1);

	for ( int i = 0; i < output_sig_lenght; i++){
		printf("%f\r\n", g_output_signal_arr[i]);
		pseudo_delay(9000);
	}
}

static void pseudo_delay(int delay){
	for(int i = 0; i < delay; i++)
		;
}
