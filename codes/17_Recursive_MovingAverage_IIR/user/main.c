#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

/*DEFINES */
#define SIGNAL_LENGHT 		320 

/*********************************************/

/*DATA TYPE */
uint32_t freq;
float32_t inputSample;
float32_t outputSample;
float32_t inputMean;

extern float32_t InputSignal_f32_1kHz_15kHz[SIGNAL_LENGHT];
float32_t *inputSignal = &InputSignal_f32_1kHz_15kHz[0];
float32_t outputSignal[SIGNAL_LENGHT];

/*********************************************/
/*FUNCTION PROTOTYPES */
extern void SystemClock_Config(void);
void plot_input_signal(void);
void plot_both_signal(void);

/*filters*/
/*mean filter*/
float32_t signal_mean(float32_t *sig_src_arr, uint32_t sig_length);

/*convolution filter Moving average FIR*/
void moving_average(float32_t* sig_src_arr, float32_t* sig_out_arr, uint32_t sig_lenght, uint32_t filter_pts);

/*Recursive Moving Average IIR*/
void recursive_moving_average(float32_t* sig_src_arr, float32_t* sig_out_arr, uint32_t sig_lenght, uint32_t filter_pts);
			
/*********************************************/



int main(void){
 	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
	
	//inputMean = signal_mean((float32_t*)&inputSignal,(uint32_t)SIGNAL_LENGHT);
	//arm_mean_f32((float32_t*)&inputSignal[0], SIGNAL_LENGHT,&inputMean);
	//plot_input_signal();
	
	recursive_moving_average((float32_t*)&inputSignal[0], (float32_t*)&outputSignal[0], (uint32_t)SIGNAL_LENGHT, (uint32_t)11);
	plot_both_signal();
	
	while(1){	
	}	
}

/*Recursive Moving Average IIR*/
void recursive_moving_average(float32_t* sig_src_arr, float32_t* sig_out_arr, uint32_t sig_lenght, uint32_t filter_pts){
	int i , j;
	float64_t accumulator = 0;
	
	for(i = 0; i < filter_pts ; i++){
			accumulator = accumulator + sig_src_arr[i];   // y[i-1] burda tutuluyor
 	}
	
	sig_out_arr[(filter_pts-1/2)] = accumulator/filter_pts;  // Toplam degerlerin ortalamasi
	
	/*ceil tavan yukari yuvarla*/
	for(i = ceil(filter_pts/2); i < (sig_lenght - (filter_pts/2))-1; i++){
		/*
		y[i] = y[i-1] + x[i+p]-x[i-q]   
		p = M-1/2  "(filter_pts-1)/2    if M=11  11/2= 5.5 11-1/2 = 5"   
		q = p+1 	 "(uint8_t)ceil(filter_pts/2)	 (11-1/2)+1 = ceil(11/2) = 6"
		*/	
		accumulator += sig_src_arr[i+((filter_pts-1)/2)] - sig_src_arr[i - ((uint8_t)ceil(filter_pts/2))];
		
		sig_out_arr[i] = accumulator/filter_pts;
	}
}




/*convolution filter Moving average FIR*/
void moving_average(float32_t* sig_src_arr, float32_t* sig_out_arr, uint32_t sig_lenght, uint32_t filter_pts){
	int i,j;
	/*  
	filter_pts should be a odd number
	floor taban
	*/
	
	for(i = floor(filter_pts/2) ; i < (sig_lenght - (filter_pts/2))-1 ; i++){
		sig_out_arr[i] = 0;
		for(j = -(floor(filter_pts/2)); j < floor(filter_pts/2); j++){
			sig_out_arr[i] +=sig_src_arr[i+j];	
		}
		sig_out_arr[i] /= filter_pts;
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

void plot_both_signal(void){
	int i, j;
	uint16_t delay = 3000;
	
	for(i = 0; i < SIGNAL_LENGHT; i++){
		inputSample  = inputSignal[i];
		outputSample = outputSignal[i];
		for(j = 0; j < delay; j++)
		;
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

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

