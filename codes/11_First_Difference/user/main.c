#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

/*DEFINES */
#define SIGNAL_LENGHT 				200 
#define IMPULSE_RESP_LENGHT 	29

/*********************************************/
/*extern DATA TYPE */
extern float32_t InputSignal_f32_1kHz_15kHz[SIGNAL_LENGHT];     // Time Domain Signal
float32_t *inputSignal = &InputSignal_f32_1kHz_15kHz[0];

/*DATA TYPE */
uint32_t freq;
float32_t inputSample;
float32_t outputSample;

float_t output_signal_arr[SIGNAL_LENGHT];

/*for DFT solution*/
float_t ReX[SIGNAL_LENGHT/2];
float_t ImX[SIGNAL_LENGHT/2];
float32_t ReX_signal;
float32_t ImX_signal;

/*********************************************/
/*FUNCTION PROTOTYPES */
extern void SystemClock_Config(void);
void plot_input_signal(void);
void plot_output_signal(void);
void plot_both_signal(void);

void plot_signal(float32_t * src_signal, uint32_t sig_lenght, float32_t *sample);

/*Calculate Running Sum*/
void calc_running_sum(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_lenght);

/*Calculate First difference*/
void calc_first_difference(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_lenght);

/*Calculate DFT of signal*/
void calc_sig_DFT(float32_t *sig_src_arr, float32_t *sig_dest_rex_arr, float32_t *sig_dest_imx_arr, uint32_t sig_lenght);
void get_DFT_output_Magnitude(void);
void plot_rex_signal(void);

/*********************************************/

int main(void){
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
//  calc_first_difference((float32_t*)&inputSignal[0], (float32_t*)&output_signal_arr[0], (uint32_t)SIGNAL_LENGHT);
//	plot_both_signal();
		
	calc_sig_DFT((float32_t*)&inputSignal[0], (float32_t*)&ReX[0], (float32_t*)&ImX[0], (uint32_t)SIGNAL_LENGHT);
	get_DFT_output_Magnitude();
	plot_rex_signal();	


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

void calc_sig_DFT(float32_t *sig_src_arr, float32_t *sig_dest_rex_arr, float32_t *sig_dest_imx_arr, uint32_t sig_lenght){
	int i, j, k;
	
	for( j = 0; j < sig_lenght/2; j++){
		sig_dest_rex_arr[j] = 0;
		sig_dest_imx_arr[j] = 0;
	}
	
	for(k=0;k < sig_lenght/2; k++){
		for(i=0; i < sig_lenght; i++){
			sig_dest_rex_arr[k] += sig_src_arr[i] * cos(2*PI*k*i/sig_lenght); 
			sig_dest_imx_arr[k] -= sig_src_arr[i] * sin(2*PI*k*i/sig_lenght);
		}
	}
}

void get_DFT_output_Magnitude(void){
	int k;
	
	for(k = 0; k < SIGNAL_LENGHT/2; k++){
		ReX[k] = fabs(ReX[k]);
	}

}



void plot_rex_signal(void){
	int i, j;
	for(i = 0; i < SIGNAL_LENGHT/2; i++){
		ReX_signal =  ReX[i];
		for(j = 0; j < 6000; j++)
		;
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

