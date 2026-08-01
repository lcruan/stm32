#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "esp8266.h"
#include "fan.h"
#include "string.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    esp8266_init(115200);
    fan_init();
    printf("hello world!\r\n");
    
    char recv_data[ESP8266_RX_BUF_SIZE];
    while(1)
    { 
          esp8266_receive_data(recv_data);
          if (strstr(recv_data, "ON") != NULL)
              fan_on();
          else if (strstr(recv_data, "OFF") != NULL)
              fan_off();
          
          delay_ms(10);
//        esp8266_test();
//        delay_ms(500);
    }
}

