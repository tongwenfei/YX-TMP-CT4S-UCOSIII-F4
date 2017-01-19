/*
*********************************************************************************************************                                              
* File        : PID.c
* By          : Wenfei Tong
* Version     : V1.0
* Date        : 03-08-2016
* Description :
* ---------------
*   PID控制函数，包括流量PID控制调节函数、PWM函数
*********************************************************************************************************
*/
#include "tempPID.h"
#include "global.h"
#include <string.h>
/*
********************************************************************************
函数名称：void TEM_PID_ReSet(PID_STRUCT *pp)
函数功能：实现PID的，空间清零
入口参数：PID结构体
出口参数：无
********************************************************************************
*/
void TEM_PID_ReSet(PID_STRUCT *pp) 
{ 
  memset(pp,0,sizeof(PID_STRUCT));     
}
/*
********************************************************************************
函数名称：void TEM_PID_Configuration(PID_STRUCT *pp,float goal,float P,float I,float D)
函数功能：实现PID的初始化配置
入口参数：PID结构体，goal目标温度，参数P、I、D（比例系数、积分系数、积分系数）
出口参数：无
********************************************************************************
*/
void TEM_PID_Configuration(PID_STRUCT *pp)
{
  pp->SetPoint = 20;			//初始化开度全开
  pp->Proportion = 10;      //设置比例系数0.05
  pp->Integral = 0.5;     //设置积分系数0.0003
  pp->Derivative = 0;     //设置积分系数0.00
}
/*
********************************************************************************
函数名称：float TEM_PID_Calculation(PID_STRUCT *pp,float NowTem)  
函数功能：实现PID的计算
入口参数：PID结构体,NowTem当前测量的温度
出口参数：返回占空比系数0~1

增量式PID控制算法
m(t)=Kp*e(t-1)+Ki*[e(1)+e(2)+...+e(t)}+Kd{e(t-1)-e(t-2)]
Ki = Kp*T/Ti 为积分系数		Kd = Kp*Td/T 为微分系数
PID参数要调节好以保证输出占空比系数0-1
********************************************************************************
*/
float TEM_PID_Calculation(PID_STRUCT *pp,float NowTem) 
{ 
  //m(t)=Kp*e(n)+Ki*{e(1)+e(2)+...+e(n)}+Kd{e(n-1)-e(n-2)}
  float Error = 0; 
  Error = (pp->SetPoint - NowTem)*100;        //偏差 = 设定流量-当前流量
  pp->Value=pp->Proportion *(Error-pp->LastError)\
    +pp->Integral * Error\
      +pp->Derivative *(Error-2*pp->LastError+pp->PrevError);
  pp->PrevError = pp->LastError;          //把当前偏差赋给上一个偏差
  pp->LastError = Error;                  //把
  
  return (pp->Value);             
} 

/*
********************************************************************************
函数名称：void TEM_PWM_Init(void)
函数功能：实现TIM2的CH1（PA8）和CH2(PA9)通道输出PWM波，控制加热制冷
入口参数：无
出口参数：无
********************************************************************************
*/
void TEM_PWM_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2  , ENABLE);  
  
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM2); //GPIOF9复用为定时器14
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM2); //GPIOF9复用为定时器14
  
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;           //GPIOF9
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
  GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
  
  
  
  TIM_TimeBaseStructure.TIM_Prescaler=83;  //定时器分频
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseStructure.TIM_Period=999;   //自动重装载值
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
  
  
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//初始化定时器14
  
  //初始化TIM2 Channel1 PWM模式	 
 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 4OC1
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2在CCR1上的预装载寄存器
  
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 4OC1
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2在CCR1上的预装载寄存器
  
  TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPE使能 
  
  TIM_Cmd(TIM2, ENABLE);
  TEM_PID_Configuration(&TempPID_struct);
}
/*
********************************************************************************
函数名称：void TEM_SetDuty(uint8_t state,uint16_t duty)
函数功能：实现PWM波的脉宽设置，配合PID控制温度
入口参数：state 0:默认加热功能； 1：制冷功能; duty:0~1000对应0‰ ~ 1000‰占空比
出口参数：无
********************************************************************************
*/
void TEM_SetDuty(uint8_t state,uint16_t duty)
{
  if(state)
  {
    TIM_SetCompare3(TIM2,0);
    TIM_SetCompare4(TIM2,duty);
  }
  else 
  {
    TIM_SetCompare4(TIM2,0);
    TIM_SetCompare3(TIM2,duty);
  }
}
/*
********************************************************************************
函数名称：void TEM_PWM_ReSet(void)
函数功能：关闭温度控制功能
入口参数：无
出口参数：无
********************************************************************************
*/
void TEM_PWM_ReSet(void)
{
  TIM_SetCompare4(TIM2,0);
  TIM_SetCompare3(TIM2,0);
}
/*
********************************************************************************
函数名称：void TEM_Compare(PID_STRUCT *pp,float NowTem)
函数功能：设定温度和测量温度进行比较，然后经过PID计算后转化为PWM的脉宽
入口参数：PID结构体，测量温度
出口参数：无
********************************************************************************
*/
void TEM_Compare(PID_STRUCT *pp,float NowTem)
{
  
  //static uint8_t pid_flag=0;
  if((pp->SetPoint-NowTem)>1)                                 //环境温度低于设定温度3℃以上，满载加热
  {
    TEM_SetDuty(HOT,1000);
  }
  else if((NowTem-pp->SetPoint)>1)                            //环境温度高于设定温度3℃以上，满载制冷
  {
    TEM_SetDuty(COOL,1000);
  }
  else if(((pp->SetPoint-NowTem)<=1)&&\
    ((pp->SetPoint-NowTem)>=0.2)) //环境温度低于设定温度1℃~7℃以内，PID调节加热
  {
    TEM_PID_Calculation(pp,NowTem);
    //   if(pp->Value>1)temp_data=1;
    //    else if(pp->Value<0)temp_data=0;
    //    else temp_data=pp->Value;
    TEM_SetDuty(HOT,(uint16_t)(250+250*pp->Value));
  }
  else if(((NowTem-pp->SetPoint)<=1)&&\
    ((NowTem-pp->SetPoint)>=0.2)) //环境温度高于设定温度1℃~7℃以内，PID调节制冷
  {
    TEM_PID_Calculation(pp,NowTem);
    //    if(pp->Value>1)temp_data=1;
    //    else if(pp->Value<0)temp_data=0;
    //    else temp_data=pp->Value;
    TEM_SetDuty(COOL,(uint16_t)(750+250*pp->Value));
  }
  else if(((NowTem-pp->SetPoint)<0.2)&&((NowTem-pp->SetPoint)>-0.2))   //环境温度高于设置温度1℃内恒温控制（持续微弱制冷）
  {
    TEM_SetDuty(COOL,CONST_COOL);
  }
  else if(((pp->SetPoint-NowTem)<0.2)&&((pp->SetPoint-NowTem)>-0.2))   //环境温度低于设置温度1℃内恒温控制（持续微弱制热）
  {
    TEM_SetDuty(HOT,CONST_HOT);
  }
  else   TEM_PWM_ReSet();                                          //停止制冷制热
  
}