#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core


#include "../drivers/led.h"

#define BLUE_LED_STACK_SIZE   100
#define RED_LED_STACK_SIZE 		100
#define ORANGE_LED_STACK_SIZE	100
#define GREEN_LED_STACK_SIZE 	100


/*Function Definition*/
void vBlueLed_ControllerTask(void* pvParameters);
void vRedLed_ControllerTask(void* pvParameters);
void vOrangeLed_ControllerTask(void* pvParameters);
void vGreenLed_ControllerTask(void* pvParameters);


int main(void){
	GPIO_Init();
	
	xTaskCreate(vBlueLed_ControllerTask,  "Blue Led Controller",  BLUE_LED_STACK_SIZE,  NULL, 1, NULL);
	xTaskCreate(vRedLed_ControllerTask, 	"Red Led Controller", 	RED_LED_STACK_SIZE, 	NULL, 1, NULL);
	xTaskCreate(vOrangeLed_ControllerTask,"Orange Led Controller",ORANGE_LED_STACK_SIZE,NULL, 1, NULL);
	xTaskCreate(vGreenLed_ControllerTask, "Green Led Controller", GREEN_LED_STACK_SIZE, NULL, 1, NULL);
	
	vTaskStartScheduler();
	
	while(1){
			
	}
}


void vBlueLed_ControllerTask(void* pvParameters){
	int i;
	
	while(1){
		HAL_GPIO_TogglePin(LED_PORT, BLUE);
		for(i = 0; i < 7000; i++)
		;
	}
}

void vRedLed_ControllerTask(void* pvParameters){
	int i;
	
	while(1){
		HAL_GPIO_TogglePin(LED_PORT, RED);
		for(i = 0; i < 7000; i++)
		;
	}
}

void vOrangeLed_ControllerTask(void* pvParameters){
	int i;
	
	while(1){
		HAL_GPIO_TogglePin(LED_PORT, ORANGE);
		for(i = 0; i < 7000; i++)
		;
	}
}

void vGreenLed_ControllerTask(void* pvParameters){
	int i;
	
	while(1){
		HAL_GPIO_TogglePin(LED_PORT, GREEN);
		for(i = 0; i < 7000; i++)
		;
	}
}

