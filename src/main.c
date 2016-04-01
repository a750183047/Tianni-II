/*
如果工程出现编译错误 请在 KEIl安装路径下 找到 stdint.h 并将下列代码添加到其中


typedef 	unsigned 	char		u8;	 
typedef 	unsigned 	short int	u16;
typedef 	unsigned 	int	        u32;
typedef 	char					s8;	 
typedef 	short int				s16;
typedef 	long  int				s32;

 */

#include "gpio.h"
#include "common.h"
#include "uart.h"
//uCOS
#include "includes.h"
#include "app.h"







int main(void)
{
		
	allInit();
    OSInit();  //OS初始化
	
	//创建初始任务
	OSTaskCreate(AppStartTast,(void *)0,
                &APP_START_STK[TASK_STK_SIZE - 1],
                APP_START_TASK_PRIO); //create the first task

    /* 控制权交给操作系统,在执行OSStart()之后操作系统开始进行任务调度 */
    OSStart();
		/* 程序永远不会运行到这 */
}
