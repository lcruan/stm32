#include "uart1.h"
#include "stdio.h"
#include "string.h"

uint8_t uart1_rx_buf[UART1_RX_BUF_SIZE];
uint16_t uart1_rx_len = 0;

UART_HandleTypeDef uart1_handle = {0};

void uart1_init(uint32_t baudRate)
{
    uart1_handle.Instance = USART1;
    uart1_handle.Init.BaudRate = baudRate;
    uart1_handle.Init.WordLength = UART_WORDLENGTH_8B;
    uart1_handle.Init.StopBits = UART_STOPBITS_1;
    uart1_handle.Init.Parity = UART_PARITY_NONE;
    uart1_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart1_handle.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&uart1_handle);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitTypeDef gpio_initstruct;
        // 打开时钟
        // 调用GPIO初始化函数
        // 配置TX
        gpio_initstruct.Pin = GPIO_PIN_9;
        gpio_initstruct.Mode = GPIO_MODE_AF_PP;
        gpio_initstruct.Pull = GPIO_PULLUP;
        gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &gpio_initstruct);
        
        // 配置RX
        gpio_initstruct.Pin = GPIO_PIN_10;
        gpio_initstruct.Mode = GPIO_MODE_AF_INPUT;
        HAL_GPIO_Init(GPIOA, &gpio_initstruct);
        
        // 配置NVIC
        HAL_NVIC_EnableIRQ(USART1_IRQn);
        HAL_NVIC_SetPriority(USART1_IRQn, 2, 2);
        
        __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
        __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE); // 空闲中断打开
        
        
    }
}

// 把接收寄存器的内容清空
void uart1_rx_clear(void)
{
    memset(uart1_rx_buf, 0, sizeof(uart1_rx_buf));
    uart1_rx_len = 0;
}

void USART1_IRQHandler(void)
{
    uint8_t receive_data = 0;
    if (__HAL_UART_GET_FLAG(&uart1_handle, UART_FLAG_RXNE) != RESET)
    {
        if (uart1_rx_len >= sizeof(uart1_rx_buf))
            uart1_rx_len = 0;
        HAL_UART_Receive(&uart1_handle, &receive_data, 1, 1000);
        uart1_rx_buf[uart1_rx_len++] = receive_data;
        // uart1_cnt++;
        // HAL_UART_Transmit(&uart1_handle, &receive_data, 1, 1000);
    }
    
    // 接收到了空闲中断,代表数据接收完整了，那么把数据打印出来
    if (__HAL_UART_GET_FLAG(&uart1_handle, UART_FLAG_IDLE) != RESET) 
    {
        printf("recv: %s\r\n", uart1_rx_buf);
        uart1_rx_clear();
        __HAL_UART_CLEAR_IDLEFLAG(&uart1_handle);
    }
}

// 就是把传来的字符串，丢到寄存器里面，然后串口工具就把数据打印出来了
int fputc(int ch, FILE *f)
{
    while((USART1->SR & 0X40) == 0);
        
    USART1->DR = (uint8_t)ch;
    return ch;
}

