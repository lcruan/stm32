#ifndef __ESP8266_H__
#define __ESP8266_H__

#include "sys.h"

#define ESP8266_RX_BUF_SIZE 128
#define ESP8266_TX_BUF_SIZE 64

//´íÎóÂë
#define ESP8266_EOK        0
#define ESP8266_ERROR      1
#define ESP8266_ETIMEOUT   2
#define ESP8266_EINVAL     3

void esp8266_init(uint32_t baudRate);
void esp8266_receive_data(void);
void esp8266_test(void);


#endif



