#include "password.h"
#include "w25q128.h"
#include "oled.h"
#include "keyboard.h"
#include "string.h"
#include "stdio.h"

#define PASSWORD_SIZE   10

uint8_t pwd_input[PASSWORD_SIZE] = {0}; // 通过矩阵键盘输入进来的
uint8_t pwd_read[PASSWORD_SIZE] = {0};
uint8_t i = 0, key_value = 0; // 定义数组索引

// 初始化函数
void password_init(void)
{
    w25q128_init();
}

// 清空输入缓存
void password_input_clear(void)
{
    memset(pwd_input, 0, PASSWORD_SIZE);
    // 清空缓存后，把索引置为0
    i = 0;
}

// 保存密码函数 把输入的密码保存到 w25q128里面
void password_save(void)
{
    // 擦除
    w25q128_erase_sector(0x000000);
    // 写入密码
    w25q128_write_page(0x000000, pwd_input, PASSWORD_SIZE);
    oled_show_changed(); // oled显示保存的密码
}
// 获取键盘输入
uint8_t password_get_input(void)
{
    // 首先清空输入缓存
    password_input_clear();
    // 不知道键盘要输入多久，不知道多少位，通过while循环一直输入，直到按下#或者*
    while(1)
    {
        key_value = keyboard_get_value();
        if (key_value == POUND_KEY)
        {
            printf("按下了#号键，input：%s\r\n", pwd_input);
            return POUND_KEY;
        }
        else if (key_value == STAR_KEY)
        {
            printf("按下了*号键\r\n");
            return STAR_KEY;
        }
        else if (key_value != 0)
        {
            printf("按下了：%c\r\n", key_value);
            oled_show_char(20 + i * 10, 4, key_value, 16);
            pwd_input[i++] = key_value;
        }
    }
}

// 密码比对
uint8_t password_compare(void)
{
    
}
// 密码输入正确的操作
void password_input_right_action(void)
{

}
// 密码输入错误的操作
void password_input_wrong_action(void)
{

}
// 旧密码输入正确的操作
void password_old_right_action(void)
{

}
// 旧密码输入错误的操作
void password_old_wrong_action(void)
{
    
}

// 检查密码是否存在
void password_check(void)
{
 
}

