#ifndef __SIGNALS_H__
#define __SIGNALS_H__

#ifdef __cplusplus
extern "C" {
#endif


/**********************************************/
#include <stdio.h>
#include "arm_math.h"		//float32_t


/*All Signals*/
#define SIG_LEN_5HZ 301
const float32_t _5hz_signal[SIG_LEN_5HZ];

#define INPUT_SIGNAL_LEN_KHZ_1_15 319
const float32_t inputSignal_f32_1kHz_15kHz[INPUT_SIGNAL_LEN_KHZ_1_15];

#define IMPULSE_SIG_LENGTH	29
const float32_t impulse_response[IMPULSE_SIG_LENGTH];

#define ECG_SIG_LENGTH	640
const float32_t _640_points_ecg_[ECG_SIG_LENGTH];



/*Designed in Matlab  check the folder: DSP_STM32F4\0_UPDATEDpart1_082022\workspace\Matlab_Signals */
#define _10HZ_100HZ_500HZ_LENGHT 1001
const float32_t Signal_10hz_100hz_500hz[_10HZ_100HZ_500HZ_LENGHT];


#define LPF_70HZ_CUTOFF_FREQ_LENGTH 101
const float32_t lpf_fc_70hz[LPF_70HZ_CUTOFF_FREQ_LENGTH];


#define HPF_400HZ_CUTOFF_FREQ_LENGTH 101
const float32_t hpf_fc_400hz[HPF_400HZ_CUTOFF_FREQ_LENGTH];

/**********************************************/
#ifdef __cplusplus
}
#endif

#endif
