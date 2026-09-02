#include "can.h"

CAN_HandleTypeDef can_handle = {0};
void can_init(void)
{
    can_handle.Instance = CAN1;
    can_handle.Init.Mode = CAN_MODE_NORMAL;
    
    can_handle.Init.Prescaler = 4;
    can_handle.Init.TimeSeg1 = CAN_BS1_9TQ;
    can_handle.Init.TimeSeg2 = CAN_BS2_8TQ;
    can_handle.Init.SyncJumpWidth = CAN_SJW_1TQ;
    
    can_handle.Init.AutoBusOff           = DISABLE;  /* 禁止自动离线管理 */
    can_handle.Init.AutoRetransmission   = DISABLE;  /* 禁止自动重发 */
    can_handle.Init.AutoWakeUp           = DISABLE;  /* 禁止自动唤醒 */
    can_handle.Init.ReceiveFifoLocked    = DISABLE;  /* 禁止接收FIFO锁定 */
    can_handle.Init.TimeTriggeredMode    = DISABLE;  /* 禁止时间触发通信模式 */
    can_handle.Init.TransmitFifoPriority = DISABLE;  /* 禁止发送FIFO优先级 */
    
    HAL_CAN_Init(&can_handle);
    
    CAN_FilterTypeDef can_filterconfig = {0};
    can_filterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
    
    can_filterconfig.FilterIdHigh = 0;
    can_filterconfig.FilterIdLow = 0;
    can_filterconfig.FilterMaskIdHigh = 0;
    can_filterconfig.FilterMaskIdLow = 0;
    
    can_filterconfig.FilterBank = 0;
    can_filterconfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    can_filterconfig.FilterActivation = CAN_FILTER_ENABLE;
    can_filterconfig.SlaveStartFilterBank = 14;
    HAL_CAN_ConfigFilter(&can_handle, &can_filterconfig);
    
    HAL_CAN_Start(&can_handle);
}


void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan)
{
    __HAL_RCC_CAN1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    GPIO_InitTypeDef gpio_initstruct;
    gpio_initstruct.Pin = GPIO_PIN_12;
    gpio_initstruct.Mode = GPIO_MODE_AF_PP;
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio_initstruct);
    
    gpio_initstruct.Pin = GPIO_PIN_11;
    gpio_initstruct.Mode = GPIO_MODE_AF_INPUT;

    HAL_GPIO_Init(GPIOA, &gpio_initstruct);
}

// can数据收发
void can_send_data(uint32_t id, uint8_t *buf, uint8_t len)
{
    
}

// can数据接收
uint8_t can_receive_data(uint8_t *buf)
{
    
}
