////////////////////////////////////////////////////////////////////
//快速初始化GPIO
/*****
/* GPIO 工作模式 */
/*
 *         @arg kGPIO_Mode_IFT :悬空输入
 *         @arg kGPIO_Mode_IPD :下拉输入
 *         @arg kGPIO_Mode_IPU :上拉输入
 *         @arg kGPIO_Mode_OOD :开漏输出 如果不清楚这2种输出的区别请 百度..
 *         @arg kGPIO_Mode_OPP :推挽输出
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
//按键扫描
/****

/* 按键返回状态 0未按 1按下 */
//#define NO_KEY          (0x00)  //0
//#define KEY_SINGLE      (0x01)   //1
/* 按键返回值 */ 
//static uint8_t gRetValue;

/* 状态机表 
typedef enum
{
    kKEY_Idle,          //空闲态 
    kKEY_Debounce,      //确认与消抖态 
    kKEY_Confirm,       //确认按键状态
}KEY_Status;
*/

/* 按键扫描程序 */
/*

static void KEY_Scan(void)
{
    static KEY_Status status = kKEY_Idle;
    switch(status)
    {
        case kKEY_Idle:
            gRetValue = NO_KEY; //=0
            if(KEY1 == 0)  //如果按键被按下 进入确认与消抖态 
            {
                status = kKEY_Debounce;
            }
            break;
        case kKEY_Debounce:  //确认与消抖态 
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
        case kKEY_Confirm: // 确认态 
            if(KEY1 == 1) ///按键松开 
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
//循环执行该函数 如果  if(gRetValue == KEY_SINGLE) //按键按下
/////////////////////////////////////////////////////////////////
//串口的配置/////////////////////////////////////////////////////
/* UART 快速初始化结构所支持的引脚* 使用时还是推荐标准初始化 */
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
//支持 printf();

/////////////////////////////////////////////////////////////////////////////
/////////////////PIT中断的快速配置//////////////////////////////////////////////
/**
 * @brief  PIT模块快速初始化配置
 * @code
 *      // 初始化PIT模块 0 通道 产生100MS中断 并开启中断 注册回调函数 在回调函数中打印调试信息
 *      //声明中断回调函数
 *      static void PIT0_CallBack(void);
 *      //初始化PIT模块的0通道，产生100ms中断
 *      PIT_QuickInit(HW_PIT_CH0, 100000);
 *      PIT_CallbackInstall(HW_PIT_CH0, PIT0_CallBack); //注册回调函数
 *      PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF,ENABLE); //开启模块0通道中断
 *      //中断回调函数
 *      static void PIT0_CallBack(void)
 *      {
 *          printf("Enter PIT0 INt\r\n");    
 *      }
 * @endcode
 * \attention 在中断函数中尽量不要放置会导致阻塞的函数，比如printf等，上述实例程序仅作
 * \attention 参考，建议实际应用中不加入printf函数
 * @param[in]  chl 通道号
 *              @arg HW_PIT_CH0 
 *              @arg HW_PIT_CH1
 *              @arg HW_PIT_CH2 
 *              @arg HW_PIT_CH3 
 * @param[in]  timeInUs 产生中断的周期 \单位US
 * @retval None
 */
 /*
 
 static void PIT0_CallBack(){
//中断要执行的代码	 
 }
void PIT_QuickInit(uint8_t chl, uint32_t timeInUs);
PIT_ITDMAConfig();
*/

///////////////////////////////////////////////////////////////////////////////////////
/////////////PWM快速初始化//////////////////////////////////////////////////////////////
/* 可用的FTM通道有: */
/*
 FTM0_CH4_PB12   // ftm0 模块 4通道 PB12引脚
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
/* 使用快速初始化 帮助初学者完成必要配置 */
//   FTM_PWM_QuickInit(FTM0_CH3_PA06, kPWM_EdgeAligned, 5000);
    
/* 设置FTM0模块3通道的占空比 */
//    FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH3, 6000); /* 0-10000 对应 0-100% */

/////////////////////////////////////////////////////////////////////////////////////
////////////////ADC快速初始化/////////////////////////////////////////////////////////

/* 可用的 ADC通道及引脚 - 144P*/
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
 * @brief  快速完成AD初始化配置
 * @code
 *    //初始化 ADC0 通道20 引脚DM1 单端 精度 12位
 *    ADC_QuickInit(ADC0_SE20_DM1, kADC_SingleDiff12or13);
 *    //读取AD转换结果
 *    value = ADC_QuickReadValue(ADC0_SE20_DM1);
 * @endcode
 * @param[in]  MAP 快速初始化宏，详见ADC.H文件
 * @param[in]  resolutionMode  转换分辨率设置
 *              @arg kADC_SingleDiff8or9   转换精度为8/9位
 *              @arg kADC_SingleDiff10or11 转换精度为10/11位
 *              @arg kADC_SingleDiff12or13 转换精度为12/13位
 *              @arg kADC_SingleDIff16     转换精度为16位
 * @retval ADC模块号
 */
 
 /*
 
 ADC_QuickInit();
 value = ADC_QuickReadValue();
 
 */
 
 //////////////////////////////////////////////////////////////////////////////////




