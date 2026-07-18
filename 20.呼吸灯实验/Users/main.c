#include "sys.h"
#include "delay.h"
#include "led.h"
#include "pwm.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    pwm_init(500 - 1, 72 - 1);
    uint16_t i = 0;
    
    while(1)
    { 
        for(i = 0; i < 300; i++)
        {
            pwm_compare_set(i);
            delay_ms(10);
        }
        
        for(i = 0; i < 300; i++)
        {
            pwm_compare_set(300 - i);
            delay_ms(10);
        }
        
//        led1_on();
//        led2_off();
//        delay_ms(500);
//        led1_off();
//        led2_on();
//        delay_ms(500);
    }
}

