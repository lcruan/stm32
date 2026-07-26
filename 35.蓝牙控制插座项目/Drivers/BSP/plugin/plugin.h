#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "stdint.h"

#define PLUGIN_STATUS_ON     0 // 继电器低电平触发，所以定义0
#define PLUGIN_STATUS_OFF    1

void plugin_init(void);
void plugin_on(void);
void plugin_off(void);
uint8_t plugin_status_get(void);

#endif
