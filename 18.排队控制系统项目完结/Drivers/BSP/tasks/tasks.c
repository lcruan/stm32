#include "tasks.h"
#include "led.h"
#include "beep.h"
#include "exti.h"
#include "lcd1602.h"
#include "gate.h"
#include "stdio.h"

enum
{
  PASS_STATE,
  WAIT_STATE
};

uint32_t led1_task_cnt = 0;
uint32_t led2_task_cnt = 0;
uint32_t wait_cnt = 0;
uint32_t passenger = 0;
uint8_t led1_task_flag = 0;
uint8_t led2_task_flag = 0;
char message[16] = {0};

uint8_t state = PASS_STATE;

void systick_isr(void)
{
   // 如果处于允许通行的状态
    if (state == PASS_STATE)
    {
       // LED1以1秒的频率闪烁
        if(led1_task_cnt < 1000)
            led1_task_cnt++;
        else
        {
            led1_task_flag = 1;
            led1_task_cnt = 0;
        }
        // LED2不闪烁
        led2_off();
        // 蜂鸣器不响
        beep_off();
        // 开门 
        gate_off(); // 继电器不闭合状态，闸门是打开的
        
    }
   // 如果处于不允许同行的状态
    else if (state == WAIT_STATE)
    {
       // LED2以200ms的频率闪烁
        if(led2_task_cnt < 200)
            led2_task_cnt++;
        else
        {
            led2_task_flag = 1;
            led2_task_cnt = 0;
        }
       // LED1不闪
       led1_off();
       // 蜂鸣器响
       beep_on();
       // 关门
       gate_on();
       // 计时3秒，之后
       if (wait_cnt < 3000)
            wait_cnt++;
       else
       {
           wait_cnt = 0;
           // 进入允许通行状态
           state = PASS_STATE;
           // LCD1602显示状态
           lcd1602_show_line(1, 1, "PASS...");
       }
     } 
}

void led1_task(void)
{
    if(led1_task_flag == 0)
        return;
    led1_task_flag = 0;
    
    led1_toggle();
}

void led2_task(void)
{
    if(led2_task_flag == 0)
        return;
    led2_task_flag = 0;
    
    led2_toggle();
}

void sensor_task(void)
{
    // 如果检测到有人通过
    if (ia_flag_get() == TRUE && state == PASS_STATE)
    {
        // 计数加1
        passenger++;
        // LCD1602显示状态
        sprintf(message, "PASS...%02d/05", passenger);
        lcd1602_show_line(1, 1, message);
    }
    // 如果通过的人数超过5个
    if (passenger >= 5)
    {
        // 计数清零
        passenger = 0;
        // 进入不允许通行状态
        state = WAIT_STATE;
        // LCD1602显示状态
        lcd1602_show_line(1, 1, "WAIT...00/05");
    }
        
}

