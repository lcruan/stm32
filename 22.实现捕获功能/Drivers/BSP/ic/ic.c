#include "ic.h"
#include "stdio.h"

TIM_HandleTypeDef ic_handle = {0};

void ic_init(uint16_t arr, uint16_t psc)
{
    TIM_IC_InitTypeDef ic_config = {0};
    ic_handle.Instance = TIM2;
    ic_handle.Init.Prescaler = psc;
    ic_handle.Init.Period = arr;
    ic_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_IC_Init(&ic_handle);
    
    ic_config.ICPolarity = TIM_ICPOLARITY_FALLING;
    ic_config.ICSelection = TIM_ICSELECTION_DIRECTTI;
    ic_config.ICPrescaler = TIM_ICPSC_DIV1;
    ic_config.ICFilter = 0;
    HAL_TIM_IC_ConfigChannel(&ic_handle, &ic_config, TIM_CHANNEL_2);
    __HAL_TIM_ENABLE_IT(&ic_handle, TIM_IT_UPDATE);
    HAL_TIM_IC_Start_IT(&ic_handle, TIM_CHANNEL_2);
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        GPIO_InitTypeDef gpio_initstruct;
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_TIM2_CLK_ENABLE();
        
        // 调用GPIO初始化函数
        gpio_initstruct.Pin = GPIO_PIN_1;
        gpio_initstruct.Mode = GPIO_MODE_INPUT;
        gpio_initstruct.Pull = GPIO_PULLUP;
        gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &gpio_initstruct);
        
        HAL_NVIC_SetPriority(TIM2_IRQn, 2, 2);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
}

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&ic_handle);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    printf("捕获到下降沿\r\n");
}
