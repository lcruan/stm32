#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "oled.h"

extern const unsigned char shuai_data[];

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();
    uart1_init(115200);
    oled_init();
    printf("hello world!\r\n");
    
    oled_fill(0x00);
    
//    oled_write_cmd(0xB0);
//    oled_write_cmd(0x00);
//    oled_write_cmd(0x10);
    
//    oled_write_data(0x80);
//    oled_write_data(0x80);
//    oled_write_data(0x80);
//    oled_write_data(0x80);
//    oled_write_data(0x80);
//    oled_write_data(0x80);
//    oled_write_data(0x80);
//    oled_write_data(0x80);
//    oled_write_data(0x80);
    
//    oled_set_cursor(0, 0);
//    oled_write_data(0x00);
//    oled_write_data(0x00);
//    oled_write_data(0xC0);
//    oled_write_data(0x38);
//    oled_write_data(0xE0);
//    oled_write_data(0x00);
//    oled_write_data(0x00);
//    oled_write_data(0x00);
//    oled_set_cursor(0, 1);
//    oled_write_data(0x20);
//    oled_write_data(0x3C);
//    oled_write_data(0x23);
//    oled_write_data(0x02);
//    oled_write_data(0x02);
//    oled_write_data(0x27);
//    oled_write_data(0x38);
//    oled_write_data(0x20);

//      oled_show_char(0, 0, 'L', 24);
//      oled_show_char(12, 0, 'X', 24);
//      oled_show_char(16, 0, '?', 16);
//      oled_show_char(24, 0, '6', 16);

    // 显示字符串
    // oled_show_string(0, 2, "hello LX", 24);
      
      // 显示汉字
//      uint8_t i;
//      for(i = 0; i < 5; i++)
//        oled_show_chinese(i*24, 0, i, 24);

        oled_show_image(0, 0, 128, 8, (unsigned char *)shuai_data);
    
    while(1)
    { 
        
    }
}

