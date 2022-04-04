#ifndef __LED_H
#define __LED_H

#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common

#define LED_PORT 	GPIOD
#define GREEN 		GPIO_PIN_12
#define ORANGE 		GPIO_PIN_13
#define RED 			GPIO_PIN_14
#define BLUE 			GPIO_PIN_15


/*function definition*/
void GPIO_Init(void);


#endif

