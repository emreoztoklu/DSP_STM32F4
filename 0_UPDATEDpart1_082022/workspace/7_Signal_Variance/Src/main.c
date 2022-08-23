#include <stdio.h>

#include "stm32f4xx.h"
#include "signals.h"
#include "uart.h"
#include "filters.h"



/*data types*/

float g_input_SigSample;



/*filters cal. global val*/

float32_t g_mean_value;
float32_t g_variance_value;
float32_t g_std_value;


/******************************************/
/*Function prototypes */
static void FPU_enable_Init(void);
static void pseudo_delay(int delay);

static void plot_input_signal(void);
static void serial_plot_input_signal(void);
/******************************************/



int main (){
	/*Init Float point*/
	FPU_enable_Init();

	/*Initialize the uart*/
	Uart2_Tx_Init(UART_BAUDRATE_115200);

	g_mean_value = signal_mean((float32_t*)inputSignal_f32_1kHz_15kHz, (uint32_t)INPUT_SIGNAL_LEN_KHZ_1_15);
	/*0.0371*/

	g_variance_value =signal_variance((float32_t*) inputSignal_f32_1kHz_15kHz, (float32_t)g_mean_value, (uint32_t)INPUT_SIGNAL_LEN_KHZ_1_15);
	/*0.6201*/

	g_std_value = signal_std((float32_t)g_variance_value);
	/*0.7875*/

	while(1){
	/*Test1*/ plot_input_signal();
	/*Test2*/ serial_plot_input_signal();

	}
}


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

static void serial_plot_input_signal(void){
	for ( int i = 0; i < INPUT_SIGNAL_LEN_KHZ_1_15; i++){
		printf("%f\r\n", inputSignal_f32_1kHz_15kHz[i]);
		pseudo_delay(9000);
	}
}

static void pseudo_delay(int delay){
	for(int i = 0; i < delay; i++)
		;
}
