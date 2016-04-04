#include "common.h"
#include "includes.h"
#include "UI.h"
#include "app.h"
#include "ftm.h"
#include "FlashUI.h"
#include "Ctrl.h"


u16 adc_max[8]={0,0,0,0,0,0,0,0};
u16 adc_min[8]={255,255,255,255,255,255,255,255};

extern PID speedPid;
u8 FLAG_RUN = 0;
static u8 Arrow = 3;//箭头所在位置
// 函数指针设计//






u8 (*FunctionPointer[11])(void)={ 
								  Menu_UI,//主界面(地址为0)
								  Run_UI,//起跑界面(地址为1)
								  State1_UI,//车体状态观察界1(地址为2)
								  Set_UI,//参数设置界面(地址为3)
								  Record_UI,//方案选择界面(地址为4)
								  Read_UI,//方案选择界面(地址为5)
								};


//菜单首页

u8 Menu_UI()
{

  
    u8 S0[]="    Menu   Bett:";
	u8 S1[]="---------------------";
	u8 S3[]="      Run";
	u8 S4[]="      Car State";
	u8 S5[]="      Set Variable";
	u8 S6[]="      Plan Record";
	u8 S7[]="      Read";
	u8 AR[]="->";//显示箭头
	u8 AC[]="  ";//清除箭头
	
	u8 key = 0;
    u8 err;

    OLED_CLS();//清屏
	OLED_P6x8Str(0,0,S0);
	OLED_P6x8Str(0,1,S1);
	OLED_P6x8Str(0,3,S3);
	OLED_P6x8Str(0,4,S4);
	OLED_P6x8Str(0,5,S5);
	OLED_P6x8Str(0,6,S6);
	OLED_P6x8Str(0,7,S7);
    OLED_P6x8Str(23,Arrow,AR);

    LCD_Write_Number(95,0,0);
	u32 Dev;
    while(1)
    {
				
		
   
		switch(key)
		{
			case 1:
				OLED_P6x8Str(23,Arrow,AC);
							Arrow--;
							if(Arrow < 3) Arrow=7;
							OLED_P6x8Str(23,Arrow,AR);
				
				break;
					case 2:
				OLED_P6x8Str(23,Arrow,AC);
							Arrow++;
							if(Arrow > 7) Arrow=3;
							OLED_P6x8Str(23,Arrow,AR);
			   
				break;
			case 3:
				switch(Arrow)
					{
						case 3: return 1;// 进入起跑页面
						case 4: return 2;// 进入车体状态观察页面
						case 5: return 3;// 进入参数设置页面
						case 6: return 4;// 进入方案选择页面
						case 7: return 5;// 进入方案选择页面
						
					}
					
					break;
			case 4:
			   
					return Menu_UI_ID;
					break;
						default:
					break;
		}
		key=(u8)OSMboxPend(msg_key,200,&err);//按键邮箱
    }
}


u8 Run_UI()
{
    
    u8 S0[]="Launching  Bett:";
	u8 S1[]="---------------------";
	u8 SR[]="RUNING";
	u8 SS[]=" STOP ";
    char  ch;
	u8 key = 0;
    u8 err;
	
    OLED_CLS();//清屏
	OLED_P6x8Str(0,0,S0);
	OLED_P6x8Str(0,1,S1);
    OLED_P6x8Str(0,2,SS);
    LCD_Write_Number(95,0, 0);
	LCD_Write_Number(95,5, last_result);
	
	
	 while(1)
    {


		 if(key ==3)
		 {
		   
			OLED_P6x8Str(0,2,SR);
			FLAG_RUN = 1;      // 通过标志位来控制中断函数的执行与否

		 }

		 if(key == 4)
		 {
					
				FLAG_RUN = 0;  //标志位清零
				speedClear();  //回到初始状态
				return Menu_UI_ID;//返回主界面

		 }
		 
		 key=(u8)OSMboxPend(msg_key,200,&err);//按键邮箱
		
    }

	
	

}

