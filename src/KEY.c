#include  "KEY.h"
#include "includes.h"
#include "gpio.h"



/******������ʼ��*******/
void KEY_Init()
{
  GPIO_QuickInit(HW_GPIOA,12, kGPIO_Mode_OPP );          //��ʼ�� PTE0 �ܽţ����ù���ΪGPIO ���½��ش����жϣ���������
  GPIO_QuickInit(HW_GPIOA,11, kGPIO_Mode_OPP );          //��ʼ�� PTE2 �ܽţ����ù���ΪGPIO ���½��ش����жϣ���������
  GPIO_QuickInit(HW_GPIOA,13, kGPIO_Mode_OPP );          //��ʼ�� PTE4 �ܽţ����ù���ΪGPIO ���½��ش����жϣ���������
  GPIO_QuickInit(HW_GPIOA,19, kGPIO_Mode_OPP );          //��ʼ�� PTE6 �ܽţ����ù���ΪGPIO ���½��ش����жϣ���������
	
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







