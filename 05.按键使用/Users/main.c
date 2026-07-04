#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    key_init();
    
    uint8_t key_num = 0;
    while(1)
    { 
      key_num = key_scan();
      if (key_num == 1)
            led1_toggle();
      
      if (key_num == 2)
            led2_toggle();
    }
}

