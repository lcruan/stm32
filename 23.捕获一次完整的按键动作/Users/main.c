#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "ic.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    printf("hello world!\r\n");
    ic_init(65536 - 1, 72 - 1);
    
    while(1)
    { 
        led1_on();
        led2_off();
        delay_ms(500);
        led1_off();
        led2_on();
        delay_ms(500);
    }
}

