#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "beep.h"
#include "key.h"
#include "oled.h"
#include "rtc.h"



void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    uart1_init(115200);
    beep_init();
    key_init();
    oled_init();
    rtc_init();
    printf("hello world!\r\n");
    
    uint8_t time_data[6] = {26, 8, 26, 23, 14, 30};
    uint8_t alarm_data[6] = {23, 15, 00};
    
    oled_show_init();
    
    if (rtc_read_bkr(1) != 0xA5A5)
    {
        rtc_write_bkr(1, 0xA5A5);
        
        rtc_set_time(time_data);
        rtc_set_alarm(alarm_data);
    }
    
    while(1)
    { 
        // 获取时间及闹钟
        rtc_get_time(time_data);
        rtc_get_alarm(alarm_data);
        // 在oled屏幕上显示
        oled_show_time_alarm(time_data, alarm_data);
        delay_ms(1000);
        
    }
}

