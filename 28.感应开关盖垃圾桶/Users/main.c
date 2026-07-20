#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "beep.h"
#include "exti.h"
#include "hcsr04.h"
#include "key.h"
#include "sg90.h"

#define OPEN 1
#define CLOSE 0
uint8_t dusbin_status = CLOSE;
// 舵机开盖
void open_dustbin(void)
{
    if (dusbin_status == CLOSE) 
    {
        sg90_angle_set(30);
        beep_on();
        led1_on();
        delay_ms(100);
        beep_off();
        led1_off();
        dusbin_status = OPEN;
    }
}

// 舵机关盖
void close_dustbin(void)
{
    sg90_angle_set(0);
    beep_off();
    led1_off();
    dusbin_status = CLOSE;
}

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    beep_init();
    exti_init();
    hcsr04_init();
    key_init();
    sg90_init();
    
    printf("hello world!\r\n");
    uint8_t key_num = 0;
    while(1)
    { 
        key_num = key_scan();
        // key1按下/检测到震动/超声波传感器测量距离 -> 开盖
        if (key_num == 1 || vibrate_flag_get() == TRUE || hcsr04_get_length() < 10)
        {
            open_dustbin();
            delay_ms(2000);
            // 振动传感器有可能检测到很多震动，在这里将他重置一下
            vibrate_flag_set(FALSE);
        }
        else
            close_dustbin();
        // 给10ms喘息，不然一直获取会很累
        delay_ms(10);
//        sg90_angle_set(0); 
//        delay_ms(1000);
//        sg90_angle_set(20);
//        delay_ms(1000);
//        sg90_angle_set(40);
//        delay_ms(1000);
//        sg90_angle_set(90);
//        delay_ms(1000);
//        sg90_angle_set(180);
//        delay_ms(1000);
//        key_num = key_scan();
//      if (key_num == 1)
//            led1_toggle();
//      
//      if (key_num == 2)
//            led2_toggle();
//        printf("dis: %.2f\r\n", hcsr04_get_length());
//        delay_ms(1000);
//         if(vibrate_flag_get() == TRUE) // 震动后，led1亮2秒关闭
//        {
//            led1_on();
//            delay_ms(2000);
//            led1_off();
//            vibrate_flag_set(FALSE); // 解决亮4秒的问题，因为传感器太灵敏，捕获两次设置为TRUE,这里再次设置为FALSE
//        }
//        beep_on();
//        delay_ms(500);
//        beep_off();
//        delay_ms(500);
//        led1_on();
//        led2_off();
//        delay_ms(500);
//        led1_off();
//        led2_on();
//        delay_ms(500);
    }
}

