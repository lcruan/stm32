#ifndef __ALARM_H__
#define __ALARM_H__

#include "stdint.h"

#define ALARM_STATUS_ON     0 // 继电器低电平触发，所以定义0
#define ALARM_STATUS_OFF    1

void alarm_init(void);
void alarm_on(void);
void alarm_off(void);
uint8_t alarm_status_get(void);

#endif
