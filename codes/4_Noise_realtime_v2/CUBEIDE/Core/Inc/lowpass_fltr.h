#ifndef __LOWPASS_FLTR_H
#define __LOWPASS_FLTR_H

#include "arm_math.h"                   // ARM::CMSIS:DSP


void low_pass_filter_init(void);
q15_t low_pass_filter(q15_t *input);













#endif
