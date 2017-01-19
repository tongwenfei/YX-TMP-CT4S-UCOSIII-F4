/*******************************************************************************
 *CopyRight Reserved:	
 *Filename£º			MS561101BA.h
 *Description£º     	        °åµ×²ã¾øÑ¹²âÁ¿Çý¶¯ 
 *Date:
 *Author:		
*******************************************************************************/

#ifndef __MS5611_H__
#define __MS5611_H__
#include "target.h"
#define PRESS_SDA_IN()  	      {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=0<<7*2;}	
#define PRESS_SDA_OUT()       {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=1<<7*2;}
#define PRESS_SET_SDA()       (PBout(7)=1)
#define PRESS_CLR_SDA()       (PBout(7)=0)
#define PRESS_GET_SDA()       PBin(7)
#define PRESS_SET_SCL()       (PBout(6)=1)
#define PRESS_CLR_SCL()       (PBout(6)=0)
/**********************º¯Êý²¿·Ö*****************************/

extern void MS561101BA_Init(void);
extern float MS561101BA_Pressure_Read(void);
extern float MS561101BA_Temperature_Read(void);




#endif