#include "app.h"



//系统固定系数

#define LongPressTime   50 //按键触发长按的时间
#define LongPressSpeed   2 //按键触发长按后执行速度


//声明任务堆栈
OS_STK  APP_START_STK[TASK_STK_SIZE];
OS_STK  APP_LED1_STK[TASK_STK_SIZE];
OS_STK  APP_LED0_STK[TASK_STK_SIZE];
OS_STK  KEY_TASK_STK[KEY_STK_SIZE];   //按键扫描
OS_STK OLED_TASK_STK[OLED_STK_SIZE];  //UI显示


//信号量 邮箱 
OS_EVENT *msg_key;				  //按键邮箱块指针




//LED小灯任务
void AppLED1Task(void *pdata)
{
    pdata = pdata; //防止编译器出错 无实际意义
	u8 key = 0;
	u8 err;//邮箱信息
	while(1)
	{
		
		switch(key)
		{
			
			
		}	
		OSTimeDlyHMSM(0, 0, 0, 100);
	}
}

void AppLED0Task(void *pdata)
{
    pdata = pdata; //防止编译器出错 无实际意义
	u16 a = 0;
	while(1)
	{
		a++;
		if(a>9999)
			a =0;
		OSTimeDlyHMSM(0, 0, 0, 300);
	}
}


/***************

按键扫描任务

***********/
void keyScan(void * pdata)
{
	
	msg_key = OSMboxCreate((void*)0);	//创建空消息邮箱
    pdata = pdata;
    u16 T =0;
    u16 Ti=0;
    u8 key;
    u8 keysave;//上次按键状态保存
	while(1)
	{
		if(key_check(KEY_UP) == 0)
		{ key =1;}   //上键
		else if(key_check(KEY_DOWN) == 0)
		{ key = 2; }  //下键
		else if(key_check(KEY_LEFT) == 0)
		{ key = 3;}  //左键
		else if(key_check(KEY_RIGHT) == 0)
		{ key = 4; }  //右键
		else key = 0;
		
		switch(keysave)
		{
			case 1:  //上
				if(key != keysave)
				{
					OSMboxPost(msg_key,(void *)keysave);
					T = 0;
					Ti = 0;
				}
				else
				{
					if(T > LongPressTime) // 触发长按
					{
						T= LongPressTime;
						if(Ti> LongPressSpeed) //长按执行速度
						{
							Ti = 0;
							OSMboxPost(msg_key,(void *)keysave);
						}
						Ti++;
					}
					T++;
				}
				break;
				
			case 2: //下
				if(key != keysave)
				{
					OSMboxPost(msg_key,(void *)keysave);
					T = 0;
					Ti = 0;
				}
				else
				{
					if(T > LongPressTime) // 触发长按
					{
						T= LongPressTime;
						if(Ti> LongPressSpeed) //长按执行速度
						{
							Ti = 0;
							OSMboxPost(msg_key,(void *)keysave);
						}
						Ti++;
					}
					T++;
				}
			
				break;
				
			case 3: //左
				if(key != keysave)
				{
					OSMboxPost(msg_key,(void *)keysave);
					T = 0;
					Ti = 0;
				}
				else
				{
					if(T > LongPressTime) // 触发长按
					{
						T= LongPressTime;
						if(Ti> LongPressSpeed) //长按执行速度
						{
							Ti = 0;
							OSMboxPost(msg_key,(void *)keysave);
						}
						Ti++;
					}
					T++;
				}
				break;
				
			case 4: //右
				if(key != keysave)
				{
					OSMboxPost(msg_key,(void *)keysave);
					T = 0;
					Ti = 0;
				}
				else
				{
					if(T > LongPressTime) // 触发长按
					{
						T= LongPressTime;
						if(Ti> LongPressSpeed) //长按执行速度
						{
							Ti = 0;
							OSMboxPost(msg_key,(void *)keysave);
						}
						Ti++;
					}
					T++;
				}
				break;
		}
		keysave = key; 
		OSTimeDlyHMSM(0, 0, 0, 10);
	}	

}

/********************************************

显示任务

*********************************************/

void Task_OLED(void *pdata)
{
	pdata = pdata;
	u8 ID = 0;
	
	
	while(1)
	{
		ID = FunctionPointer[ID]();
		OSTimeDlyHMSM(0, 0, 0, 10);
	
	}


}


/********************************************


任务创建，创建其他任务


********************************************/
void AppStartTast(void *pdata)
{
	
#if OS_CRITICAL_METHOD == 3
	OS_CPU_SR cpu_sr;
#endif
	pdata = pdata;
	
	
//////////////////////////////////////////////////////////////////////
/////////////////把要创建的任务放在这里////////////////////////////////
	

    OSTaskCreate(AppLED1Task,(void *)0,
                &APP_LED1_STK[TASK_STK_SIZE - 1],
                APP_LED1_TASK_PRIO); //建立LED1 任务
	
    OSTaskCreate(AppLED0Task,(void *)0,
                &APP_LED0_STK[TASK_STK_SIZE - 1],
                APP_LED0_TASK_PRIO); //建立LED0 任务
	
	 OSTaskCreate(keyScan,(void *)0,
                &KEY_TASK_STK[TASK_STK_SIZE - 1],
                App_KEY_SCAN_PRIO); //建立按键 任务
	  OSTaskCreate(Task_OLED,(void *)0,
                &OLED_TASK_STK[OLED_STK_SIZE -1],
                OLED_TASK_PRIO); //建立按键 任务
	 
	
	
	
/////////////////把要创建的任务放在这里/////////////////////////////////		
//////////////////////////////////////////////////////////////////////

	
	 
	OS_ENTER_CRITICAL();   //进入临界区
		//开启时钟节拍中断
	SYSTICK_Init(1000*1000/OS_TICKS_PER_SEC);
    SYSTICK_ITConfig(true);
    SYSTICK_Cmd(true);
	
	OS_EXIT_CRITICAL();   //退出临界区
	
	
	for(;;)
		{
				OSTaskSuspend(APP_START_TASK_PRIO);	//挂起起始任务.
		}
	

}



void allInit(void)
{

   DelayInit();    //延时初始化
   OLED_Init();    //OLED初始化
   KEY_Init();     //按键初始化
   


}











