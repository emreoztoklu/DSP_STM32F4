/**********************************************************
* project_name : 11_Convolution_Algorithm
* file_name    : algorithm.h
*
* date         : Aug 23, 2022
* file_path    : /11_Convolution_Algorithm/Inc/algorithm.h
*
* Autor        : Eng.Emre ÖZTOKLU
***********************************************************/

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* INCLUDES*/

#include "arm_math.h"  //float32_t


/* DEFINES */




/*********************************************************/
/*Data types*/
/*********************************************************/



/*********************************************************/
/*function prototypes*/
/*********************************************************/

void convolution (const float32_t *sig_src_arr, const float32_t *imp_response_arr, float32_t *sig_dest_arr,
				  uint32_t sig_src_lenght, uint32_t imp_response_lenght);




#ifdef __cplusplus
}
#endif

#endif /* ALGORITHM_H_ */
