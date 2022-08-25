/*
 * algorithm
 *
 *  Created on: Aug 23, 2022
 *      Author: Eng.Emre ÖZTOKLU
 */

#include <string.h>

#include "arm_math.h"  //float32_t
#include "signals.h"

#include "algorithm.h"


#define arr_size(x)        (sizeof(x)/sizeof(x[0]))

/****************************************************************************/
/* CONVOLUTION
 * NOTE:
 * {USERNAME} \DSP\DSP_ARM\DSP_STM32F4\0_UPDATEDpart1_082022\images
 * file_name: 00_DSP_ARM_FEATURE_38.jpg
 * */


void convolution(const float32_t *sig_src_arr, const float32_t *imp_response_arr, float32_t *sig_dest_arr, uint32_t sig_src_lenght, uint32_t imp_response_lenght){
	uint32_t i, j;
	uint32_t sig_dest_lenght = (sig_src_lenght + imp_response_lenght - 1);

	// Clean dest_arry  or  use memset func. to clean dest buffer for new values
	for (i = 0; i < sig_dest_lenght ; i++)
		sig_dest_arr[i] = 0;
	// Test this func: memset((void*)sig_dest_arr, 0, arr_size(sig_dest_arr));

	//Perfom Convolution
	for (i = 0; i < sig_src_lenght ; i++){
		for ( j = 0; j < imp_response_lenght ; j++){
			sig_dest_arr[i + j] += sig_src_arr [i] * imp_response_arr [j];
		}
	}
}
/****************************************************************************/
/*Running Sum
 *
 * y[n] = x[n] + y[n-1]
 *
*/
void running_sum_cal(const float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_lenght){

	for(int i = 0; i < sig_lenght ; i++)
		sig_dest_arr[i] = sig_dest_arr[i-1] + sig_src_arr[i];

}
/****************************************************************************/






