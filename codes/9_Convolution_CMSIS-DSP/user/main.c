#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

/*DEFINES */
#define SIGNAL_LENGHT 				320 
#define IMPULSE_RESP_LENGHT 	29
#define OUTPUT_SIG_LENGHT  		(SIGNAL_LENGHT + IMPULSE_RESP_LENGHT)
/*********************************************/
/*extern DATA TYPE */
extern float32_t InputSignal_f32_1kHz_15kHz[SIGNAL_LENGHT];
float32_t *inputSignal = &InputSignal_f32_1kHz_15kHz[0];

/*This is actually filter Kernel. So, low pass filter response,
48Khz Sample Frequency, 6khz cutoff frequency
this mean is our input signal which is 1khz 15 khz
will pass trough low-pass filter which is 6khz cutoff freq
then out signal will be 1 khz signal.
*/
extern const float32_t firCoeffs32[IMPULSE_RESP_LENGHT];
const float32_t *impulse_response = &firCoeffs32[0];


/*DATA TYPE */

float_t output_Signal_arr[OUTPUT_SIG_LENGHT];

uint32_t freq;
float32_t inputSample;
float32_t imp_resSample;
float32_t outputSample;


float32_t inputStd;					// 0.787501931


/*********************************************/
/*FUNCTION PROTOTYPES */

extern void SystemClock_Config(void);
void plot_input_signal(void);
void plot_impulse_response(void);
void plot_output_signal(void);
void plot_all_signal(void);
void plot_signal(float32_t * src_signal, uint32_t sig_lenght, float32_t *sample);


/*********************************************/

int main(void){
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
	//plot_impulse_response();
	//plot_signal((float32_t*)impulse_response, (uint32_t)IMPULSE_RESP_LENGHT, (float32_t*)&imp_resSample);
	
	/*************************************************************/
	/*Calculate Convolution input signal according to impulse response of low-pass filter*/
	arm_conv_f32((const float32_t*)&inputSignal[0],(uint32_t)SIGNAL_LENGHT,
							 (const float32_t*)&impulse_response[0],(uint32_t)IMPULSE_RESP_LENGHT,
							 (float32_t*)&output_Signal_arr[0] );
							 
	//plot_output_signal();
	//plot_signal((float32_t*)&output_Signal_arr[0], (uint32_t)OUTPUT_SIG_LENGHT, (float32_t*)&outputSample);
	
	plot_all_signal();
							
	while(1){	
	
	}	

}


void plot_input_signal(void){
	int i, j;
	uint16_t delay = 3000;
	
	for(i = 0; i < SIGNAL_LENGHT; i++){
		inputSample =  inputSignal[i];
		for(j = 0; j < delay; j++)
		;
	}
}

void plot_impulse_response(void){
	int i, j;
	uint16_t delay = 3000;
	
	for(i = 0; i < IMPULSE_RESP_LENGHT; i++){
		imp_resSample =  impulse_response[i];
		for(j = 0; j < delay; j++)
		;
	}
}

void plot_output_signal(void){
	int i, j;
	uint16_t delay = 3000;
	
	for(i = 0; i < (SIGNAL_LENGHT +IMPULSE_RESP_LENGHT); i++){
		outputSample =  output_Signal_arr[i];
		for(j = 0; j < delay; j++)
		;
	}
}

void plot_all_signal(void){
	int i, j, k, m;
	uint32_t delay = 20000;
	i=j=0;
	
	for(k = 0; k < OUTPUT_SIG_LENGHT; k++){
		if(i++ == SIGNAL_LENGHT) 
			i=0;
		if(j++ == IMPULSE_RESP_LENGHT) 
			j=0;
		if(k == OUTPUT_SIG_LENGHT-1) 
			k=0;
		
		inputSample = inputSignal[i];
		imp_resSample = impulse_response[j];
		outputSample =  output_Signal_arr[k];
		
		for(m = 0; m < delay; m++)
		;
		
	}
}


void plot_signal(float32_t * src_signal, uint32_t sig_lenght, float32_t* sample){
	int i, j;
	uint16_t delay = 3000;
	for(i = 0; i < sig_lenght; i++){
		*sample =  src_signal[i];
		for(j = 0; j < delay; j++)
		;
	}
}	

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

