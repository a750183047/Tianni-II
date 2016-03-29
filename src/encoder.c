#include "gpio.h"
#include "common.h"
#include "uart.h"
#include "dma.h"
#include "dma.h"
#include "pit.h"
#include "encoder.h"

/*���������*/
static uint32_t ChlValue[2];

/*����Դ*/
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
static void DMA_PulseCountInit(uint32_t dmaChl, uint32_t instance, uint32_t pinIndex)
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

//�жϺ�������
static void PIT_ISR(void)
{
    /* ����DMA �ǵ������� ������Ҫ�����ֵ��һ�� */
    /* CH0 */
    ChlValue[0] = DMA_CITER_ELINKNO_CITER_MASK - DMA_GetMajorLoopCount(HW_DMA_CH0);
    
    /* ������� */
    DMA_CancelTransfer();
    DMA_SetMajorLoopCounter(HW_DMA_CH0, DMA_CITER_ELINKNO_CITER_MASK);
    
    /* ��ʼ��һ�δ��� */
    DMA_EnableRequest(HW_DMA_CH0);
   
}

int encoder(void)
{
	 GPIO_QuickInit(HW_GPIOA, 6, kGPIO_Mode_OPP);
    UART_QuickInit(UART4_RX_PC14_TX_PC15, 115200);
    
    /* ����DMA��׽���������ź� */
    DMA_PulseCountInit(HW_DMA_CH0, HW_GPIOA, 6);
    
    /* ����һ��PIT�ж�������ʾ�յ��ļ��� */
    PIT_QuickInit(HW_PIT_CH0, 1000 * 1000);
    PIT_CallbackInstall(HW_PIT_CH0, PIT_ISR);
    PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF, true);

    while(1)
    {
			    /* ����һ��PIT�ж�������ʾ�յ��ļ��� */
        PIT_QuickInit(HW_PIT_CH0, 1000 * 1000);
        PIT_CallbackInstall(HW_PIT_CH0, PIT_ISR);
        PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF, true);
			
        printf("[CH%d]:%4d\r\n", 0, ChlValue[0]);
        DelayMs(500);
			
			return ChlValue[0];
    }
}



