#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "stm32f4xx.h"                  // Device header

int32_t count1, count2, count3;


void thread1(void const *argument){
	
	while(1){
	
		++count1;
	}
}


void thread2(void const *argument){
	
	while(1){
		
		++count2;
	}
}


void thread3(void const *argument){
	
	while(1){
		
		++count3;
	}
}

osThreadDef(thread1,osPriorityNormal, 1, 0);
osThreadDef(thread2,osPriorityNormal, 1, 0);
osThreadDef(thread3,osPriorityNormal, 1, 0);


int main(void){
	
	osThreadCreate(osThread(thread1), NULL);
	osThreadCreate(osThread(thread2), NULL);
	osThreadCreate(osThread(thread3), NULL);
	
	while(1){
	
	}
}


