#include "includes.h"

extern u32 now_10ms;

extern PID speedPid;
extern PID stree_pid;

/***
2016-3-11
新PID测试函数

***/
void speedPID(u32 nowValue)
{
	
	speedPid.error[0] = 0;
	speedPid.error[1] = 0;
	speedPid.error[2] = 0;
    speedPid.error[0] = speedPid.goal - nowValue;   //求误差
	speedPid.result = speedPid.p * speedPid.error[0] + speedPid.i * speedPid.error[1]+ speedPid.d * speedPid.error[2];
	speedPid.error[2] = speedPid.error[1];
	speedPid.error[1] = speedPid.error[0];
										
}

//速度控制
void speedCtrl()
{
	u32 duty = 0;
	speedPID(ChlValue[1]);
	duty = speedPid.result;
	if(duty>5000)
	{
		duty = 5000;
	}else
	{
		FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH3, duty);
		FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH2,0);
	}
	

}


//编码器读值
void readencode()
{

		ChlValue[1] = DMA_CITER_ELINKNO_CITER_MASK - DMA_GetMajorLoopCount(HW_DMA_CH1);
		speedCtrl();
		DMA_CancelTransfer();
		DMA_SetMajorLoopCounter(HW_DMA_CH1, DMA_CITER_ELINKNO_CITER_MASK);
		DMA_EnableRequest(HW_DMA_CH1);
	


}
//舵机PID
void streePID(int nowValue)
{

	stree_pid.error[0] = 0;
	stree_pid.error[1] = 0;
	stree_pid.error[2] = 0;
	stree_pid.error[3] = 0;
	
	stree_pid.error[0] = nowValue;
	stree_pid.error[1] += stree_pid.error[0];
	stree_pid.error[2] = stree_pid.error[0] - stree_pid.error[3];
	stree_pid.error[3] = stree_pid.error[0];
	
	
	stree_pid.result = stree_pid.p * stree_pid.error[0] 
						+ stree_pid.i * stree_pid.error[1]
						+ stree_pid.d * stree_pid.error[2];
	
}


void  ctrls(int r,int l)
{

	int dutyValue = 0;
	
	int yr,yl;
	
	int value;
	
	float p1 =   0.1399;
	float p2 =  -364.1;
	
	float p3 =  -0.8495;
	float p4 = 2370;


	yr =  p1*r + p2;
	
	yl = p1*l + p2;
	
	value = yl-yr ;
	
	if(value>0)
	streePID(yr);
	if(value<0)
	streePID(yl);
	
	dutyValue = stree_pid.result *17;
	
	if(dutyValue>170)
	{
		dutyValue = 170;
	}
	if(dutyValue<-170)
	{
		dutyValue = -170;
	}
	FTM_PWM_ChangeDuty(HW_FTM1, HW_FTM_CH1, 1460-dutyValue);


}