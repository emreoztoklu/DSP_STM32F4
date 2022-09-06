/*
 * dft_algorithm.c
 *
 *  Created on: Aug 24, 2022
 *      Author: Eng.Emre ÖZTOKLU
 */



#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "arm_math.h"  //float32_t
#include "signals.h"
#include "dft_algorithm.h"


void dft_signal_calc(float32_t* sig_src_arr, float32_t* sig_dest_rex_arr, float32_t* sig_dest_imx_arr, uint32_t sig_lenght){
	/*Clear destination buffers*/
	for(int j = 0; j < sig_lenght/2; j++){
		sig_dest_rex_arr[j] = 0;
		sig_dest_imx_arr[j] = 0;
	}

	/*Compute DFT*/
	for(int k = 0; k < sig_lenght/2; k++){
		for(int i = 0; i < sig_lenght; i++){
			sig_dest_rex_arr[k] += sig_src_arr[i] * cos(2*PI*k*i/sig_lenght);
			sig_dest_imx_arr[k] += sig_src_arr[i] * sin(2*PI*k*i/sig_lenght); // += işareti kontrol etmen gerekebilir
		}
	}
}

void get_dft_output_magnitude(float32_t* sig_src_rex_arr, uint32_t src_sig_rex_lenght){
	for(int k = 0; k < src_sig_rex_lenght; k++){
		sig_src_rex_arr[k] = fabs(sig_src_rex_arr[k]);
	}
}


void idft_signal_calc(float32_t* idft_output_arr, float32_t* sig_src_rex_arr, float32_t* sig_src_imx_arr, uint32_t idft_length){
	int i , k;
	/*Normalize Amplitude :
	 *
	 * ReX'[k] = ReX[k] / (N/2)
	 * ImX'[K] = -ImX[k]/ (N/2)
	 *
	 * 2 special cases:
	 *
	 * ReX'[0] = ReX[0] / N
	 * ReX'[N/2] = ReX[N/2] / N
	 * */
	for( k = 0; k < idft_length /2 ; k++){
		sig_src_rex_arr[k] = sig_src_rex_arr[k] / (idft_length/2);
		sig_src_imx_arr[k] = -sig_src_imx_arr[k]/ (idft_length/2);
	}
	/*special cases:*/
	sig_src_rex_arr[0] = sig_src_rex_arr[0] / (idft_length) ;
	sig_src_imx_arr[0] = -sig_src_imx_arr[0] / (idft_length) ;

	sig_src_rex_arr[idft_length/2] = sig_src_rex_arr[idft_length/2] / (idft_length) ;
	sig_src_imx_arr[idft_length/2] = -sig_src_imx_arr[idft_length/2] / (idft_length) ;

	/*CLEAR OUTPUT BUFFER*/
	for( i = 0; i < idft_length; i++)
		idft_output_arr[i] = 0;

	/*PERFORM IDFT*/
	for( k = 0; k < idft_length/2; k++){
		for ( i = 0; i< idft_length; i++){
			idft_output_arr[i] += sig_src_rex_arr[k] * cos(2*PI*k*i/idft_length);
			idft_output_arr[i] += sig_src_imx_arr[k] * sin(2*PI*k*i/idft_length);
		}
	}
}

