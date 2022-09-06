/**********************************************************
* project_name : 25_FIR_LP_Filter_ADC_LIVE_EXAMPLE
* file_name    : fir_filter.h
*
* date         : Sep 1, 2022
* file_path    : /25_FIR_LP_Filter_ADC_LIVE_EXAMPLE/Inc/fir_filter.h
*
* Autor        : Eng.Emre ÖZTOKLU
***********************************************************/
#ifndef FIR_FILTER_H_
#define FIR_FILTER_H_

#ifdef __cplusplus
extern "C" {
#endif

/********************* INCLUDES  **************************/
#include <stdint.h>
#include "arm_math.h"  //float32_t


/********************** DEFINES  *************************/

/********************** TYPEDEF **************************/

typedef struct{
	float32_t *buffer;
	uint32_t buffer_index;
	float32_t * kernel;
	uint32_t kernel_length;
	float32_t out_put;
}FIR_filter_t;


/*********************************************************/
/*Data types*/
/*********************************************************/



/*********************************************************/
/*function prototypes*/
/*********************************************************/
void FIR_filter_init(FIR_filter_t * fir,  const float32_t * filter_kernel, const uint32_t filter_kernel_len);
float32_t FIR_filter_update(FIR_filter_t * fir, float32_t curr_sample);



#ifdef __cplusplus
}
#endif

#endif /* FIR_FILTER_H_ */
