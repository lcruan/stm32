#include "sys.h"
#include "delay.h"
#include "led.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    // led1_on();
    // led1_off();
    while(1)
    { 
        // 方法一：使用toggle
        //led1_toggle();
        //delay_ms(500);
        
        // 方法二：循环中 开启和关闭
        led1_on();
        delay_ms(500);
        led1_off();
        delay_ms(500);
    }
}
