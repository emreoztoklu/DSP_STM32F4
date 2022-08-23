#ifndef __SIGNALS_H__
#define __SIGNALS_H__

#ifdef __cplusplus
extern "C" {
#endif


/**********************************************/
#include <stdio.h>
#include "arm_math.h"		//float32_t

#define SIG_LEN_5HZ 301
#define INPUT_SIGNAL_LEN_KHZ_1_15 320



float _5hz_signal[SIG_LEN_5HZ];
float32_t inputSignal_f32_1kHz_15kHz[INPUT_SIGNAL_LEN_KHZ_1_15];




/**********************************************/
#ifdef __cplusplus
}
#endif

#endif
