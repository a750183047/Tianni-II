#include "common.h"
#include "includes.h"
#include "UI.h"


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

  KEY_ = 0;
  u8 S0[]="    Menu   Bett:";
	u8 S1[]="---------------------";
	u8 S3[]="      Run";
	u8 S4[]="      Car State";
	u8 S5[]="      Set Variable";
	u8 S6[]="      Plan Record";
	u8 S7[]="      Read";
	u8 AR[]="->";//显示箭头
	u8 AC[]="  ";//清除箭头

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
				
		
    KEY_Service();  //按键服务
    switch(KEY_)
    {
        case 1:
            OLED_P6x8Str(23,Arrow,AC);
						Arrow--;
						if(Arrow < 3) Arrow=7;
						OLED_P6x8Str(23,Arrow,AR);
            KEY_ = 0;
			break;
				case 2:
            OLED_P6x8Str(23,Arrow,AC);
						Arrow++;
						if(Arrow > 7) Arrow=3;
						OLED_P6x8Str(23,Arrow,AR);
             KEY_ = 0;
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
                 KEY_ = 0;
				break;
        case 4:
            KEY_ = 0;
				return Menu_UI_ID;
				break;
					default:
				break;
    }
    }
}


u8 Run_UI()
{
    KEY_ = 0;          //进入函数需要先清掉按键标志，使按键准确
  u8 S0[]="Launching  Bett:";
	u8 S1[]="---------------------";
	u8 SR[]="RUNING";
	u8 SS[]=" STOP ";
  char  ch;
  OLED_CLS();//清屏
	OLED_P6x8Str(0,0,S0);
	OLED_P6x8Str(0,1,S1);
  OLED_P6x8Str(0,2,SS);
  LCD_Write_Number(95,0, 0);
	
	
	 while(1)
    {


      KEY_Service();  //按键服务

     if(KEY_ ==3)
     {
        KEY_ = 0;
        OLED_P6x8Str(0,2,SR);
        FLAG_RUN = 1;      // 通过标志位来控制中断函数的执行与否

     }

     if(KEY_ == 4)
		{
                KEY_ = 0;
                FLAG_RUN = 0;         //标志位清零
				FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH2,0);
				FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH3,0);
				FTM_PWM_ChangeDuty(HW_FTM1, HW_FTM_CH1, 1460);
		
			
				return Menu_UI_ID;//返回主界面

		}
    }

	
	

}

u8 State1_UI()
{
    KEY_ = 0;          //进入函数需要先清掉按键标志，使按键准确
  	u8 S0[]="Car State  Bett:";
		u8 S1[]="---------------------";
		u8 S2[]="MID                  ";
		u8 S3[]="F_L_C      F_R_C     ";
		u8 S4[]="F_L_V      F_R_V     ";
		u8 S5[]="S_L        S_R       ";
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
    KEY_ = 0;      //进入函数需要先清掉按键标志，使按键准确


//    Plan_1 =  PTD1_IN;
//    Plan_2 =  PTD0_IN;
//    Plan_3 =  PTD3_IN;
//    Plan_4 =  PTD2_IN;
//    Plan_5 =  PTD5_IN;
//    Plan_6 =  PTD4_IN;

//    LCD_Write_Number(80,2, Plan_1);
//    LCD_Write_Number(80,3, Plan_2);
//    LCD_Write_Number(80,4, Plan_3);
//    LCD_Write_Number(80,5, Plan_4);
//    LCD_Write_Number(80,6, Plan_5);
//    LCD_Write_Number(80,7, Plan_6);

	return 0;
		
	}
