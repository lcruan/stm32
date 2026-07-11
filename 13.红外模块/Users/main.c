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
        if(ia_flag_get() == TRUE) // 震动后，led1亮2秒关闭
        {
            led1_on();
            delay_ms(2000);
            led1_off();
            ia_flag_set(FALSE); // 解决亮4秒的问题，因为传感器太灵敏，捕获两次设置为TRUE,这里再次设置为FALSE
        }
    }
}

