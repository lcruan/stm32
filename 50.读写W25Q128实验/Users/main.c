#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "w25q128.h"

uint8_t data_write[4] = {0xAA, 0xBB, 0xCC, 0xDD};
uint8_t data_read[4] = {0};

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
    
    // 擦除
    w25q128_erase_sector(0x000000);
    // 写内容
    w25q128_write_page(0x000000, data_write, 4);
    // 读
    w25q128_read_data(0x000000, data_read, 4);
    
    printf("data read: %X, %X, %X, %X\r\n", data_read[0], data_read[1], data_read[2], data_read[3]);
    
    while(1)
    { 
        
    }
}