//#define SetOptionsNum 14 //设置项滚轮大小
u8	Read_UI()
{
    u8 S0[]  =  "Reading:";
	u8 S1[]  =  "---------------------";
	u8 S2[]  =  "    Left = ";
    u8 S3[]  =  "    Right = ";
    u8 S4[]  =  "    CBH = ";
	u8 S5[]  =  "    Encoder = ";
	


	  OLED_CLS();//清屏
    OLED_P6x8Str(0,0,S0);
    OLED_P6x8Str(0,1,S1);
    OLED_P6x8Str(0,2,S2);
    OLED_P6x8Str(0,3,S3);
    OLED_P6x8Str(0,4,S4);
    OLED_P6x8Str(0,5,S5);
    LCD_Write_Number(95,0, 0);
                                   

//  static u8 SetArrow = 2;//箭头标记位(2~6)
//	static u8 Page = 0;//页面标记位(0~6)
//	static u8 Item = 1;//项目标记位(1~SetOptionsNum)

//  u8 AR[]="->";//显示箭头
//	u8 AM[]="- ";//选中模式
//	u8 AC[]="  ";//清除箭头
		

		while(1)
		{
			if(xbh<0)
				xbh = -xbh;
	
		  KEY_Service();  //按键服务
			
			LCD_Write_Number(95,2, ChlValue[0]);
			LCD_Write_Number(95,3, ChlValue[2]);
			LCD_Write_Number(95,4, (int)xbh*1000);
			LCD_Write_Number(95,5, ChlValue[1]);
			
				if(KEY_U ||KEY_D||KEY_A||KEY_B==1)
				{

				OLED_CLS();//清屏
					
				return Menu_UI_ID;
					
				}
		}
		
	//	OLED_P6x8Str(0,0,S0);

	
//		sprintf((char *)text,"%4d",(int)(speedPid.i*10));
//		AddNumString(SR[1],text);
//		sprintf((char *)text,"%4d",(int)(speedPid.d*10));
//		AddNumString(SR[2],text);
//		sprintf((char *)text,"%4d",(int)(stree_pid.p*10));
//		AddNumString(SR[3],text);
}
	
	
	
	/*
		#define SetOptionsNum 14 //设置项滚轮大小
u8 Set_UI()
{
    KEY_ = 0;


  u8 S0[]  =  "Set Variable Bett:";
	u8 S1[]  =  "---------------------";
	u8 SS[SetOptionsNum][19]={
		"      Speed_P:    ",
		"      Spedd_D:    ",
	};
	static u8 SetArrow = 2;
	static u8 Page = 0;
	static u8 Item = 1;

  u8 AR[]="->";
	u8 AM[]="- ";
	u8 AC[]="  ";
  u8 SaveSetArrow = 2;
	u8 ArrowState = 0;
  u8 text[5];
  u8 i;

  OLED_CLS();
	OLED_P6x8Str(0,0,S0);
	OLED_P6x8Str(0,1,S1);
  LCD_Write_Number(95,0, 0);
    while(1)
	{

        KEY_Service();  
		switch(KEY_)
		{
			case 0:break;

			case 1:

                KEY_ = 0;
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

			case 2:

                KEY_ = 0;
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

              case 3:
                KEY_ = 0;
				if(ArrowState == 0) ArrowState = 1;
				else ArrowState = 0;
				break;

              case 4:

				
                Falsh_Reserve();
				

				if(ArrowState == 1) ArrowState = 0;
				else
				{
					return Menu_UI_ID;
				}
				break;
        }

		if(ArrowState)
		{
           KEY_Service();  
			switch(Item)
			{
				case 1:
					if(KEY_ == 1) speedPid.p += 0.1;
					if(KEY_ == 2) speedPid.p -= 0.1;
					if(speedPid.p > 99.9) speedPid.p = 0.0;
					//if(KEY_ == 3) ArrowState=1;
                KEY_ = 0;
					break;

                case 2:
					if(KEY_ == 1) speedPid.d += 0.1;
					if(KEY_ == 2) speedPid.d -= 0.1;
					if(speedPid.d > 99.9) speedPid.d = 0.0;
												//	if(KEY_ == 3) ArrowState=1;
                KEY_ = 0;
					break;

                default:
					ArrowState = 0;
					break;
            }
        }
    sprintf((char *)text,"%4d",(int)(speedPid.p*10));
		AddNumString(SS[0],text);
		sprintf((char *)text,"%4d",(int)(speedPid.d*10));
		AddNumString(SS[1],text);

		for(i=2;i<8;i++)
		{
			OLED_P6x8Str(0,i,SS[Page+i-2]);
		}

		if(ArrowState == 0)
		{
			OLED_P6x8Str(24,SaveSetArrow,AC);
			OLED_P6x8Str(24,SetArrow,AR);
			SaveSetArrow = SetArrow;
		}
		else
		{
			OLED_P6x8Str(24,SaveSetArrow,AM);
		}
    }
}


void AddNumString(u8 ss[],u8 n[])
{
	u8 i;
	for(i=0;i<4;i++)
	{
		ss[14+i] = n [i];
	}
	ss[18] = '\0';
}

*/


