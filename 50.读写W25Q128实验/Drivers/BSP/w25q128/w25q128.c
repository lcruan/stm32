#include "w25q128.h"


SPI_HandleTypeDef spi_handle = {0};
void w25q128_spi_init(void)
{ 
    spi_handle.Instance = SPI1;
    spi_handle.Init.Mode = SPI_MODE_MASTER;
    spi_handle.Init.Direction = SPI_DIRECTION_2LINES;
    spi_handle.Init.DataSize = SPI_DATASIZE_8BIT;
    spi_handle.Init.CLKPolarity = SPI_POLARITY_LOW;
    spi_handle.Init.CLKPhase = SPI_PHASE_1EDGE;
    spi_handle.Init.NSS = SPI_NSS_SOFT;
    spi_handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    spi_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
    spi_handle.Init.TIMode = SPI_TIMODE_DISABLE;
    spi_handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    spi_handle.Init.CRCPolynomial = 7;
    HAL_SPI_Init(&spi_handle);
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    if (hspi->Instance == SPI1)
    {
        GPIO_InitTypeDef gpio_initstruct;
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_SPI1_CLK_ENABLE();
        
        // 调用GPIO初始化函数
        gpio_initstruct.Pin = GPIO_PIN_4;
        gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
        gpio_initstruct.Pull = GPIO_PULLUP;
        gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &gpio_initstruct);
        
        gpio_initstruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
        gpio_initstruct.Mode = GPIO_MODE_AF_PP;
        HAL_GPIO_Init(GPIOA, &gpio_initstruct);
        
        gpio_initstruct.Pin = GPIO_PIN_6;
        gpio_initstruct.Mode = GPIO_MODE_INPUT;
        HAL_GPIO_Init(GPIOA, &gpio_initstruct);
    }
}

uint8_t w25q128_spi_swap_byte(uint8_t data)
{
    uint8_t recv_data = 0;
    HAL_SPI_TransmitReceive(&spi_handle, &data, &recv_data, 1, 1000);
    return recv_data;
}




