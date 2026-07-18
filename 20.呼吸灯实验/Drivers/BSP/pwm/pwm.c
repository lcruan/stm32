#include "pwm.h"

TIM_HandleTypeDef pwm_handle = {0};

// init函数
void pwm_init(uint16_t arr, uint16_t psc)
{
    TIM_OC_InitTypeDef pwm_config = {0};
    pwm_handle.Instance = TIM4; // 定时器4
    pwm_handle.Init.Prescaler = psc;
    pwm_handle.Init.Period = arr;
    pwm_handle.Init.CounterMode = TIM_COUNTERMODE_UP;     
    HAL_TIM_PWM_Init(&pwm_handle);
    
    pwm_config.OCMode = TIM_OCMODE_PWM1;
    pwm_config.Pulse = arr / 2;
    pwm_config.OCPolarity = TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&pwm_handle, &pwm_config, TIM_CHANNEL_3);
    
    HAL_TIM_PWM_Start(&pwm_handle, TIM_CHANNEL_3);
}


// msp函数 init函数会自动调用这个函数
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM4)
    {
        GPIO_InitTypeDef gpio_initstruct;
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_TIM4_CLK_ENABLE();
        
        // 调用GPIO初始化函数
        gpio_initstruct.Pin = GPIO_PIN_8;
        gpio_initstruct.Mode = GPIO_MODE_AF_PP;
        gpio_initstruct.Pull = GPIO_PULLUP;
        gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &gpio_initstruct); 
    }
}


// 修改 CCR值的函数
void pwm_compare_set(uint16_t val)
{
    __HAL_TIM_SET_COMPARE(&pwm_handle, TIM_CHANNEL_3, val);
}

