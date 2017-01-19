#include "target.h"


void Delay_100ns(void)  
{
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    
}
void Delay_Nus(uint32_t t)  
{  
  while(t--)
  {
    
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
     __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
     __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
    __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
     __no_operation();__no_operation();__no_operation();__no_operation();__no_operation();__no_operation();
  }
}  
/*
********************************************************************************
函数名称：void Delay10us(int32u m)   
函数功能：实现延时10us
入口参数：m  
出口参数：无
********************************************************************************
*/
void Delay10us(uint32_t m)        
{
  uint32_t j;
  uint32_t i;
  for(i=0; i<m; i++)
  {
    for(j=0; j<256; j++)
    {
      
      __no_operation();
    }
  }
}

/*
********************************************************************************
函数名称：void  Delayms(int32u m)    
函数功能：实现延时1ms
入口参数：m  
出口参数：无
********************************************************************************
*/
void Delayms(uint32_t m)       
{
  uint32_t i;   
  for(i=0; i<m; i++)
  {
    Delay10us(101);
  }
}
void LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*
********************************************************************************
函数名称：void Pump_IOinit(void)  
函数功能：实现气泵IO的初始化
入口参数：无 
出口参数：无
********************************************************************************
*/
void Pump_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);
}
