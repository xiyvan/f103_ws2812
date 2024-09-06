
#include "Display_task.h"
#include "bsp_ws2812.h"
#include "Z_math.h"
#include "bsp_ColorMixer.h"
#include "bsp_base.h"
#include "string.h"
#include "Clock.h"
#include "ModeSet_task.h"
#include "Light.h"
#include "Temputer.h"


extern Display_msg_t display_main;
extern ModeSet_msg_t mode_main;

unsigned char numbum = 0;
extern Picture_msg_t one;

extern const unsigned char SmallWig_Fish[][288];
extern const unsigned int SmallWight_AlarmClock[];

void display_show(void)
{
    static short num = 10;
    static unsigned char numbnum = 0;
    switch (mode_main.Display_mode)
    {
        case MODE_DISPLAY_CLOCK:
        {
            Clock_ShowClock();
        }break;
        case MODE_DISPLAY_LIGHT:
        {
            Light_Show();
        }break;
        case MODE_DISPLAY_DATE:
        {
            Clock_ShowDate();
        }break;
        case MODE_DISPLAY_TEMPUTER:
        {
            Temputer_show();
        }break;
        case MODE_DISPLAY_TEMPUTER_SHI:
        {
            Temputer_show_shi();
        }break;
        case MODE_DISPLAY_SMALL_PIC:
        {
            clear_all(&one);
            numbnum ++;
            if(numbnum >= 10)
            {
                write_picture(&one,1,1,12,8,&SmallWig_Fish[num][0]);
                Display_Update();
                num--;
                if(num < 0) num = 10;
                numbnum = 0;
            }
        }break;
        case MODE_DISPLAY_TEST:
        {
            clear_all(&one);
            write_picture_main(&one,1,1,7,7,SmallWight_AlarmClock);
            Display_Update();
        }break;;
	}
}



