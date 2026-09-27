#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "dht11.h"
#include "string.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    printf("hello world!\r\n");
    
    uint8_t dht11_result[4];
    
    while(1)
    {
        memset(dht11_result, 0, 4);
        dht11_read(dht11_result);
    }
}

