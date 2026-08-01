#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "esp8266.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    esp8266_init(115200);
    printf("hello world!\r\n");
    
    while(1)
    { 
          esp8266_receive_data();
//        esp8266_test();
        delay_ms(10);
    }
}

