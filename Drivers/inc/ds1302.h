/*******************************************************************************
 *CopyRight Reserved:	
 *Filename：			Ds1302.h
 *Description：     	        实现对实时时钟的读写
 *Date:
 *Author:		
*******************************************************************************/

#ifndef __DS1302_H
#define __DS1302_H
#include "target.h"
#include "delay.h"


extern u8 ascii_time[7];     //保存ascii格式数据

extern u8 bcd_time[7];       //保存bcd码数据


#define DS1302_RST      PEout(1)
#define DS1302_CLK      PBout(9)
#define DS1302_DATIN    PEin(0)
#define DS1302_DATOUT   PEout(0)


#define DS1302_DAT_INPUT()  {GPIOE->MODER&=~(3<<(0*2));GPIOE->MODER|=0<<0*2;}	
#define DS1302_DAT_OUTPUT()  {GPIOE->MODER&=~(3<<(0*2));GPIOE->MODER|=1<<0*2;} 



/******************************************************************************
                                 定义时间结构
******************************************************************************/

typedef struct
{
	uint16_t year;	//年
	uint8_t month;	//月
	uint8_t date;	//日
	uint8_t week;	//星期
	uint8_t hour;	//小时
	uint8_t minute;	//分钟
	uint8_t second;	//秒钟 
}Time_Typedef;

extern Time_Typedef TimeValue;	//定义时间数据缓存

#define test_data				0x55	//此数据用来检测DS1302是否存在于总线上用，可以改用其他值

/******************************************************************************
                                定义相关命令宏
******************************************************************************/

#define Clock_Address_Bass		0x80	//基地址

#define Address_year			(Clock_Address_Bass | 0x0c)	//年
#define Address_month			(Clock_Address_Bass | 0x08)	//月
#define Address_date			(Clock_Address_Bass | 0x06)	//日
#define Address_week			(Clock_Address_Bass | 0x0a)	//星期
#define Address_hour			(Clock_Address_Bass | 0x04)	//小时
#define Address_minute			(Clock_Address_Bass | 0x02)	//分钟
#define Address_second			(Clock_Address_Bass | 0x00)	//秒

#define Clock_Burst				(Clock_Address_Bass | 0x3e)	//时钟软复位

//写保护寄存器
#define Address_WP				(Clock_Address_Bass | 0x0e)	//写保护

#define WP_Enable				0x80	//打开写保护
#define WP_Disable				0x00	//关闭写保护

/******************************************************************************
电源管理寄存器位描述
    bit7  bit6  bit5  bit4  bit3  bit2  bit1  bit0
	TCS3  TCS2  TCS1  TCS0   DS1   DS0   RS1   RS0

	TCSx：充电电流大小选择，值为0xa0时打开充电，其他值时关闭，DS1302默认是关闭的
	DSx：设置VCC1和VCC2之间的二极管串联数量，0x01时为串联一只二极管，0x10时为串联两只二极管，0x00或0x11时关闭充电功能
	RSx：设置限流电阻大小，0x00为开路并关闭充电功能，0x01为2K，0x10为4K，0x11为8K
******************************************************************************/
//充电管理寄存器结构
typedef struct
{
	uint8_t TCSx;	//充电开关
	uint8_t DSx;	//串联二极管
	uint8_t RSx;	//限流电阻 
}Charge_Typedef;

extern Charge_Typedef ChargeValue;	//定义充电寄存器

//电源管理
#define Trickle_Charger_Address	(Clock_Address_Bass | 0x10)	//管理电源，主电源供电时可以设置给备用电池充电

#define Open_Trickle_Charge		0x0a
#define Close_Trickle_Charge	0x00	//设置为其他值也可以

#define One_Diode				0x01
#define Two_Diode				0x10
#define None_Diode				0x00	//or 0x11，断开串联并关闭充电功能

#define Resistor_For2K			0x01
#define Resistor_For4K			0x10
#define Resistor_For8K			0x11
#define None_Resistor			0x00	//断开串联限流电阻并关闭充电功能


//RAM地址
#define RAM_Address_Bass		0xc0	//基地址

#define RAM_Address0			(RAM_Address_Bass | 0x00)	//RAM地址 = 基地址 + 地址偏移量
#define RAM_Address1			(RAM_Address_Bass | 0x02)
#define RAM_Address2			(RAM_Address_Bass | 0x04)
#define RAM_Address3			(RAM_Address_Bass | 0x06)
#define RAM_Address4			(RAM_Address_Bass | 0x08)
#define RAM_Address5			(RAM_Address_Bass | 0x0a)
#define RAM_Address6			(RAM_Address_Bass | 0x0c)
#define RAM_Address7			(RAM_Address_Bass | 0x0e)

#define RAM_Address8			(RAM_Address_Bass | 0x10)
#define RAM_Address9			(RAM_Address_Bass | 0x12)
#define RAM_Address10			(RAM_Address_Bass | 0x14)
#define RAM_Address11			(RAM_Address_Bass | 0x16)
#define RAM_Address12			(RAM_Address_Bass | 0x18)
#define RAM_Address13			(RAM_Address_Bass | 0x1a)
#define RAM_Address14			(RAM_Address_Bass | 0x1c)
#define RAM_Address15			(RAM_Address_Bass | 0x1e)

#define RAM_Address16			(RAM_Address_Bass | 0x20)
#define RAM_Address17			(RAM_Address_Bass | 0x22)
#define RAM_Address18			(RAM_Address_Bass | 0x24)
#define RAM_Address19			(RAM_Address_Bass | 0x26)
#define RAM_Address20			(RAM_Address_Bass | 0x28)
#define RAM_Address21			(RAM_Address_Bass | 0x2a)
#define RAM_Address22			(RAM_Address_Bass | 0x2c)
#define RAM_Address23			(RAM_Address_Bass | 0x2e)

#define RAM_Address24			(RAM_Address_Bass | 0x32)
#define RAM_Address25			(RAM_Address_Bass | 0x34)
#define RAM_Address26			(RAM_Address_Bass | 0x36)
#define RAM_Address27			(RAM_Address_Bass | 0x38)
#define RAM_Address28			(RAM_Address_Bass | 0x3a)
#define RAM_Address29			(RAM_Address_Bass | 0x3c)

#define RAM_BURST				(RAM_Address_Bass | 0x3e)


//写秒为00并启动时钟
#define DS1302_Start_Second()	(Ds1302_Write(Address_second,0x00))

//写保护命令
#define	DS1302_WP_Enable()		(Ds1302_Write(Address_WP,WP_Enable))	//打开写保护
#define	DS1302_WP_Disable()		(Ds1302_Write(Address_WP,WP_Disable))	//关闭写保护

//关闭充电功能，可以直接调用
#define DS1302_Disable_Charge()	(Ds1302_Write(Trickle_Charger_Address,0x00))

/******************************************************************************
                                 外部功能函数
******************************************************************************/



void Ds1302_GPIO_Init(void);
void Ds1302_Time_Init(void);
void Ds1302_Read_Time(void);
  u8 DS1302_Check(void);
void Ds1302_Set_Time(Time_Typedef *time);
void Ds1302_Write(u8 address,u8 dat);

#endif






