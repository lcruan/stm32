#include "counter.h"
#include "stdio.h"

TIM_HandleTypeDef counter_handle = {0};
uint16_t new_count = 0;
uint16_t old_count = 0;
void counter_init(uint16_t arr, uint16_t psc)
{
    TIM_SlaveConfigTypeDef slave_config = {0};
    
    counter_handle.Instance = TIM2;
    counter_handle.Init.Prescaler = psc;
    counter_handle.Init.Period = arr;
    counter_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_IC_Init(&counter_handle);
    
    slave_config.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
    slave_config.InputTrigger = TIM_TS_TI2FP2;
    slave_config.TriggerPolarity = TIM_TRIGGERPOLARITY_FALLING;
    slave_config.TriggerFilter = 0;
    HAL_TIM_SlaveConfigSynchro(&counter_handle, &slave_config);
    
    HAL_TIM_IC_Start(&counter_handle, TIM_CHANNEL_2);
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        GPIO_InitTypeDef gpio_initstruct;
        // 打开时钟
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_TIM2_CLK_ENABLE();
        // 调用GPIO初始化函数
        gpio_initstruct.Pin = GPIO_PIN_0;
        gpio_initstruct.Mode = GPIO_MODE_AF_PP;
        gpio_initstruct.Pull = GPIO_PULLUP;
        gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &gpio_initstruct);
    }
}

void count_get(void)
{
    new_count = __HAL_TIM_GET_COUNTER(&counter_handle);
    if (new_count != old_count)
    {
        old_count = new_count;
        printf("CNT: %d\r\n", new_count);
    }
}


