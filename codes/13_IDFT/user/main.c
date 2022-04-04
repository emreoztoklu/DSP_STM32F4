#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

/*DEFINES */
#define SIGNAL_LENGHT 				320 
#define IMPULSE_RESP_LENGHT 	29
#define ECG_SIG_SIZE					640

/*********************************************/
/*extern DATA TYPE */
extern float32_t InputSignal_f32_1kHz_15kHz[SIGNAL_LENGHT];     // Time Domain Signal
float32_t *inputSignal = &InputSignal_f32_1kHz_15kHz[0];


extern float32_t _640_points_ecg_[ECG_SIG_SIZE];
float32_t *ecg_inputSignal = &_640_points_ecg_[0];



/*****************************DATA TYPE****************************/
uint32_t freq;
float32_t inputSample;
float32_t outputSample;
float32_t ecg_signal;
float32_t idft_outputSample;

float_t output_signal_arr[SIGNAL_LENGHT];

/*for DFT solution*/
float32_t ReX[SIGNAL_LENGHT/2];
float32_t ImX[SIGNAL_LENGHT/2];
float32_t ReX_signal;
float32_t ImX_signal;

/*for IDFT solution*/
float32_t ecg_ReX[ECG_SIG_SIZE/2];
float32_t ecg_ImX[ECG_SIG_SIZE/2];
float32_t ecg_ReXsignal;
float32_t ecg_ImXsignal;

/*for IDFT solution*/
float32_t idft_output_sig[ECG_SIG_SIZE];



/*********************************************/
/*FUNCTION PROTOTYPES */
extern void SystemClock_Config(void);
void plot_input_signal(void);
void plot_output_signal(void);
void plot_both_signal(void);
void plot_ecg_signal(void);
void plot_ecg_idft_signal(void);
void plot_ecg_rex_signal(void);
void plot_originalSig_and_idftSig(void);
void plot_signal(float32_t * src_signal, uint32_t sig_lenght, float32_t *sample);








/*Calculate Running Sum*/
void calc_running_sum(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_lenght);

/*Calculate First difference*/
void calc_first_difference(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_lenght);

/*Calculate DFT of signal*/
void calc_sig_DFT(float32_t *sig_src_arr, float32_t *sig_dest_rex_arr, float32_t *sig_dest_imx_arr, uint32_t sig_lenght);
void calc_sig_IDFT(float32_t *idft_out_arr, float32_t *sig_src_rex_arr, float32_t *sig_src_imx_arr, uint32_t idft_lenght);

void get_DFT_output_Magnitude(void);
void get_ecgDFT_output_Magnitude(void);
void plot_rex_signal(void);








/*********************************************/

int main(void){
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
	calc_sig_DFT((float32_t*)&ecg_inputSignal[0],(float32_t*)&ecg_ReX[0],(float32_t*)&ecg_ImX[0],(uint32_t) ECG_SIG_SIZE);
	calc_sig_IDFT((float32_t*)&idft_output_sig[0],(float32_t*)&ecg_ReX[0],(float32_t*)&ecg_ImX[0],(uint32_t) ECG_SIG_SIZE);
	plot_originalSig_and_idftSig();
	
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

void calc_sig_IDFT(float32_t *idft_out_arr, float32_t *sig_src_rex_arr, float32_t *sig_src_imx_arr, uint32_t idft_lenght){
	int i, j ,k;
	
	for(k =0; k < (idft_lenght/2); k++){
		sig_src_rex_arr [k] = sig_src_rex_arr[k]/(idft_lenght/2);
		sig_src_imx_arr [k] = -sig_src_imx_arr[k]/(idft_lenght/2);
	}
	
	sig_src_rex_arr [0] = sig_src_rex_arr[0]/(idft_lenght);
	sig_src_imx_arr [0] = -sig_src_imx_arr[0]/(idft_lenght);

	for(i =0; i < (idft_lenght); i++){
		idft_out_arr[i] = 0;
	}
	
	for(k =0; k < (idft_lenght/2); k++){
		for(i =0; i < (idft_lenght); i++){
				idft_out_arr[i] += sig_src_rex_arr[k] * cos (2 * PI * k * i / idft_lenght); 
				idft_out_arr[i] += sig_src_imx_arr[k] * sin (2 * PI * k * i / idft_lenght); 
		}
	}
}

/*****************************************/
void get_DFT_output_Magnitude(void){
	int k;
	
	for(k = 0; k < SIGNAL_LENGHT/2; k++){
		ReX[k] = fabs(ReX[k]);
	}

}

void get_ecgDFT_output_Magnitude(void){
	int k;
	
	for(k = 0; k < ECG_SIG_SIZE/2; k++){
		ecg_ReX[k] = fabs(ecg_ReX[k]);
	}
}



/*****************************************/
void plot_ecg_signal(void){
	int i, j;
	for(i = 0; i < ECG_SIG_SIZE; i++){
		ecg_signal =  _640_points_ecg_[i];
		for(j = 0; j < 6000; j++)
		;
		if(i == ECG_SIG_SIZE-1)i = 0;
	}
}

void plot_ecg_idft_signal(void){
	int i, j;
	for(i = 0; i < ECG_SIG_SIZE; i++){
		idft_outputSample =  idft_output_sig[i];
		for(j = 0; j < 6000; j++)
		;
	}
}

void plot_originalSig_and_idftSig(void){
	int i, j;
	for(i = 0; i < ECG_SIG_SIZE; i++){
		ecg_signal =  _640_points_ecg_[i];
		idft_outputSample =  idft_output_sig[i];
		for(j = 0; j < 6000; j++)
		;
		if (i == ECG_SIG_SIZE-1) i = 0;
	}
}

/*****************************************/
void plot_rex_signal(void){
	int i, j;
	for(i = 0; i < SIGNAL_LENGHT/2; i++){
		ReX_signal =  ReX[i];
		for(j = 0; j < 6000; j++)
		;
	}
}

void plot_ecg_rex_signal(void){
	int i, j;
	for(i = 0; i < ECG_SIG_SIZE/2; i++){
		ecg_ReXsignal =  ecg_ReX[i];
		for(j = 0; j < 3000; j++)
		;
	}
}
/*****************************************/
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

