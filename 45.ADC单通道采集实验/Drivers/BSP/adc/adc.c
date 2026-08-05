#include "adc.h"

ADC_HandleTypeDef adc_handle = {0};

void adc_init(void)
{
    adc_handle.Instance = ADC1;
    adc_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    adc_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;
    adc_handle.Init.ContinuousConvMode = DISABLE;
    adc_handle.Init.NbrOfConversion = 1;
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
        __HAL_RCC_ADC1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        
    }
}

void adc_channel_config(ADC_HandleTypeDef* hadc, uint32_t ch, uint32_t rank, uint32_t stime)
{

}

uint32_t adc_get_result(uint32_t ch)
{
    
}