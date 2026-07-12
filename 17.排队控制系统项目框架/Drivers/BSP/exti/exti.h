#ifndef __EXTI_H__
#define __EXTI_H__

#include "stdint.h"

#define TRUE    1
#define FALSE   0

void exti_init(void);
uint8_t ia_flag_get(void);
void ia_flag_set(uint8_t value);

#endif
