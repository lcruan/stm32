#ifndef __KEY_H__
#define __KEY_H__

#include "sys.h"

void key_init(void);
uint8_t key_scan(void); // uint8_t要包含一个stdint.h头文件，这个头文件sys.h也有

#endif
