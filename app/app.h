#ifndef _APP_H_
#define _APP_H_

#include "includes.h"
#include "systick.h"
#include "OLED.h"
#include "KEY.h"


//�����ջ��С
#define TASK_STK_SIZE              (128)
#define KEY_STK_SIZE 			   (128) //����ɨ������
//�����������ȼ�
#define APP_START_TASK_PRIO        (4)
#define APP_LED1_TASK_PRIO         (5)
#define APP_LED0_TASK_PRIO         (7)
#define App_KEY_SCAN_PRIO		   (8)



//���������ջ
extern OS_STK  APP_START_STK[TASK_STK_SIZE];
extern OS_STK  APP_LED1_STK[TASK_STK_SIZE];
extern OS_STK  APP_LED0_STK[TASK_STK_SIZE];
extern OS_STK  KEY_TASK_STK[KEY_STK_SIZE];



void AppLED1Task(void *pdata);
void AppLED0Task(void *pdata);
void TaskStart(void *pdata);
void AppStartTast(void *pdata);   //�������������
void allInit(void);           //��ʼ����������
void keyScan(void * pdata);   //����ɨ��









#endif