//	#define SetOptionsNum 14 //设置项滚轮大小
//u8 Set_UI()
//{
//    KEY_ = 0;


//  u8 S0[]  =  "Set Variable Bett:";
//	u8 S1[]  =  "---------------------";
//	u8 SS[SetOptionsNum][19]={
//		"      Speed_P:    ",
//		"      Spedd_I:    ",
//		"      Spedd_D:    ",
//		"      Turn__P:    ",
//                "      Turn__I:    ",
//		"      Turn__D:    ",
//		"      _Speed_:    ",
//                "      vim_p1_:    ",
//                "      vim_p2_:    ",
//                "      vim_p3_:    ",
//                "      vim_p4_:    ",
//                "      vim_p5_:    ",
//                "      missline    ",
//                "      missline_m  ",
//                                    };

//    static u8 SetArrow = 2;//箭头标记位(2~6)
//	static u8 Page = 0;//页面标记位(0~6)
//	static u8 Item = 1;//项目标记位(1~SetOptionsNum)

//    u8 AR[]="->";//显示箭头
//	u8 AM[]="- ";//选中模式
//	u8 AC[]="  ";//清除箭头
//    u8 SaveSetArrow = 2;
//	u8 ArrowState = 0;//箭头状态标记0:正常选择项 1:数值修改
//    u8 text[5];
//    u8 i;

//    OLED_CLS();
//	OLED_P6x8Str(0,0,S0);
//	OLED_P6x8Str(0,1,S1);
//    LCD_Write_Number(95,0,0);
//																	}
	
//起跑函数，电机启动
//u8 Run_UI()
//{
//  KEY_ = 0;          //进入函数需要先清掉按键标志，使按键准确
//  u8 S0[]="Launching  Bett:";
//	u8 S1[]="---------------------";
//	u8 SR[]="RUNING";
//	u8 SS[]=" STOP ";
//    char  ch;
//    OLED_CLS();//清屏
//	OLED_P6x8Str(0,0,S0);
//	OLED_P6x8Str(0,1,S1);
//    OLED_P6x8Str(0,2,SS);
//    LCD_Write_Number(95,0, 0);
//    while(1)
//    {
//      KEY_Service();  //按键服务
//     if(KEY_ ==3)
//     {
//        KEY_ = 0;
//        OLED_P6x8Str(0,2,SR);
//			 
//#ifdef  BROTHER
//        DELAY_MS(2000);
//        uart_putchar(UART0,1);
//        FLAG_RUN = 1;      // 通过标志位来控制中断函数的执行与否
//        stop = 1;

//#endif

//#ifdef RED_LIGHT

//    while(uart_querychar(UART0,&ch)!=1);

//           FLAG_RUN = 1;      // 通过标志位来控制中断函数的执行与否
//           stop = 1;

//#endif
//     }

//     if(KEY_ == 4)
//		{
//                KEY_ = 0;
//  //              FLAG_RUN = 0;         //标志位清零
//              ftm_pwm_duty(FTM0 , FTM_CH1,0);  //电机占空比赋0，使其停止
//                 Steer_duty(440);    //舵机回中
//				return Menu_UI_ID;//返回主界面

//		}
//    }

//}


// //看参数
//u8 State1_UI()
//{
//    KEY_ = 0;          //进入函数需要先清掉按键标志，使按键准确
//  	u8 S0[]="Car State  Bett:";
//	u8 S1[]="---------------------";
//	u8 S2[]="MID                  ";
//	u8 S3[]="F_L_C      F_R_C     ";
//	u8 S4[]="F_L_V      F_R_V     ";
//	u8 S5[]="S_L        S_R       ";
//    OLED_CLS();//清屏
//    OLED_P6x8Str(0,0,S0);
//    OLED_P6x8Str(0,1,S1);
//    OLED_P6x8Str(0,2,S2);
//    OLED_P6x8Str(0,3,S3);
//    OLED_P6x8Str(0,4,S4);
//    OLED_P6x8Str(0,5,S5);
//    LCD_Write_Number(95,0, better());
//    while(1)
//    {

//      KEY_Service();  //按键服务

//     if(KEY_ ==3)
//     {
//        KEY_ = 0;
//        FLAG_RUN = 1;      // 通过标志位来控制中断函数的执行与否

//     }

