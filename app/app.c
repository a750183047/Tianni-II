#include "app.h"


static const uint32_t DMA_PORT_TriggerSourceTable[] = 
{
    PORTA_DMAREQ,
    PORTB_DMAREQ,
    PORTC_DMAREQ,
    PORTD_DMAREQ,
    PORTE_DMAREQ,
};


//系统固定系数

#define LongPressTime   20 //按键触发长按的时间
#define LongPressSpeed   2 //按键触发长按后执行速度


//声明任务堆栈
OS_STK  APP_START_STK[TASK_STK_SIZE];
OS_STK  APP_LED1_STK[TASK_STK_SIZE];
OS_STK  APP_LED0_STK[TASK_STK_SIZE];
OS_STK  KEY_TASK_STK[KEY_STK_SIZE];   //按键扫描
OS_STK  OLED_TASK_STK[OLED_STK_SIZE];  //UI显示
OS_STK  DMA_TASK_STK[DMA_STK_SIZE];  //DMA
OS_STK  SPEED_TASK_STK[SPEED_STK_SIZE];  //速度控制
OS_STK  CTRL_TASK_STK[CTRL_STK_SIZE];    //路径识别


//信号量 邮箱 
OS_EVENT *msg_key;				  //按键邮箱块指针


//全局变量 
int LEFT = 0;   //左线圈的值
int RIGHT = 0;  //右线圈的值
int ENCODE = 0; //编码器的值



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
		{ key = 4;}  //左键
		else if(key_check(KEY_RIGHT) == 0)
		{ key = 3; }  //右键
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

/*********************************************


DMA检测

*********************************************/
void DMA_COUNT_TAST(void *pdata)
{
	pdata =pdata;
	
	while(1)
	{
		LEFT = DMA_CITER_ELINKNO_CITER_MASK - DMA_GetMajorLoopCount(HW_DMA_CH2);
		RIGHT = DMA_CITER_ELINKNO_CITER_MASK - DMA_GetMajorLoopCount(HW_DMA_CH0);
		
		
	
		DMA_CancelTransfer();
		DMA_SetMajorLoopCounter(HW_DMA_CH0, DMA_CITER_ELINKNO_CITER_MASK);
		DMA_SetMajorLoopCounter(HW_DMA_CH2, DMA_CITER_ELINKNO_CITER_MASK);
	
		
		/* 开始下一次传输 */
		DMA_EnableRequest(HW_DMA_CH0);
		DMA_EnableRequest(HW_DMA_CH2);
		
		
		OSTimeDlyHMSM(0, 0, 0, 10);
		
		
	}
		

}


/********************************************

   速度控制任务

********************************************/

void SPEED_TASK(void *pdata)
{
	pdata = pdata;
	while(1)
	{
		ENCODE = DMA_CITER_ELINKNO_CITER_MASK - DMA_GetMajorLoopCount(HW_DMA_CH1);
		
	
		if(FLAG_RUN)
		{
			speedCtrl();
		}
		
		DMA_CancelTransfer();
		DMA_SetMajorLoopCounter(HW_DMA_CH1, DMA_CITER_ELINKNO_CITER_MASK);
		DMA_EnableRequest(HW_DMA_CH1);
		
	 OSTimeDlyHMSM(0, 0, 0, 5);
	}

}

