#include "exti.h"
#include "sys.h"
#include "delay.h"
#include "led.h"

uint8_t ia_flag = FALSE;

void exti_init(void)
{
    // 1. 使能GPIO时钟
    GPIO_InitTypeDef gpio_initstruct;
    // 2. 使用HAL_GPIO_Init一步到位：
    //    设置GPIO模式，设置AFIO(开启时钟/IO口映射)，设置EXTI上/下沿
    // 打开时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    // 调用GPIO初始化函数
    gpio_initstruct.Pin = GPIO_PIN_4;
    gpio_initstruct.Mode = GPIO_MODE_IT_FALLING; // 向下沿触发
    gpio_initstruct.Pull = GPIO_PULLUP; // 上拉
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);
    
    // 3. 设置NVIC(优先级分组，设置优先级，使能中断)
    // (1) 优先级分组在stm32f1xx_hal_def.h中修改HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    // (2) 设置优先级
    HAL_NVIC_SetPriority(EXTI4_IRQn, 2, 0); // 参数为：中断线，抢占优先级，响应优先级
    // (3) 使能中断
    HAL_NVIC_EnableIRQ(EXTI4_IRQn); // 参数中断源
}

// 中断服务函数
void EXTI4_IRQHandler(void)
{
    // 调用公共服务函数
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

// 回调函数 - 业务代码
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // (1) 中断函数中最好不要用延时函数，之前是按键，按键有抖动，震动传感器也有抖动，但是可以忽略不计
    // delay_ms(20); 
    // (2) 判断是不是p0引脚
    if (GPIO_Pin == GPIO_PIN_4)
    {
        // 检测PA0引脚是不是拉低的 检测到震动
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_RESET)
            // led1_toggle();
            ia_flag = TRUE;
            
    }
}

uint8_t ia_flag_get(void)
{
    // 解决 vibrate_flag值一直为TRUE问题，在拿到值后，先存临时变量中，再将值
    // 改为false，返回临时变量保存的旧值
    uint8_t temp = ia_flag;
    ia_flag = FALSE;
    return temp;
}

void ia_flag_set(uint8_t value)
{
    ia_flag = value;
}
