#include "dma.h"


DMA_HandleTypeDef dma_handle = {0};

void dma_init(void)
{
    __HAL_RCC_DMA1_CLK_ENABLE();
    dma_handle.Instance = DMA1_Channel1;
    dma_handle.Init.Direction = ;
    
    // 内存相关配置
    dma_handle.Init.MemDataAlignment = ;
    dma_handle.Init.MemInc = ;
    
    // 外设相关配置
    dma_handle.Init.PeriphDataAlignment = ;
    dma_handle.Init.PeriphInc = ;
    
    dma_handle.Init.Priority = ;
    dma_handle.Init.Mode = ;
    
    HAL_DMA_Init(&dma_handle);
}


