
#include <stdint.h>
#include "uart.h"


#define GPIOAEN  		(1U<<0)
#define UART2EN  		(1U<<17)
#define CR1_TE			(1U<<3)  //Transmit enable
#define CR1_UE			(1U<<13) //USART enable


#define SR_TXE          (1U<<7)

//https://www.udemy.com/course/arm-cortex-dsp/learn/lecture/33396372#questions/18142862
#define SYS_FREQ  		(100000000)	// 100MhZ
#define APB1_CLK  		(SYS_FREQ / 2) 	// ABP1 bus_freq clock = 50

/* This used for MCU internal Clock frequency
	#define SYS_FREQ  		(16'000'000)
	#define APB1_CLK  		(SYS_FREQ)
*/


static void uart2_set_baudrate(uint32_t periph_clk , uint32_t baudrate);
void uart2_write(int ch);

int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}

void Uart2_Tx_Init(uint32_t baudrate){
/*Configure_UART GPIO_PIN*/
 /*1. Enable clock access to GPIOA
	==> RCC AHB1 peripheral clock enable register (RCC_AHB1ENR) */
	RCC->AHB1ENR |= GPIOAEN;

 /*2. PA2 mode to ALTERNATE FUNCTION MODE
    ==> GPIO port mode register (GPIOx_MODER) (x = A..E and H)*/
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);

 /*3. Set PA2 alternate function type to UART_TX (AF07)
	==> GPIO alternate function low register (GPIOx_AFRL) (x = A..E and H)
	==> GPIO alternate function high register (GPIOx_AFRH)(x = A..E and H)*/
	GPIOA->AFR[0] |= (1U<<8); /*PIN2 --> AFRL2*/
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

		/*OR Try this under commend */
			/*GPIOA->AFR[0] |= (7U<<8);*/
			/*GPIOA->AFR[0] &= ~(1U<<11)*/
/****************************************************************************/
/*Configure_UART*/

	/*1. Enable clock access to UART2
	 ==> RCC APB1 peripheral clock enable register (RCC_APB1ENR)
	 UART2 ENABLE bit is 17*/
	RCC->APB1ENR |= UART2EN;

	/*2. Configure Baudrate*/
	uart2_set_baudrate(APB1_CLK, baudrate);

	/*3. Configure the transfer direction
	 ==> Control register 1 (USART_CR1)*/
	USART2->CR1 = (CR1_TE);

	/*4. Enable UART module*/
	USART2->CR1 |= (CR1_UE);

}

void uart2_write(int ch){
	/*1) make sure transmit data register is empty
	 ==> Status register (USART_SR)*/
	while (!(USART2->SR & SR_TXE))
		;
	/*2) write to the transmit data register*/
	USART2->DR = (0xFF & ch);
}


static uint16_t uart_compute(uint32_t periph_clk , uint32_t baudrate){
	return ((periph_clk + (baudrate/2U))/baudrate);
}

static void uart2_set_baudrate(uint32_t periph_clk , uint32_t baudrate){

	USART2->BRR = uart_compute(periph_clk, baudrate);

}


