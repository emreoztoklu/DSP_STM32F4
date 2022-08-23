#include "stm32f4xx.h"
#include "signals.h"

/*data types*/

float g_SigSample;



/*Function prototypes */
void Task_set_FPU_unit(void);
static void plot_input_signal(void);
static void pseudo_delay(int delay);


int main (){
	Task_set_FPU_unit();


	while(1){
		plot_input_signal();

	}

}


void Task_set_FPU_unit(void){
	/*Enable Floating point unit*/
	/*Doc: Cortex™-M4 Devices Generic User Guide*/
	/*System Control Block (SCB)*/
	/*Coprocessor Access Control Register*/
		/*0b11 = Full access.  (3UL)*/
#define CP10  (2*10)   /*21 20*/
#define CP11  (2*11)   /*23 22*/

	SCB->CPACR |= ((3UL << CP10) | (3UL << CP11));
}


static void plot_input_signal(){
	for ( int i = 0; i < SIG_LEN_5HZ; i++){
		g_SigSample = _5hz_signal[i];
		pseudo_delay(9000);
	}
}

static void pseudo_delay(int delay){
	for(int i = 0; i < delay; i++)
		;
}


