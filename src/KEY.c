#include  "KEY.h"
#include "includes.h"
#include "gpio.h"



/******按键初始化*******/
void KEY_Init()
{
  GPIO_QuickInit(HW_GPIOA,12, kGPIO_Mode_OPP );          //初始化 PTE0 管脚，复用功能为GPIO ，下降沿触发中断，上拉电阻
  GPIO_QuickInit(HW_GPIOA,11, kGPIO_Mode_OPP );          //初始化 PTE2 管脚，复用功能为GPIO ，下降沿触发中断，上拉电阻
  GPIO_QuickInit(HW_GPIOA,13, kGPIO_Mode_OPP );          //初始化 PTE4 管脚，复用功能为GPIO ，下降沿触发中断，上拉电阻
  GPIO_QuickInit(HW_GPIOA,19, kGPIO_Mode_OPP );          //初始化 PTE6 管脚，复用功能为GPIO ，下降沿触发中断，上拉电阻
	
}


u8 key_check(KEY_e key)
{
    
    if(PAin(key) == 1)
    {
        OSTimeDly(10);
        if(PAin(key)  == 1)
        {
            return 0;
        }
    }
    return 1;
}







