#ifndef __TASKS_H__
#define __TASKS_H__

#include "sys.h"

void systick_isr(void);
void led1_task(void);
void led2_task(void);
void sensor_task(void);

#endif
