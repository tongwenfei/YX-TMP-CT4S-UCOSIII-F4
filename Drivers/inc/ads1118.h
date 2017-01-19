#ifndef __ADS1118_H
#define __ADS1118_H
#include "target.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//SPI驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
#define SET_ADS_CS1()    GPIO_SetBits(GPIOD,GPIO_Pin_8)
#define CLR_ADS_CS1()    GPIO_ResetBits(GPIOD,GPIO_Pin_8)

#define SET_ADS_CS2()    GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define CLR_ADS_CS2()    GPIO_ResetBits(GPIOB,GPIO_Pin_12)

#define ADS1118_SCK_H()  GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define ADS1118_SCK_L()  GPIO_ResetBits(GPIOB,GPIO_Pin_13)

#define ADS1118_MOSI_H() GPIO_SetBits(GPIOB,GPIO_Pin_15)
#define ADS1118_MOSI_L() GPIO_ResetBits(GPIOB,GPIO_Pin_15)

#define ADS1118_DO_PIN() GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)
typedef enum 
{
  FLOW_ADC,
  CURRENT_ADC
}ADS1118_type;
typedef enum 
{
  ADC_CH1,
  ADC_CH2,
  ADC_CH3,
  ADC_CH4
}ADS1118_CH; 	 				  	    													  
void SPI2_Init(void);			 //初始化SPI口

uint8_t SPI2_ReadWriteByte(uint8_t TxData);//SPI总线读写一个字节
uint32_t ADS1118_ReadWord(void);
uint16_t ADS1118_ReadWriteReg(uint16_t reg);
uint16_t ADS118_Convert(ADS1118_type adc,ADS1118_CH adc_ch);
float Get_Avg(ADS1118_type adc,ADS1118_CH adc_ch);
float Filter(ADS1118_type adc,ADS1118_CH ch) ;
#endif