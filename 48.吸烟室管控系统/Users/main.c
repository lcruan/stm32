#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "adc.h"
#include "key.h"
#include "lcd1602.h"
#include "fan.h"
#include "beep.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    float smoke_value = 0;
    float limit_value = 2.0;
    uint8_t key_num = 0;
    
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    adc_dma_init();
    key_init();
    lcd1602_init();
    fan_init();
    beep_init();
    
    printf("hello world!\r\n");
    
    lcd1602_show_line(1, 1, "Smoke:   0.0 V");
    lcd1602_show_line(2, 1, "Limit: - 1.0 +");
    
    while(1)
    { 
        key_num == key_scan();
        if (key_num == 1)
            limit_value += 0.1;
        else if (key_num == 2)
            limit_value -= 0.1;
        
        lcd1602_display_limit(limit_value);
        
        smoke_value = adc_get_smoke();
        lcd1602_display_smoke(smoke_value);
        
        // 超标了，打开蜂鸣器
        if (smoke_value > limit_value)
        {
            beep_on();
            fan_on();
        }
        else 
        {
            beep_off();
            fan_off();
        }
    }
}

