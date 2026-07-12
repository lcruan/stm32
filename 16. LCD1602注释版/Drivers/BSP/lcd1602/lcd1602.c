#include "lcd1602.h"
#include "string.h"
#include <stdarg.h>
#include "delay.h"

// RS引脚定义
#define RS_GPIO_Port GPIOB
#define RS_GPIO_PIN GPIO_PIN_1
#define RS_HIGH     HAL_GPIO_WritePin(RS_GPIO_Port, RS_GPIO_PIN, GPIO_PIN_SET)
#define RS_LOW      HAL_GPIO_WritePin(RS_GPIO_Port, RS_GPIO_PIN, GPIO_PIN_RESET)

// RW引脚定义
#define RW_GPIO_Port GPIOB
#define RW_GPIO_PIN GPIO_PIN_2
#define RW_HIGH     HAL_GPIO_WritePin(RW_GPIO_Port, RW_GPIO_PIN, GPIO_PIN_SET)
#define RW_LOW      HAL_GPIO_WritePin(RW_GPIO_Port, RW_GPIO_PIN, GPIO_PIN_RESET)

// EN引脚定义
#define EN_GPIO_Port GPIOB
#define EN_GPIO_PIN GPIO_PIN_10
#define EN_HIGH     HAL_GPIO_WritePin(EN_GPIO_Port, EN_GPIO_PIN, GPIO_PIN_SET)
#define EN_LOW      HAL_GPIO_WritePin(EN_GPIO_Port, EN_GPIO_PIN, GPIO_PIN_RESET)

/**
 * @brief       LCD1602 GPIO初始化
 * @param       无
 * @retval      无
 */
void lcd1602_gpio_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  //__HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
//                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_SET);

//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10, GPIO_PIN_SET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB1 PB2 PB10 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
 * @brief       lcd开始工作
 * @param       无
 * @retval      无
 */
void lcd1602_start(void)
{
//（1）延时 15ms
    delay_ms(15);
//（2）写指令 38H(不检测忙信号) 
    lcd1602_write_cmd(0x38);
//（3）延时 5ms
    delay_ms(5);
//（4）检测忙信号(省略)
//（5）写指令 38H：显示模式设置
    lcd1602_write_cmd(0x38);
//（6）写指令 08H：显示关闭
    lcd1602_write_cmd(0x08);
//（7）写指令 01H：显示清屏
    lcd1602_write_cmd(0x01);
//（8）写指令 06H：显示光标移动设置
    lcd1602_write_cmd(0x06);
//（9）写指令 0CH：显示开及光标设置
    lcd1602_write_cmd(0x0c);
}

/**
 * @brief       LCD1602初始化
 * @param       无
 * @retval      无
 */
void lcd1602_init(void)
{
    lcd1602_gpio_init();
    lcd1602_start();
}

/**
 * @brief       写指令
* @param        cmd：指令
 * @retval      无
 */
void lcd1602_write_cmd(char cmd)
{
    RS_LOW;
    RW_LOW;
    EN_LOW;
    GPIOA->ODR = cmd;       //将一字节数据发到GPIOA 8个引脚
    delay_ms(5);
    EN_HIGH;
    delay_ms(5);
    EN_LOW;
}

/**
 * @brief       写数据
 * @param       dataShow：显示的字符
 * @retval      无
 */
void lcd1602_write_data(char dataShow)
{
    RS_HIGH;
    RW_LOW;
    EN_LOW;
    GPIOA->ODR = dataShow;   //将一字节数据发到GPIOA 8个引脚
    delay_ms(5);
    EN_HIGH;
    delay_ms(5);
    EN_LOW;
}

/**
 * @brief       画面右移
 * @param       无
 * @retval      无
 */
void lcd1602_right_move(void)
{
    for(int i=0;i < 16;i++){
        delay_ms(1000);
        lcd1602_write_cmd(0x18);            //画面右移一位 0x18
    }
}

/**
 * @brief       显示字符
 * @param       row: 显示行，col： 显示起始列，string：显示字符
 * @retval      无
 */
void lcd1602_show_line(char row, char col, char *string)
{
    switch(row){
    case 1:
        lcd1602_write_cmd(0x80+col);        //最高位 D7 为高电平
        while(*string){
            lcd1602_write_data(*string);
            string++;
        }
        break;
    
    case 2:
        lcd1602_write_cmd(0x80+0x40+col);
        while(*string){
            lcd1602_write_data(*string);
            string++;
        }
        break;
    }
}
