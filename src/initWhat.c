////////////////////////////////////////////////////////////////////
//���ٳ�ʼ��GPIO
/*****
/* GPIO ����ģʽ */
/*
 *         @arg kGPIO_Mode_IFT :��������
 *         @arg kGPIO_Mode_IPD :��������
 *         @arg kGPIO_Mode_IPU :��������
 *         @arg kGPIO_Mode_OOD :��©��� ����������2������������� �ٶ�..
 *         @arg kGPIO_Mode_OPP :�������
 */
 
 /**
GPIO_QuickInit(HW_GPIOE, 6, kGPIO_Mode_OPP);

PEout(6) = 0;
PEout(6) = 1;

GPIO_QuickInit(HW_GPIOE, 26, kGPIO_Mode_IPU);
PEin(26)
 val[0] = GPIO_ReadBit(HW_GPIOE, 26);

*/

//////////////////////////////////////////////////////////////////
//����ɨ��
/****

/* ��������״̬ 0δ�� 1���� */
//#define NO_KEY          (0x00)  //0
//#define KEY_SINGLE      (0x01)   //1
/* ��������ֵ */ 
//static uint8_t gRetValue;

/* ״̬���� 
typedef enum
{
    kKEY_Idle,          //����̬ 
    kKEY_Debounce,      //ȷ��������̬ 
    kKEY_Confirm,       //ȷ�ϰ���״̬
}KEY_Status;
*/

/* ����ɨ����� */
/*

static void KEY_Scan(void)
{
    static KEY_Status status = kKEY_Idle;
    switch(status)
    {
        case kKEY_Idle:
            gRetValue = NO_KEY; //=0
            if(KEY1 == 0)  //������������� ����ȷ��������̬ 
            {
                status = kKEY_Debounce;
            }
            break;
        case kKEY_Debounce:  //ȷ��������̬ 
            if(KEY1 == 0)
            {
                status = kKEY_Confirm;
            }
            else
            {
                status = kKEY_Idle;
                gRetValue = NO_KEY;
            }
            break;
        case kKEY_Confirm: // ȷ��̬ 
            if(KEY1 == 1) ///�����ɿ� 
            {
                gRetValue = KEY_SINGLE;
                status = kKEY_Idle;
            }
            break;
        default:
            break;
    }
}
*/
//ѭ��ִ�иú��� ���  if(gRetValue == KEY_SINGLE) //��������
/////////////////////////////////////////////////////////////////
//���ڵ�����/////////////////////////////////////////////////////
/* UART ���ٳ�ʼ���ṹ��֧�ֵ�����* ʹ��ʱ�����Ƽ���׼��ʼ�� */
/*
 UART1_RX_PE01_TX_PE00   
 UART0_RX_PF17_TX_PF18   
 UART3_RX_PE05_TX_PE04   
 UART5_RX_PF19_TX_PF20   
 UART5_RX_PE09_TX_PE08   
 UART2_RX_PE17_TX_PE16   
 UART4_RX_PE25_TX_PE24   
 UART0_RX_PA01_TX_PA02   
 UART0_RX_PA15_TX_PA14   
 UART3_RX_PB10_TX_PB11   
 UART0_RX_PB16_TX_PB17   
 UART1_RX_PC03_TX_PC04   
 UART4_RX_PC14_TX_PC15   
 UART3_RX_PC16_TX_PC17   
 UART2_RX_PD02_TX_PD03   
 UART0_RX_PD06_TX_PD07   
 UART2_RX_PF13_TX_PF14   
 UART5_RX_PD08_TX_PD09   
*/

// UART_QuickInit(UART0_RX_PD06_TX_PD07, 115200);   
//֧�� printf();

/////////////////////////////////////////////////////////////////////////////
/////////////////PIT�жϵĿ�������//////////////////////////////////////////////
/**
 * @brief  PITģ����ٳ�ʼ������
 * @code
 *      // ��ʼ��PITģ�� 0 ͨ�� ����100MS�ж� �������ж� ע��ص����� �ڻص������д�ӡ������Ϣ
 *      //�����жϻص�����
 *      static void PIT0_CallBack(void);
 *      //��ʼ��PITģ���0ͨ��������100ms�ж�
 *      PIT_QuickInit(HW_PIT_CH0, 100000);
 *      PIT_CallbackInstall(HW_PIT_CH0, PIT0_CallBack); //ע��ص�����
 *      PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF,ENABLE); //����ģ��0ͨ���ж�
 *      //�жϻص�����
 *      static void PIT0_CallBack(void)
 *      {
 *          printf("Enter PIT0 INt\r\n");    
 *      }
 * @endcode
 * \attention ���жϺ����о�����Ҫ���ûᵼ�������ĺ���������printf�ȣ�����ʵ���������
 * \attention �ο�������ʵ��Ӧ���в�����printf����
 * @param[in]  chl ͨ����
 *              @arg HW_PIT_CH0 
 *              @arg HW_PIT_CH1
 *              @arg HW_PIT_CH2 
 *              @arg HW_PIT_CH3 
 * @param[in]  timeInUs �����жϵ����� \��λUS
 * @retval None
 */
 /*
 
 static void PIT0_CallBack(){
//�ж�Ҫִ�еĴ���	 
 }
void PIT_QuickInit(uint8_t chl, uint32_t timeInUs);
PIT_ITDMAConfig();
*/

