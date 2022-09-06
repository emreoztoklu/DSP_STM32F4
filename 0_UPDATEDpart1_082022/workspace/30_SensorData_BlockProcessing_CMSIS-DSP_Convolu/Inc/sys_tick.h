/**********************************************************
* project_name : 14_DynamicPerfomance-CMSIS-DSP
* file_name    : sys_tick.h
*
* date         : Aug 23, 2022
* file_path    : /14_DynamicPerfomance-CMSIS-DSP/Inc/sys_tick.h
*
* Autor        : Eng.Emre ÖZTOKLU
***********************************************************/

#ifndef SYS_TICK_H_
#define SYS_TICK_H_

#ifdef __cplusplus
extern "C" {
#endif
/*********************************************************/
/*INCLUDES*/
/*********************************************************/
#include "stm32f4xx.h"

/*********************************************************/
/*TYPEDEFS*/
/*********************************************************/
typedef float float32_t;

/*********************************************************/
/*Data types*/
/*********************************************************/


/*********************************************************/
/*function prototypes*/
/*********************************************************/

void Systick_Init(void);

float32_t second(uint32_t val);
float32_t milli_second(uint32_t val);


#ifdef __cplusplus
}
#endif

#endif /* SYS_TICK_H_ */
