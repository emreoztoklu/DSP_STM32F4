#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define	SIG_LENGTH		200
#define IMP_RSP_LENGTH		29
extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LENGTH];

float32_t REX[SIG_LENGTH/2 ];
float32_t IMX[SIG_LENGTH/2];



void plot_input_signal(void);
void plot_both_signal(void);

float32_t inputSample;
float32_t rexSample;
float32_t imxSample;

void plot_imp_response(void);
void plot_output_signal(void);
void plot_all(void);
void calc_sig_dft(float32_t *sig_src_arr, float32_t *sig_dest_rex_arr, float32_t *sig_dest_imx_arr, uint32_t sig_length);
void plot_rex_signal(void);
void get_dft_output_mag(void);

uint32_t freq;

int main()
{
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	calc_sig_dft(&inputSignal_f32_1kHz_15kHz[0],&REX[0], &IMX[0],SIG_LENGTH);
	get_dft_output_mag();
	plot_rex_signal();

 

	while(1)
	{
	}
}



 void calc_running_sum(float32_t *sig_src_arr,float32_t *sig_dest_arr,uint32_t sig_length)
 {
	 int i;
	 sig_src_arr[0] = sig_dest_arr[0];
	 for(i=0;i<sig_length;i++)
	 {
		 sig_dest_arr[i]= sig_dest_arr[i-1]+sig_src_arr[i];
	 }
 }
 
  void calc_first_difference(float32_t *sig_src_arr,float32_t *sig_dest_arr, uint32_t sig_length)
{
		sig_dest_arr[0] =0;
		int  i;
		for(i=0;i<sig_length;i++)
		{
			 sig_dest_arr[i] = sig_src_arr[i] - sig_src_arr[i-1];
		}
}





void calc_sig_dft(float32_t *sig_src_arr, float32_t *sig_dest_rex_arr, float32_t *sig_dest_imx_arr, uint32_t sig_length){
	int i,k,j;
	for(j=0;j<(sig_length/2);j++)
	{
		 sig_dest_rex_arr[j] =0;
		  sig_dest_imx_arr[j] =0;
	}
	
	 for(k=0;k<(sig_length/2);k++){
		for(i=0;i<sig_length;i++){
			sig_dest_rex_arr[k] =  sig_dest_rex_arr[k] + sig_src_arr[i]*cos(2*PI*k*i/sig_length);
			sig_dest_imx_arr[k] =  sig_dest_imx_arr[k] - sig_src_arr[i]*sin(2*PI*k*i/sig_length);		// - işareti kontrol etmen gerekebilir
		}
	}
}


void get_dft_output_mag(void){
	int k;
	for(k=0;k<(SIG_LENGTH/2);k++){
	 REX[k] = fabs(REX[k]);
	}
}


void plot_rex_signal(void){
	int i,j;
	 for(i=0;i<(SIG_LENGTH/2);i++)
	{
		rexSample = REX[i];
	  for(j=0;j<3000;j++){}
	}
}


void SysTick_Handler(void){
	 HAL_IncTick();
	 HAL_SYSTICK_IRQHandler();
	
}