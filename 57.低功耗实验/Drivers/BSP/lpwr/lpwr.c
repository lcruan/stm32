#include "lpwr.h"


// 初始化
void lpwr_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    // 打开时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();
    // 调用GPIO初始化函数
    gpio_initstruct.Pin = GPIO_PIN_0;
    gpio_initstruct.Mode = GPIO_MODE_IT_RISING;
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio_initstruct);
    
    HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 2);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

// 睡眠模式
void lpwr_enter_sleep(void)
{
    HAL_SuspendTick();
    // HAL_PWR_EnterSLEEPMode();
    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFI);
}

// 停机模式
void lpwr_enter_stop(void)
{

}

// 待机模式
void lpwr_enter_standby(void)
{
    
}
    




