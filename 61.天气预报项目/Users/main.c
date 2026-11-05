#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "key.h"
#include "oled.h"
#include "cJSON.h"
#include "esp8266.h"
#include "weather.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
//    led_init();
    uart1_init(115200);
    key_init();
    oled_init();
    esp8266_init(115200);
    
    printf("hello world!\r\n");
    
//    esp8266_get_weather(0);
    get_3days_weather();
    show_weather(0);
//    oled_show_init();
    
    uint8_t key_num = 0;
    uint8_t day = 0;
    while(1)
    { 
        key_num = key_scan();
        if(key_num == 1)  // 按下key1，切换天气
        {
            day++;
            day %= 3;
            show_weather(day);
        }
        else if (key_num == 2) // 按下key2，更新天气
        {
            printf("更新天气...\r\n");
            get_3days_weather();
            show_weather(0);
            day = 0;
        }
    }
}

