#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core

#include "../drivers/led.h"

#define BLUE_LED_STACK_SIZE   100
#define RED_LED_STACK_SIZE 		100
#define ORANGE_LED_STACK_SIZE	100
#define GREEN_LED_STACK_SIZE 	100



/*Function Definition*/
void vBlueLedControllerTask(void* pvParameters);
void vRedLedControllerTask(void* pvParameters);
void vOrangeLedControllerTask(void* pvParameters);
void vGreenLedControllerTask(void* pvParameters);


int main(void){
	GPIO_Init();
	
	xTaskCreate(vBlueLedControllerTask, 	"Blue Led Controller", 	BLUE_LED_STACK_SIZE, 		NULL, 1, NULL);
	xTaskCreate(vRedLedControllerTask, 		"Red Led Controller", 	RED_LED_STACK_SIZE, 		NULL, 1, NULL);
	xTaskCreate(vOrangeLedControllerTask, "Orange Led Controller",ORANGE_LED_STACK_SIZE, 	NULL, 1, NULL);
	xTaskCreate(vGreenLedControllerTask, 	"Green Led Controller", GREEN_LED_STACK_SIZE, 	NULL, 1, NULL);
	
	vTaskStartScheduler();
	
	while(1){
			
		
	}
}


void vBlueLedControllerTask(void* pvParameters){
	int i;
	
	while(1){
		HAL_GPIO_TogglePin(GPIOD, BLUE);
		for(i = 0; i < 700000; i++)
		;
	}
}

void vRedLedControllerTask(void* pvParameters){
	int i;
	
	while(1){
		HAL_GPIO_TogglePin(GPIOD, RED);
		for(i = 0; i < 700000; i++)
		;
	}
}

void vOrangeLedControllerTask(void* pvParameters){
	int i;
	
	while(1){
		HAL_GPIO_TogglePin(GPIOD, ORANGE);
		for(i = 0; i < 700000; i++)
		;
	}
}

void vGreenLedControllerTask(void* pvParameters){
	int i;
	
	while(1){
		HAL_GPIO_TogglePin(GPIOD, GREEN);
		for(i = 0; i < 700000; i++)
		;
	}
}