#include "beep.h"
#include "sys.h"

// 初始化GPIO函数
void beep_init(void) 
{
    GPIO_InitTypeDef gpio_initstruct;
    // 打开时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    // 调用GPIO初始化函数
    gpio_initstruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);
    // 关闭LED
    beep_off();
}

// 点亮LED1的函数
void beep_on(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,GPIO_PIN_RESET);
}

// 熄灭LED1的函数
void beep_off(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,GPIO_PIN_SET);
}
