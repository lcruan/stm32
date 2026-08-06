#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "adc.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    adc_init();
    printf("hello world!\r\n");
    
    while(1)
    { 
        printf("adc result: %f\r\n", (float)adc_get_result(ADC_CHANNEL_1) / 4096 * 3.3);
        delay_ms(500);
    }
}

