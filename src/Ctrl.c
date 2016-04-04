#include "includes.h"
#include "FlashUI.h"
#include "app.h"
#include "Ctrl.h"



extern u32 now_10ms;

extern PID speedPid;
extern PID stree_pid;

//上一次的转角方向

int last_result = 0;

/***
2016-3-11
新PID测试函数

***/
void speedPID(u32 nowValue)
{
	
//	speedPid.error[0] = 0;
//	speedPid.error[1] = 0;
//	speedPid.error[2] = 0;
//    speedPid.error[0] = speedPid.goal - nowValue;   //求误差
//	speedPid.result   = speedPid.p * speedPid.error[0] + speedPid.i * speedPid.error[1]+ speedPid.d * speedPid.error[2];
//	speedPid.error[2] = speedPid.error[1];
//	speedPid.error[1] = speedPid.error[0];
	
//	 float  SpeedKP = speedPid.p;
//     float  SpeedKI = speedPid.i;
//     float  SpeedKD = speedPid.d;
//     speedPid.error[2]= speedPid.goal -  nowValue;
//     speedPid.result = (int)(SpeedKP * (speedPid.error[2]-speedPid.error[1]));
//     speedPid.result += SpeedKI * speedPid.error[2];
//     speedPid.result += SpeedKD * (speedPid.error[2] - 2 * speedPid.error[1] + speedPid.error[2]);
//     speedPid.error[0] = speedPid.error[1];
//     speedPid.error[1] = speedPid.error[2];
	

   float  SpeedKP = speedPid.p ;
   float  SpeedKI = speedPid.i ;
   float  SpeedKD = speedPid.d ;

   static int16_t LastSpeedCut0,LastSpeedCut1,LastSpeedCut2 ,SpeedLastPWMK ;
   int16_t  SpeedPWMKP ,SpeedPWMKI ,SpeedPWMKD,SpeedPWMK ;
   int16_t  SpeedPWMOUT;
   int16_t  SpeedDifference0=0;
   int16_t  speedDEARE1,speedDEARE2,DSpeed ;

   LastSpeedCut0 =  nowValue ;
   DSpeed =(int16_t) speedPid.goal ;

   SpeedDifference0 = DSpeed - LastSpeedCut0  ;  //当前误差
   speedDEARE1 = LastSpeedCut0 - LastSpeedCut1;  // 误差的误差 
   speedDEARE2 = LastSpeedCut2+LastSpeedCut0-2*LastSpeedCut1;  //当前的误差 +上上次的误差 - 2倍的上次误差
   LastSpeedCut2  = LastSpeedCut1;
   LastSpeedCut1  = LastSpeedCut0;


          SpeedPWMKP = SpeedKP*SpeedDifference0;   
          if(SpeedPWMKP>KPPLUSMAX){
           SpeedPWMKP = KPPLUSMAX;
          }else if (SpeedPWMKP <KPNEGATIVEMAX){
          SpeedPWMKP = KPNEGATIVEMAX;
          }

 

          SpeedPWMKI = SpeedKI* speedDEARE1;
          if(SpeedPWMKI > KIPLUSMAX){
          SpeedPWMKI = KIPLUSMAX;
          } else if(SpeedPWMKI < KINEGATIVEMAX){
          SpeedPWMKI = KINEGATIVEMAX;
          }

          SpeedPWMKD = SpeedKD* speedDEARE2;
          if(SpeedPWMKD > KDPLUSMAX){
             SpeedPWMKD = KDPLUSMAX;
          } else if(SpeedPWMKD < KDNEGATIVEMAX){
            SpeedPWMKD = KDNEGATIVEMAX;
          }

          SpeedPWMK = SpeedPWMKD-SpeedPWMKI+SpeedPWMKP ;
          if(SpeedPWMK > KWPLUSMAX){
          SpeedPWMK = KWPLUSMAX;
          }else if(SpeedPWMK < KWNEGATIVEMAX){
          SpeedPWMK = KWNEGATIVEMAX;

          }



         SpeedPWMOUT = SpeedLastPWMK + SpeedPWMK ;
         if(SpeedPWMOUT < 0 ){
            SpeedPWMOUT = 0 ;
         } else if(SpeedPWMOUT > KOUPLUSMAX){
           SpeedPWMOUT = KOUPLUSMAX ;

         }
         SpeedLastPWMK = SpeedPWMOUT ;
   
         speedPid.result = SpeedPWMOUT;	
	
										
}

//速度控制
void speedCtrl(void)
{
	u32 duty = 0;
	speedPID(ENCODE);
	duty += speedPid.result;
	
	if(duty >5000)
		duty = 5000;
	
	FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH3, duty);
	FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH2,0);
	
	

}

//舵机PID
void streePID(int nowValue)
{
	

    float stree_p,stree_i,stree_d;
	
    int pid_count = 0,pid_errsum = 0;
	
	int CZ;
	
	//拟合参数
	
		float p1 =  0.1614 ;
		float p2 =  -8.265;
		float x= 0;
		 
	
    stree_p = stree_pid.p;
	
    stree_i = stree_pid.i;
	
    stree_d = stree_pid.d;
	
	
	
	if(DOWN_LEFT<2650||DOWN_RIGHT<2810)
	{
		if(last_result == 1)	
		{
			stree_pid.result = DUTY_MAX;
		}
		if(last_result ==2)
		{
		stree_pid.result = DUTY_MIN;
		}
		
		
		
	}else
	

	{
		
		x = p1*nowValue+p2;
		stree_pid.error[1] = x;
	
		//stree_pid.error[1] = nowValue - 55;
		
		pid_errsum +=  stree_pid.error[1] * stree_i;
		
		stree_pid.result =(int) (stree_p * stree_pid.error[1]);
		
		stree_pid.result += pid_errsum;
		
		stree_pid.result += stree_d * (stree_pid.error[1] - stree_pid.error[0]);
		
		pid_count ++;
		
		stree_pid.error[0] = stree_pid.error[1];
		
		if(stree_pid.result>0)
		{
		  last_result = 1;
		}
		if(stree_pid.result<0)
		{
		  last_result = 2;
		}
		
	   if(stree_pid.result > DUTY_MAX)
	   {
		  
		  stree_pid.result = DUTY_MAX;
		 
		  
	   }
	   if(stree_pid.result < DUTY_MIN)
	   {
		  
		  stree_pid.result = DUTY_MIN;
		
	   }
	   
	  
   }
	
    
}


void  ctrls(void)
{

	int C = LEFT - RIGHT;
	
	streePID(C);
	
	FTM_PWM_ChangeDuty(HW_FTM1, HW_FTM_CH1, 1460+stree_pid.result);


}


















