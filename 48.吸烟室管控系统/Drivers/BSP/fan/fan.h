#ifndef __FAN_H__
#define __FAN_H__

#include "stdint.h"

#define FAN_STATUS_ON     0
#define FAN_STATUS_OFF    1

void fan_init(void);
void fan_on(void);
void fan_off(void);
uint8_t fan_status_get(void);

#endif