/********************************************

  路径识别

********************************************/
void CTRL_TASK(void * pdata)
{

	pdata = pdata;
	while(1)
	{
		if(FLAG_RUN)
		{
			ctrls();	
		
		}
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
	


	
	 OSTaskCreate(keyScan,(void *)0,
                &KEY_TASK_STK[TASK_STK_SIZE - 1],
                App_KEY_SCAN_PRIO); //建立按键 任务
	  OSTaskCreate(Task_OLED,(void *)0,
                &OLED_TASK_STK[OLED_STK_SIZE -1],
                OLED_TASK_PRIO); //建立  oled 任务
	  
	  OSTaskCreate(DMA_COUNT_TAST,(void *)0,
                &DMA_TASK_STK[DMA_STK_SIZE -1],
                DMA_TASK_PRIO); //建  dma 任务
	  
	  OSTaskCreate(SPEED_TASK,(void *)0,
                &SPEED_TASK_STK[SPEED_STK_SIZE -1],
                SPEED_TASK_PRIO); //建立  speed 任务
	 
	  OSTaskCreate(CTRL_TASK,(void *)0,
                &CTRL_TASK_STK[CTRL_STK_SIZE -1],
                CTRL_TASK_PRIO); //建立  speed 任务
	
	
	
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


/**
 * @brief  DMA 用作脉冲计数初始化     
 * @param  dmaChl :DMA通道号
 * @param  instance :端口号 比如HW_GPIOA
 * @param  pinIndex :引脚号
 * @retval None
 */
 void DMA_PulseCountInit(uint32_t dmaChl, uint32_t instance, uint32_t pinIndex)
{
    /* 开启2路引脚 配置为DMA触发 */
    GPIO_QuickInit(instance, pinIndex, kGPIO_Mode_IFT);
    /* 配置为DMA上升沿触发 */
    GPIO_ITDMAConfig(instance, pinIndex, kGPIO_DMA_RisingEdge, true);
    /* 配置DMA */
    static uint8_t dummy1, dummy2;
    DMA_InitTypeDef DMA_InitStruct1 = {0};  
    DMA_InitStruct1.chl = dmaChl;  
    DMA_InitStruct1.chlTriggerSource = DMA_PORT_TriggerSourceTable[instance];
    DMA_InitStruct1.triggerSourceMode = kDMA_TriggerSource_Normal; 
    DMA_InitStruct1.minorLoopByteCnt = 1;
    DMA_InitStruct1.majorLoopCnt = DMA_CITER_ELINKNO_CITER_MASK; /* 最大值 */
    
    DMA_InitStruct1.sAddr = (uint32_t)&dummy1;
    DMA_InitStruct1.sLastAddrAdj = 0; 
    DMA_InitStruct1.sAddrOffset = 0;
    DMA_InitStruct1.sDataWidth = kDMA_DataWidthBit_8;
    DMA_InitStruct1.sMod = kDMA_ModuloDisable;
    
    DMA_InitStruct1.dAddr = (uint32_t)&dummy2; 
    DMA_InitStruct1.dLastAddrAdj = 0;
    DMA_InitStruct1.dAddrOffset = 0; 
    DMA_InitStruct1.dDataWidth = kDMA_DataWidthBit_8;
    DMA_InitStruct1.dMod = kDMA_ModuloDisable;
    DMA_Init(&DMA_InitStruct1);
    /* 启动传输 */
    DMA_EnableRequest(dmaChl);
}



//DMA初始化
void dmaInit(void)
{

	DMA_PulseCountInit(HW_DMA_CH0, HW_GPIOB, 0);
	DMA_PulseCountInit(HW_DMA_CH2, HW_GPIOC, 6);
	DMA_PulseCountInit(HW_DMA_CH1, HW_GPIOA, 6);
	DMA_PulseCountInit(HW_DMA_CH3, HW_GPIOD, 1);
	DMA_PulseCountInit(HW_DMA_CH4, HW_GPIOE, 1);


}


void speedInit()
{
	FTM_PWM_QuickInit(FTM0_CH3_PC04,kPWM_EdgeAligned,10000);
	FTM_PWM_QuickInit(FTM0_CH2_PC03,kPWM_EdgeAligned,10000);
    FTM_PWM_QuickInit(FTM1_CH1_PA09,kPWM_EdgeAligned,100);
	FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH3, 0);
	FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH2, 0);
	FTM_PWM_ChangeDuty(HW_FTM1, HW_FTM_CH1, 1460);

}

void allInit(void)
{

   DelayInit();    //延时初始化
   OLED_Init();    //OLED初始化
   KEY_Init();     //按键初始化
   dmaInit();      //DMA初始化
   speedInit();    //PWM初始化
   flash_init();   //Flash初始化	
   Flash_Read();   //读取Flash中储存的值
	
	


}











