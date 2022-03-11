#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

/*DEFINES */
#define SIGNAL_LENGHT 		320 

/*********************************************/

/*DATA TYPE */
uint32_t freq;
float32_t inputSample;
float32_t inputMean;

extern float32_t InputSignal_f32_1kHz_15kHz[SIGNAL_LENGHT];

float32_t *inputSignal = &InputSignal_f32_1kHz_15kHz[0];


/*********************************************/
/*FUNCTION PROTOTYPES */


extern void SystemClock_Config(void);
void plot_input_signal(void);

//filters
float32_t signal_mean(float32_t *sig_src_arr, uint32_t sig_length);
		
/*********************************************/



int main(void){
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
	
	inputMean = signal_mean((float32_t*)&inputSignal,(uint32_t)SIGNAL_LENGHT);
	
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
		
	uint32_t i;
	float32_t _mean = 0.0;
	
	for( i = 0; i < sig_length; i++)  {
		_mean += sig_src_arr[i]; 
	}
	
	return _mean = _mean /(float32_t)sig_length;
}







void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

