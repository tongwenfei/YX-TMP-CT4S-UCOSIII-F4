#include "flow_PID.h"
#include "string.h"
#include "global.h"
/*
********************************************************************************
函数名称：void Flow_PID_Init(PID *pp)
函数功能：实现PID的初始化，空间清零
入口参数：PID结构体
出口参数：无
********************************************************************************
*/
void Flow_PID_Init(PID_STRUCT *pp) 
{ 
  memset(pp,0,sizeof(PID_STRUCT)); 
  pp->SetPoint = 0;			//初始化开度全开
  pp->Proportion = 0.5;      //设置比例系数0.05
  pp->Integral = 0.21;     //设置积分系数0.0003
  pp->Derivative = 0.00;     //设置微分系数0.00
} 
/*
********************************************************************************
函数名称：float Flow_PID_Calculation(PID_STRUCT *pp,float NowPoint) 
函数功能：实现PID的计算
入口参数：PID结构体，NowPoint当前流量
出口参数：返回脉宽系数0~1000

位置式PID控制算法
u(t)=kp[e(t)+1/Ti∫e(t)dt+Td*de(t)/dt]
kp 比例系数	, Ti 控制器的积分时间 , Td 控制器的微分时间。
m(t)=Kp*e(t)+Ki*[e(1)+e(2)+...+e(t)}+Kd{e(t-1)-e(t-2)]
Ki = Kp*T/Ti 为积分系数		Kd = Kp*Td/T 为微分系数
********************************************************************************
*/
float Flow_PID_Calculation(PID_STRUCT *pp,float NowPoint) 
{ 
  //m(t)=Kp*e(n)+Ki*{e(1)+e(2)+...+e(n)}+Kd{e(n-1)-e(n-2)}
  float dError = 0;
  float Error = 0; 
  Error = pp->SetPoint - NowPoint;        //偏差 = 设定流量-当前流量
  pp->SumError += Error;                  //对偏差进行积分叠加
  dError = pp->LastError - pp->PrevError; //微分 = 当前偏差【-1】 - 上一次偏差【-2】 
  pp->PrevError = pp->LastError;          //把当前偏差赋给上一个偏差
  pp->LastError = Error;                  //把
  
  return (pp->Proportion * Error          //比例
          + pp->Integral * pp->SumError           //积分项
            + pp->Derivative * dError);             //微分项 
} 
/*
********************************************************************************
函数名称：void Flow_PWM_Init(void)
函数功能：流量PWM波初始化，TIM3的CH1~CH4(PC6~PC9)
入口参数：无
出口参数：无
********************************************************************************
*/
/*这个是TMP温度控制的PWM引脚*/
void Flow_PWM_Init(void)
{
	//此部分需手动修改IO口设置
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//使能PORTF时钟	
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3); //GPIOF9复用为定时器14
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3); //GPIOF9复用为定时器14
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3); //GPIOF9复用为定时器14
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3); //GPIOF9复用为定时器14
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //初始化PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=6;  //定时器分频
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseStructure.TIM_Period=999;   //自动重装载值
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
  
  
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//初始化定时器14
  
  //初始化TIM3 Channel1 PWM模式	 
 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 4OC1
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
  
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 4OC1
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
  
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 4OC1
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
  
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 4OC1
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
 
  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
  
 
//  TIM_SetCompare1(TIM3,500);
//  TIM_SetCompare2(TIM3,500);
//  TIM_SetCompare3(TIM3,500);
//  TIM_SetCompare4(TIM3,500);
  Flow_PID_Init(&FlowPID_struct[0]);
  Flow_PID_Init(&FlowPID_struct[1]);
  Flow_PID_Init(&FlowPID_struct[2]);
  Flow_PID_Init(&FlowPID_struct[3]);
}
/*
********************************************************************************
函数名称：void Flow_PWM_Config(FLOW_STRUCT *FLOW)
函数功能：PWM为TIM3 Channel1~4  PC6~PC9
入口参数：流量控制结构体指针
出口参数：无
********************************************************************************
*/
/*这个是TMP温度控制的PWM引脚*/
void Flow_PWM_Config(FLOW_STRUCT *FLOW)
{
  TIM_SetCompare1(TIM3,FLOW->Flow_Duty1);
  TIM_SetCompare2(TIM3,FLOW->Flow_Duty2);
  TIM_SetCompare3(TIM3,FLOW->Flow_Duty3);
  TIM_SetCompare4(TIM3,FLOW->Flow_Duty4);
}
