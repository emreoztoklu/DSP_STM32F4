#include "stm32f4xx.h"


#define GPIOAEN  	(1U<<0)
#define PIN5     	(1U<<5)
#define LED_PIN   	(PIN5)

void Init_GPIOA(void){

	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;
	/*Set PA5 to output mode*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
}

void Task_LedOnOff(void){

	GPIOA->ODR ^= LED_PIN;		/*Toggle the pin*/
	for(int i = 0; i<100000; i++)
		;
}

int main (){

	Init_GPIOA();

	while(1){
		Task_LedOnOff();
	}
}





