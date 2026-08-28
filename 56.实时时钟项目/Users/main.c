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
    uint8_t set_time_shift = TIME_SECOND;
    uint8_t set_alarm_shift = ALARM_SECOND;
    uint8_t set_time_flag = 0, set_alarm_flag = 0;
    
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
        
        switch(key_scan())
        {
            case KEY_SET:
                // 按键1按下，进入时间设置模式
                set_time_flag = 1;
                while(set_time_flag)
                {
                    // 闪动要修改的坑位
                    // 先闪动秒
                    oled_show_element(time_data[set_time_shift], OFF, set_time_shift);
                    delay_ms(100);
                    oled_show_element(time_data[set_time_shift], ON, set_time_shift);
                    delay_ms(100);
                    
                       // 闪动的状态下，按下按键的不同状态处理
                       switch(key_scan())
                        {
                            case KEY_SET:
                                // 退出时间设置模式
                                set_time_flag = 0;
                                set_time_shift = TIME_SECOND;
                                // 保存修改后的时间
                                rtc_set_time(time_data);
                                break;
                            
                            case KEY_SHIFT:
                                // 跳转到下一个需要修改的元素（秒 分 时 日 月 年）
                                if (set_time_shift-- <= TIME_YEAR) // 是枚举，--相当于移动位置
                                    set_time_shift = TIME_SECOND;
                                break;
                            
                            case KEY_UP:
                                // 增加数值
                                // 分和秒，不能超过60
                                if (set_time_shift == TIME_SECOND || set_time_shift == TIME_MINUTE)
                                    if (time_data[set_time_shift] < 59)
                                        time_data[set_time_shift]++;
                                    
                                if (set_time_shift == TIME_HOUR) // 小时
                                    if (time_data[set_time_shift] < 23)
                                        time_data[set_time_shift]++;
                                    
                                if (set_time_shift == TIME_DAY) // 日
                                    if (time_data[set_time_shift] < 31)
                                        time_data[set_time_shift]++;
                                    
                                if (set_time_shift == TIME_MONTH) // 月
                                    if (time_data[set_time_shift] < 12)
                                        time_data[set_time_shift]++;
                                    
                                if (set_time_shift == TIME_YEAR) // 年
                                    if (time_data[set_time_shift] < 99)
                                        time_data[set_time_shift]++;
                                break;
                            
                            case KEY_DOWN:
                                // 减少数值
                                if (time_data[set_time_shift] > 0)
                                    time_data[set_time_shift]--;
                                break;

                            default: 
                                break;
                        }
                }
                break;
            
            case KEY_SHIFT:
                // 按键2按下，进入闹钟设置模式
                set_alarm_flag = 1;
                while(set_alarm_flag)
                {
                    // 闪动要修改的坑位
                    // 先闪动秒
                    oled_show_element(alarm_data[set_alarm_shift - ALARM_HOUR], OFF, set_alarm_shift);
                    delay_ms(100);
                    oled_show_element(alarm_data[set_alarm_shift - ALARM_HOUR], ON, set_alarm_shift);
                    delay_ms(100);
                    switch(key_scan())
                    {
                        case KEY_SET:
                            // 退出闹钟设置模式
                            set_alarm_flag = 0;
                            set_alarm_shift = ALARM_SECOND;
                            // 保存修改后的闹钟
                            rtc_set_alarm(alarm_data);
                            break;
                        
                        case KEY_SHIFT:
                            // 跳转到下一个需要修改的元素（秒 分 时 日 月 年）
                            if (set_alarm_shift-- <= ALARM_HOUR) // 是枚举，--相当于移动位置
                                set_alarm_shift = ALARM_SECOND;
                            break;
                        
                        case KEY_UP:
                            // 增加数值
                            if (alarm_data[set_alarm_shift - ALARM_HOUR] < 59)
                                alarm_data[set_alarm_shift - ALARM_HOUR]++;
                            break;
                        
                        case KEY_DOWN:
                            // 减少数值
                            if (alarm_data[set_alarm_shift - ALARM_HOUR] > 0)
                                alarm_data[set_alarm_shift - ALARM_HOUR]--;
                            break;

                        default: 
                            break;
                    }
                }
                break;
            
            case KEY_UP:
            case KEY_DOWN:
                // 按键4/3按下，停止蜂鸣器
                beep_off();
                break;
            
            default: 
                break;
        }
        
        
//        delay_ms(1000);
        
    }
}

