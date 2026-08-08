#include "adc.h"

ADC_HandleTypeDef adc_handle = {0};
DMA_HandleTypeDef dma_handle = {0};

void adc_config(void)
{
    adc_handle.Instance = ADC1;
    adc_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    adc_handle.Init.ScanConvMode = ADC_SCAN_ENABLE;
    adc_handle.Init.ContinuousConvMode = ENABLE;
    adc_handle.Init.NbrOfConversion = 4; // 通道数目
    adc_handle.Init.DiscontinuousConvMode = DISABLE;
    adc_handle.Init.NbrOfDiscConversion = 0;
    adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    HAL_ADC_Init(&adc_handle);
    
    HAL_ADCEx_Calibration_Start(&adc_handle);
}


void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    if (hadc->Instance == ADC1)
    {
        RCC_PeriphCLKInitTypeDef adc_clk_init = {0};
        GPIO_InitTypeDef gpio_init_struct = {0};
        
        __HAL_RCC_ADC1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
        gpio_init_struct.Mode = GPIO_MODE_ANALOG;
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);
        
        adc_clk_init.PeriphClockSelection = RCC_PERIPHCLK_ADC;
        adc_clk_init.AdcClockSelection = RCC_ADCPCLK2_DIV6;
        HAL_RCCEx_PeriphCLKConfig(&adc_clk_init);
    }
}

void dma_config(void)
{
    __HAL_RCC_DMA1_CLK_ENABLE();
    dma_handle.Instance = DMA1_Channel1;
    dma_handle.Init.Direction = DMA_PERIPH_TO_MEMORY;
    
    // 内存相关配置
    dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    dma_handle.Init.MemInc = DMA_MINC_ENABLE;
    
    // 外设相关配置
    dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    dma_handle.Init.PeriphInc = DMA_PINC_DISABLE;
    
    dma_handle.Init.Priority = DMA_PRIORITY_MEDIUM;
    dma_handle.Init.Mode = DMA_CIRCULAR;
    
    HAL_DMA_Init(&dma_handle);
    
    __HAL_LINKDMA(&adc_handle, DMA_Handle, dma_handle);
}

// 通道配置
void adc_channel_config(ADC_HandleTypeDef* hadc, uint32_t ch, uint32_t rank, uint32_t stime)
{
    ADC_ChannelConfTypeDef adc_ch_config = {0};
    adc_ch_config.Channel = ch;
    adc_ch_config.Rank = rank;
    adc_ch_config.SamplingTime = stime;
    HAL_ADC_ConfigChannel(hadc, &adc_ch_config);
}

void adc_dma_init(uint32_t *mar)
{
    adc_config();
    adc_channel_config(&adc_handle, ADC_CHANNEL_0, ADC_REGULAR_RANK_1, ADC_SAMPLETIME_239CYCLES_5);
    adc_channel_config(&adc_handle, ADC_CHANNEL_1, ADC_REGULAR_RANK_2, ADC_SAMPLETIME_239CYCLES_5);
    adc_channel_config(&adc_handle, ADC_CHANNEL_2, ADC_REGULAR_RANK_3, ADC_SAMPLETIME_239CYCLES_5);
    adc_channel_config(&adc_handle, ADC_CHANNEL_3, ADC_REGULAR_RANK_4, ADC_SAMPLETIME_239CYCLES_5);
    dma_config();
    
    HAL_ADC_Start_DMA(&adc_handle, mar, 4);
}




