#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "lpwr.h"
#include "key.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    lpwr_init();
    key_init();
    printf("hello world!\r\n");
    
    uint8_t i = 0;
    
    while(1)
    { 
        if (key_scan() == 2)
        {
            lpwr_enter_sleep();
        }
        
        if ((i % 20) == 0 )
            led1_toggle();
        
           i++;
           delay_ms(10);
    }
}

