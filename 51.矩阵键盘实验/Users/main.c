#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "keyboard.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    keyboard_init();
    printf("hello world!\r\n");
    
    uint8_t key_value = 0;// 定义一个变量来接收按键的返回值
    while(1)
    { 
        key_value = keyboard_get_value();
        if (key_value != 0)
        {
            printf("按下了：%c\r\n", key_value);
            key_value = 0;
        }
    }
}

