#include "global.h"

/////////////////////////////////////////////////////////////////
extern void PIT_ISR(void);  //PIT�ж�
extern void DMA_PulseCountInit(uint32_t dmaChl, uint32_t instance, uint32_t pinIndex);  //DMA����
extern void PIT_ISR2(void);

/////////////////////////////////////////////////////////////////

/********
������־����
********/

u8 KEY_ = 0;


//��������ʼ��
void  init_encoders(void)
{
	  DMA_PulseCountInit(HW_DMA_CH1, HW_GPIOA, 6);
	  PIT_QuickInit(HW_PIT_CH1, 5 * 1000);
      PIT_CallbackInstall(HW_PIT_CH1, PIT_ISR2);
      PIT_ITDMAConfig(HW_PIT_CH1, kPIT_IT_TOF, true);
}


//DMA��ʼ��
void dmaInit(void)
{

	DMA_PulseCountInit(HW_DMA_CH0, HW_GPIOB, 0);
	DMA_PulseCountInit(HW_DMA_CH2, HW_GPIOC, 6);


}
//PIT ��ʼ��
void pitInit(void)
{

	/* ����һ��PIT�ж����ڼ��� */
    PIT_QuickInit(HW_PIT_CH0, 10 * 1000);
    PIT_CallbackInstall(HW_PIT_CH0, PIT_ISR);
    PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF, true);
	
	/* ����һ��PIT�ж����ڿ��ƶ�� */
    PIT_QuickInit(HW_PIT_CH2, 20 * 1000);
    PIT_CallbackInstall(HW_PIT_CH2, PIT_ISR3);
    PIT_ITDMAConfig(HW_PIT_CH2, kPIT_IT_TOF, true);
	
	/* ����һ��PIT�ж����ڿ��ƶ�� */
    PIT_QuickInit(HW_PIT_CH3, 15 * 1000);
    PIT_CallbackInstall(HW_PIT_CH3, PIT_ISR4);
    PIT_ITDMAConfig(HW_PIT_CH3, kPIT_IT_TOF, true);
	
	

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
void initAll(void)
{

	DelayInit();  //��ʱ��ʼ��
	dmaInit();
	init_encoders();
	speedInit();
	pitInit();
	UART_QuickInit(UART0_RX_PB16_TX_PB17, 38400);
	OLED_Init();
    KEY_Init();
	flash_init();	
	Flash_Read();

}