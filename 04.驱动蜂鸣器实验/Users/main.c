#include "sys.h"
#include "delay.h"
#include "beep.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    beep_init();
    while(1)
    { 
        beep_on();
        delay_ms(500);
        beep_off();
        delay_ms(500);
    }
}

