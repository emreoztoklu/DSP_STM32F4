/**********************************************************
* project_name : 24_ADC_Driver_LIVE_EXAMPLE
* file_name    : adc.h
*
* date         : Sep 1, 2022
* file_path    : /24_ADC_Driver_LIVE_EXAMPLE/Inc/adc.h
*
* Autor        : Eng.Emre ÖZTOKLU
***********************************************************/
#ifndef ADC_H_
#define ADC_H_

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************/
/*INCLUDES*/
/*********************************************************/
#include "stm32f4xx.h"



/*********************************************************/
/*Data types*/
/*********************************************************/



/*********************************************************/
/*function prototypes*/
/*********************************************************/
void PA1_ADC_init(void);
void Start_Conversion(void);
uint32_t Read_ADC(void);




#ifdef __cplusplus
}
#endif

#endif /* ADC_H_ */
