#include "adc.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//ADC 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/6
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//定义读取的测量值
#define     POWER_10V           0        //10V电源电压
#define     POWER_12V          1        //12V电源电压     //电池电压
#define     POWER_15V          2        //15V电源电压


#define     Channel_Num     3       //通道数
#define     Sample_Num      30      //样品数
//初始化ADC		
static uint16_t ADC_ConvertedValue[Sample_Num][Channel_Num];

void  ADC1_Init(void)
{    
   ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  DMA_InitTypeDef       DMA_InitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;
NVIC_InitTypeDef   NVIC_InitStructure;
  /* Enable ADCx, DMA and GPIO clocks ****************************************/ 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  

  /* DMA2 Stream0 channel2 configuration **************************************/
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t )&ADC1->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC_ConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = Sample_Num*Channel_Num;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
  DMA_Cmd(DMA2_Stream0, ENABLE);
// 	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /* Configure ADC3 Channel7 pin as analog input ******************************/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);

  /* ADC3 Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 3;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC3 regular channel7 configuration **************************************/
  ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_144Cycles);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 2, ADC_SampleTime_144Cycles);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 3, ADC_SampleTime_144Cycles);

 /* Enable DMA request after last transfer (Single-ADC mode) */
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

  /* Enable ADC3 DMA */
  ADC_DMACmd(ADC1, ENABLE);

  /* Enable ADC3 */
  ADC_Cmd(ADC1, ENABLE);
    ADC_SoftwareStartConv(ADC1);                               //使能或者失能指定的ADC的软件转换启动功能

}				  


	 



/*
********************************************************************************
函数名称：SYSTEM_POWER ReadADCAverageValue(void)
函数功能：实现ADC1值的读取
入口参数：无
出口参数：无
********************************************************************************
*/
SYSTEM_POWER ReadADCAverageValue(void)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t k = 0;
    uint32_t tmp = 0;
    float val0 = 0;
    float val1 = 0;
    float val2 = 0;
    uint16_t  adctemp[Sample_Num][Channel_Num]={0};
    memcpy(adctemp,ADC_ConvertedValue,Sample_Num*Channel_Num*2);
    SYSTEM_POWER power;
    //排序
    for(i = 0; i < Channel_Num; i++)		
    {
        for (j = 1; j < Sample_Num; j++)
        {
            for (k = 0; k < (Sample_Num-j); k++)
            {
                //从小到大排序
                if (adctemp[k][i] > adctemp[k+1][i])
                {
                    tmp = adctemp[k][i];
                    adctemp[k][i] = adctemp[k+1][i];
                    adctemp[k+1][i] = tmp;
                }
            }
        }
    }
    //取中间10位求和   
    for(j = 0; j < Sample_Num/3; j++)	
    {
        val0 = (uint32_t)val0 + adctemp[j+Sample_Num/3][0];
        val1 = (uint32_t)val1 + adctemp[j+Sample_Num/3][0];
        val2 = (uint32_t)val2 + adctemp[j+Sample_Num/3][1];
    }
    //求平均出电压值（根据电路电阻分压得到实际电压）
    power.pc0_adc10_power = (((val0 / 10.0) * 3.3) / 4096.0) / 27.0 * (100.0 + 27.0);   
    power.pc1_adc11_batter = (((val1 / 10.0) * 3.3) / 4096.0) / 1 *  (1 + 3); 
    power.pc2_adc12_power = (((val2 / 10.0) * 3.3) / 4096.0) / 4.7 *  (4.7 + 27); 
    
    return power; 
}
