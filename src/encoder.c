#include "gpio.h"
#include "common.h"
#include "uart.h"
#include "dma.h"
#include "dma.h"
#include "pit.h"
#include "encoder.h"

/*存放脉冲数*/
static uint32_t ChlValue[2];

/*触发源*/
static const uint32_t DMA_PORT_TriggerSourceTable[] = 
{
    PORTA_DMAREQ,
    PORTB_DMAREQ,
    PORTC_DMAREQ,
    PORTD_DMAREQ,
    PORTE_DMAREQ,
};

/**
 * @brief  DMA 用作脉冲计数初始化     
 * @param  dmaChl :DMA通道号
 * @param  instance :端口号 比如HW_GPIOA
 * @param  pinIndex :引脚号
 * @retval None
 */
static void DMA_PulseCountInit(uint32_t dmaChl, uint32_t instance, uint32_t pinIndex)
{
    /* 开启2路引脚 配置为DMA触发 */
    GPIO_QuickInit(instance, pinIndex, kGPIO_Mode_IFT);
    /* 配置为DMA上升沿触发 */
    GPIO_ITDMAConfig(instance, pinIndex, kGPIO_DMA_RisingEdge, true);
    /* 配置DMA */
    static uint8_t dummy1, dummy2;
    DMA_InitTypeDef DMA_InitStruct1 = {0};  
    DMA_InitStruct1.chl = dmaChl;  
    DMA_InitStruct1.chlTriggerSource = DMA_PORT_TriggerSourceTable[instance];
    DMA_InitStruct1.triggerSourceMode = kDMA_TriggerSource_Normal; 
    DMA_InitStruct1.minorLoopByteCnt = 1;
    DMA_InitStruct1.majorLoopCnt = DMA_CITER_ELINKNO_CITER_MASK; /* 最大值 */
    
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
    /* 启动传输 */
    DMA_EnableRequest(dmaChl);
}

//中断函数处理
static void PIT_ISR(void)
{
    /* 由于DMA 是倒计数的 所需需要用最大值减一下 */
    /* CH0 */
    ChlValue[0] = DMA_CITER_ELINKNO_CITER_MASK - DMA_GetMajorLoopCount(HW_DMA_CH0);
    
    /* 清零计数 */
    DMA_CancelTransfer();
    DMA_SetMajorLoopCounter(HW_DMA_CH0, DMA_CITER_ELINKNO_CITER_MASK);
    
    /* 开始下一次传输 */
    DMA_EnableRequest(HW_DMA_CH0);
   
}

int encoder(void)
{
	 GPIO_QuickInit(HW_GPIOA, 6, kGPIO_Mode_OPP);
    UART_QuickInit(UART4_RX_PC14_TX_PC15, 115200);
    
    /* 开启DMA捕捉引脚脉冲信号 */
    DMA_PulseCountInit(HW_DMA_CH0, HW_GPIOA, 6);
    
    /* 开启一个PIT中断用于显示收到的计数 */
    PIT_QuickInit(HW_PIT_CH0, 1000 * 1000);
    PIT_CallbackInstall(HW_PIT_CH0, PIT_ISR);
    PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF, true);

    while(1)
    {
			    /* 开启一个PIT中断用于显示收到的计数 */
        PIT_QuickInit(HW_PIT_CH0, 1000 * 1000);
        PIT_CallbackInstall(HW_PIT_CH0, PIT_ISR);
        PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF, true);
			
        printf("[CH%d]:%4d\r\n", 0, ChlValue[0]);
        DelayMs(500);
			
			return ChlValue[0];
    }
}



