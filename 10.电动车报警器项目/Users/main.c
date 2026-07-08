#include "sys.h"
#include "delay.h"
#include "led.h"
#include "exti.h"
#include "alarm.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    exti_init(); // 手动控制led1灯开关同时，led2灯一直闪烁
    alarm_init();
    
    uint8_t alert_mode = FALSE; // 警戒标志位
    
    while(1)
    { 
        // A按键是否按下？->进入警戒模式
        if (buttonA_flag_get() == TRUE)
        {
            alarm_on();
            delay_ms(2000);
            alarm_off();
            alert_mode = TRUE;
        }
        // B按键是否按下？ -> 退出警戒模式
        if (buttonB_flag_get() == TRUE)
        {
            // 如果在响的状态下，直接关闭
            if (alarm_status_get() == ALARM_STATUS_ON)
            {
                alarm_off();
            }
            else // 如果没有响，就响一秒钟
            {
                alarm_on();
                delay_ms(1000);
                alarm_off();
            }
            alert_mode = FALSE;
        }
        // 如果处于警戒模式
        if (alert_mode == TRUE)
        {
            if (vibrate_flag_get() == TRUE)
                alarm_on();
        }
        else
        {
            // 非警戒模式，一定要清除,不然非警戒模式触发多次，首次打开警戒会一直响
            // 按B之后，一直触碰传感器
            vibrate_flag_set(FALSE);
        }
    }
}