///////////////////////////////////////////////////////////////////////////////////////
/////////////PWM���ٳ�ʼ��//////////////////////////////////////////////////////////////
/* ���õ�FTMͨ����: */
/*
 FTM0_CH4_PB12   // ftm0 ģ�� 4ͨ�� PB12����
 FTM0_CH5_PB13   
 FTM0_CH5_PA00   
 FTM0_CH6_PA01   
 FTM0_CH7_PA02   
 FTM0_CH0_PA03
 FTM0_CH1_PA04   
 FTM0_CH2_PA05   
 FTM0_CH3_PA06   
 FTM0_CH4_PA07   
 FTM0_CH0_PC01   
 FTM0_CH1_PC02   
 FTM0_CH2_PC03   
 FTM0_CH3_PC04   
 FTM0_CH4_PD04   
 FTM0_CH5_PD05   
 FTM0_CH6_PD06   
 FTM0_CH7_PD07   
 FTM1_CH0_PB12   
 FTM1_CH1_PB13   
 FTM1_CH0_PA08   
 FTM1_CH1_PA09   
 FTM1_CH0_PA12   
 FTM1_CH1_PA13   
 FTM1_CH0_PB00   
 FTM1_CH1_PB01   
 FTM2_CH0_PA10   
 FTM2_CH1_PA11   
 FTM2_CH0_PB18   
 FTM2_CH1_PB19   
*/
/* ʹ�ÿ��ٳ�ʼ�� ������ѧ����ɱ�Ҫ���� */
//   FTM_PWM_QuickInit(FTM0_CH3_PA06, kPWM_EdgeAligned, 5000);
    
/* ����FTM0ģ��3ͨ����ռ�ձ� */
//    FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH3, 6000); /* 0-10000 ��Ӧ 0-100% */

/////////////////////////////////////////////////////////////////////////////////////
////////////////ADC���ٳ�ʼ��/////////////////////////////////////////////////////////

/* ���õ� ADCͨ�������� - 144P*/
/*
 ADC0_SE0_DP0        
 ADC0_SE1_DP1        
 ADC0_SE3_DP3        
 ADC0_SE4B_PC2       
 ADC0_SE5B_PD1       
 ADC0_SE6B_PD5       
 ADC0_SE7B_PD6       
 ADC0_SE8_PB0        
 ADC0_SE9_PB1        
 ADC0_SE12_PB2       
 ADC0_SE13_PB3       
 ADC0_SE14_PC0       
 ADC0_SE15_PC1       
 ADC0_SE17_E24       
 ADC0_SE18_E25       
 ADC0_SE19_DM0       
 ADC0_SE20_DM1       
 ADC0_SE26_TEMP      
 ADC1_SE0_DP0        
 ADC1_SE1_DP1        
 ADC1_SE3_DP3        
 ADC1_SE4_PE0        
 ADC1_SE5_PE1        
 ADC1_SE6_PE2        
 ADC1_SE7_PE3        
 ADC1_SE4B_PC8       
 ADC1_SE5B_PC9       
 ADC1_SE6B_PC10      
 ADC1_SE7B_PC11      
 ADC1_SE8_PB0        
 ADC1_SE9_PB1        
 ADC1_SE14_PB10      
 ADC1_SE15_PB11      
 ADC1_SE17_PB117     
 ADC1_SE19_DM0       
 ADC1_SE20_DM1       
 ADC1_SE26_TEMP      
*/

/**
 * @brief  �������AD��ʼ������
 * @code
 *    //��ʼ�� ADC0 ͨ��20 ����DM1 ���� ���� 12λ
 *    ADC_QuickInit(ADC0_SE20_DM1, kADC_SingleDiff12or13);
 *    //��ȡADת�����
 *    value = ADC_QuickReadValue(ADC0_SE20_DM1);
 * @endcode
 * @param[in]  MAP ���ٳ�ʼ���꣬���ADC.H�ļ�
 * @param[in]  resolutionMode  ת���ֱ�������
 *              @arg kADC_SingleDiff8or9   ת������Ϊ8/9λ
 *              @arg kADC_SingleDiff10or11 ת������Ϊ10/11λ
 *              @arg kADC_SingleDiff12or13 ת������Ϊ12/13λ
 *              @arg kADC_SingleDIff16     ת������Ϊ16λ
 * @retval ADCģ���
 */
 
 /*
 
 ADC_QuickInit();
 value = ADC_QuickReadValue();
 
 */
 
 //////////////////////////////////////////////////////////////////////////////////




