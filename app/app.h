#ifndef _APP_H_
#define _APP_H_

#include "includes.h"
#include "systick.h"
#include "OLED.h"
#include "KEY.h"
#include "dma.h"
#include "UI.h"


//任务堆栈大小
#define TASK_STK_SIZE              128
#define KEY_STK_SIZE 			   128 //按键扫描任务
#define OLED_STK_SIZE    		   2048 //UI显示
#define DMA_STK_SIZE			   512
//定义任务优先级
#define APP_START_TASK_PRIO        4
#define APP_LED1_TASK_PRIO         5
#define APP_LED0_TASK_PRIO         7
#define App_KEY_SCAN_PRIO		   8
#define OLED_TASK_PRIO	           9 //液晶显示任务
#define DMA_TASK_PRIO			   6



//声明任务堆栈
extern OS_STK  APP_START_STK[TASK_STK_SIZE];
extern OS_STK  APP_LED1_STK[TASK_STK_SIZE];
extern OS_STK  APP_LED0_STK[TASK_STK_SIZE];
extern OS_STK  KEY_TASK_STK[KEY_STK_SIZE];
extern OS_STK OLED_TASK_STK[OLED_STK_SIZE];  //UI显示
extern OS_STK  DMA_TASK_STK[DMA_STK_SIZE];  //DMA


//声明邮箱 
extern OS_EVENT *msg_key;				  //按键邮箱块指针


//全局变量 
extern int LEFT ;   //左线圈的值
extern int RIGHT;   //右线圈的值
extern int ENCODE;  //编码器的值



void AppLED1Task(void *pdata);
void AppLED0Task(void *pdata);
void TaskStart(void *pdata);
void AppStartTast(void *pdata);   //创建任务的任务
void allInit(void);           //初始化所有外设
void keyScan(void * pdata);   //按键扫描









#endif










