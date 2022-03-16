#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

/*DEFINES */
#define SIGNAL_LENGHT 		320 

/*********************************************/

/*DATA TYPE */
uint32_t freq;
float32_t inputSample;
float32_t inputMean;				// 0.0371118784
float32_t inputVariance;		// 0.620159328
float32_t inputStd;					// 0.787501931



extern float32_t InputSignal_f32_1kHz_15kHz[SIGNAL_LENGHT];
float32_t *inputSignal = &InputSignal_f32_1kHz_15kHz[0];

/*********************************************/
/*FUNCTION PROTOTYPES */

extern void SystemClock_Config(void);
void plot_input_signal(void);

//filters
float32_t signal_mean(float32_t *sig_src_arr, uint32_t sig_length);
float32_t signal_variance(float32_t*sig_src_arr, float32_t sig_mean, uint32_t sig_lenght);
float32_t signal_std(float32_t sig_variance);		
/*********************************************/

int main(void){
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
/*My own implementation */
	//inputMean =	signal_mean((float32_t*)&inputSignal[0], (uint32_t) SIGNAL_LENGHT);
	//inputVariance = signal_variance((float32_t*)&inputSignal[0], (float32_t) inputMean, (uint32_t) SIGNAL_LENGHT);
	//inputStd = signal_std((float32_t) inputVariance);	
	
/*DSP library implementation*/
	arm_mean_f32((float32_t*)&inputSignal[0],(uint32_t) SIGNAL_LENGHT, &inputMean);
	arm_var_f32 ((float32_t*)&inputSignal[0],(uint32_t) SIGNAL_LENGHT, &inputVariance);
	arm_std_f32 ((float32_t*)&inputSignal[0],(uint32_t) SIGNAL_LENGHT, &inputStd);
	while(1){	
	}	
}


void plot_input_signal(void){
	int i, j;
	uint16_t delay = 3000;
	
	for(i = 0; i < SIGNAL_LENGHT; i++){
		inputSample =  InputSignal_f32_1kHz_15kHz[i];
		for(j = 0; j < delay; j++)
		;
	}
}


float32_t signal_mean(float32_t *sig_src_arr, uint32_t sig_length){		
	float32_t _mean = 0.0f;
	uint32_t i;
	
	for( i = 0; i < sig_length; i++)  {
		_mean += sig_src_arr[i]; 
	}
	_mean = _mean /(float32_t)sig_length;
	
	return _mean ;
}

float32_t signal_variance(float32_t*sig_src_arr, float32_t sig_mean, uint32_t sig_lenght){
	float32_t _variance =0.0f;
	uint32_t i;
	
	for(i = 0; i < sig_lenght; i++){
		_variance += pow(sig_src_arr[i] - sig_mean, 2);
	}
	_variance = _variance/(sig_lenght-1);

	return _variance;
}

float32_t signal_std(float32_t sig_variance){
	float32_t _std = sqrtf(sig_variance);
	return _std;
}

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

