#ifndef __GATE_H__
#define __GATE_H__

#include "stdint.h"

#define GATE_STATUS_ON     0 // 继电器低电平触发，所以定义0
#define GATE_STATUS_OFF    1

void gate_init(void);
void gate_on(void);
void gate_off(void);
uint8_t gate_status_get(void);

#endif