//     if(KEY_ == 4)
//		{
//                KEY_ = 0;
//                FLAG_RUN = 0;         //标志位清零
//                ftm_pwm_duty(FTM0 , FTM_CH1,0);  //电机占空比赋0，使其停止
//                Steer_duty(460);    //舵机回中
//				return Menu_UI_ID;//返回主界面

//		}
//    if(PTD5_IN==1)
//    {

//     LCD_Write_Number(33,2, adc_guiyi[MID]);
//     LCD_Write_Number(97,2,cbbh);  // 打印查比和

//     LCD_Write_Number(33,3, adc_guiyi[F_L_CROSS]);
//     LCD_Write_Number(33,4, adc_guiyi[F_L_VER]);
//     LCD_Write_Number(33,5, adc_guiyi[S_L]);
//     LCD_Write_Number(97,3, adc_guiyi[F_R_CROSS]);
//     LCD_Write_Number(97,4, adc_guiyi[F_R_VER]);
//     LCD_Write_Number(97,5, adc_guiyi[S_R]);
//    }



//   if(PTD5_IN==0)
//   {
//     LCD_Write_Number(33,2, average[MID]);
//     LCD_Write_Number(33,3, average[F_L_CROSS]);
//     LCD_Write_Number(33,4, average[F_L_VER]);
//     LCD_Write_Number(33,5, average[S_L]);
//     LCD_Write_Number(97,3, average[F_R_CROSS]);
//     LCD_Write_Number(97,4, average[F_R_VER]);
//     LCD_Write_Number(97,5, average[S_R]);
//   }

//    }

//}


