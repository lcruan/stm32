#include "sys.h"
#include "uart1.h"
#include "delay.h"

#define LED_CLK()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define LED_GPIO        GPIOB
#define LED_PIN         GPIO_PIN_8

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    led_init();                         /* LED初始化 */
    uart1_init(115200);
    printf("running...\r\n");
    while(1)
    { 
        HAL_GPIO_WritePin(LED_GPIO,LED_PIN,GPIO_PIN_SET);
        delay_ms(500);
        HAL_GPIO_WritePin(LED_GPIO,LED_PIN,GPIO_PIN_RESET);
        delay_ms(500); 
    }
}

/**
 * @brief       初始化LED相关IO口, 并使能时钟
 * @param       无
 * @retval      无
 */
void led_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    LED_CLK();                                             /* IO口时钟使能 */

    gpio_initstruct.Pin = LED_PIN;                         /* LED0引脚 */
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_initstruct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(LED_GPIO, &gpio_initstruct);             /* 初始化LED0引脚 */
}
