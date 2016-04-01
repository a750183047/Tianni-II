#include "app.h"


static const uint32_t DMA_PORT_TriggerSourceTable[] = 
{
    PORTA_DMAREQ,
    PORTB_DMAREQ,
    PORTC_DMAREQ,
    PORTD_DMAREQ,
    PORTE_DMAREQ,
};


//ϵͳ�̶�ϵ��

#define LongPressTime   20 //��������������ʱ��
#define LongPressSpeed   2 //��������������ִ���ٶ�


//���������ջ
OS_STK  APP_START_STK[TASK_STK_SIZE];
OS_STK  APP_LED1_STK[TASK_STK_SIZE];
OS_STK  APP_LED0_STK[TASK_STK_SIZE];
OS_STK  KEY_TASK_STK[KEY_STK_SIZE];   //����ɨ��
OS_STK  OLED_TASK_STK[OLED_STK_SIZE];  //UI��ʾ
OS_STK  DMA_TASK_STK[DMA_STK_SIZE];  //DMA
OS_STK  SPEED_TASK_STK[SPEED_STK_SIZE];  //�ٶȿ���
OS_STK  CTRL_TASK_STK[CTRL_STK_SIZE];    //·��ʶ��


//�ź��� ���� 
OS_EVENT *msg_key;				  //���������ָ��


//ȫ�ֱ��� 
int LEFT = 0;   //����Ȧ��ֵ
int RIGHT = 0;  //����Ȧ��ֵ
int ENCODE = 0; //��������ֵ



