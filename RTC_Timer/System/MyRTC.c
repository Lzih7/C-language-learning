#include "stm32f10x.h"
#include <time.h>

uint16_t MyRTC_Time[] = {2024, 1, 1, 23, 59, 55};

void MyRTC_SetTime(void);

void MyRTC_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    PWR_BackupAccessCmd(ENABLE); // 开启对备份寄存器的访问

    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {
        RCC_LSEConfig(RCC_LSE_ON); // 开启LSE
        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
            ; // 等待LSE就绪

        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); // 选取LSE作为RTC时钟源
        RCC_RTCCLKCmd(ENABLE);

        RTC_WaitForSynchro();
        RTC_WaitForLastTask();

        RTC_SetPrescaler(32767 - 1); // 设置RTC预分频器，32767对应1秒
        RTC_WaitForLastTask();

        MyRTC_SetTime(); // 设置时间

        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5); // 设置标志位
    }
    else
    {
        RTC_WaitForSynchro();
        RTC_WaitForLastTask();
    }
}

void MyRTC_SetTime(void)
{
    time_t time_cnt;
    struct tm time_info;
    time_info.tm_year = MyRTC_Time[0] - 1900; // 年份从1900开始
    time_info.tm_mon = MyRTC_Time[1] - 1;     // 月份
    time_info.tm_mday = MyRTC_Time[2];        // 日
    time_info.tm_hour = MyRTC_Time[3];        // 小时
    time_info.tm_min = MyRTC_Time[4];         // 分钟
    time_info.tm_sec = MyRTC_Time[5];         // 秒

    time_cnt = mktime(&time_info) - 8 * 60 * 60;
    RTC_SetCounter(time_cnt);

    RTC_WaitForLastTask();
}

void MyRTC_ReadTime(void)
{
    time_t time_cnt;
    struct tm time_info;
    time_cnt = RTC_GetCounter() + 8 * 60 * 60; // 转换为北京时间
    time_info = *localtime(&time_cnt);         // 获取本地时间

    MyRTC_Time[0] = time_info.tm_year + 1900; // 年份
    MyRTC_Time[1] = time_info.tm_mon + 1;     // 月份
    MyRTC_Time[2] = time_info.tm_mday;        // 日
    MyRTC_Time[3] = time_info.tm_hour;        // 小时
    MyRTC_Time[4] = time_info.tm_min;         // 分钟
    MyRTC_Time[5] = time_info.tm_sec;         // 秒
}
