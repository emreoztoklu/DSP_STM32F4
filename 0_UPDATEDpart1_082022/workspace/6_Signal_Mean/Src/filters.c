/*
 * filters.c
 *
 *  Created on: Aug 18, 2022
 *      Author: Eng.Emre ÖZTOKLU
 */
#include <stdint.h>

#include "arm_math.h"  //float32_t
#include "filters.h"



float32_t mean_filter(float32_t *sig_src_arr, uint32_t sig_length){

	float32_t _mean = 0.0f;

	for(uint32_t i = 0 ; i < sig_length; i++)
		_mean = _mean +  sig_src_arr[i];

	return _mean = _mean / (float32_t) sig_length ;

}

