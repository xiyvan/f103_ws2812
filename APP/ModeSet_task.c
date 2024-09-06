
#include "ModeSet_task.h"
#include "Light.h"


static unsigned char ReadKey(void);


ModeSet_msg_t mode_main;
extern Light_msg_t Light_main;

void ModeSet_task(void)
{
    static char num = 0;

    if(num == 0)
    {
        memset(&mode_main,0,sizeof(mode_main));
        num = 1;
    }

    mode_main.now = ReadKey();

//********************************************************* 显示模式设置 ********************************************/

    if(mode_main.state == MODE_SET_SHORT_0)
    {
        mode_main.state = MODE_SET_NO;
        mode_main.Display_mode --;
        if(mode_main.Display_mode < 0) mode_main.Display_mode = 0;
    }
    else if(mode_main.state == MODE_SET_SHORT_1)
    {
        mode_main.state = MODE_SET_NO;
        mode_main.Display_mode ++;
        if(mode_main.Display_mode > 6) mode_main.Display_mode = 6;
    }


///********************************************************** 判断长短按 **************************************************/
    if(mode_main.now == 0 && mode_main.last_now == 4)           // 判断按键抬起
    {
        // 长按时间清零
        mode_main.time[1] = 0;                                  
        // 判断是不是已经被赋予长按或者已经响应标志位
        if(mode_main.state != MODE_SET_LONG_1 && mode_main.state != MODE_SET_X)
        {
            // 如果没有的话 就赋予按键1短按标志位
            mode_main.state = MODE_SET_SHORT_1;
        }
        // 如果被赋予了已响应标志位， 按键抬起来的时候就赋予他 没有按下 标志位
        if(mode_main.state == MODE_SET_X)   mode_main.state = MODE_SET_NO;
    }
    else if(mode_main.now == 0 && mode_main.last_now == 2)      // 判断短按
    {   
        // 本内容同上
        mode_main.time[0] = 0;
        if(mode_main.state != MODE_SET_LONG_0 && mode_main.state != MODE_SET_X)
        {
            mode_main.state = MODE_SET_SHORT_0;
        }
        if(mode_main.state == MODE_SET_X)   mode_main.state = MODE_SET_NO;
    }
    
    // 如果按键被按下 就让时间增加
    if(mode_main.now == 2 && mode_main.last_now == 2)
    {
        mode_main.time[0] ++;
    }

    if(mode_main.now == 4 && mode_main.last_now == 4)
    {
        mode_main.time[1] ++;
    }

    // 时间增加到长按设定时间的时候
    if(mode_main.time[0] >= MODE_SET_LONGTIME)
    {
        // 判断是不是已经响应过了
        if(mode_main.state != MODE_SET_X)
        {
            // 如果没有 已经响应标志位 就付给他长按0标志位
            mode_main.state = MODE_SET_LONG_0;              // 确定为一号长按
        }
        mode_main.time[0] = MODE_SET_LONGTIME + 2;
    }
    if(mode_main.time[1] >= MODE_SET_LONGTIME) 
    {   
        if(mode_main.state != MODE_SET_X)
        {
            mode_main.state = MODE_SET_LONG_1;              // 确定为二号长按
        }
        mode_main.time[1] = MODE_SET_LONGTIME + 2;
    }
///********************************************************** endl ***************************************************/

    mode_main.last_now = mode_main.now;
}






/// @brief 如果读取到按键的动作就返回相应的数字
/// @return 如果没有读取到就返回 0
static unsigned char ReadKey(void)
{
    if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1) == 0)
    {
        return 2;
    }
    else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) == 0)
    {
        return 4;
    }

    return 0;
}
