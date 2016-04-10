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
static u8 Arrow = 3;//¼ýÍ·ËùÔÚÎ»ÖÃ
// º¯ÊýÖ¸ÕëÉè¼Æ//






u8 (*FunctionPointer[11])(void)={ 
								  Menu_UI,//Ö÷½çÃæ(µØÖ·Îª0)
								  Run_UI,//ÆðÅÜ½çÃæ(µØÖ·Îª1)
								  State1_UI,//³µÌå×´Ì¬¹Û²ì½ç1(µØÖ·Îª2)
								  Set_UI,//²ÎÊýÉèÖÃ½çÃæ(µØÖ·Îª3)
								  Record_UI,//·½°¸Ñ¡Ôñ½çÃæ(µØÖ·Îª4)
								  Read_UI,//·½°¸Ñ¡Ôñ½çÃæ(µØÖ·Îª5)
								};


//²Ëµ¥Ê×Ò³

u8 Menu_UI()
{

  
    u8 S0[]="    Menu   Bett:";
	u8 S1[]="---------------------";
	u8 S3[]="      Run";
	u8 S4[]="      Car State";
	u8 S5[]="      Set Variable";
	u8 S6[]="      Plan Record";
	u8 S7[]="      Read";
	u8 AR[]="->";//ÏÔÊ¾¼ýÍ·
	u8 AC[]="  ";//Çå³ý¼ýÍ·
	
	u8 key = 0;
    u8 err;

    OLED_CLS();//ÇåÆÁ
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
						case 3: return 1;// ½øÈëÆðÅÜÒ³Ãæ
						case 4: return 2;// ½øÈë³µÌå×´Ì¬¹Û²ìÒ³Ãæ
						case 5: return 3;// ½øÈë²ÎÊýÉèÖÃÒ³Ãæ
						case 6: return 4;// ½øÈë·½°¸Ñ¡ÔñÒ³Ãæ
						case 7: return 5;// ½øÈë·½°¸Ñ¡ÔñÒ³Ãæ
						
					}
					
					break;
			case 4:
			   
					return Menu_UI_ID;
					break;
						default:
					break;
		}
		key=(u8)OSMboxPend(msg_key,200,&err);//°´¼üÓÊÏä
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
	
    OLED_CLS();//ÇåÆÁ
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
			FLAG_RUN = 1;      // Í¨¹ý±êÖ¾Î»À´¿ØÖÆÖÐ¶Ïº¯ÊýµÄÖ´ÐÐÓë·ñ

		 }

		 if(key == 4)
		 {
					
				FLAG_RUN = 0;  //±êÖ¾Î»ÇåÁã
				speedClear();  //»Øµ½³õÊ¼×´Ì¬
				return Menu_UI_ID;//·µ»ØÖ÷½çÃæ

		 }
		 
		 key=(u8)OSMboxPend(msg_key,200,&err);//°´¼üÓÊÏä
		
    }

	
	

}