/***************

����ɨ������

***********/
void keyScan(void * pdata)
{
	
	msg_key = OSMboxCreate((void*)0);	//��������Ϣ����
    pdata = pdata;
    u16 T =0;
    u16 Ti=0;
    u8 key;
    u8 keysave;//�ϴΰ���״̬����
	while(1)
	{
		if(key_check(KEY_UP) == 0)
		{ key =1;}   //�ϼ�
		else if(key_check(KEY_DOWN) == 0)
		{ key = 2; }  //�¼�
		else if(key_check(KEY_LEFT) == 0)
		{ key = 4;}  //���
		else if(key_check(KEY_RIGHT) == 0)
		{ key = 3; }  //�Ҽ�
		else key = 0;
		
		switch(keysave)
		{
			case 1:  //��
				if(key != keysave)
				{
					OSMboxPost(msg_key,(void *)keysave);
					T = 0;
					Ti = 0;
				}
				else
				{
					if(T > LongPressTime) // ��������
					{
						T= LongPressTime;
						if(Ti> LongPressSpeed) //����ִ���ٶ�
						{
							Ti = 0;
							OSMboxPost(msg_key,(void *)keysave);
						}
						Ti++;
					}
					T++;
				}
				break;
				
			case 2: //��
				if(key != keysave)
				{
					OSMboxPost(msg_key,(void *)keysave);
					T = 0;
					Ti = 0;
				}
				else
				{
					if(T > LongPressTime) // ��������
					{
						T= LongPressTime;
						if(Ti> LongPressSpeed) //����ִ���ٶ�
						{
							Ti = 0;
							OSMboxPost(msg_key,(void *)keysave);
						}
						Ti++;
					}
					T++;
				}
			
				break;
				
			case 3: //��
				if(key != keysave)
				{
					OSMboxPost(msg_key,(void *)keysave);
					T = 0;
					Ti = 0;
				}
				else
				{
					if(T > LongPressTime) // ��������
					{
						T= LongPressTime;
						if(Ti> LongPressSpeed) //����ִ���ٶ�
						{
							Ti = 0;
							OSMboxPost(msg_key,(void *)keysave);
						}
						Ti++;
					}
					T++;
				}
				break;
				
			case 4: //��
				if(key != keysave)
				{
					OSMboxPost(msg_key,(void *)keysave);
					T = 0;
					Ti = 0;
				}
				else
				{
					if(T > LongPressTime) // ��������
					{
						T= LongPressTime;
						if(Ti> LongPressSpeed) //����ִ���ٶ�
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

��ʾ����

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


DMA���

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
	
		
		/* ��ʼ��һ�δ��� */
		DMA_EnableRequest(HW_DMA_CH0);
		DMA_EnableRequest(HW_DMA_CH2);
		
		
		OSTimeDlyHMSM(0, 0, 0, 10);
		
		
	}
		

}


/********************************************

   �ٶȿ�������

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

  ·��ʶ��

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


���񴴽���������������


********************************************/
void AppStartTast(void *pdata)
{
	
#if OS_CRITICAL_METHOD == 3
	OS_CPU_SR cpu_sr;
#endif
	pdata = pdata;
	
	
//////////////////////////////////////////////////////////////////////
/////////////////��Ҫ�����������������////////////////////////////////
	


	
	 OSTaskCreate(keyScan,(void *)0,
                &KEY_TASK_STK[TASK_STK_SIZE - 1],
                App_KEY_SCAN_PRIO); //�������� ����
	  OSTaskCreate(Task_OLED,(void *)0,
                &OLED_TASK_STK[OLED_STK_SIZE -1],
                OLED_TASK_PRIO); //����  oled ����
	  
	  OSTaskCreate(DMA_COUNT_TAST,(void *)0,
                &DMA_TASK_STK[DMA_STK_SIZE -1],
                DMA_TASK_PRIO); //��  dma ����
	  
	  OSTaskCreate(SPEED_TASK,(void *)0,
                &SPEED_TASK_STK[SPEED_STK_SIZE -1],
                SPEED_TASK_PRIO); //����  speed ����
	 
	  OSTaskCreate(CTRL_TASK,(void *)0,
                &CTRL_TASK_STK[CTRL_STK_SIZE -1],
                CTRL_TASK_PRIO); //����  speed ����
	
	
	
/////////////////��Ҫ�����������������/////////////////////////////////		
//////////////////////////////////////////////////////////////////////

	
	 
	OS_ENTER_CRITICAL();   //�����ٽ���
		//����ʱ�ӽ����ж�
	SYSTICK_Init(1000*1000/OS_TICKS_PER_SEC);
    SYSTICK_ITConfig(true);
    SYSTICK_Cmd(true);
	
	OS_EXIT_CRITICAL();   //�˳��ٽ���
	
	
	for(;;)
		{
				OSTaskSuspend(APP_START_TASK_PRIO);	//������ʼ����.
		}
	

}


/**
 * @brief  DMA �������������ʼ��     
 * @param  dmaChl :DMAͨ����
 * @param  instance :�˿ں� ����HW_GPIOA
 * @param  pinIndex :���ź�
 * @retval None
 */
 void DMA_PulseCountInit(uint32_t dmaChl, uint32_t instance, uint32_t pinIndex)
{
    /* ����2·���� ����ΪDMA���� */
    GPIO_QuickInit(instance, pinIndex, kGPIO_Mode_IFT);
    /* ����ΪDMA�����ش��� */
    GPIO_ITDMAConfig(instance, pinIndex, kGPIO_DMA_RisingEdge, true);
    /* ����DMA */
    static uint8_t dummy1, dummy2;
    DMA_InitTypeDef DMA_InitStruct1 = {0};  
    DMA_InitStruct1.chl = dmaChl;  
    DMA_InitStruct1.chlTriggerSource = DMA_PORT_TriggerSourceTable[instance];
    DMA_InitStruct1.triggerSourceMode = kDMA_TriggerSource_Normal; 
    DMA_InitStruct1.minorLoopByteCnt = 1;
    DMA_InitStruct1.majorLoopCnt = DMA_CITER_ELINKNO_CITER_MASK; /* ���ֵ */
    
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
    /* �������� */
    DMA_EnableRequest(dmaChl);
}



//DMA��ʼ��
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

   DelayInit();    //��ʱ��ʼ��
   OLED_Init();    //OLED��ʼ��
   KEY_Init();     //������ʼ��
   dmaInit();      //DMA��ʼ��
   speedInit();    //PWM��ʼ��
   flash_init();   //Flash��ʼ��	
   Flash_Read();   //��ȡFlash�д����ֵ
	
	


}











