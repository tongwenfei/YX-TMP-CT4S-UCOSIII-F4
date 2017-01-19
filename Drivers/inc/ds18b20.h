#ifndef __DS18B20_H
#define __DS18B20_H 
#include "target.h"
//IO方向设置

#define DS18B20_IO_IN()  {GPIOA->MODER&=~(3<<(8*2));GPIOA->MODER|=0<<8*2;}	
#define DS18B20_IO_OUT()  {GPIOA->MODER&=~(3<<(8*2));GPIOA->MODER|=1<<8*2;} 
////IO操作函数											   
#define	DS18B20_DQ_OUT PAout(8) //数据端口	PA0 
#define	DS18B20_DQ_IN  PAin(8)  //数据端口	PA0 
   	
uint8_t DS18B20_Init(void);//初始化DS18B20
float DS18B20_Get_Temp(void);//获取温度
void DS18B20_Start(void);//开始温度转换
void DS18B20_Write_Byte(uint8_t dat);//写入一个字节
uint8_t DS18B20_Read_Byte(void);//读出一个字节
uint8_t DS18B20_Read_Bit(void);//读出一个位
uint8_t DS18B20_Check(void);//检测是否存在DS18B20
void DS18B20_Rst(void);//复位DS18B20    
#endif















