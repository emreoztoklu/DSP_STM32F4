/**********************************************************
* project_name : 27_BackgroundThread
* file_name    : tim.h
*
* date         : Sep 2, 2022
* file_path    : /27_BackgroundThread/Inc/tim.h
*
* Autor        : Eng.Emre ÖZTOKLU
***********************************************************/
#ifndef TIM_H_
#define TIM_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************  INCLUDES   *******************/
#include <stdint.h>
#include "stm32f4xx.h"
/*******************  DEFINES   *******************/

#define SR_UIF  (1U << 0)

/*******************  TYPEDEF   *******************/

/*******************  MACROS   *******************/

/******************  DATA_TYPES   ****************/

/***************FUNCTION_PROTOTYPES  *************/
void TIM2_1Hz_interrupt_init(void);


#ifdef __cplusplus
}
#endif

#endif /* TIM_H_ */
