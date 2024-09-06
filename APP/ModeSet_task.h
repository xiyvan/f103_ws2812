
#ifndef _MODESET_TASK_H_
#define _MODESET_TASK_H_

#include "bsp_ws2812.h"

//长按时间 n X 10ms
#define MODE_SET_LONGTIME 100   



typedef struct 
{
    // 总的显示页面
    short Display_mode;

    // 小夜灯亮度调节
    unsigned char Light_num;

    unsigned char now;          // 当前的按键状态
    unsigned char last_now;     // 上一次的按键状态
    unsigned char state;        // 按下的状态
    unsigned char time[2];      // 记录一个按键按下去的时间

}ModeSet_msg_t;


enum
{
    MODE_SET_NO,                // 没有按下
    MODE_SET_SHORT_0,           // 短按
    MODE_SET_SHORT_1,
    MODE_SET_LONG_0,            // 长按标志位
    MODE_SET_LONG_1,
    MODE_SET_X                  // 已响应过标志位
};



enum
{
    MODE_DISPLAY_CLOCK,
    MODE_DISPLAY_DATE,
    MODE_DISPLAY_TEMPUTER,
    MODE_DISPLAY_TEMPUTER_SHI,
    MODE_DISPLAY_LIGHT,
    MODE_DISPLAY_SMALL_PIC,
    MODE_DISPLAY_TEST,
    MODE_DISPLAY_ALL
};




void ModeSet_task(void);



#endif
