#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP
#include "lowpass_fltr.h"
#include "sinus_generator.h"


/*DEFINES*/
#define SAMPLING_FREQ		1000				// 1Khz
#define SIGNAL_FREQ			10					// 10hz
#define NOISE_FREQ			50					// 50hz

/*DATA TYPES*/
uint32_t freq;


sine_generator_q15_t  Signal_set;
sine_generator_q15_t  Noise_set;

q15_t sinus, noise, disturbed, filtered;


/* FUNTION DECLERATION*/
extern void SystemClock_Config(void);


int main(void){
	
	HAL_Init();
	SystemClock_Config();
	
	freq = HAL_RCC_GetHCLKFreq();
	
	/*user calls 	initial functions*/

	sine_generator_init_q15(&Signal_set, SIGNAL_FREQ, SAMPLING_FREQ);
	sine_generator_init_q15(&Noise_set, NOISE_FREQ, SAMPLING_FREQ);
	
	/*filtering*/
	low_pass_filter_init();
	
	/********************************/
	
	while(1){
		sinus = sine_calc_sample_q15(&Signal_set);
		noise = sine_calc_sample_q15(&Noise_set);
		disturbed = sinus + noise;
		
		filtered = low_pass_filter(&disturbed);
		
		HAL_Delay(10);
	}
}


void SysTick_Handler (void){
	
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
	
}
