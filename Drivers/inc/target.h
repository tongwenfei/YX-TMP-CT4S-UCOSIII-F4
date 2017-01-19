/*******************************************************************************
*CopyRight Reserved:	
*Filename：			target.c
*Description：     	        实现目标板的初始化
*Date:
*Author:		
*******************************************************************************/
#ifndef __TARGET_H
#define __TARGET_H
#include "sys.h"
#define LED0 PCout(13)

#define     PUMP2_ON()		PEout(5)=1
#define     PUMP2_OFF()		PEout(5)=0

#define     PUMP4_ON()		PEout(4)=1
#define     PUMP4_OFF()		PEout(4)=0

#define     PUMP1_ON()		PEout(3)=1
#define     PUMP1_OFF()		PEout(3)=0

#define     PUMP3_ON()		PEout(2)=1
#define     PUMP3_OFF()		PEout(2)=0
void Delay_100ns(void);
void Delay_Nus(uint32_t t);
void Delay10us(uint32_t m);
void Delayms(uint32_t m);
void LED_Init(void);
void Pump_Init(void);
#endif