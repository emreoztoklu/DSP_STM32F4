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

#include "signals.h"
#include "filters.h"

#define arr_size(x)        (sizeof(x)/sizeof(*x))    // same like: (sizeof(x)/sizeof(x[0]))

#define OFFSET1		5
#define OFFSET2		10


#define MOV_AVR_FLTR_POINTS  11			// here is more suitable
//#define MOV_AVR_FLTR_POINTS  5		// it shows little bit noisy


#if 0
/**********SIGNALS**********************//******************************************/
/*1Khz & 15Khz Mixed Signal*/
extern const float32_t inputSignal_f32_1kHz_15kHz[INPUT_SIGNAL_LEN_KHZ_1_15];
/*6Khz Low-pass filter Impulse Response*/
extern const float32_t  impulse_response[IMPULSE_SIG_LENGTH];
/*640 point ECG signal*/
extern const float32_t _640_points_ecg_[ECG_SIG_LENGTH];
/***********************NEW**********************************/
// Signals in 3 differencer frequency
extern const float32_t Signal_10hz_100hz_500hz[1001];
// 70Hz cut-off freq LOW-pass filter impluse responce coeffients
extern const float32_t lpf_fc_70hz[LPF_70HZ_CUTOFF_FREQ_LENGTH];
// 400Hz cut-off freq HIGH-pass filter impluse responce coeffients
extern const float32_t hpf_fc_400hz[HPF_400HZ_CUTOFF_FREQ_LENGTH];
/******************************************//******************************************/
#endif

/*this array will keep it idft_output signal*/
float32_t g_output_signal_arr[INPUT_SIGNAL_LEN_KHZ_1_15];


/*data types*/
float32_t g_sensor_value;




/******************************************/
/*Function prototypes */
static void FPU_enable_Init(void);
static void pseudo_delay(int delay);

static void plot_input_signal(void);
static void serial_plot_input_signal(void);
void serial_plot_all_2(void);

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

/******************************************************************/
	while(1){

		g_sensor_value = Read_ADC()/4095.0;
		pseudo_delay(10000);
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



#if 0
/**********************************************************************/
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

void serial_plot_all_2(void){
	//NOTE: https://www.udemy.com/course/arm-cortex-dsp/learn/lecture/33321696#reviews
	for(uint32_t k = 0; k < (INPUT_SIGNAL_LEN_KHZ_1_15); k++){
		printf("%f,", OFFSET1 + inputSignal_f32_1kHz_15kHz[k]);
		printf("%f\n\r",g_output_signal_arr[k]);
		pseudo_delay(9000);
	}
}
#endif

