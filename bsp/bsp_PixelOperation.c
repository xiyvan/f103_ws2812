
#include "bsp_PixelOperation.h"
#include "Z_math.h"





/// @brief 矩形填充
/// @param date 页面数据
/// @param x 左上角点x坐标
/// @param y 左上角点y坐标
/// @param x_end 右下角点x坐标
/// @param y_end 右下角点y坐标
/// @param rgb 填充颜色
void write_rectangle_full(Picture_msg_t* date,uint16_t x,uint16_t y,uint16_t x_end,uint16_t y_end,WS2812_msg_t* rgb)
{
    if(date == NULL || rgb == NULL) return ;

    // 判断输入的数据合法性
    if((x_end - x < 0) || ((y_end - y < 0)))
    {
        return ;
    }

    // 判断输入值是否超过边界
    if(x_end > RGB_KEY) x_end = RGB_KEY;
    if(y_end > RGB_BAR) y_end = RGB_BAR;


    for(uint8_t i = x;i <= x_end;i ++)
    {
        for(uint8_t j = y;j <= y_end;j++)
        {
            Ws2812_Set(date,i,j,rgb->R,rgb->G,rgb->B);
        }
    }
}



/// @brief 矩形框（不填充）
/// @param date 页面数据
/// @param x 左上角点x坐标
/// @param y 左上角点y坐标
/// @param x_end 右下角点x坐标
/// @param y_end 右下角点y坐标
/// @param rgb 填充颜色
/// @param wide 线宽像素
void write_rectangle_no(Picture_msg_t* date,uint16_t x,uint16_t y,uint16_t x_end,uint16_t y_end,WS2812_msg_t* rgb,uint16_t wide)
{
    if(date == NULL) return;

    // 判断输入的数据合法性
    if((x_end - x <= 0) || ((y_end - y <= 0)))
    {
        return ;
    }

    // 判断输入值是否超过边界
    if(x_end > RGB_KEY) x_end = RGB_KEY;
    if(y_end > RGB_BAR) y_end = RGB_BAR;

    // 上边框
    write_rectangle_full(date,x,y,x_end,(y+wide),rgb);
    // 下边框
    write_rectangle_full(date,x,(y_end - wide),x_end,y_end,rgb);
    // 左边框
    write_rectangle_full(date,x,y,(x+wide),y_end,rgb);
    // 右边框
    write_rectangle_full(date,(x_end - wide),y,x_end,y_end,rgb);
}



/// @brief 矩形区域清屏函数
/// @param date 图片结构体指针
/// @param x 
/// @param y 
/// @param x_end 
/// @param y_end 
/// @param back 背景颜色
void clear_rectangle(Picture_msg_t* date,unsigned char x,unsigned char y,unsigned char x_end,unsigned char y_end,WS2812_msg_t* back)
{
    write_rectangle_full(date,x,y,x_end,y_end,back);
}



/// @brief 全屏置零
/// @param date 图片指针
void clear_all(Picture_msg_t* date)
{
    memset(&date->rgb,0,sizeof(date->rgb));
}


/// @brief 画圆形
/// @param date 信息结构体
/// @param x 圆心x坐标
/// @param y 圆心y坐标
/// @param r 圆的版ing
/// @param rgb 颜色
void write_circular_no(Display_msg_t* date,uint16_t x,uint16_t y,uint16_t r,WS2812_msg_t* rgb)
{
    
}

unsigned short i_t = 1;
unsigned short j_t = 1;

/// @brief 写入图片
/// @param date 缓冲数据
/// @param x 起始行号
/// @param y 起始列号
/// @param widh 宽度
/// @param high 高度
/// @param T 颜色数据 RGB的顺序
void write_picture(Picture_msg_t* date,uint16_t x,uint16_t y,uint16_t widh,uint16_t high,const unsigned char* T)
{
    if(T == NULL || date == NULL)  return ;
    unsigned int num = 0;
    for(unsigned short i = x;i < x + high;i++)
    {
        for(unsigned short j = y;j < y + widh;j++)
        {
            Ws2812_Set(date,i,j,T[num],T[num+1],T[num+2]);
            num += 3;
        }
    }
}


/// @brief 写入图片负片
/// @param date 缓冲数据
/// @param x 起始行号
/// @param y 起始列号
/// @param widh 宽度
/// @param high 高度
/// @param T 颜色数据 RGB的顺序
void write_picture_F(Picture_msg_t* date,uint16_t x,uint16_t y,uint16_t widh,uint16_t high,const unsigned char* T,uint8_t max)
{
    if(T == NULL || date == NULL)  return ;
    unsigned int num = 0;
    for(unsigned short i = x;i < x + high;i++)
    {
        for(unsigned short j = y;j < y + widh;j++)
        {
            Ws2812_Set(date,i,j,max-T[num],max-T[num+1],max-T[num+2]);
            num += 3;
        }
    }
}



/// @brief 主要的绘制图片的方式可以使用取模软件直接生成的 RGB888类型的图片 24bit类型的 
/// @param date 缓冲数据
/// @param x 起始行号
/// @param y 起始列号
/// @param widh 宽度
/// @param high 高度
/// @param T 颜色数据 RGB的顺序
void write_picture_main(Picture_msg_t* date,uint16_t x,uint16_t y,uint16_t widh,uint16_t high,const unsigned int* T)
{
    if(date == NULL || T == NULL) return ;

    unsigned char R,G,B;
    unsigned int num = 0;

    for(unsigned short i = x;i < x + high;i++)
    {
        for(unsigned short j = y;j < y + widh;j++)
        {
            R = ((T[num] & 0xff0000) >> 16) & 0x0000ff;
            G = ((T[num] & 0x00ff00) >> 8)  & 0x0000ff;
            B = (T[num] & 0x0000ff);
            Ws2812_Set(date,i,j,R,G,B);
            num ++;
        }
    }
}



