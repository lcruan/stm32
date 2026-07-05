#include "exti.h"
#include "sys.h"
#include "delay.h"
#include "led.h"

void exti_init(void)
{
    // 1. 使能GPIO时钟
    GPIO_InitTypeDef gpio_initstruct;
    // 2. 使用HAL_GPIO_Init一步到位：
    //    设置GPIO模式，设置AFIO(开启时钟/IO口映射)，设置EXTI上/下沿
    // 打开时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();
    // 调用GPIO初始化函数
    gpio_initstruct.Pin = GPIO_PIN_0;
    gpio_initstruct.Mode = GPIO_MODE_IT_FALLING; // 向下沿
    gpio_initstruct.Pull = GPIO_PULLUP; // 上拉
    HAL_GPIO_Init(GPIOA, &gpio_initstruct);
    
    // 3. 设置NVIC(优先级分组，设置优先级，使能中断)
    // (1) 优先级分组在stm32f1xx_hal_def.h中修改HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    // (2) 设置优先级
    HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0); // 参数为：中断源，抢占优先级，响应优先级
    // (3) 使能中断
    HAL_NVIC_EnableIRQ(EXTI0_IRQn); // 参数中断源
}

void EXTI0_IRQHandler(void)
{
    // 调用公共服务函数
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

// 回调函数 - 业务代码
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // (1) 消抖
    delay_ms(20);
    // (2) 判断是不是p0引脚
    if (GPIO_Pin == GPIO_PIN_0)
    {
        // 检测PA0引脚是不是拉低的
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
            led1_toggle();
            
    }
}
