#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "w25q128.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    w25q128_init();
    printf("hello world!\r\n");
    
    uint16_t device_id = w25q128_read_id();
    printf("device_id: %X\r\n", device_id);
    
    while(1)
    { 
        
    }
}

