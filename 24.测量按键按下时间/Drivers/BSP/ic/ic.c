#include "ic.h"
#include "stdio.h"
#include "string.h"

struct 
{
    uint8_t succeed_flag;
    uint8_t rising_flag;
    uint8_t falling_flag;
    uint16_t timout_cnt;
} capture_status = {0};

uint16_t last_cnt = 0;
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
    //printf("捕获到下降沿\r\n");
    // 这个回调函数很多定时器用得到，所以加一下判断
    if (htim->Instance == TIM2)
    {
        // 为 0 开始去捕获了
        // 为 1 上升沿和下降沿都已经捕获到了
        if (capture_status.succeed_flag == 0) 
        {
            // 默认先走的else分支下降沿，当else分支设置为上升沿就会到if分支了
            if (capture_status.falling_flag == 1)
            {
                printf("捕获到上升沿\r\n");
                capture_status.succeed_flag = 1;
                // 获取最后一个计数器的值，也就是CCR的值
                last_cnt = HAL_TIM_ReadCapturedValue(&ic_handle, TIM_CHANNEL_2);
                // 清除通道设置
                TIM_RESET_CAPTUREPOLARITY(&ic_handle, TIM_CHANNEL_2);
                // 设置上升沿捕获
                TIM_SET_CAPTUREPOLARITY(&ic_handle, TIM_CHANNEL_2, TIM_ICPOLARITY_FALLING);
                // 清空后falling_flag和succeed_flag都为0
                // memset(&capture_status, 0, sizeof(capture_status));
            }
            else
            {
                printf("捕获到下降沿\r\n");
                // 清空
                memset(&capture_status, 0, sizeof(capture_status));
                capture_status.falling_flag = 1; // 第一次走到这里
                // 关闭定时器
                __HAL_TIM_DISABLE(&ic_handle);
                // 定时器计数清零
                __HAL_TIM_SET_COUNTER(&ic_handle, 0);
                // 清除通道设置
                TIM_RESET_CAPTUREPOLARITY(&ic_handle, TIM_CHANNEL_2);
                // 设置上升沿捕获
                TIM_SET_CAPTUREPOLARITY(&ic_handle, TIM_CHANNEL_2, TIM_ICPOLARITY_RISING);
                // 定时器重新起来
                __HAL_TIM_ENABLE(&ic_handle); 
            }
        }
    }
}

// 溢出中断回到函数,计算出有多少次溢出
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        // 判断是否捕获到一个下降沿
        if (capture_status.falling_flag == 1)
            capture_status.timout_cnt++;
    }
}

// 按键 按下到松开的完整时间
void pressed_time_get(void)
{
    if (capture_status.succeed_flag == 1)
    {  
        printf("按下时间：%d us\r\n", capture_status.timout_cnt * 65536 + last_cnt);
        memset(&capture_status, 0, sizeof(capture_status)); // 开启下一次捕获
    }
}
