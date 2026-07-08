#include "exti.h"
#include "sys.h"
#include "delay.h"
#include "led.h"

uint8_t buttonA_flag = FALSE;
uint8_t buttonB_flag = FALSE;
uint8_t vibrate_flag = FALSE; // 检测到震动标志位

void exti_init(void)
{
    // 1. 使能GPIO时钟
    GPIO_InitTypeDef gpio_initstruct;
    // 2. 使用HAL_GPIO_Init一步到位：
    //    设置GPIO模式，设置AFIO(开启时钟/IO口映射)，设置EXTI上/下沿
    // 打开时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    // 配置PA12
    gpio_initstruct.Pin = GPIO_PIN_12; // PA12
    gpio_initstruct.Mode = GPIO_MODE_IT_RISING; // 上升沿
    gpio_initstruct.Pull = GPIO_PULLDOWN; // 下拉
    HAL_GPIO_Init(GPIOA, &gpio_initstruct);
    
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0); // 参数为：中断源，抢占优先级，响应优先级
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn); // 参数中断源
    
    // 配置PB5
    gpio_initstruct.Pin = GPIO_PIN_5; // PA12
    gpio_initstruct.Mode = GPIO_MODE_IT_RISING; // 上升沿
    gpio_initstruct.Pull = GPIO_PULLDOWN; // 下拉
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);
    
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0); // 参数为：中断源，抢占优先级，响应优先级
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn); // 参数中断源
    
    // 震动传感器配置
    gpio_initstruct.Pin = GPIO_PIN_4;
    gpio_initstruct.Mode = GPIO_MODE_IT_FALLING; // 向下沿触发
    gpio_initstruct.Pull = GPIO_PULLUP; // 上拉
    HAL_GPIO_Init(GPIOA, &gpio_initstruct);
    HAL_NVIC_SetPriority(EXTI4_IRQn, 2, 0); // 参数为：中断线，抢占优先级，响应优先级
    HAL_NVIC_EnableIRQ(EXTI4_IRQn); // 参数中断源
}

// PA12对应中断线的服务函数
void EXTI15_10_IRQHandler(void)
{
    // 调用公共服务函数
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
}

// PB5对应中断线的服务函数
void EXTI9_5_IRQHandler(void)
{
    // 调用公共服务函数
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
}

// 震动传感器 中断服务函数
void EXTI4_IRQHandler(void)
{
    // 调用公共服务函数
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

// 回调函数 - 业务代码
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // (2) 判断是不是p0引脚  PA12 <-> D1 <-> B键 <-> LED2灯
    if (GPIO_Pin == GPIO_PIN_12) // 收到B按键，把LED2灯翻转
    {
        // 检测PA0引脚是不是拉低的
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == GPIO_PIN_SET) // GPIO_PIN_SET 高电平
            // led2_toggle();
            buttonB_flag = TRUE;
            
    }
    else if (GPIO_Pin == GPIO_PIN_5) // 收到A键，把LED1灯翻转
    {
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_SET) // GPIO_PIN_SET 高电平
            // led1_toggle();
            buttonA_flag = TRUE;
    }
    else if (GPIO_Pin == GPIO_PIN_4) // 震动传感器
    {
        // 检测PA0引脚是不是拉低的 检测到震动
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_RESET)
            // led1_toggle();
            vibrate_flag = TRUE;
            
    }
}

uint8_t buttonA_flag_get(void)
{
    uint8_t temp = buttonA_flag;
    buttonA_flag = FALSE;
    return temp;
}

void buttonA_flag_set(uint8_t value)
{
    buttonA_flag = value;
}

uint8_t buttonB_flag_get(void)
{
    uint8_t temp = buttonB_flag;
    buttonB_flag = FALSE;
    return temp;
}

void buttonB_flag_set(uint8_t value)
{
    buttonB_flag = value;
}

// 震动传感器的 get/set函数
uint8_t vibrate_flag_get(void)
{
    // 解决 vibrate_flag值一直为TRUE问题，在拿到值后，先存临时变量中，再将值
    // 改为false，返回临时变量保存的旧值
    uint8_t temp = vibrate_flag;
    vibrate_flag = FALSE;
    return temp;
}

void vibrate_flag_set(uint8_t value)
{
    vibrate_flag = value;
}


