#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "bluetooth.h"
#include "plugin.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    bt_init(115200);
    plugin_init();
    printf("hello world!\r\n");
    
//    uint8_t i = 0;
    while(1)
    { 
//        bt_send("hello, bt%d\r\n", i++);
//        delay_ms(500);
//        led1_on();
//        led2_off();
//        delay_ms(500);
//        led1_off();
//        led2_on();
//        delay_ms(500);
    }
}

