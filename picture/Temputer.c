
#include "Temputer.h"
#include "string.h"
#include "bsp_PixelOperation.h"
#include "bsp_base.h"
#include "stdio.h"

temputer_msg_t Temputer_main;
extern Display_msg_t display_main;
extern const unsigned char Temputer_icon_pic[][144];
extern const unsigned char Temputer_icon_shi[][90];
extern Picture_msg_t one;
static unsigned char error = 0;         // 用来记录读取失败的次数

void Temputer_show(void)
{
    clear_all(&one);
    static unsigned char number = 0;    // 用来延时
    static short num = 0;               // 用来做动画的计数
    number ++;
    if(number >= 25)
    {
        if(dht11_ReadDate(&Temputer_main.temp_date) == 0) error ++;       // 读取温度
        else error = 0;
        write_picture(&one,1,2,6,8,&Temputer_icon_pic[num][0]);
        if(error <= 10)
        {
            sprintf(Temputer_main.T,"%1d",(short)Temputer_main.temp_date.temputer / 10);                   // 温度十位
            sprintf(&Temputer_main.T[1],"%1d",(short)Temputer_main.temp_date.temputer % 10);               // 温度个位
            sprintf(&Temputer_main.T[2],"%1d",(short)(Temputer_main.temp_date.temputer * 10) % 10);        // 温度小数位

            SetCursor(2,12);                     // 温度
            Write_OneChar(&one,209,59,13,Temputer_main.T[0],0);
            SetCursor(2,16);
            Write_OneChar(&one,209,59,13,Temputer_main.T[1],0);
            Ws2812_Set(&one,6,20,209,59,13);                         // 小数点
            SetCursor(2,22);
            Write_OneChar(&one,209,59,13,Temputer_main.T[2],0);      // 小数位
            SetCursor(2,28);
            Write_OneChar(&one,209,59,13,'C',0);
        }
        else
        {
            error = 100;
            SetCursor(2,16);                     // 湿度
            Write_OneChar(&one,128,0,0,'X',0);
        }
        num ++;
        if(num > 3) num = 0;
        Display_Update();
        number = 0;
    }
}


void Temputer_show_shi(void)
{
    clear_all(&one);
    static unsigned char number = 0;    // 用来延时
    static short num = 0;                   // 动画播放
    number ++;

    if(number > 25)
    {
        if(dht11_ReadDate(&Temputer_main.temp_date) == 0) error ++;       // 读取温度
        else error = 0;
        write_picture(&one,2,2,5,6,&Temputer_icon_shi[num][0]);                   // 画湿度检测的图标
        if(error <= 10)
        {
            sprintf(&Temputer_main.T[3],"%1d",(short)Temputer_main.temp_date.humidity / 10);               // 湿度十位
            sprintf(&Temputer_main.T[4],"%1d",(short)Temputer_main.temp_date.humidity % 10);               // 湿度个位
            sprintf(&Temputer_main.T[5],"%1d",(short)(Temputer_main.temp_date.humidity * 10) % 10);        // 湿度小数位

            SetCursor(2,12);                     // 湿度
            Write_OneChar(&one,54,135,222,Temputer_main.T[3],0);
            SetCursor(2,16);
            Write_OneChar(&one,54,135,222,Temputer_main.T[4],0);
            Ws2812_Set(&one,6,20,54,135,222);                         // 小数点
            SetCursor(2,22);
            Write_OneChar(&one,54,135,222,Temputer_main.T[5],0);      // 小数位
        }
        else
        {
            error = 100;
            SetCursor(2,16);                     // 湿度
            Write_OneChar(&one,128,0,0,'X',0);
        }
        number = 0;
        num++;
        if(num > 2) num = 0;
        Display_Update();
    }
}


