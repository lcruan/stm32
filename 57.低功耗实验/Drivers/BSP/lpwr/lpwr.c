#include "lpwr.h"
#include "led.h"


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
    // 暂停滴答定时器
    HAL_SuspendTick();
    // 点亮LED2,代表进入停机模式
    led2_on();
    // 进入停机模式
    HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFI);
    // 熄灭LED2，代表退出停机模式
    led2_off();
    // 从停机模式唤醒，需要重新配置系统时钟
    stm32_clock_init(RCC_PLL_MUL9);
}

// 待机模式
void lpwr_enter_standby(void)
{
    // 使能电源时钟（关闭电压调节器）
    __HAL_RCC_PWR_CLK_ENABLE();
    // 使能WAKEUP引脚的唤醒功能
    HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
    // 清除唤醒标记，否则将持续保持唤醒状态
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
    // 进入待机模式
    HAL_PWR_EnterSTANDBYMode();
    // 测试：看看代码会不会运行到下面？
    led2_on();
}
    




