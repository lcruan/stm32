#include "password.h"
#include "w25q128.h"
#include "oled.h"
#include "keyboard.h"
#include "string.h"
#include "stdio.h"
#include "lock.h"
#include "beep.h"
#include "delay.h"

#define PASSWORD_SIZE   10

uint8_t pwd_input[PASSWORD_SIZE] = {0}; // 通过矩阵键盘输入进来的
uint8_t pwd_read[PASSWORD_SIZE] = {0};
uint8_t i = 0, key_value = 0, try_times = 0; // 定义数组索引

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
            // 关键：手动补字符串结束符
            pwd_input[i] = '\0';
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
            // 防止溢出，最多输入PASSWORD_SIZE?1位，留一个位置给'\0'
            if(i < PASSWORD_SIZE -1)
            {
                printf("按下了：%c\r\n", key_value);
                oled_show_char(20 + i * 10, 4, key_value, 16);
                pwd_input[i++] = key_value;
            }
//            printf("按下了：%c\r\n", key_value);
//            oled_show_char(20 + i * 10, 4, key_value, 16);
//            pwd_input[i++] = key_value;
        }
    }
}

// 密码比对 那输入的pwd_input密码和保存的w25q128的密码
uint8_t password_compare(void)
{
    uint8_t i = 0;
    
    w25q128_read_data(0x000000, pwd_read, PASSWORD_SIZE);
    
    // 数组比对 pwd_input和pwd_read比对
    if (strlen((char *)pwd_input) != strlen((char *)pwd_read)) // 比较长度
        return FALSE;
    
    // 长度一样，比较每一位，循环
    for (i = 0; i < strlen((char *)pwd_read); i++)
    {
        if (pwd_input[i] != pwd_read[i]) // 只要有一位不一样
            return FALSE;
    }
    
    return TRUE;
    
}
// 密码输入正确的操作
// 锁打开，蜂鸣器响起来,oled显示密码正确
void password_input_right_action(void)
{
    oled_show_right();
    lock_on(); // 继电器闭合
    beep_on();
    delay_ms(300);
    beep_off();
    delay_ms(1000);
    lock_off();
    try_times = 0; // 密码输入正确设置为0，为了解决前两次错误，第三次正确
}
// 密码输入错误的操作
void password_input_wrong_action(void)
{
    // 提示用户，密码输入错误
    oled_show_wrong();
    try_times++;
    if (try_times >= 3)
    {
        beep_on();
        delay_ms(1000);
        beep_off();
        try_times = 0;
    }
    // 刚开始输入错误，防止oled_show_wrong一闪而过，加延时
    delay_ms(1000);
    
}
// 旧密码输入正确的操作
void password_old_right_action(void)
{
    // 显示请输入新密码
    oled_show_new();
    password_get_input();
    // 保存新密码
    password_save();
    
    // 蜂鸣器提示下用户
    beep_on();
    delay_ms(300);
    beep_off();
    delay_ms(500); // 目的为了上面oled_show_new停留时间长一点
}
// 旧密码输入错误的操作
void password_old_wrong_action(void)
{
    oled_show_wrong();
    delay_ms(1000);
}

// 检查密码是否存在
void password_check(void)
{
    // 读取数据
    w25q128_read_data(0x000000, pwd_read, PASSWORD_SIZE);
    pwd_read[PASSWORD_SIZE-1] = '\0';
    printf("读出密码：%s\r\n", pwd_read);
    
    if (pwd_read[0] == '\0' || pwd_read[0] == 0xFF)// 代表没有密码
    {
        oled_show_set();
        password_get_input();
        password_save();
    }
}

