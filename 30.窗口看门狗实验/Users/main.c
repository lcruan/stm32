#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "wwdg.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    wwdg_init(0x7f, 0x5f, WWDG_PRESCALER_8);
    printf("hello world!\r\n");
    
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET)
    {
        printf("窗口看门狗复位！\r\n");
        __HAL_RCC_CLEAR_RESET_FLAGS();
    }
    else
        printf("外部复位！\r\n");
    
    while(1)
    { 
        delay_ms(10);
        wwdg_feed();
        led1_toggle();
//        led1_on();
//        led2_off();
//        delay_ms(500);
//        led1_off();
//        led2_on();
//        delay_ms(500);
    }
}

