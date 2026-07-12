#include "sys.h"
#include "delay.h"
#include "led.h"
#include "lcd1602.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟, 72Mhz */
    led_init();                         /* 初始化LED灯 */
    lcd1602_init();
    //lcd1602_show_char();
    lcd1602_show_line(1, 2, "STM32");
    lcd1602_show_line(2, 1, "LX Handsome");

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

