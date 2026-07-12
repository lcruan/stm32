#include "sys.h"
#include "delay.h"
#include "led.h"
#include "lcd1602.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    lcd1602_init();
    lcd1602_show_char();
    lcd1602_show_line(1, 2, "STM32");
    lcd1602_show_line(2, 1, "lcruan");
    while(1)
    { 
//        led1_on();
//        led2_off();
//        delay_ms(500);
//        led1_off();
//        led2_on();
//        delay_ms(500);
    }
}

