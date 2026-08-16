#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "rtc.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    rtc_init();
    printf("hello world!\r\n");
    
    // 判断里面有么有写入的内容
    if (rtc_read_bkr(1) != 0xA5A5) 
    {
        struct tm time_data;
        time_data.tm_year = 2026;
        time_data.tm_mon = 8;
        time_data.tm_mday = 16;
        time_data.tm_hour = 16;
        time_data.tm_min = 30;
        time_data.tm_sec = 40;
        // 设置时间
        rtc_set_time(time_data);
    }
    rtc_write_bkr(1, 0xA5A5);
    printf("读出来的值为：%X\r\n", rtc_read_bkr(1));
    
    
    while(1)
    { 
        rtc_get_time();
        delay_ms(1000);
    }
}