#define SetOptionsNum 8 //ÉèÖÃÏî¹öÂÖ´óÐ
u8 State1_UI()
{
	
  static u8 SetArrow = 2;
	static u8 Page = 0;
	static u8 Item = 1;
	u8 key = 0;
  u8 err;
  u8 i,n;
	
  u8 S0[]  =  "Reading:";
	u8 S1[]  =  "---------------------";
	u8 SS[SetOptionsNum][19]={
		"      LMAX = ",
		"      LMIN = ",
		"      RMAX = ",
		"      RMIN = ",
		"      DLMAX = ",
		"      DLMIN = ",
		"      DRMAX = ",
		"      DRMIN = ",
	};

	
	
	float dnum[9];
	
  u8 AR[]="->";//ÏÔÊ¾¼ýÍ·
	u8 AC[]="  ";//Çå³ý¼ýÍ·
	
	OLED_CLS();//ÇåÆÁ
  OLED_P6x8Str(0,0,S0);
  OLED_P6x8Str(0,1,S1);
    
	u8 SaveSetArrow = 2;
	u16 ArrowState = 0;//¼ýÍ·×´Ì¬±ê¼Ç0:Õý³£Ñ¡ÔñÏî 1:ÊýÖµÐÞ¸Ä
  u8 text[5];
	while(1)
	{
			min_max();    //×î´ó×îÐ¡Öµ
		switch(key)
		{
			case 0:break;

			case 1://ÉÏ¼ü
			{
				if(ArrowState== 0)
				{
					SetArrow--;
					Item--;
					if(Item < 1) Item = SetOptionsNum;
					if(SetArrow<2)
					{
						if(Page == 0)
						{
							Page = 2;
							SetArrow = 7;
						}
						else
						{
							SetArrow = 2;
              Page--;
						}
					}
				}
			}
				break;

			case 2://ÏÂ¼ü
			{
				if(ArrowState== 0)
				{
					SetArrow++;
					Item++;
					if(Item > SetOptionsNum) Item = 1;
					if(SetArrow>7)
					{
						if(Page == 2)
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
			}
				break;
		}
			
		if(key == 4)
		{

			OLED_CLS();//ÇåÆÁ
					
			return Menu_UI_ID;
					
		}
		key=(u8)OSMboxPend(msg_key,5,&err);//°´¼üÓÊÏä
	
	for(i=2;i<8;i++)
		 {
			OLED_P6x8Str(0,i,SS[Page+i-2]);//´òÓ¡ÏÔÊ¾
		 }
		if(ArrowState == 0)//¼ýÍ·ÎªÐÞ¸ÄÊýÖµ×´Ì¬
		{
			OLED_P6x8Str(24,SaveSetArrow,AC);
			OLED_P6x8Str(24,SetArrow,AR);
			SaveSetArrow = SetArrow;
		}
		
			 dnum[0]=LMAX;         //LMAX
			 dnum[1]=LMIN;         //LMIN
			 dnum[2]=RMAX;         //RMAX
			 dnum[3]=RMIN;         //RMIN
			 dnum[4]=DLMAX;         //DLMAX
		   dnum[5]=DLMIN;        //DLMIN
		   dnum[6]=DRMAX;        //DRMAX
		   dnum[7]=DRMIN;        //DRMIN
		 for(i=2;i<8;i++)
		 {
			LCD_Write_Number(95,i, dnum[Page+i-2]);
		 }
	 }

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
#define SetOptionsNum 14 //ÉèÖÃÏî¹öÂÖ´óÐ¡
u8	Read_UI()
{
	static u8 SetArrow = 2;
	static u8 Page = 0;
	static u8 Item = 1;
	u8 key = 0;
  u8 err;
  u8 i,n;
	
  u8 S0[]  =  "Reading:";
	u8 S1[]  =  "---------------------";
	u8 SS[SetOptionsNum][19]={
		"      Left = ",
    "      Right = ",
	  "      Enco = ",     //Encoder
	  "      l_cha = ",    //left_cha
	  "      D_RIGHT = ",
	  "      D_LEFT = ",
		"      LMAX = ",
		"      LMIN = ",
		"      RMAX = ",
		"      RMIN = ",
		"      DLMAX = ",
		"      DLMIN = ",
		"      DRMAX = ",
		"      DRMIN = ",
	};

	
	
	float dnum[14];
	
  u8 AR[]="->";//ÏÔÊ¾¼ýÍ·
	u8 AC[]="  ";//Çå³ý¼ýÍ·
	
	OLED_CLS();//ÇåÆÁ
  OLED_P6x8Str(0,0,S0);
  OLED_P6x8Str(0,1,S1);
	
//  LCD_Write_Number(95,0, 0);
    
	u8 SaveSetArrow = 2;
	u16 ArrowState = 0;//¼ýÍ·×´Ì¬±ê¼Ç0:Õý³£Ñ¡ÔñÏî 1:ÊýÖµÐÞ¸Ä
  u8 text[5];
	while(1)
	{
		switch(key)
		{
			case 0:break;

			case 1://ÉÏ¼ü
			{
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
			}
				break;

			case 2://ÏÂ¼ü
			{
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
			}
				break;
		}
			
		if(key == 4)
		{

			OLED_CLS();//ÇåÆÁ
					
			return Menu_UI_ID;
					
		}
		key=(u8)OSMboxPend(msg_key,5,&err);//°´¼üÓÊÏä
	
	for(i=2;i<8;i++)
		 {
			OLED_P6x8Str(0,i,SS[Page+i-2]);//´òÓ¡ÏÔÊ¾
		 }
		if(ArrowState == 0)//¼ýÍ·ÎªÐÞ¸ÄÊýÖµ×´Ì¬
		{
			OLED_P6x8Str(24,SaveSetArrow,AC);
			OLED_P6x8Str(24,SetArrow,AR);
			SaveSetArrow = SetArrow;
		}
		
			 dnum[0]=LEFT;
		   dnum[1]=RIGHT;
		   dnum[2]=ENCODE;
		   dnum[3]=LEFT-DOWN_LEFT-188+61;
			 dnum[4]=DOWN_LEFT;
			 dnum[5]=DOWN_RIGHT;
			 dnum[6]=LMAX;         //LMAX
			 dnum[7]=LMIN;         //LMIN
			 dnum[8]=RMAX;         //RMAX
			 dnum[9]=RMIN;         //RMIN
			 dnum[10]=DLMAX;         //DLMAX
		   dnum[11]=DLMIN;        //DLMIN
		   dnum[12]=DRMAX;        //DRMAX
		   dnum[13]=DRMIN;        //DRMIN
		 for(i=2;i<8;i++)
		 {
			LCD_Write_Number(95,i, dnum[Page+i-2]);
		 }
	 }
		
}
		
	
#define SetOptionsNum 14 //ÉèÖÃÏî¹öÂÖ´óÐ¡
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

    static u8 SetArrow = 2;//¼ýÍ·±ê¼ÇÎ»(2~6)
	static u8 Page = 0;//Ò³Ãæ±ê¼ÇÎ»(0~6)
	static u8 Item = 1;//ÏîÄ¿±ê¼ÇÎ»(1~SetOptionsNum)

   u8 AR[]="->";//ÏÔÊ¾¼ýÍ·
	u8 AM[]="- ";//Ñ¡ÖÐÄ£Ê½
	u8 AC[]="  ";//Çå³ý¼ýÍ·
    u8 SaveSetArrow = 2;
	u16 ArrowState = 0;//¼ýÍ·×´Ì¬±ê¼Ç0:Õý³£Ñ¡ÔñÏî 1:ÊýÖµÐÞ¸Ä
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

			case 1://ÉÏ¼ü

                
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

			case 2://ÏÂ¼ü

              
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

              case 3://È·ÈÏ
               
				if(ArrowState == 0) ArrowState = 1;
				else ArrowState = 0;
				break;

              case 4://ÍË³ö

				//ÌîÐ´±£´æµ½flashµÄ´úÂë
                Falsh_Reserve();
				//ÌîÐ´±£´æµ½flashµÄ´úÂë

				if(ArrowState == 1) ArrowState = 0;//¼ýÍ·×´Ì¬ÐÞ¸Ä
				else
				{
					return Menu_UI_ID;
				}
				break;
        }
         //*****ÊýÖµÐÞ¸Ä
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
					ArrowState = 0;//Î´Éè¶¨µÄ±äÁ¿²»¸øÓè½øÈë×´Ì¬
					break;
            }
        }
        //ÊýÖµÐÞ¸Ä

        //ÊýÖµÇ¶Èë
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
        //*****ÊýÖµÇ¶Èë

		for(i=2;i<8;i++)
		{
			OLED_P6x8Str(0,i,SS[Page+i-2]);//´òÓ¡ÏÔÊ¾
		}

		if(ArrowState == 0)//¼ýÍ·ÎªÐÞ¸ÄÊýÖµ×´Ì¬
		{
			OLED_P6x8Str(24,SaveSetArrow,AC);
			OLED_P6x8Str(24,SetArrow,AR);
			SaveSetArrow = SetArrow;
		}
		else//ÐÞ¸Ä¼ýÍ·ÎªÊýÖµÑ¡Ôñ×´Ì¬
		{
			OLED_P6x8Str(24,SaveSetArrow,AM);
		}
		
		key=(u8)OSMboxPend(msg_key,0,&err);//°´¼üÓÊÏä
    }
}



void AddNumString(u8 ss[],u8 n[])//Êý×Ö¼ÓÈëÏÔÊ¾×Ö·û´®
{
	u8 i;
	for(i=0;i<4;i++)
	{
		ss[14+i] = n [i];
	}
	ss[18] = '\0';
}


/***********************************
¶æ»ú¹éÖÐ µç»úÍ£Ö¹ 
***********************************/
void speedClear(void)
{

	FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH2,0);
	FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH3,0);
	FTM_PWM_ChangeDuty(HW_FTM1, HW_FTM_CH1,1460);

}

