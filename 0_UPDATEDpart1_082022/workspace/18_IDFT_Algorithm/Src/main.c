/*
 * https://www.keil.com/pack/doc/CMSIS/DSP/html/index.html
 * https://www.udemy.com/course/arm-cortex-dsp/learn/lecture/33321742#reviews
 * */

#include <stdio.h>

#include "stm32f4xx.h"
#include "signals.h"
#include "uart.h"
#include "dft_algorithm.h"
#include "sys_tick.h"

#define arr_size(x)        (sizeof(x)/sizeof(x[0]))

#define OFFSET1		5
#define OFFSET2		10


/*data types*/
float g_input_SigSample;
float g_impluse_rsp_Sample;  //6kHz Cutt-off frequence of Low-pass filter
float g_output_Sample;


/**********SIGNALS**********************/
/*1Khz & 15Khz Mixed Signal*/
extern const float32_t inputSignal_f32_1kHz_15kHz[INPUT_SIGNAL_LEN_KHZ_1_15];
/*6Khz Low-pass filter Impulse Response*/
extern const float32_t  impulse_response[IMPULSE_SIG_LENGTH];



/*640 point ECG signal*/
extern const float32_t _640_points_ecg_[ECG_SIG_LENGTH];

/*this array will keep it idft_output signal*/
float32_t g_output_signal_arr[ECG_SIG_LENGTH];

//////////////////////////////////////////////////
/*DFT calculatın ReX & ImX buffers*/
float ReX_buffer[ECG_SIG_LENGTH/2];
float ImX_buffer[ECG_SIG_LENGTH/2];
//////////////////////////////////////////////////



/******************************************/
/*Function prototypes */

/*Input Signal*/
static void plot_input_signal(void);
static void serial_plot_input_signal(void);

/*Impulse Responce of the System*/
static void plot_impulse_response(void);
static void serial_plot_impulse_response(void);

/*Output Signal*/
static void plot_output_signal(void);
static void serial_plot_output_signal(void);

void serial_plot_all(void);
void serial_plot_all_2(void);

/*DFT  ReX & Imx plot functions*/
static void serial_plot_ReX(void);
static void serial_plot_ImX(void);

/*plot ECG signal*/
static void serial_plot_ECG(void);
static void serial_plot_origECG_and_idftECG(void);
/******************************************/
static void FPU_enable_Init(void);
static void pseudo_delay(int delay);
/***********************
 *
 *
************************/
int main (){
	/*Init Float point*/
	FPU_enable_Init();

	/*Initialize the uart*/
	Uart2_Tx_Init(UART_BAUDRATE_115200);

	/*Initialize SysTick*/
	Systick_Init();


/******************************************************************/
//https://www.udemy.com/course/arm-cortex-dsp/learn/lecture/33321722#reviews

/*Calculation DFT of the input signal*/
	dft_signal_calc((float32_t*) _640_points_ecg_,
					(float32_t*) ReX_buffer,
					(float32_t*) ImX_buffer,
					(uint32_t) ECG_SIG_LENGTH);

/*Calculation IDFT from ReX_buffer and ImX buffer*/
	idft_signal_calc((float32_t*) g_output_signal_arr,
			         (float32_t*) ReX_buffer,
					 (float32_t*) ImX_buffer,
					 (uint32_t) ECG_SIG_LENGTH);


	//get_dft_output_magnitude((float32_t*)ReX_buffer, (uint32_t) INPUT_SIGNAL_LEN_KHZ_1_15/2);

/******************************************************************/


	while(1){
		// Watch on Arduino serial plotter
		//or https://x-io.co.uk/serial-oscilloscope/
		serial_plot_origECG_and_idftECG();
	}//while loop

} //main



/***********************
*
*
************************/
static void FPU_enable_Init(void){
	/*Enable Floating point unit*/
	/*Doc: Cortex™-M4 Devices Generic User Guide*/
	/*System Control Block (SCB)*/
	/*Coprocessor Access Control Register*/
		/*0b11 = Full access.  (3UL)*/

#define CP10  (2*10)   /*21 20*/
#define CP11  (2*11)   /*23 22*/

	SCB->CPACR |= ((3UL << CP10) | (3UL << CP11));
}

