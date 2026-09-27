#include "dht11.h"
#include "delay.h"

// 输入模式
void dht11_gpio__input(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    DHT11_CLK_ENABLE();
    
    gpio_initstruct.Pin = DHT11_PIN;
    gpio_initstruct.Mode = GPIO_MODE_INPUT;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DHT11_PORT, &gpio_initstruct);
}

// 输出模式
void dht11_gpio_output(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    DHT11_CLK_ENABLE();
    
    gpio_initstruct.Pin = DHT11_PIN;
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DHT11_PORT, &gpio_initstruct);
}

// 起始信号
void dht11_start(void)
{
    dht11_gpio_output();
    DHT11_DQ_OUT(1);
    DHT11_DQ_OUT(0);
    delay_ms(20);
    DHT11_DQ_OUT(1);
    
    dht11_gpio__input();
    while(DHT11_DQ_IN);     // 等待DHT11拉低电平
    while(!DHT11_DQ_IN); // 低电平状态下，一直卡住，循环成立， 等待DHT11拉高电平
    while(DHT11_DQ_IN);
    
}

uint8_t dth11_read_byte(void)
{
    
}

void dth11_read(uint8_t *result)
{
    
}

