/*
 * https://www.keil.com/pack/doc/CMSIS/DSP/html/index.html
 *
 * */

#include <stdio.h>

#include "stm32f4xx.h"
#include "clock.h"
#include "sys_tick.h"
#include "uart.h"
#include "adc.h"
#include "fir_filter.h"
#include "signals.h"

#define arr_size(x)        (sizeof(x)/sizeof(*x))    // same like: (sizeof(x)/sizeof(x[0]))

#define OFFSET1		5

/************************************************/

extern const float32_t lpf_1hz_3hz_impulse_response[IMP_RESPONSE_1HZ_3HZ];



/*this array will keep it idft_output signal*/
float32_t g_output_signal_arr[10];

/*data types*/
uint32_t g_sensor_value;
uint32_t filtered_sensor_value;

FIR_filter_t lpf_fir;


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


	/***********************/
	//Initialize fir filter
	FIR_filter_init(&lpf_fir,  lpf_1hz_3hz_impulse_response,  IMP_RESPONSE_1HZ_3HZ);


/******************************************************************/
	while(1){

		g_sensor_value = Read_ADC();
		/*U can use this sensor: https://www.robimek.com/arduino-ile-mikrofon-modulu-kullanimi */

		filtered_sensor_value = FIR_filter_update(&lpf_fir, g_sensor_value);

		printf("%d,", (int)g_sensor_value);
		printf("%d\n\r",(int) filtered_sensor_value);

		pseudo_delay(90000);
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
