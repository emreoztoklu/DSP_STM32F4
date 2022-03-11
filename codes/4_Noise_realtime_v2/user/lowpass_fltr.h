#ifndef __LOWPASS_FLTR_H__
#define __LOWPASS_FLTR_H__
#include "arm_math.h"                   // ARM::CMSIS:DSP

/*Finite Impulse Response (FIR) Initialize*/
void low_pass_filter_init(void);


/*filtering input signals   return is filtered output signal.*/
q15_t low_pass_filter(q15_t *input);


#endif

