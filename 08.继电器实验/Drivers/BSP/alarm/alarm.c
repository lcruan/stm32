#include "alarm.h"
#include "sys.h"

// 初始化GPIO函数
void alarm_init(void) 
{
    GPIO_InitTypeDef gpio_initstruct;
    // 打开时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();                 // 使能GPIOB时钟
    // 调用GPIO初始化函数
    gpio_initstruct.Pin = GPIO_PIN_7;             // 继电器IN对应的引脚
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;   // 推挽输出
    gpio_initstruct.Pull = GPIO_PULLUP;           // 给一个下降沿，所以默认是上拉
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH; // 高速
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);
    // 关闭继电器
    alarm_off();
}

// 打开继电器函数
void alarm_on(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_RESET); // 拉低引脚
}

// 关闭继电器函数
void alarm_off(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_SET); // 拉低引脚
}

// 返回继电器的高低平状态
// 直接返回1或者0不好看，定义两个宏定义
uint8_t alarm_status_get(void)
{
    return (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7); // (uint8_t)强制转换
}
    

