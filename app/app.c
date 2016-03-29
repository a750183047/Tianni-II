#include "app.h"


//ϵͳ�̶�ϵ��

#define LongPressTime   50 //��������������ʱ��
#define LongPressSpeed   2 //��������������ִ���ٶ�


//���������ջ
OS_STK  APP_START_STK[TASK_STK_SIZE];
OS_STK  APP_LED1_STK[TASK_STK_SIZE];
OS_STK  APP_LED0_STK[TASK_STK_SIZE];
OS_STK  KEY_TASK_STK[KEY_STK_SIZE];   //����ɨ��


//�ź��� ���� 
OS_EVENT *msg_key;				  //���������ָ��




//LEDС������
void AppLED1Task(void *pdata)
{
    pdata = pdata; //��ֹ���������� ��ʵ������
	u8 key = 0;
	u8 err;//������Ϣ
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
    pdata = pdata; //��ֹ���������� ��ʵ������
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

����ɨ������

***********/
void keyScan(void * pdata)
{
    pdata = pdata;
    u16 T =0;
    u16 Ti=0;
    u8 key;
    u8 keysave;//�ϴΰ���״̬����
	while(1)
	{
		if(KEY_U == 1)
		{ key =1;}   //�ϼ�
		else if(KEY_D == 1)
		{ key = 2; }  //�¼�
		else if(KEY_A == 1)
		{ key = 3;}  //���
		else if(KEY_B == 1)
		{ key = 4; }  //�Ҽ�
		else key = 0;
		
		switch(keysave)
		{
			case 1:  //��
				if(key != keysave)
				{
					OSMboxPost(msg_key,(u8 *)keysave);
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
		OSTimeDlyHMSM(0, 0, 0, 50);
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
	

    OSTaskCreate(AppLED1Task,(void *)0,
                &APP_LED1_STK[TASK_STK_SIZE - 1],
                APP_LED1_TASK_PRIO); //����LED1 ����
	
    OSTaskCreate(AppLED0Task,(void *)0,
                &APP_LED0_STK[TASK_STK_SIZE - 1],
                APP_LED0_TASK_PRIO); //����LED0 ����
	
	 OSTaskCreate(keyScan,(void *)0,
                &KEY_TASK_STK[TASK_STK_SIZE - 1],
                App_KEY_SCAN_PRIO); //����LED0 ����
	
	
	
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



void allInit(void)
{

   DelayInit();    //��ʱ��ʼ��
   OLED_Init();    //OLED��ʼ��
   KEY_Init();     //������ʼ��
   


}











