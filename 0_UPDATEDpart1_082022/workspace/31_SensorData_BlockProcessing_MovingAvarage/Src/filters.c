/*
 * filters.c
 *
 *  Created on: Aug 18, 2022
 *      Author: Eng.Emre ÖZTOKLU
 */
#include <stdint.h>

#include "arm_math.h"  //float32_t
#include "filters.h"


float32_t signal_mean(float32_t *sig_src_arr, uint32_t sig_length){
	float32_t _mean = 0.0f;

	for(uint32_t i = 0 ; i < sig_length; i++)
		_mean = _mean +  sig_src_arr[i];

	return _mean = _mean / (float32_t) sig_length ;
}

float32_t signal_variance(float32_t* sig_src_arr, float32_t sig_mean, uint32_t sig_length){
	float32_t _variance = 0.0f;

	for(uint32_t i = 0; i<sig_length; i++)
		_variance = _variance + powf((sig_src_arr[i]- sig_mean),2);

	return _variance = _variance/(sig_length-1);
}

/*Standart Deviation*/
float32_t signal_std(float32_t sig_variance){
	float32_t std;

	return std = sqrt(sig_variance);
}

/***************************************//***************************************/
/*Hareketli Ortalama (Moving average)
 *
 * Check :https://www.youtube.com/watch?v=rttn46_Y3c8
 *
 * This filter same like FIR filter, so Low-pass-filter
 *
 * */

/*Moving average will keep your nosiy signal filtered and smooth same like LPF*/

void moving_average(float32_t * sig_src_arr, float32_t* sig_out_arr, uint32_t signal_length, uint32_t filter_points){

	for (int i = floor(filter_points/2); i < (signal_length - (filter_points/2)); i++){
		sig_out_arr[i] = 0;

		for(int j = -(floor(filter_points/2)); j < floor(filter_points/2); j++){
			sig_out_arr[i] += sig_src_arr[i+j];

		}
		sig_out_arr[i] = sig_out_arr[i]/filter_points;
	}

}

/***************************************//***************************************/

void moving_average_2(uint32_t * sig_src_arr, uint32_t* sig_out_arr, uint32_t signal_length, uint32_t filter_points){

	for (int i = floor(filter_points/2); i < (signal_length - (filter_points/2)); i++){
		sig_out_arr[i] = 0;

		for(int j = -(floor(filter_points/2)); j < floor(filter_points/2); j++){
			sig_out_arr[i] += sig_src_arr[i+j];

		}
		sig_out_arr[i] = sig_out_arr[i]/filter_points;
	}

}



























