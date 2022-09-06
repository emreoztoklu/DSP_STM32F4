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
#include "filters.h"
#include "fifo.h"
#include "tim.h"
#include "algorithm.h"


/*******************  DEFINES   *******************/
#define arr_size(x)        (sizeof(x)/sizeof(*x))    // same like: (sizeof(x)/sizeof(x[0]))

#define OFFSET1		10

/************************************************/
#define INPUT_SIG_LEN RX_FIFO_SIZE



/******************  DATA_TYPES   ****************/
extern const float32_t lpf_1hz_3hz_impulse_response[IMP_RESPONSE_1HZ_3HZ];

/**/
uint8_t g_fifo_full_Flag, g_process_Flag;

rx_data_t  sensor_DataBuffer[RX_FIFO_SIZE];


uint32_t g_output_signal_arr[INPUT_SIG_LEN];



rx_data_t data;

/******************************************/
/*Function prototypes */
static void FPU_enable_Init(void);
static void pseudo_delay(int delay);




/**/
static void clear_DataBuffer(void); 				//sensor_DataBuffer
static uint8_t read_fifo(rx_data_t *dataBuffer);

/******************************************/


int main (){
	/*DEBUG*/
	RCC->AHB1ENR |= (1U<<0);
	GPIOA->MODER |= (1U<<16);   // PA8 Test_pin for TIM int.
	/*******************************************/

	/*Init Float point*/
	FPU_enable_Init();

	/*Set Clock Tree*/
	clock_100MHz_config();

	/*Initialize SysTick*/
	//Systick_Init();

	/*Initialize the UART*/
	Uart2_Tx_Init(UART_BAUDRATE_115200);
	/***********************************/
	/*Initialize the ADC*/
	PA1_ADC_init();

/*Enable  background thread*/
	TIM2_1kHz_interrupt_init();

	/*Start ADC Conversion*/
	Start_Conversion();

	/*İnitialize Fifo*/
	RX_FIFO_init();


/******************************************************************/
	while(1){
		/*U can use this sensor: https://www.robimek.com/arduino-ile-mikrofon-modulu-kullanimi */
		/***********************************/


		/******************************************************************/
	/*NOTE: if g_processFlag is set to 1 , then Do DSP processing*/

		if(g_process_Flag){

			/*1. Reset sensor_data_buffer*/
			clear_DataBuffer();

			/*2. Read Fifo content into data buffer*/
			for(int i = 0 ; i < RX_FIFO_SIZE; i++){

				/*Wait untill entire batch is collected from adc*/
				while(g_fifo_full_Flag == 1)
					;

				/*Read data into Sensor_DataBuffer*/
				g_fifo_full_Flag = read_fifo(sensor_DataBuffer + i);
			}

			/*Perform Digital Signal Procession*/


			//ui32_convolution((uint32_t*) sensor_DataBuffer,(float32_t*) lpf_1hz_3hz_impulse_response,(uint32_t*) g_output_signal_arr, (uint32_t) INPUT_SIG_LEN,(uint32_t) IMPULSE_SIG_LENGTH);
			//arm_conv_f32((float32_t*) sensor_DataBuffer,(uint32_t) INPUT_SIG_LEN,(float32_t*) lpf_1hz_3hz_impulse_response,(uint32_t) IMPULSE_SIG_LENGTH,(float32_t*) g_output_signal_arr);

			moving_average_2((uint32_t*) sensor_DataBuffer,
							 (uint32_t*) g_output_signal_arr,
							 (uint32_t) INPUT_SIG_LEN,
							 (uint32_t) 11);

			for(int i = 0; i < (INPUT_SIG_LEN); i++){
				printf("%d,", (int)(OFFSET1 + sensor_DataBuffer[i]));
				printf("%d\n\r", (int)g_output_signal_arr[i]);
			}

			/*Reset Process Flag */
			g_process_Flag = 0;

		}
		/******************************************************************/
		// Watch on Arduino serial plotter
		// or https://x-io.co.uk/serial-oscilloscope/
	}//while loop

} //main


static void clear_DataBuffer(void){
	for(int i = 0; i < RX_FIFO_SIZE; i++){
		sensor_DataBuffer[i] = 0;
	}
}

static uint8_t read_fifo(rx_data_t *dataBuffer){

	__IO uint8_t read_flag;

/*place fifo data into data_buffer*/
	read_flag = get_data_RX_FIFO(dataBuffer);

	/*if fifo is empty then reset g_fifo_full_Flag */

	if(read_flag == 0)
		g_fifo_full_Flag = 1; /*buffer is not full, empty*/
	else
		g_fifo_full_Flag = 0;

	/* g_fifo_full_Flag = 1:
	 *  This will start the fifo_put routine again
	 *  to collect the next batch of sample */

	/* g_fifo_full_Flag = 0;
	 * keep fifo g_fifo_full_Flag at fifo FULL*/

	return (uint8_t) g_fifo_full_Flag;
}

/*******************************************************************************************/
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
