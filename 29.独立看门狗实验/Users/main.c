#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "iwdg.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    iwdg_init(IWDG_PRESCALER_32, 1250);
    printf("hello world!\r\n");
    printf("狗儿肚子饿了，再不喂它的话就咬人了！\r\n");
    
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET)
    {
        printf("独立看门狗复位！\r\n");
        __HAL_RCC_CLEAR_RESET_FLAGS();
    }
    else
    {
        printf("外部复位！\r\n");
    }
    
    while(1)
    { 
        delay_ms(1500);
        iwdg_feed();
        printf("狗儿已经喂饱了，不会咬人了！\r\n");
//        led1_on();
//        led2_off();
//        delay_ms(500);
//        led1_off();
//        led2_on();
//        delay_ms(500);
    }
}

