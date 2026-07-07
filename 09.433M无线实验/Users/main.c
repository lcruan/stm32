#include "sys.h"
#include "delay.h"
#include "led.h"
#include "exti.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    exti_init(); // 手动控制led1灯开关同时，led2灯一直闪烁
    while(1)
    { 
        if (buttonA_flag_get() == TRUE)
            led1_toggle();
        
        if (buttonB_flag_get() == TRUE)
            led2_toggle();
    }
}

