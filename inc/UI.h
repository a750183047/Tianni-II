#ifndef _UI_H_
#define _UI_H_
#include "common.h"
#include  "KEY.h"
/*******变量声明*******/

extern u8 (*FunctionPointer[11])(void);
//extern u8 KEY_;
extern u8 FLAG_RUN;
extern u8 Plan_1;
extern u8 Plan_2;
extern u8 Plan_3;
extern u8 Plan_4;
extern u8 Plan_5;
extern u8 Plan_6;


extern u8 FLAG_RUN;

extern u8 (*FunctionPointer[11])(void);


#define Menu_UI_ID               0
#define Run_UI_ID                1
#define State1_UI_ID             2
#define Set_UI_ID                3
#define Record_UI_ID             4
#define Read_UI_ID               5

/*******函数声明*******/

//void KEY_Init();    //按键初始化
//void KEY_Service(); //中断管脚配置


void KEY_Display(void);   //界面功能显示

u8 UI_Menu(void);      //主界面
u8 UI_Star(void);      //起跑
u8 UI_PID(void);       //显示PID参数界面
u8 UI_State(void);     //显示小车状态界面
u8 UI_Flash(void);  //显示方案A
u8 UI_Scheme_B(void);  //显示方案B


u8 Menu_UI(void); //  主界面 ID为0
u8 Run_UI(void);  //  起跑界面 ID为1
u8 State1_UI(void); //  查看磁头状态界面 ID为2
u8 Set_UI(void);   //  参数设置界面 ID为3
u8 Record_UI(void); // 参数储存界面 ID为4
u8 Read_UI(void); //ID为5
void AddNumString(u8 ss[],u8 n[]);//数字加入显示字符串
void speedClear(void);            //电机舵机 回到初始状态

#endif

