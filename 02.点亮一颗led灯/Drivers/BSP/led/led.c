#include "led.h"
#include "sys.h"

// 初始化GPIO函数
void led_init(void) 
{
    GPIO_InitTypeDef gpio_initstruct;
    // 打开时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    // 调用GPIO初始化函数
    gpio_initstruct.Pin = GPIO_PIN_8;
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);
    // 关闭LED
    led1_off();
}

// 点亮LED1的函数
void led1_on(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,GPIO_PIN_RESET);
}

// 熄灭LED1的函数
void led1_off(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,GPIO_PIN_SET);
}

// 翻转LED1状态的函数
void led1_toggle(void)
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
}
