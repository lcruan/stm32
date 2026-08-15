#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "beep.h"
#include "keyboard.h"
#include "lock.h"
#include "oled.h"
#include "w25q128.h"
#include "password.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    uart1_init(115200);
    
    beep_init();
    keyboard_init();
    lock_init();
    oled_init();
    password_init();
//    w25q128_init();
    
    password_check();
    
    printf("hello world!\r\n");
    
//    oled_show_input();
    
    uint8_t key_last = 0;
    while(1)
    { 
        oled_show_input();
        key_last = password_get_input();
        if (key_last == POUND_KEY)
        {
            if (password_compare() == TRUE)
                password_input_right_action();
            else
                password_input_wrong_action();
        }
        else  if (key_last == STAR_KEY) // * 修改密码
        {
            oled_show_old();
            password_get_input();
            if (password_compare() == TRUE)
                password_old_right_action();
            else
                password_old_wrong_action();
        }
        
    }
}

