#include "rtc.h"


RTC_HandleTypeDef rtc_handle = {0};
void rtc_init(void)
{
    rtc_handle.Instance = RTC;
    rtc_handle.Init.AsynchPrediv = 32767;
    rtc_handle.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
    HAL_RTC_Init(&rtc_handle);
}

uint16_t rtc_read_bkr(uint8_t bkrx)
{
    
}

void rtc_write_bkr(uint8_t bkrx, uint16_t data)
{
    
}



