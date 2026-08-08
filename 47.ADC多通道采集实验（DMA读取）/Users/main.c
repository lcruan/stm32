#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "adc.h"

void led_init(void);                       /* LED初始化函数声明 */

uint16_t adc_result[4] = {0};

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    adc_dma_init((uint32_t *)&adc_result);
    printf("hello world!\r\n");
    
    while(1)
    { 
        printf("通道0电压: %f\r\n", (float)adc_result[0] / 4096 * 3.3);
        printf("通道1电压: %f\r\n", (float)adc_result[1] / 4096 * 3.3);
        printf("通道2电压: %f\r\n", (float)adc_result[2] / 4096 * 3.3);
        printf("通道3电压: %f\r\n\r\n", (float)adc_result[3] / 4096 * 3.3);
        
        delay_ms(500);
    }
}

