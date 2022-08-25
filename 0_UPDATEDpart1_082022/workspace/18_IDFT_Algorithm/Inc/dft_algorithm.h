/**********************************************************
* project_name : 16_DFT_Algorithm
* file_name    : dft_algorithm.h
*
* date         : Aug 24, 2022
* file_path    : /16_DFT_Algorithm/Inc/dft_algorithm.h
*
* Autor        : Eng.Emre ÖZTOKLU
***********************************************************/

#ifndef DFT_ALGORITHM_H_
#define DFT_ALGORITHM_H_

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************/
/*INCLUDES*/
/*********************************************************/
#include "stm32f4xx.h"
#include "arm_math.h"  //float32_t
#include "signals.h"


/*********************************************************/
/*Data types*/
/*********************************************************/




/*********************************************************/
/*function prototypes*/
/*********************************************************/


void dft_signal_calc(float32_t* sig_src_arr, float32_t * sig_dest_rex_arr, float32_t * sig_dest_imx_arr, uint32_t sig_lenght);
void get_dft_output_magnitude(float32_t* sig_rex_arr, uint32_t sig_rex_lenght);


void idft_signal_calc(float32_t * idft_output_arr, float32_t * sig_src_rex_arr, float32_t * sig_src_imx_arr, uint32_t idft_length);





#ifdef __cplusplus
}
#endif

#endif /* DFT_ALGORITHM_H_ */
