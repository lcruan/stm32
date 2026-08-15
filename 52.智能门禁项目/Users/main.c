#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "beep.h"
#include "keyboard.h"
#include "lock.h"
#include "oled.h"
#include "w25q128.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    uart1_init(115200);
    
    beep_init();
    keyboard_init();
    lock_init();
    oled_init();
//    w25q128_init();
    
    printf("hello world!\r\n");
    
    oled_show_input();
    
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

