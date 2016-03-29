#ifndef _APP_H_
#define _APP_H_

#include "includes.h"
#include "systick.h"
#include "OLED.h"
#include "KEY.h"


//任务堆栈大小
#define TASK_STK_SIZE              (128)
#define KEY_STK_SIZE 			   (128) //按键扫描任务
//定义任务优先级
#define APP_START_TASK_PRIO        (4)
#define APP_LED1_TASK_PRIO         (5)
#define APP_LED0_TASK_PRIO         (7)
#define App_KEY_SCAN_PRIO		   (8)



//声明任务堆栈
extern OS_STK  APP_START_STK[TASK_STK_SIZE];
extern OS_STK  APP_LED1_STK[TASK_STK_SIZE];
extern OS_STK  APP_LED0_STK[TASK_STK_SIZE];
extern OS_STK  KEY_TASK_STK[KEY_STK_SIZE];



void AppLED1Task(void *pdata);
void AppLED0Task(void *pdata);
void TaskStart(void *pdata);
void AppStartTast(void *pdata);   //创建任务的任务
void allInit(void);           //初始化所有外设
void keyScan(void * pdata);   //按键扫描









#endif










