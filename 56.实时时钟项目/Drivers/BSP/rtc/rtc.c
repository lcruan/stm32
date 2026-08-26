#include "rtc.h"
#include "stdio.h"
#include "beep.h"


RTC_HandleTypeDef rtc_handle = {0};
void rtc_init(void)
{
    // 使能电源及后备域时钟
    // 使能后备域访问
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_BKP_CLK_ENABLE();
    HAL_PWR_EnableBkUpAccess();
    
    rtc_handle.Instance = RTC;
    rtc_handle.Init.AsynchPrediv = 32767;
    rtc_handle.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
    HAL_RTC_Init(&rtc_handle);
}

void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc)
{
    __HAL_RCC_RTC_ENABLE();
    
    RCC_OscInitTypeDef osc_initstruct = {0};
    RCC_PeriphCLKInitTypeDef periphclk_initstruct = {0};
    
    // 配置LSE
    osc_initstruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
    osc_initstruct.LSEState = RCC_LSE_ON;
    osc_initstruct.PLL.PLLState = RCC_PLL_NONE;
    HAL_RCC_OscConfig(&osc_initstruct);
    
    periphclk_initstruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    periphclk_initstruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    HAL_RCCEx_PeriphCLKConfig(&periphclk_initstruct);
    
    HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 2, 2); // 设置优先级
    HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn); // 启动中断
}

void RTC_Alarm_IRQHandler(void)
{
    HAL_RTC_AlarmIRQHandler(&rtc_handle);
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
    printf("ring ring ring...\r\n");
    beep_on();
}

uint16_t rtc_read_bkr(uint8_t bkrx)
{
    uint32_t data = 0;
    data = HAL_RTCEx_BKUPRead(&rtc_handle, bkrx);
    return (uint16_t)data;
}

void rtc_write_bkr(uint8_t bkrx, uint16_t data)
{
    HAL_RTCEx_BKUPWrite(&rtc_handle, bkrx, data);
}

void rtc_get_time(uint8_t *time_data)
{
    RTC_TimeTypeDef rtc_time = {0};
    RTC_DateTypeDef rtc_date = {0};
    // 获取当前时间
    HAL_RTC_GetTime(&rtc_handle, &rtc_time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&rtc_handle, &rtc_date, RTC_FORMAT_BIN);
    
    time_data[0] = rtc_date.Year;
    time_data[1] = rtc_date.Month;
    time_data[2] = rtc_date.Date;
    time_data[3] = rtc_time.Hours;
    time_data[4] = rtc_time.Minutes;
    time_data[5] = rtc_time.Seconds;
    
//    printf("rtc time: %d-%02d-%02d %02d:%02d:%02d\r\n", rtc_date.Year + 2000, rtc_date.Month, rtc_date.Date, 
//        rtc_time.Hours, rtc_time.Minutes, rtc_time.Seconds);
}

void rtc_set_time(uint8_t *time_data)
{
    RTC_TimeTypeDef rtc_time = {0};
    RTC_DateTypeDef rtc_date = {0};
    
    rtc_time.Hours = time_data[3];
    rtc_time.Minutes = time_data[4];
    rtc_time.Seconds = time_data[5];
    HAL_RTC_SetTime(&rtc_handle, &rtc_time, RTC_FORMAT_BIN);
    
//    rtc_date.Year = time_data.tm_year - 2000
    rtc_date.Year = time_data[0]; // uint8_t是2^8=256，如果+2000就溢出了
    rtc_date.Month = time_data[1];
    rtc_date.Date = time_data[2];
    HAL_RTC_SetDate(&rtc_handle, &rtc_date, RTC_FORMAT_BIN);
    
    while(!__HAL_RTC_ALARM_GET_FLAG(&rtc_handle, RTC_FLAG_RTOFF));
}

void rtc_get_alarm(uint8_t *alarm_data)
{
    RTC_AlarmTypeDef alarm = {0}; 
    HAL_RTC_GetAlarm(&rtc_handle, &alarm, RTC_ALARM_A, RTC_FORMAT_BIN);
    
    alarm_data[0] = alarm.AlarmTime.Hours;
    alarm_data[1] = alarm.AlarmTime.Minutes;
    alarm_data[2] = alarm.AlarmTime.Seconds;
    
}

void rtc_set_alarm(uint8_t *alarm_data)
{
    RTC_AlarmTypeDef alarm = {0}; 
    alarm.Alarm = RTC_ALARM_A;
    alarm.AlarmTime.Hours = alarm_data[0];
    alarm.AlarmTime.Minutes = alarm_data[1];
    alarm.AlarmTime.Seconds = alarm_data[2];
    HAL_RTC_SetAlarm_IT(&rtc_handle, &alarm, RTC_FORMAT_BIN);
}




