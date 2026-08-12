#include "keyboard.h"
#include "delay.h"

uint8_t key_value = 0;

void keyboard_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    // 打开时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    // 配置行
    gpio_initstruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_10;
    gpio_initstruct.Mode = GPIO_MODE_IT_FALLING;
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);
    
    // 配置列
    gpio_initstruct.Pin = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
    gpio_initstruct.Mode = GPIO_MODE_INPUT;
    gpio_initstruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);
    
    // 配置中断相关1
    HAL_NVIC_SetPriority(EXTI0_IRQn, 3, 0);
    // 开启使能中断1
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    
    HAL_NVIC_SetPriority(EXTI1_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
    
    HAL_NVIC_SetPriority(EXTI2_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);
    
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

// 中断服务函数
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void EXTI1_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}

void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint8_t row = 0, column = 0;
    
    if (key_value != 0) return;
    
    // 确认行
    if (GPIO_Pin == GPIO_PIN_0)
        row = 0x10;
    else if (GPIO_Pin == GPIO_PIN_1)
        row = 0x20;
    else if (GPIO_Pin == GPIO_PIN_2)
        row = 0x30;
    else if (GPIO_Pin == GPIO_PIN_10)
        row = 0x40;
    
    
    // 确认列
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == GPIO_PIN_SET) // 被拉高
    {
        delay_ms(10); // 防抖
        while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11))
            column = 0x01;
    }
    else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_SET) // 被拉高
    {
        delay_ms(10); // 防抖
        while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))
            column = 0x02;
    }
    else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_SET) // 被拉高
    {
        delay_ms(10); // 防抖
        while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13))
            column = 0x03;
    }
    
    if (row != 0 && column != 0)
        key_value = row | column; // 若按位与是0x12则证明是第一行/第二列被按下了
}

uint8_t keyboard_get_value(void)
{
    uint8_t ch = 0;
    if (key_value != 0)
    {
        if (key_value == 0x11) ch = '1';
        else if (key_value == 0x12) ch = '2';
        else if (key_value == 0x13) ch = '3';
        else if (key_value == 0x21) ch = '4';
        else if (key_value == 0x22) ch = '5';
        else if (key_value == 0x23) ch = '6';
        else if (key_value == 0x31) ch = '7';
        else if (key_value == 0x32) ch = '8';
        else if (key_value == 0x33) ch = '9';
        else if (key_value == 0x41) ch = '*';
        else if (key_value == 0x42) ch = '0';
        else if (key_value == 0x43) ch = '#';
        delay_ms(400);
        key_value = 0x00;
    }
    return ch;
}











