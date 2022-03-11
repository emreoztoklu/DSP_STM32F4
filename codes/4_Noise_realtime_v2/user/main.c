#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP
#include "lowpass_fltr.h"
#include "sine_generator.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX


/*DEFINES*/
#define SAMPLING_FREQ		1000				// 1Khz
#define SIGNAL_FREQ			10					// 10hz
#define NOISE_FREQ			50					// 50hz
/*****************************************************************/
/*DATA TYPES*/
uint32_t freq;

sine_generator_q15_t  Signal_set;
sine_generator_q15_t  Noise_set;

q15_t sinus, noise, disturbed, filtered;

/*****************************************************************/
/*RTOS implement ID data types*/
osThreadId sineID, noiseID, disturbedID, filteredID, syncID;

/*****************************************************************/
/* FUNTION DECLERATION*/
extern void SystemClock_Config(void);

void sine_thread(void const *argument);
void noise_thread(void const *argument);
void disturbed_thread(void const *argument);
void filtered_thread(void const *argument);
void sync_thread(void const *argument);
/*****************************************************************/
/*RTOS SETUP:thread functions operating*/
osThreadDef(sine_thread, 			osPriorityNormal, 1, 0);
osThreadDef(noise_thread, 		osPriorityNormal, 1, 0);
osThreadDef(disturbed_thread, osPriorityNormal, 1, 0);
osThreadDef(filtered_thread, 	osPriorityNormal, 1, 0);
osThreadDef(sync_thread, 			osPriorityNormal, 1, 0);

/*****************************************************************/

uint32_t tim;				// each thread will run only 10ms


int main(){
	
	HAL_Init();
	SystemClock_Config();
	
	freq = HAL_RCC_GetHCLKFreq();
	
	/*user calls 	initial functions*/

	sine_generator_init_q15(&Signal_set, SIGNAL_FREQ, SAMPLING_FREQ);
	sine_generator_init_q15(&Noise_set, NOISE_FREQ, SAMPLING_FREQ);
	
	/*filtering*/
	low_pass_filter_init();
	
	/********************************/
	/*RTOS creating thread and getting ID numbers*/
	sineID = osThreadCreate(osThread(sine_thread),NULL);
	noiseID = osThreadCreate(osThread(noise_thread),NULL);
	disturbedID	= osThreadCreate(osThread(disturbed_thread),NULL);
	filteredID	= osThreadCreate(osThread(filtered_thread),NULL);
	syncID	= osThreadCreate(osThread(sync_thread),NULL);
	
	
	while(1){
		
	}
	
}


void sine_thread(void const *argument){
	while(1){
		osSignalWait(0x0001, 0);
		osDelay(tim);
		sinus = sine_calc_sample_q15(&Signal_set)/2;
		osSignalSet(noiseID, 0x0001);
	}
}


void noise_thread(void const *argument){
	while(1){
		osSignalWait(0x0001, 0);
		osDelay(tim);
		noise = sine_calc_sample_q15(&Noise_set)/6;
		osSignalSet(disturbedID, 0x0001);
	}
}


void disturbed_thread(void const *argument){
	while(1){
		osSignalWait(0x0001, 0);
		osDelay(tim);
		disturbed = sinus + noise;
		osSignalSet(filteredID, 0x0001);
	}
}


void filtered_thread(void const *argument){
	while(1){
		osSignalWait(0x0001, 0);
		osDelay(tim);
		filtered = low_pass_filter(&disturbed);
		osSignalSet(syncID, 0x0001);
	}
}


void sync_thread(void const *argument){
	while(1){
		osDelay(tim);
		osSignalWait(0x0001,osWaitForever);
		osSignalSet(sineID, 0x0001);
		
	}
}

//void SysTick_Handler (void){
//	
//	HAL_IncTick();
//	HAL_SYSTICK_IRQHandler();
//}

