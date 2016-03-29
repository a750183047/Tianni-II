/*
 * 实验名称：uc/os-II 移植实验
 * 实验平台：渡鸦开发板
 * 板载芯片：MK60DN512ZVLQ10
 * 实验效果：
 *  				1.在串口上输出交替出现的LED1任务和LED2任务
 *					2.显示当前uc/os-II的版本
 * 					3.每秒显示CPU的使用率(%),大家可以在AppLED1Task中增加printf的个数来观察CPU占用率的情况
 * 修改记录：
 *					1.2015.10.31 FreeXc 将时钟节拍中断移至OSStart()函数之后，增加了版本显示以及CPU占用率的显示
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