u8 State1_UI()
{
   
    u8 S0[]="Car State  Bett:";
    u8 S1[]="---------------------";
	u8 S2[]="MID                  ";
	u8 S3[]="F_L_C      F_R_C     ";
	u8 S4[]="F_L_V      F_R_V     ";
	u8 S5[]="S_L        S_R       ";
	u8 key = 0;
    u8 err;
    OLED_CLS();//清屏
    OLED_P6x8Str(0,0,S0);
    OLED_P6x8Str(0,1,S1);
    OLED_P6x8Str(0,2,S2);
    OLED_P6x8Str(0,3,S3);
    OLED_P6x8Str(0,4,S4);
    OLED_P6x8Str(0,5,S5);
    LCD_Write_Number(95,0, 0);
	
	return 0;

}

u8 Record_UI()
{
    u8 S0[]  =  "         Plan:";
    u8 S1[]  =  "---------------------";
	u8 S2[]  =  "    Plan_1 = ";
    u8 S3[]  =  "    Plan_2 = ";
    u8 S4[]  =  "    Plan_3 = ";
    u8 S5[]  =  "    Plan_4 = ";
    u8 S6[]  =  "    Plan_5 = ";
    u8 S7[]  =  "    Plan_6 = ";

    OLED_CLS();
    OLED_P6x8Str(0,0,S0);
    OLED_P6x8Str(0,1,S1);
    OLED_P6x8Str(0,2,S2);
    OLED_P6x8Str(0,3,S3);
    OLED_P6x8Str(0,4,S4);
    OLED_P6x8Str(0,5,S5);
    OLED_P6x8Str(0,6,S6);
    OLED_P6x8Str(0,7,S7);


	return 0;
		
	}
