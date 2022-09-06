/****************************************************************
 * Project_Name: 25_FIR_LP_Filter_ADC_LIVE_EXAMPLE
 * File_name   : fir_filter.c
 *
 *  Created on: Sep 1, 2022
 *      Author: Eng.Emre ÖZTOKLU
 *
 *****************************************************************/

/*********************  INCLUDES *********************/
#include <stdlib.h>		/*calloc*/
#include "fir_filter.h"


/*********************  FUCNTIONS ********************/

void FIR_filter_init(FIR_filter_t *fir, const float32_t * filter_kernel, const uint32_t filter_kernel_len){
/*1. Reset buffer index*/
	fir->buffer_index = 0;

/*2. Clear filter Output*/
	fir->out_put = 0.0f;

/*3. Set filter kernel*/
	fir->kernel = (float32_t*)filter_kernel;

/*4. Set filter kernel length*/
	fir->kernel_length = filter_kernel_len;

/*Dynamic allocate buffer and initialize to zero*/
	fir->buffer = (float32_t*)calloc(fir->kernel_length, sizeof(float32_t));
}


float32_t FIR_filter_update(FIR_filter_t *fir, float32_t curr_sample){

	uint32_t sum_idx;

/*1. Store lastest sample in the buffer*/
	fir->buffer[fir->buffer_index] = curr_sample;

/*2. Increment buffer index and wrap around if the end*/
	fir->buffer_index++;

	if(fir->buffer_index == fir->kernel_length){
		fir->buffer_index = 0;
	}

/*3. Perform Convolution*/
	fir->out_put = 0.0f;

	sum_idx = fir->buffer_index;

	for(int i = 0; i < (fir->kernel_length); i++){
		if(sum_idx > 0)
			sum_idx--;
		else
			sum_idx = (fir->kernel_length - 1);

		fir->out_put += fir->kernel[i] * fir->buffer[sum_idx];
	}

	return (float32_t) fir->out_put;
}



