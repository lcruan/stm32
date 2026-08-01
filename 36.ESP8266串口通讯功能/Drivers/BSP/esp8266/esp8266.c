#include "esp8266.h"
#include "stdio.h"
#include "string.h"
#include "delay.h"

uint8_t esp8266_rx_buf[ESP8266_RX_BUF_SIZE];
uint16_t esp8266_cnt = 0, esp8266_cntPre = 0;

UART_HandleTypeDef esp8266_handle = {0};

void esp8266_uart_init(uint32_t baudRate)
{
    esp8266_handle.Instance = USART2;
    esp8266_handle.Init.BaudRate = baudRate;
    esp8266_handle.Init.WordLength = UART_WORDLENGTH_8B;
    esp8266_handle.Init.StopBits = UART_STOPBITS_1;
    esp8266_handle.Init.Parity = UART_PARITY_NONE;
    esp8266_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    esp8266_handle.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&esp8266_handle);
}

void USART2_IRQHandler(void)
{
    uint8_t receive_data = 0;
    if (__HAL_UART_GET_FLAG(&esp8266_handle, UART_FLAG_RXNE) != RESET)
    {
        if (esp8266_cnt >= sizeof(esp8266_rx_buf))
            esp8266_cnt = 0;
        HAL_UART_Receive(&esp8266_handle, &receive_data, 1, 1000);
        esp8266_rx_buf[esp8266_cnt++] = receive_data;
        // uart1_cnt++;
        // HAL_UART_Transmit(&uart1_handle, &receive_data, 1, 1000);
    }
}


// 判断uart1_cnt有没有在动
uint8_t esp8266_wait_receive(void)
{
    // 发现错误
    if (esp8266_cnt == 0)
        return ESP8266_ERROR;
    
    // 如果跟上一次一样，说明不动了
    if (esp8266_cnt == esp8266_cntPre)
    {
        esp8266_cnt = 0;
        return ESP8266_EOK;
    }
    
    // 当前的值赋给之前的值
    esp8266_cntPre = esp8266_cnt;
    return ESP8266_ERROR;
}

// 把接收寄存器的内容清空
void esp8266_rx_clear(void)
{
    memset(esp8266_rx_buf, 0, sizeof(esp8266_rx_buf));
    esp8266_cnt = 0;
}

void esp8266_receive_data(void)
{
    if (esp8266_wait_receive() == ESP8266_EOK)
    {
        printf("esp8266 recv: %s\r\n", esp8266_rx_buf);
        esp8266_rx_clear();
    }
}

void esp8266_init(uint32_t baudRate)
{
    esp8266_uart_init(baudRate);
    
    // esp8266的其他初始化
}

uint8_t esp8266_send_command(char *cmd, char *res)
{
    uint8_t time_out = 250;
    esp8266_rx_clear();
    // 通过这个函数把我们要发送的指令，发送过去
    HAL_UART_Transmit(&esp8266_handle, (uint8_t *)cmd, strlen(cmd), 100);
    // 等待接收esp8266返回值
    
    // 循环不停的检测 接收缓存区里面的数值 有没有我们期待的 数值有没有ok
    while(time_out--)
    {
        // 判断接收缓冲区里面是否有值
        if (esp8266_wait_receive() == ESP8266_EOK)
        {
            // 接收缓冲区里面有我期待的 res里面的字符串
            if (strstr((const char*)esp8266_rx_buf, res) != NULL)
                return ESP8266_EOK;
        }
        delay_ms(10);
    }
    
    return ESP8266_ERROR;
}

void esp8266_test(void)
{
    // 测试函数：有接收到OK这个返回值
    if(esp8266_send_command("AT", "OK") == ESP8266_EOK)
        printf("esp8266 test: %s\r\n", esp8266_rx_buf);  
}