/*********************************************/
/*********************************************/
/*plot ECG signal*/
static void serial_plot_ECG(void){
	for(int i = 0; i < ECG_SIG_LENGTH; i++){
		printf("%f\n\r", _640_points_ecg_[i]);
		pseudo_delay(9000);
	}
}

static void serial_plot_origECG_and_idftECG(void){
	for(int i = 0; i < ECG_SIG_LENGTH; i++){
		printf("%f,", OFFSET1 + _640_points_ecg_[i]);
		printf("%f\n\r", g_output_signal_arr[i]);
		pseudo_delay(9000);
	}
}



/*********************************************/
/*plot ReX + ImX  signal*/
static void serial_plot_ReX(void){
	for(int i = 0; i < INPUT_SIGNAL_LEN_KHZ_1_15 /2 ; i++){
		printf("%f\n\r", ReX_buffer[i]);
		pseudo_delay(9000);
	}
}

static void serial_plot_ImX(void){
	for(int i = 0; i < INPUT_SIGNAL_LEN_KHZ_1_15 /2 ; i++){
		printf("%f\n\r", ImX_buffer[i]);
		pseudo_delay(9000);
	}
}
/*********************************************/
static void plot_input_signal(void){
	/*
	 * The signal is 1Khz -- 15Khz Mixed Sin. signal
	 * */
	for ( int i = 0; i < INPUT_SIGNAL_LEN_KHZ_1_15; i++){
		g_input_SigSample = inputSignal_f32_1kHz_15kHz[i];
		pseudo_delay(9000);
	}
}
static void plot_impulse_response(void){
	for ( int i = 0; i < IMPULSE_SIG_LENGTH; i++){
		g_impluse_rsp_Sample = impulse_response[i];
		pseudo_delay(9000);
	}
}
static void plot_output_signal(void){

	uint32_t output_sig_lenght = arr_size(g_output_signal_arr);

	for ( int i = 0; i < output_sig_lenght; i++){
		g_output_Sample = g_output_signal_arr[i];
		pseudo_delay(9000);
	}
}
/*********************************************/
void serial_plot_all(void){
	//NOTE: https://www.udemy.com/course/arm-cortex-dsp/learn/lecture/33309590#reviews
	uint32_t i,j,k;
	i = j = 0;

	for( k = 0; k < (INPUT_SIGNAL_LEN_KHZ_1_15 + IMPULSE_SIG_LENGTH - 1); k++){

		(i==INPUT_SIGNAL_LEN_KHZ_1_15) ? i=0 : printf("%f,",OFFSET1 +inputSignal_f32_1kHz_15kHz[i++]);
		(j==IMPULSE_SIG_LENGTH) ? j=0 : printf("%f,",OFFSET2 + impulse_response[j++]);

		printf("%f\n\r",g_output_signal_arr[k]);

		pseudo_delay(9000);
	}
}
void serial_plot_all_2(void){
	//NOTE: https://www.udemy.com/course/arm-cortex-dsp/learn/lecture/33321696#reviews
	for(uint32_t k = 0; k < (INPUT_SIGNAL_LEN_KHZ_1_15); k++){
		printf("%f,",OFFSET1 + inputSignal_f32_1kHz_15kHz[k]);
		printf("%f\n\r",g_output_signal_arr[k]);
		pseudo_delay(9000);
	}
}
/*********************************************/

static void serial_plot_input_signal(void){
	for ( int i = 0; i < INPUT_SIGNAL_LEN_KHZ_1_15; i++){
		printf("%f\r\n", inputSignal_f32_1kHz_15kHz[i]);
		pseudo_delay(9000);
	}
}
static void serial_plot_impulse_response(void){
	for ( int i = 0; i < IMPULSE_SIG_LENGTH; i++){
		printf("%f\r\n", impulse_response[i]);
		pseudo_delay(9000);
	}
}
static void serial_plot_output_signal(void){
	uint32_t output_sig_lenght = (INPUT_SIGNAL_LEN_KHZ_1_15 + IMPULSE_SIG_LENGTH - 1);

	for ( int i = 0; i < output_sig_lenght; i++){
		printf("%f\r\n", g_output_signal_arr[i]);
		pseudo_delay(9000);
	}
}

static void pseudo_delay(int delay){
	for(int i = 0; i < delay; i++)
		;
}
