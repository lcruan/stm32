#include "sys.h"
#include "delay.h"
#include "led.h"
#include "tasks.h"
#include "gate.h"
#include "beep.h"
#include "exti.h"
#include "lcd1602.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    gate_init();
    beep_init();
    exti_init();
    lcd1602_init();
    
    lcd1602_show_line(1, 1, "PASS...");
    while(1)
    { 
        led1_task();
        led2_task();
        sensor_task();
//        if (ia_flag_get() == TRUE)
//        {
//            led1_on();
//            delay_ms(2000);
//            led1_off();
//        }
//        beep_on();
//        delay_ms(500);
//        beep_off();
//        delay_ms(500);
//        task1();
//        task2();
    }
}