//#define SetOptionsNum 14 //设置项滚轮大小
u8	Read_UI()
{
    u8 S0[]  =  "Reading:";
	u8 S1[]  =  "---------------------";
	u8 S2[]  =  "    Left = ";
    u8 S3[]  =  "    Right = ";
	u8 S4[]  =  "    Encoder = ";
	u8 S5[]  =  "    left_cha = ";
	u8 S6[]  =  "    right_cha = ";
	u8 S7[]  =  "    DOWN_LEFT = ";
	
	u8 key = 0;
    u8 err;


	OLED_CLS();//清屏
    OLED_P6x8Str(0,0,S0);
    OLED_P6x8Str(0,1,S1);
    OLED_P6x8Str(0,2,S2);
    OLED_P6x8Str(0,3,S3);
    OLED_P6x8Str(0,4,S4);
    OLED_P6x8Str(0,5,S5);
	OLED_P6x8Str(0,6,S6);
	OLED_P6x8Str(0,7,S7);
    LCD_Write_Number(95,0, 0);
                                   
	while(1)
	{
			
		  
			
		LCD_Write_Number(95,2, LEFT);
		LCD_Write_Number(95,3, RIGHT);
		LCD_Write_Number(95,4, ENCODE);
		LCD_Write_Number(95,5, LEFT-DOWN_LEFT-188+61);
		LCD_Write_Number(95,6, RIGHT-DOWN_LEFT-134+61);
		LCD_Write_Number(95,7, DOWN_LEFT);
;
		
			
		if(key == 4)
		{

			OLED_CLS();//清屏
					
			return Menu_UI_ID;
					
		}
		key=(u8)OSMboxPend(msg_key,5,&err);//按键邮箱
		
	}
		
}
		
	
#define SetOptionsNum 14 //设置项滚轮大小
u8 Set_UI()
{
   

    u8 S0[]  =  "Set Variable Bett:";
	u8 S1[]  =  "---------------------";
	u8 SS[SetOptionsNum][19]={
		"      Speed_P:    ",
		"      Spedd_I:    ",
		"      Spedd_D:    ",
		"      Turn__P:    ",
        "      Turn__I:    ",
		"      Turn__D:    ",
		"      _Speed_:    ",
        "      vim_p1_:    ",
		"      vim_p2_:    ",
		"      vim_p3_:    ",
		"      vim_p4_:    ",
		"      vim_p5_:    ",
		"      missline    ",
		"      missline_m  ",
                                    };

    static u8 SetArrow = 2;//箭头标记位(2~6)
	static u8 Page = 0;//页面标记位(0~6)
	static u8 Item = 1;//项目标记位(1~SetOptionsNum)

    u8 AR[]="->";//显示箭头
	u8 AM[]="- ";//选中模式
	u8 AC[]="  ";//清除箭头
    u8 SaveSetArrow = 2;
	u16 ArrowState = 0;//箭头状态标记0:正常选择项 1:数值修改
    u8 text[5];
    u8 i;

    u8 key = 0;
    u8 err;
									
    OLED_CLS();
	OLED_P6x8Str(0,0,S0);
	OLED_P6x8Str(0,1,S1);
    LCD_Write_Number(95,0, 0);
    while(1)
	{

		
		switch(key)
		{
			case 0:break;

			case 1://上键

                
				if(ArrowState== 0)
				{
					SetArrow--;
					Item--;
					if(Item < 1) Item = SetOptionsNum;
					if(SetArrow<2)
					{
						if(Page == 0)
						{
							Page = 8;
							SetArrow = 7;
						}
						else
						{
							SetArrow = 2;
                        	Page--;
						}
					}
				}
				break;

			case 2://下键

              
				if(ArrowState== 0)
				{
					SetArrow++;
					Item++;
					if(Item > SetOptionsNum) Item = 1;
					if(SetArrow>7)
					{
						if(Page == 8)
						{
							Page = 0;
							SetArrow = 2;
						}
						else
						{
							SetArrow = 7;
                       	 	Page++;
						}
					}
				}
				break;

              case 3://确认
               
				if(ArrowState == 0) ArrowState = 1;
				else ArrowState = 0;
				break;

              case 4://退出

				//填写保存到flash的代码
                Falsh_Reserve();
				//填写保存到flash的代码

				if(ArrowState == 1) ArrowState = 0;//箭头状态修改
				else
				{
					return Menu_UI_ID;
				}
				break;
        }
         //*****数值修改
		if(ArrowState)
		{

          
			switch(Item)
			{
				case 1:
					if(key == 1) speedPid.p += 0.1;
					if(key == 2) speedPid.p -= 0.1;
					if(speedPid.p > 99.9) speedPid.p = 0.0;
                    
					break;

				case 2:
					if(key == 1) speedPid.i += 0.1;
					if(key == 2) speedPid.i -= 0.1;
					if(speedPid.i > 99.9) speedPid.i = 0.0;
                 
					break;

                case 3:
					if(key == 1) speedPid.d += 0.1;
					if(key == 2) speedPid.d -= 0.1;
					if(speedPid.d > 99.9) speedPid.d = 0.0;
                  
					break;

                case 4:
					if(key == 1) stree_pid.p += 0.1;
					if(key == 2) stree_pid.p -= 0.1;
					if(stree_pid.p > 99.9) stree_pid.p = 0.0;
                  
					break;

                case 5:
					if(key == 1) stree_pid.i += 0.1;
					if(key == 2) stree_pid.i -= 0.1;
					if(stree_pid.i > 99.9) stree_pid.i = 0.0;
                 
					break;

                case 6:
					if(key == 1) stree_pid.d += 0.1;
					if(key == 2) stree_pid.d -= 0.1;
					if(stree_pid.d > 99.9) stree_pid.d = 0.0;
                  
					break;

                case 7:
					if(key == 1) speedPid.goal +=1;
					if(key == 2) speedPid.goal -= 1;
					if(speedPid.goal> 999) speedPid.goal = 0;
                  
					break;

                 case 8:
					if(key == 1)
                      stree_vim_pid.Kp_1 +=0.1;
					if(key == 2)
                      stree_vim_pid.Kp_1 -= 0.1;
					if(stree_vim_pid.Kp_1> 99.9) stree_vim_pid.Kp_1 = 0.0;
                  
					break;

                 case 9:
					if(key == 1)
                      stree_vim_pid.Kp_2 +=0.1;
					if(key == 2)
                      stree_vim_pid.Kp_2 -= 0.1;
					if(stree_vim_pid.Kp_2> 99.9) stree_vim_pid.Kp_2 = 0.0;
                   
					break;

                 case 10:
					if(key == 1)
                      stree_vim_pid.Kp_3 +=0.1;
					if(key == 2)
                      stree_vim_pid.Kp_3 -= 0.1;
					if(stree_vim_pid.Kp_3> 99.9) stree_vim_pid.Kp_3 = 0.0;
                 
					break;

                 case 11:
					if(key == 1)
                      stree_vim_pid.Kp_4 +=0.1;
					if(key == 2)
                      stree_vim_pid.Kp_4 -= 0.1;
					if(stree_vim_pid.Kp_4> 99.9) stree_vim_pid.Kp_4 = 0.0;
                  
					break;

                 case 12:
					if(key == 1)
                      stree_vim_pid.Kp_5 +=0.1;
					if(key == 2)
                      stree_vim_pid.Kp_5 -= 0.1;
					if(stree_vim_pid.Kp_5> 99.9) stree_vim_pid.Kp_5 = 0.0;
                  
					break;

                default:
					ArrowState = 0;//未设定的变量不给予进入状态
					break;
            }
        }
        //数值修改

        //数值嵌入
        sprintf((char *)text,"%4d",(int)(speedPid.p*10));
		AddNumString(SS[0],text);
		sprintf((char *)text,"%4d",(int)(speedPid.i*10));
		AddNumString(SS[1],text);
		sprintf((char *)text,"%4d",(int)(speedPid.d*10));
		AddNumString(SS[2],text);
		sprintf((char *)text,"%4d",(int)(stree_pid.p*10));
		AddNumString(SS[3],text);
		sprintf((char *)text,"%4d",(int)(stree_pid.i*10));
		AddNumString(SS[4],text);
		sprintf((char *)text,"%4d",(int)(stree_pid.d*10));
		AddNumString(SS[5],text);
		sprintf((char *)text,"%4d",(int)(speedPid.goal));
		AddNumString(SS[6],text);
        sprintf((char *)text,"%4d",(int)(stree_vim_pid.Kp_1*10));
		AddNumString(SS[7],text);
        sprintf((char *)text,"%4d",(int)(stree_vim_pid.Kp_2*10));
	 	AddNumString(SS[8],text);
        sprintf((char *)text,"%4d",(int)(stree_vim_pid.Kp_3*10));
		AddNumString(SS[9],text);
        sprintf((char *)text,"%4d",(int)(stree_vim_pid.Kp_4*10));
		AddNumString(SS[10],text);
        sprintf((char *)text,"%4d",(int)(stree_vim_pid.Kp_5*10));
		AddNumString(SS[11],text);
        //*****数值嵌入

		for(i=2;i<8;i++)
		{
			OLED_P6x8Str(0,i,SS[Page+i-2]);//打印显示
		}

		if(ArrowState == 0)//箭头为修改数值状态
		{
			OLED_P6x8Str(24,SaveSetArrow,AC);
			OLED_P6x8Str(24,SetArrow,AR);
			SaveSetArrow = SetArrow;
		}
		else//修改箭头为数值选择状态
		{
			OLED_P6x8Str(24,SaveSetArrow,AM);
		}
		
		key=(u8)OSMboxPend(msg_key,0,&err);//按键邮箱
    }
}



void AddNumString(u8 ss[],u8 n[])//数字加入显示字符串
{
	u8 i;
	for(i=0;i<4;i++)
	{
		ss[14+i] = n [i];
	}
	ss[18] = '\0';
}


/***********************************
舵机归中 电机停止 
***********************************/
void speedClear(void)
{

	FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH2,0);
	FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH3,0);
	FTM_PWM_ChangeDuty(HW_FTM1, HW_FTM_CH1,1460);

}