#define SetOptionsNum 14 //设置项滚轮大小
u8 Set_UI()
{
    KEY_ = 0;

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

  OLED_CLS();
	OLED_P6x8Str(0,0,S0);
	OLED_P6x8Str(0,1,S1);
  LCD_Write_Number(95,0, 0);
    while(1)
	{

    KEY_Service();  //按键服务
		switch(KEY_)
		{
			case 0:break;

			case 1://上键

                KEY_ = 0;
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

                KEY_ = 0;
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
                KEY_ = 0;
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

           KEY_Service();  //按键服务
			switch(Item)
			{
				case 1:
					if(KEY_ == 1) speedPid.p += 0.1;
					if(KEY_ == 2) speedPid.p -= 0.1;
					if(speedPid.p > 99.9) speedPid.p = 0.0;
                    KEY_ = 0;
					break;

				case 2:
					if(KEY_ == 1) speedPid.i += 0.1;
					if(KEY_ == 2) speedPid.i -= 0.1;
					if(speedPid.i > 99.9) speedPid.i = 0.0;
                    KEY_ = 0;
					break;

                case 3:
					if(KEY_ == 1) speedPid.d += 0.1;
					if(KEY_ == 2) speedPid.d -= 0.1;
					if(speedPid.d > 99.9) speedPid.d = 0.0;
                    KEY_ = 0;
					break;

                case 4:
					if(KEY_ == 1) stree_pid.p += 0.1;
					if(KEY_ == 2) stree_pid.p -= 0.1;
					if(stree_pid.p > 99.9) stree_pid.p = 0.0;
                    KEY_ = 0;
					break;

                case 5:
					if(KEY_ == 1) stree_pid.i += 0.1;
					if(KEY_ == 2) stree_pid.i -= 0.1;
					if(stree_pid.i > 99.9) stree_pid.i = 0.0;
                    KEY_ = 0;
					break;

                case 6:
					if(KEY_ == 1) stree_pid.d += 0.1;
					if(KEY_ == 2) stree_pid.d -= 0.1;
					if(stree_pid.d > 99.9) stree_pid.d = 0.0;
                    KEY_ = 0;
					break;

                case 7:
					if(KEY_ == 1) speedPid.goal +=1;
					if(KEY_ == 2) speedPid.goal -= 1;
					if(speedPid.goal> 999) speedPid.goal = 0;
                    KEY_ = 0;
					break;

                 case 8:
					if(KEY_ == 1)
                      stree_vim_pid.Kp_1 +=0.1;
					if(KEY_ == 2)
                      stree_vim_pid.Kp_1 -= 0.1;
					if(stree_vim_pid.Kp_1> 99.9) stree_vim_pid.Kp_1 = 0.0;
                    KEY_ = 0;
					break;

                 case 9:
					if(KEY_ == 1)
                      stree_vim_pid.Kp_2 +=0.1;
					if(KEY_ == 2)
                      stree_vim_pid.Kp_2 -= 0.1;
					if(stree_vim_pid.Kp_2> 99.9) stree_vim_pid.Kp_2 = 0.0;
                    KEY_ = 0;
					break;

                 case 10:
					if(KEY_ == 1)
                      stree_vim_pid.Kp_3 +=0.1;
					if(KEY_ == 2)
                      stree_vim_pid.Kp_3 -= 0.1;
					if(stree_vim_pid.Kp_3> 99.9) stree_vim_pid.Kp_3 = 0.0;
                    KEY_ = 0;
					break;

                 case 11:
					if(KEY_ == 1)
                      stree_vim_pid.Kp_4 +=0.1;
					if(KEY_ == 2)
                      stree_vim_pid.Kp_4 -= 0.1;
					if(stree_vim_pid.Kp_4> 99.9) stree_vim_pid.Kp_4 = 0.0;
                    KEY_ = 0;
					break;

                 case 12:
					if(KEY_ == 1)
                      stree_vim_pid.Kp_5 +=0.1;
					if(KEY_ == 2)
                      stree_vim_pid.Kp_5 -= 0.1;
					if(stree_vim_pid.Kp_5> 99.9) stree_vim_pid.Kp_5 = 0.0;
                    KEY_ = 0;
					break;
//                 case 13:
//					if(KEY_ == 1)
//                     missLine +=10;
//					if(KEY_ == 2)
//                     missLine-= 10;
//					if(stree_vim_pid.Kp_5> 300) stree_vim_pid.Kp_5 = 10;
//                    KEY_ = 0;
//					break;

//                 case 14:
//					if(KEY_ == 1)
//                     missLine_M +=10;
//					if(KEY_ == 2)
//                     missLine_M-= 10;
//					//if(stree_vim_pid.Kp_5> 300) stree_vim_pid.Kp_5 = 10;
//                    KEY_ = 0;
//					break;
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
//                sprintf((char *)text,"%4d",(int)(missLine));
//		AddNumString(SS[12],text);
//                sprintf((char *)text,"%4d",(int)(missLine_M));
//		AddNumString(SS[13],text);
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
    }
}

////拨码开关调整计划
//u8 Record_UI()
//{
//    u8 S0[]  =  "         Plan:";
//    u8 S1[]  =  "---------------------";
//	u8 S2[]  =  "    Plan_1 = ";
//    u8 S3[]  =  "    Plan_2 = ";
//    u8 S4[]  =  "    Plan_3 = ";
//    u8 S5[]  =  "    Plan_4 = ";
//    u8 S6[]  =  "    Plan_5 = ";
//    u8 S7[]  =  "    Plan_6 = ";

//    OLED_CLS();
//    OLED_P6x8Str(0,0,S0);
//    OLED_P6x8Str(0,1,S1);
//    OLED_P6x8Str(0,2,S2);
//    OLED_P6x8Str(0,3,S3);
//    OLED_P6x8Str(0,4,S4);
//    OLED_P6x8Str(0,5,S5);
//    OLED_P6x8Str(0,6,S6);
//    OLED_P6x8Str(0,7,S7);
//    KEY_ = 0;      //进入函数需要先清掉按键标志，使按键准确

//    Plan_1 =  PTD1_IN;
//    Plan_2 =  PTD0_IN;
//    Plan_3 =  PTD3_IN;
//    Plan_4 =  PTD2_IN;
//    Plan_5 =  PTD5_IN;
//    Plan_6 =  PTD4_IN;

//    LCD_Write_Number(80,2, Plan_1);
//    LCD_Write_Number(80,3, Plan_2);
//    LCD_Write_Number(80,4, Plan_3);
//    LCD_Write_Number(80,5, Plan_4);
//    LCD_Write_Number(80,6, Plan_5);
//    LCD_Write_Number(80,7, Plan_6);

//    while(1)
//    {
//        KEY_Service();  //按键服务
//        if(KEY_!=0)
//          return Menu_UI_ID;

//    }


//}

void AddNumString(u8 ss[],u8 n[])//数字加入显示字符串
{
	u8 i;
	for(i=0;i<4;i++)
	{
		ss[14+i] = n [i];
	}
	ss[18] = '\0';
}

