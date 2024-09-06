
#include "Clock.h"
#include "bsp_PixelOperation.h"
#include "bsp_base.h"
#include "stdio.h"

extern Display_msg_t display_main;
extern RTC_TimeTypeDef rtc_main;
extern RTC_DateTypeDef rtc_date;
extern RTC_HandleTypeDef hrtc;


/// 保存RTC时间
RTC_TimeTypeDef rtc_main;
// 保存RTC日期
RTC_DateTypeDef rtc_date;

// 用来显示时间
extern Picture_msg_t one;

char t[6] = {0};

const unsigned char Clock_icon_pic[]={128,128,128, 128,128,128, 32,32,32, 32,32,32,    32,32,32,    32,32,32,    128,128,128, 128,128,128,
                                      128,128,128, 16,16,16,    0,0,0,    128,128,128, 0,0,0,       0,0,0,       16,16,16,    128,128,128,
                                      32,32,32,       0,0,0,    0,0,0,    128,128,128, 0,0,0,       0,0,0,       0,0,0,       32,32,32,
                                      32,32,32,       0,0,0,    0,0,0,    128,128,128, 0,0,0,       128,128,128, 0,0,0,       32,32,32,
                                      32,32,32,       0,0,0,    0,0,0,    128,128,128, 128,128,128, 0,0,0,       0,0,0,       32,32,32,
                                      32,32,32,       0,0,0,    0,0,0,    0,0,0,       0,0,0,       0,0,0,       0,0,0,       32,32,32,
                                      128,128,128, 16,16,16,    0,0,0,    0,0,0,       0,0,0,       0,0,0,       16,16,16,    128,128,128,
                                      128,128,128, 128,128,128, 32,32,32, 32,32,32,    32,32,32,    32,32,32,    128,128,128, 128,128,128};


/// @brief 根据获取到的时间与选炫彩的更新，将他们显示到屏幕上面
void Clock_ShowClock(void)
{
    clear_all(&one);
    static uint8_t n = 0;
    // 用来记录运行了几次
    static unsigned char number = 0;

    if(n == 0)
    {
        // 初始化  这里的函数只会执行一次

        n = 1;
    }
    // 每20ms运行一次
    Clock_GetTime_Color();
    number ++;
    // 每100ms运行一次
    if(number >= 4)
    {
        sprintf(&t[2],"%1d",rtc_main.Minutes / 10);         // 分十位
        sprintf(&t[3],"%1d",rtc_main.Minutes % 10);         // 分个位
        sprintf(&t[4],"%1d",rtc_main.Hours / 10);           // 小时十位
        sprintf(&t[5],"%1d",rtc_main.Hours % 10);           // 小时个位

        SetCursor(2,13);
        Write_OneChar(&one,66,20,150,t[4],0);
        SetCursor(2,17);
        Write_OneChar(&one,66,20,150,t[5],0);

        SetCursor(2,23);
        Write_OneChar(&one,66,20,150,t[2],0);
        SetCursor(2,27);
        Write_OneChar(&one,66,20,150,t[3],0);

        Ws2812_Set(&one,3,21,66,20,150);
        Ws2812_Set(&one,5,21,66,20,150);
        write_picture(&one,1,1,8,8,Clock_icon_pic);
        
        Display_Update();
        number = 0;
    }
}



/// @brief 显示日期
void Clock_ShowDate(void)
{
    clear_all(&one);
    static uint8_t n = 0;
    char t [6] = {0};

    n ++;
    if(n >= 4)
    {
        Ws2812_Set(&one,4,11,66,20,150);

        sprintf(t,"%1d",rtc_date.Month/10);                     // 月十位
        sprintf(&t[1],"%1d",rtc_date.Month % 10);               // 月个位
        sprintf(&t[2],"%1d",rtc_date.Date / 10);                // 日十位
        sprintf(&t[3],"%1d",rtc_date.Date % 10);                // 日个位
        sprintf(&t[4],"%1d",rtc_date.WeekDay / 10);             // 星期十位
        sprintf(&t[5],"%1d",rtc_date.WeekDay % 10);             // 星期个位

        SetCursor(2,3);
        Write_OneChar(&one,66,20,150,t[0],0);             // 显示月份
        SetCursor(2,7);
        Write_OneChar(&one,66,20,150,t[1],0);

        SetCursor(2,13);                                // 显示日期
        Write_OneChar(&one,66,20,150,t[2],0);
        SetCursor(2,17);
        Write_OneChar(&one,66,20,150,t[3],0);

        SetCursor(2,23);                                // 显示星期
        Write_OneChar(&one,66,20,150,t[4],0);
        SetCursor(2,27);                                
        Write_OneChar(&one,66,20,150,t[5],0);

        Display_Update();
        n = 0;
    }
}



/// @brief 闹钟显示画面
void Clock_ShowAlarmClock(void)
{
    
}


/// @brief 获取时间并刷新炫彩颜色
void Clock_GetTime_Color(void)
{
    HAL_RTC_GetTime(&hrtc,&rtc_main,RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc,&rtc_date,RTC_FORMAT_BIN);
}




