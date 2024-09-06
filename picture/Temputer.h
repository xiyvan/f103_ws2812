
#ifndef _TEMPUTER_H_
#define _TEMPUTER_H_


#include "dht11_driver.h"
#include "bsp_ws2812.h"


typedef struct 
{
    dht11_msg_t temp_date;
    char T[6];              // 用来保存6个字符
}temputer_msg_t;


///**************************************  函数声明 ************************************/

void Temputer_show(void);
void Temputer_show_shi(void);

///*************************************** endl ****************************************/





#endif
