#ifndef _KEY_H
#define _KEY_H
#include "common.h"

 
#define KEY_U  PAin(13)
#define KEY_D  PAin(12)
#define KEY_A  PAin(19)
#define KEY_B  PAin(11)


///////////////////////////////////////

typedef enum
{   
    KEY_DOWN    = 12,  //下键
    KEY_RIGHT   = 19,  //右键
    KEY_UP      = 13, //上键
    KEY_LEFT    = 11, //左键
	
	
}KEY_e;

static void KEY_Scan(void);
void KEY_Init(void);    //按键初始化
void KEY_Service(void); //中断管脚配置

#endif












