#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

/*DEFINES */
#define SIGNAL_LENGHT 				200 
#define IMPULSE_RESP_LENGHT 	29

/*********************************************/
/*extern DATA TYPE */
extern float32_t InputSignal_f32_1kHz_15kHz[SIGNAL_LENGHT];
float32_t *inputSignal = &InputSignal_f32_1kHz_15kHz[0];

/*DATA TYPE */
uint32_t freq;
float32_t inputSample;
float32_t outputSample;
float_t output_signal_arr[SIGNAL_LENGHT];


/*********************************************/
/*FUNCTION PROTOTYPES */
extern void SystemClock_Config(void);
void plot_input_signal(void);
void plot_output_signal(void);
void plot_both_signal(void);

void plot_signal(float32_t * src_signal, uint32_t sig_lenght, float32_t *sample);


void calc_running_sum(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_lenght);

void calc_first_difference(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_lenght);
	

/*********************************************/

int main(void){
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
  calc_first_difference((float32_t*)&inputSignal[0], (float32_t*)&output_signal_arr[0], (uint32_t)SIGNAL_LENGHT);
	plot_both_signal();
	
	while(1){	
	
	}	

}

/*running sound smooth and filter ses yumusatma */
void calc_running_sum(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_lenght){
	int i;
	
	sig_src_arr[0] = sig_dest_arr[0];
	
	for(i = 1; i <= sig_lenght ; i++){
		
		//y[n] = x[n] + y[n-1]  running sum
		sig_dest_arr[i] = sig_src_arr[i] +  sig_dest_arr[i-1];
	}

}


void calc_first_difference(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_lenght){
	
	int i ;
	
	sig_dest_arr[0]= 0;
	
	for(i = 1; i <= sig_lenght; i++){
			
			//y[n] = x[n] - x[n-1]
			sig_dest_arr[i] = sig_src_arr[i]-sig_src_arr[i-1];
	}
}	

void plot_both_signal(void){
	int i, j;
	
	for(i = 0; i < SIGNAL_LENGHT; i++){
		outputSample =  output_signal_arr[i];
		inputSample =  inputSignal[i];
		for(j = 0; j < 6000; j++)
		;
	}
}


void plot_input_signal(void){
	int i, j;

	for(i = 0; i < SIGNAL_LENGHT; i++){
		inputSample =  inputSignal[i];
		for(j = 0; j < 3000; j++)
		;
	}
}

void plot_output_signal(void){
	int i, j;
	
	for(i = 0; i < SIGNAL_LENGHT; i++){
		outputSample =  output_signal_arr[i];
		for(j = 0; j < 3000; j++)
		;
	}
}


void plot_signal(float32_t * src_signal, uint32_t sig_lenght, float32_t* sample){
	int i, j;
	
	for(i = 0; i < sig_lenght; i++){
		*sample =  src_signal[i];
		for(j = 0; j < 3000; j++)
		;
	}
}	

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

