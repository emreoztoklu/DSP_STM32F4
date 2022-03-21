#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

/*DEFINES */
#define SIGNAL_LENGHT 		320 
#define IMPULSE_RESP_LENGHT 29
#define OUTPUT_SIG_LENGHT  (SIGNAL_LENGHT + IMPULSE_RESP_LENGHT)
/*********************************************/
/*DATA TYPE */
extern float32_t InputSignal_f32_1kHz_15kHz[SIGNAL_LENGHT];
float32_t *inputSignal = &InputSignal_f32_1kHz_15kHz[0];


/*This is actually filter Kernel, 
so, low pass filter response,
48Khz Sample Frequency, 6khz cutoff frequency
*/
extern const float32_t firCoeffs32[IMPULSE_RESP_LENGHT];
const float32_t *impulse_response = &firCoeffs32[0];


uint32_t freq;
float32_t inputSample;
float32_t imp_resSample;
float32_t outputSignal;

/*output_sample  ==> signal lenght + impulse lenght */
float32_t output_signal[SIGNAL_LENGHT + IMPULSE_RESP_LENGHT];


/*********************************************/
/*FUNCTION PROTOTYPES */

extern void SystemClock_Config(void);
void plot_input_signal(void);
void plot_impulse_response(void);
void plot_output_signal(void);
void plot_signal(float32_t * src_signal, uint32_t sig_lenght, float32_t *sample);


void convolution(float32_t *sig_src_arr, float32_t *imp_response_arr, float32_t *sig_dest_arr, uint32_t sig_src_lenght, uint32_t imp_resp_lenght);

//filters
		
/*********************************************/

int main(void){
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
	// plot_input_signal();
	// plot_impulse_response();
	
	convolution((float32_t*)inputSignal,(float32_t*)impulse_response,(float32_t*)output_signal,(uint32_t) SIGNAL_LENGHT,(uint32_t) IMPULSE_RESP_LENGHT);

	//plot_signal((float32_t*)inputSignal,(uint32_t) SIGNAL_LENGHT, (float32_t*)&inputSample);
	//plot_signal((float32_t*)impulse_response,(uint32_t)IMPULSE_RESP_LENGHT, (float32_t*)&imp_resSample);
	plot_signal((float32_t*)output_signal,(uint32_t)OUTPUT_SIG_LENGHT, (float32_t*)&outputSignal);
	
	while(1){	 
		
	}	
	
}



void convolution(float32_t *sig_src_arr, float32_t *imp_response_arr, float32_t *sig_dest_arr, uint32_t sig_src_lenght, uint32_t imp_resp_lenght){
	uint32_t i, j;
	
	/*clean destination array*/
	for(i = 0; i < (sig_src_lenght + imp_resp_lenght); i++)
		sig_dest_arr[i] = 0;
	
	
	/*y[n] = h[n] * x[n] */
	for(i = 0; i <sig_src_lenght ; i++){
		for(j = 0; j <imp_resp_lenght ; j++){
			sig_dest_arr[i+j] += imp_response_arr[i] * sig_src_arr[i];  
		}
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
		outputSignal =  output_signal[i];
		for(j = 0; j < delay; j++)
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

