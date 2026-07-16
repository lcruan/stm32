#include "timer.h"
#include "led.h"

TIM_HandleTypeDef timer_handle = {0};

// 定时器初始化函数
void timer_init(uint16_t arr, uint16_t psc)
{
    timer_handle.Instance = TIM2;
    timer_handle.Init.Prescaler = psc;
    timer_handle.Init.Period = arr;
    timer_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    timer_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&timer_handle);
    HAL_TIM_Base_Start_IT(&timer_handle);
}

// msp函数 - 系统自动被调用
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        __HAL_RCC_TIM2_CLK_ENABLE();
        HAL_NVIC_SetPriority(TIM2_IRQn, 2, 2);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
}

// 中断服务函数
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&timer_handle);
}

// 更新中断回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        led1_toggle();
    }
}

