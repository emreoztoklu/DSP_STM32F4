#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "stm32f4xx.h"                  // Device header

#include "../drivers/leds.h"

/*******FUNCTION DECLERATIONs***********/

/*Periodic Delay thread*/
void orange_Pthread (void const*argument);

/*Normal delay threads*/
void blue_thread(void const*argument);
void red_thread(void const*argument);
void green_thread (void const*argument);


/****************************************/
/*setting up periodic timer*/
osTimerDef(orange_timer, orange_Pthread);
osTimerId orange_Id;

/****************************************/


osThreadDef(blue_thread, 	 osPriorityNormal, 1, 0);
osThreadDef(red_thread, 	 osPriorityNormal, 1, 0);
osThreadDef(orange_Pthread,osPriorityNormal, 1, 0);
osThreadDef(green_thread,  osPriorityNormal, 1, 0);


int main(void){	
	LEDS_init();
	
	osThreadCreate(osThread(orange_Pthread), NULL);
	osThreadCreate(osThread(blue_thread), NULL);
	osThreadCreate(osThread(red_thread), NULL);
	osThreadCreate(osThread(green_thread), NULL);
	
	//orange_Id = osTimerCreate(osTimer(orange_timer),osTimerPeriodic,NULL);
	orange_Id = osTimerCreate(osTimer(orange_timer),osTimerOnce,NULL);
	osTimerStart(orange_Id,1000);
	
	while(1){
		
	}
}

void orange_Pthread (void const*argument){
		
	ORANGE_toggle();
	
}


/*******************************************/
void blue_thread(void const*argument){
	
	while(1){
		BLUE_toggle();
		osDelay((uint32_t)150);  //150milisecond
	}
}

void red_thread(void const*argument){
	
	while(1){
		RED_toggle();
		osDelay((uint32_t)150);  //150milisecond
	}
}

void green_thread (void const*argument){
	
	while(1){
		GREEN_toggle();
		osDelay((uint32_t)150);  //150milisecond
	}
}