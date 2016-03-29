#include "includes.h"


///////////////////////////////////////////////////////
float ChlValue[3];
u32 now_10ms = 0;
int valuesL[5] = {0,0,0,0,0};
int valuesR[5] = {0,0,0,0,0};
float xbh = 0;
static const uint32_t DMA_PORT_TriggerSourceTable[] = 
{
    PORTA_DMAREQ,
    PORTB_DMAREQ,
    PORTC_DMAREQ,
    PORTD_DMAREQ,
    PORTE_DMAREQ,
};

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


char  FLAG = 1;
//�жϺ�������
 void PIT_ISR(void)
{
    /* ����DMA �ǵ������� ������Ҫ�����ֵ��һ�� */
    /* CH0 */
    ChlValue[0] = DMA_CITER_ELINKNO_CITER_MASK - DMA_GetMajorLoopCount(HW_DMA_CH0) +176 ;
    /* CH1 */
	ChlValue[2] = DMA_CITER_ELINKNO_CITER_MASK - DMA_GetMajorLoopCount(HW_DMA_CH2)  ;
	
    /* ������� */
	
	//��һ��
	
	ChlValue[0] = (500*(ChlValue[0] - 2785)/(2830-2785));
	ChlValue[2] = (500*(ChlValue[2] - 2785)/(2830-2785));
	
	xbh = (ChlValue[2]- ChlValue[0])/(ChlValue[2]+ ChlValue[0]);
	
    DMA_CancelTransfer();
    DMA_SetMajorLoopCounter(HW_DMA_CH0, DMA_CITER_ELINKNO_CITER_MASK);
	DMA_SetMajorLoopCounter(HW_DMA_CH2, DMA_CITER_ELINKNO_CITER_MASK);
    /* ��ʼ��һ�δ��� */
    DMA_EnableRequest(HW_DMA_CH0);;
	DMA_EnableRequest(HW_DMA_CH2);
}




void PIT_ISR2(void)
{

    if(FLAG_RUN)
	{
		readencode();
	}
	

}

void PIT_ISR3(void)
{

	if(FLAG)
	ctrls(ChlValue[0],ChlValue[2]);

}

void PIT_ISR4(void)
{

	

}

