#include "app.h"


//系统固定系数

#define LongPressTime   50 //按键触发长按的时间
#define LongPressSpeed   2 //按键触发长按后执行速度


//声明任务堆栈
OS_STK  APP_START_STK[TASK_STK_SIZE];
OS_STK  APP_LED1_STK[TASK_STK_SIZE];
OS_STK  APP_LED0_STK[TASK_STK_SIZE];
OS_STK  KEY_TASK_STK[KEY_STK_SIZE];   //按键扫描


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
			case 1:
			OLED_P6x8Str(0,0,"1");
			
			break;
			
			case 2:
				OLED_P6x8Str(0,0,"2");
			break;
			case 3:
			OLED_P6x8Str(0,0,"3");
			
			break;
			
			case 4:
				OLED_P6x8Str(0,0,"4");
			break;
			
		}	
		key = (u8)OSMboxPend(msg_key,200,&err);
		OSTimeDlyHMSM(0, 0, 0, 300);
	}
}

void AppLED0Task(void *pdata)
{
    pdata = pdata; //防止编译器出错 无实际意义
	u16 a = 0;
	while(1)
	{
		a++;
		LCD_Write_Number(1,2,a);
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
    pdata = pdata;
    u16 T =0;
    u16 Ti=0;
    u8 key;
    u8 keysave;//上次按键状态保存
	while(1)
	{
		if(KEY_U == 1)
		{ key =1;}   //上键
		else if(KEY_D == 1)
		{ key = 2; }  //下键
		else if(KEY_A == 1)
		{ key = 3;}  //左键
		else if(KEY_B == 1)
		{ key = 4; }  //右键
		else key = 0;
		
		switch(keysave)
		{
			case 1:  //上
				if(key != keysave)
				{
					OSMboxPost(msg_key,(u8 *)keysave);
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
		OSTimeDlyHMSM(0, 0, 0, 50);
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
                App_KEY_SCAN_PRIO); //建立LED0 任务
	
	
	
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











