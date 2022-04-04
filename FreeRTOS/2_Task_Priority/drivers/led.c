#include "../drivers/led.h"




void GPIO_Init(void){
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	/*GPIO Ports Clock Enable*/
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	
	/*Configure GPIO pin Output Level*/
	HAL_GPIO_WritePin(LED_PORT, GREEN | ORANGE | RED | BLUE, GPIO_PIN_RESET);
	
	/*Configure GPIO pins : PD12, PD13, PD14, PD15*/
	GPIO_InitStruct.Pin 	= GREEN | ORANGE | RED | BLUE;
	GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}

