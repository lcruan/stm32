#ifndef __DELAY_H__
#define __DELAY_H__

#include "sys.h"

enum key_num
{
    KEY_SET = 1,
    KEY_SHIFT,
    KEY_UP,
    KEY_DOWN
};


void delay_ms(uint32_t nms);            /* 延时nms */
void delay_us(uint32_t nus);            /* 延时nus */
void delay_s(uint32_t ns);              /* 延时ns */
void HAL_Delay(uint32_t nms);           /* 延时nms */


#endif





























