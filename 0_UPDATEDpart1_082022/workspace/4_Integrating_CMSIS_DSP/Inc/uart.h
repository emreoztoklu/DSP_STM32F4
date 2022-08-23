#ifndef __UART_H__
#define __UART_H__


#ifdef __cplusplus
extern "C" {
#endif
/**********************************************/
#include <stdint.h>
#include "stm32f4xx.h"

#define UART_BAUDRATE 	(115200)

void Uart2_Tx_Init(uint32_t baudrate);

void uart2_write(int ch);






/**********************************************/
#ifdef __cplusplus
}
#endif
#endif
