#include "leds.h"

#define BLUE 				(1U<<15)
#define RED 				(1U<<14)
#define ORANGE 			(1U<<13)
#define GREEN 			(1U<<12)

#define BLUE_BIT 		(1U<<30)
#define RED_BIT  		(1U<<28)
#define ORANGE_BIT  (1U<<26)
#define GREEN_BIT 	(1U<<24)

#define GPIOD_CLOCK (1U<<3)


#define TOGGLE_BIT(REG, PORT_NO)   ((REG) ^= (PORT_NO))  // xor gate



void LEDS_init(void){
	SET_BIT(RCC->AHB1ENR, GPIOD_CLOCK);
	SET_BIT(GPIOD->MODER, RED_BIT | GREEN_BIT | BLUE_BIT | ORANGE_BIT);
}

void RED_toggle(void){
	TOGGLE_BIT(GPIOD->ODR, RED);
}

void BLUE_toggle(void){
	TOGGLE_BIT(GPIOD->ODR, BLUE);
}

void GREEN_toggle(void){
	TOGGLE_BIT(GPIOD->ODR, GREEN);
}

void ORANGE_toggle(void){
	TOGGLE_BIT(GPIOD->ODR, ORANGE);
}

