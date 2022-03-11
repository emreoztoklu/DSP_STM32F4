#include <stdint.h>
#include <stdlib.h>


/**depencies library**/
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

/**********DEFINES***************/
#define SIGNAL_LENGHT  	320
#define NUM_TAPS  			29
#define BLOCK_SIZE			32   						//ARM_cmsis library generate the signal by bloks


/**********data types*************/
uint32_t freq;
float32_t inputSample, outputSample;


extern float32_t InputSignal_f32_1kHz_15kHz[SIGNAL_LENGHT];
extern const float32_t firCoeffs32[NUM_TAPS];


float32_t outputSignal_f32[SIGNAL_LENGHT];


/*store filtered signal*/
static float32_t firState_f32[BLOCK_SIZE + NUM_TAPS - 1];

uint32_t numBlocks = SIGNAL_LENGHT/BLOCK_SIZE;



/*******FUNCTION PROTOTYPES********/
extern void SystemClock_Config(void);
void plot_Input_signal(void);
void plot_Output_signal(void);
void plot_both_signal(void);




int main(){
	
	int i;
	
	HAL_Init();
	SystemClock_Config();
	
	/*FIR filters*/
	
	arm_fir_instance_f32 _1Khz_15Khz_sig;  		// this is a instance
	arm_fir_init_f32(&_1Khz_15Khz_sig,NUM_TAPS,(float32_t*)&firCoeffs32,&firState_f32[0],BLOCK_SIZE);
	
	for(i = 0; i < numBlocks; i++){
		arm_fir_f32(&_1Khz_15Khz_sig, &InputSignal_f32_1kHz_15kHz[0] + (i*BLOCK_SIZE),&outputSignal_f32[0] + (i*BLOCK_SIZE),BLOCK_SIZE);
	}

	
	// 1 plot_Input_signal();
	// 2 plot_Output_signal();
	plot_both_signal();
	
	while(1){
		
		
		
	}	
}

void plot_Input_signal(void){
	int i, j;
	for(i = 0; i < SIGNAL_LENGHT ; i++){	
		inputSample = InputSignal_f32_1kHz_15kHz[i];
		for(j = 0; j < 3000; j++)
		;	
		if(i == SIGNAL_LENGHT-1) i = 0;	
	}
}

void plot_Output_signal(void){
	int i, j;
	for(i = 0; i < SIGNAL_LENGHT ; i++){
		outputSample = outputSignal_f32[i];
		for(j = 0; j < 5000; j++)
		;
		if(i == SIGNAL_LENGHT-1) i = 0;
	}
}

void plot_both_signal(void){
	int i , j;
	
	for(i = 0; i < SIGNAL_LENGHT ; i++){
		inputSample = InputSignal_f32_1kHz_15kHz[i];
		outputSample = outputSignal_f32[i];
		HAL_Delay(1);
		for(j = 0; j < 3000; j++)
		;
		
		if(i == SIGNAL_LENGHT-1) i = 0;
	}
}



void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}