/*
 * https://www.keil.com/pack/doc/CMSIS/DSP/html/index.html
 *
 * */

/*********************  INCLUDES *********************/
#include <stdio.h>

#include "stm32f4xx.h"
#include "clock.h"
#include "sys_tick.h"
#include "uart.h"
#include "adc.h"

#include "signals.h"
#include "fir_filter.h"
#include "fifo.h"


/*******************  DEFINES   *******************/
#define arr_size(x)        (sizeof(x)/sizeof(*x))    // same like: (sizeof(x)/sizeof(x[0]))
#define OFFSET1		5

/************************************************/
/******************  DATA_TYPES   ****************/
extern const float32_t lpf_1hz_3hz_impulse_response[IMP_RESPONSE_1HZ_3HZ];

uint32_t my_rx_data[50];



/******************************************/
/*Function prototypes */
static void FPU_enable_Init(void);
static void pseudo_delay(int delay);

/******************************************/


int main (){
	/*Init Float point*/
	FPU_enable_Init();

	/*Set Clock Tree*/
	clock_100MHz_config();

	/*Initialize SysTick*/
	Systick_Init();

	/*Initialize the UART*/
	Uart2_Tx_Init(UART_BAUDRATE_115200);
	/***********************************/
	/*Initialize the ADC*/
	PA1_ADC_init();

	/*Start ADC Conversion*/
	Start_Conversion();

	/*İnitialize Fifo*/
	RX_FIFO_init();

	uint32_t rx_data;

	for(int i = 0; i < 50 ; i++){
		put_data_RX_FIFO(Read_ADC());
	}

	for(int i = 0; i < 50 ; i++){
		get_data_RX_FIFO(&rx_data);
		my_rx_data[i] = rx_data;
	}



/******************************************************************/
	while(1){
		/*U can use this sensor: https://www.robimek.com/arduino-ile-mikrofon-modulu-kullanimi */
		/***********************************/

		// Watch on Arduino serial plotter
		// or https://x-io.co.uk/serial-oscilloscope/
	}//while loop

} //main




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

static void pseudo_delay(int delay){
	for(int i = 0; i < delay; i++)
		;
}
