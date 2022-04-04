#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "stm32f4xx.h"                  // Device header

#include "../drivers/leds.h"

void blue_thread(void const*argument){
	
	while(1){
		BLUE_toggle();
		osDelay((uint32_t)50);  //200ms
	}
}

void red_thread(void const*argument){
	
	while(1){
		RED_toggle();
		osDelay((uint32_t)100);  //200ms
	}
}

void orange_thread (void const*argument){
	
	while(1){
		ORANGE_toggle();
		osDelay((uint32_t)150);  //200ms
	}
}

void green_thread (void const*argument){
	
	while(1){
		GREEN_toggle();
		osDelay((uint32_t)200);  //200ms
	}
}

osThreadDef(blue_thread, 	osPriorityNormal, 1, 0);
osThreadDef(red_thread, 	osPriorityNormal, 1, 0);
osThreadDef(orange_thread,osPriorityNormal, 1, 0);
osThreadDef(green_thread, osPriorityNormal, 1, 0);


int main(void){	
	LEDS_init();
	
	osThreadCreate(osThread(blue_thread), NULL);
	osThreadCreate(osThread(red_thread), NULL);
	osThreadCreate(osThread(orange_thread), NULL);
	osThreadCreate(osThread(green_thread), NULL);
	
	while(1){
		
	}
}

