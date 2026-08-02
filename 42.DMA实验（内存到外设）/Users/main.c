#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "dma.h"

extern UART_HandleTypeDef uart1_handle;

uint8_t send_buf[1000] = {0};

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    dma_init();
    // printf("hello world!\r\n");
    
    int i = 0;
    for (i = 0; i < 1000; i++)
        send_buf[i] = 'A';
    
    HAL_UART_Transmit_DMA(&uart1_handle, send_buf, 1000);
    
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

