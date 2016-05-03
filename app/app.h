#ifndef _APP_H_
#define _APP_H_

#include "includes.h"
#include "systick.h"
#include "OLED.h"
#include "KEY.h"
#include "dma.h"
#include "UI.h"
#include "ftm.h"
#include "FlashUI.h"
#include "Ctrl.h"






//�����ջ��С
#define TASK_STK_SIZE              128
#define KEY_STK_SIZE 			   128   //����ɨ������
#define OLED_STK_SIZE    		   2048  //UI��ʾ
#define DMA_STK_SIZE			   512   //DMA
#define SPEED_STK_SIZE             512   //�ٶȿ���
#define CTRL_STK_SIZE              512   //·��ʶ��
//�����������ȼ�
#define APP_START_TASK_PRIO        11    //���񴴽�
#define App_KEY_SCAN_PRIO		   8     //����ɨ��
#define OLED_TASK_PRIO	           9     //Һ����ʾ����
#define DMA_TASK_PRIO			   6     // DMA
#define SPEED_TASK_PRIO            7     //�ٶȿ���
#define CTRL_TASK_PRIO             5     //·��ʶ��



//���������ջ
extern OS_STK  APP_START_STK[TASK_STK_SIZE];
extern OS_STK  APP_LED1_STK[TASK_STK_SIZE];
extern OS_STK  APP_LED0_STK[TASK_STK_SIZE];
extern OS_STK  KEY_TASK_STK[KEY_STK_SIZE];
extern OS_STK  OLED_TASK_STK[OLED_STK_SIZE];  //UI��ʾ
extern OS_STK  DMA_TASK_STK[DMA_STK_SIZE];  //DMA
extern OS_STK  SPEED_TASK_STK[SPEED_STK_SIZE]; //�ٶȿ���


//�������� 
extern OS_EVENT *msg_key;				  //���������ָ��


//ȫ�ֱ��� 
extern int LEFT ;   //����Ȧ��ֵ
extern int RIGHT;   //����Ȧ��ֵ
extern int ENCODE;  //��������ֵ
extern int DOWN_LEFT;
extern int DOWN_RIGHT;
extern int CHA;
extern int LMAX;   //����Ȧ�����С
extern int LMIN;   
extern int RMAX;   //����Ȧ
extern int RMIN;  
extern int DLMAX;  
extern int DLMIN;
extern int DRMAX;
extern int DRMIN;
extern int min[5];


void AppLED1Task(void *pdata);
void AppLED0Task(void *pdata);
void TaskStart(void *pdata);
void AppStartTast(void *pdata);   //�������������
void allInit(void);           //��ʼ����������
void keyScan(void * pdata);   //����ɨ��









#endif










