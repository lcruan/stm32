#include "sys.h"
#include "delay.h"
#include "led.h"
#include "sg90.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    sg90_init();
//    uint16_t i = 0;
    
    while(1)
    { 
        sg90_angle_set(0); 
        delay_ms(1000);
        sg90_angle_set(20);
        delay_ms(1000);
        sg90_angle_set(40);
        delay_ms(1000);
        sg90_angle_set(90);
        delay_ms(1000);
        sg90_angle_set(180);
        delay_ms(1000);
//        for(i = 5; i <= 25; i++)
//        {
//            tim3_compare_set(i);
//            delay_ms(100);
//        }
//        
//        for(i = 5; i <= 25; i++)
//        {
//            tim3_compare_set(30 - i);
//            delay_ms(100);
//        }
        
//        led1_on();
//        led2_off();
//        delay_ms(500);
//        led1_off();
//        led2_on();
//        delay_ms(500);
    }
}

