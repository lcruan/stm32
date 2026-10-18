#include "key.h"
#include "delay.h"

// 初始化GPIO
void key_init(void)
{
     GPIO_InitTypeDef gpio_initstruct;
    // 打开时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();
    // 调用GPIO初始化函数
    gpio_initstruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    gpio_initstruct.Mode = GPIO_MODE_INPUT;
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio_initstruct);
}


// 按键扫描函数
uint8_t key_scan(void)
{
     // 检测按键是否按下 - 检测key1 - PA0
     if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
     {
         // 消抖
         delay_ms(10);
         // 再次判断按键是否按下 GPIO_PIN_RESET低电平
         if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
         {
            // 如果确实是按下状态，等待按键松开
             while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET);
            // 返回按键值
             return 1;
         }

     }
     
     // 检测key2 - PA1
     if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
     {
         // 消抖
         delay_ms(10);
         // 再次判断按键是否按下 GPIO_PIN_RESET低电平
         if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
         {
            // 如果确实是按下状态，等待按键松开
             while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET);
            // 返回按键值
             return 2;
         }

     }
     // 否则返回默认值
     return 0;
}
