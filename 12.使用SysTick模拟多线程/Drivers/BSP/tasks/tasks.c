#include "tasks.h"
#include "led.h"

uint32_t task1_cnt = 0;
uint32_t task2_cnt = 0;
uint8_t task1_flag = 0;
uint8_t task2_flag = 0;

void systick_isr(void)
{
  if(task1_cnt < 1000)
    task1_cnt++;
  else
  {
      task1_flag = 1;
      task1_cnt = 0;
  }
  
  if(task2_cnt < 500)
    task2_cnt++;
  else
  {
      task2_flag = 1;
      task2_cnt = 0;
  }
}

void task1(void)
{
    if(task1_flag == 0)
        return;
    task1_flag = 0;
    
    led1_toggle();
}

void task2(void)
{
    if(task2_flag == 0)
        return;
    task2_flag = 0;
    
    led2_toggle();
}

