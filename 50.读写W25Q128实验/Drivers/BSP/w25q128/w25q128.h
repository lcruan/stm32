#ifndef __W25Q128_H__
#define __W25Q128_H__

#include "sys.h"

#define W25Q128_CS(x)   do{ x ? HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);}while(0)

void w25q128_init(void);
uint16_t w25q128_read_id(void);

#endif

