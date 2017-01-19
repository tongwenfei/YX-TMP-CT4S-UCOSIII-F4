/*
********************************************************************************
*CopyRight Reserved:	宇星科技
*Filename：		ds18b20.c
*Description：     DS18B20底层驱动     
*Date:
*Author:		Wenfei Tong
********************************************************************************
*/
#include "ds18b20.h" 
#include "task.h"
 uint8_t Cal_CRC(uint8_t *ptr,uint32_t len)
{
  uint8_t DATA=0,i;
  while(len--)
  {
    DATA^=*ptr++;
    for(i=0;i<8;i++)
    {
      if(DATA&0x01)DATA=(DATA>>1)^0x8C;
      else DATA>>=1;
    }
  }
  return DATA;
}


//复位DS18B20
void DS18B20_Rst(void)	   
{                 
	DS18B20_IO_OUT(); 	//SET PA8 OUTPUT
    DS18B20_DQ_OUT=0; 	//拉低DQ
    Delay_Nus(750);    	//拉低750us
    DS18B20_DQ_OUT=1; 	//DQ=1 
	Delay_Nus(15);     	//15US
}
//等待DS18B20的回应
//返回1:未检测到DS18B20的存在
//返回0:存在
uint8_t DS18B20_Check(void) 	   
{   
	uint8_t retry=0;
	DS18B20_IO_IN();	//SET PA8 INPUT	 
    while (DS18B20_DQ_IN&&retry<200)
	{
		retry++;
		Delay_Nus(1);
	};	 
	if(retry>=200)return 1;
	else retry=0;
    while (!DS18B20_DQ_IN&&retry<240)
	{
		retry++;
		Delay_Nus(1);
	};
	if(retry>=240)return 1;	    
	return 0;
}
//从DS18B20读取一个位
//返回值：1/0
uint8_t DS18B20_Read_Bit(void) 	 
{
    uint8_t data;
     CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();
	DS18B20_IO_OUT();	//SET PA8 OUTPUT
    DS18B20_DQ_OUT=0; 
	Delay_Nus(2);
    DS18B20_DQ_OUT=1; 
	DS18B20_IO_IN();	//SET PA8 INPUT
	Delay_Nus(12);
	if(DS18B20_DQ_IN)data=1;
    else data=0;	 
    Delay_Nus(50);  
    	CPU_CRITICAL_EXIT();	//退出临界区	
    return data;
}
//从DS18B20读取一个字节
//返回值：读到的数据
uint8_t DS18B20_Read_Byte(void)     
{        
    uint8_t i,j,dat;
    dat=0;
 CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();
	for (i=1;i<=8;i++) 
	{
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
        }
	CPU_CRITICAL_EXIT();	//退出临界区	
    return dat;
}
//写一个字节到DS18B20
//dat：要写入的字节
void DS18B20_Write_Byte(uint8_t dat)     
 {             
    uint8_t j;
    uint8_t testb;
    CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();
	DS18B20_IO_OUT();	//SET PA8 OUTPUT;
    for (j=1;j<=8;j++) 
	{
        testb=dat&0x01;
        dat=dat>>1;
        if (testb) 
        {
            DS18B20_DQ_OUT=0;	// Write 1
            Delay_Nus(2);                            
            DS18B20_DQ_OUT=1;
            Delay_Nus(60);             
        }
        else 
        {
            DS18B20_DQ_OUT=0;	// Write 0
            Delay_Nus(60);             
            DS18B20_DQ_OUT=1;
            Delay_Nus(2);                          
        }
    }
    	CPU_CRITICAL_EXIT();	//退出临界区	
}
//开始温度转换
void DS18B20_Start(void) 
{   						               
    DS18B20_Rst();	   
	DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);	// skip rom
    DS18B20_Write_Byte(0x44);	// convert
} 

//初始化DS18B20的IO口 DQ 同时检测DS的存在
//返回1:不存在
//返回0:存在    	 
uint8_t DS18B20_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化TEM2_CS TEM2_START

 	GPIO_SetBits(GPIOA,GPIO_Pin_8);    //输出1

	DS18B20_Rst();

	return DS18B20_Check();
}  
//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值  
float DS18B20_Get_Temp(void)
{

  float value=0;
  uint8_t ptr[9]={0},i=0;
  CPU_SR_ALLOC();
  CPU_CRITICAL_ENTER();
    DS18B20_Start ();  			// ds1820 start convert
    DS18B20_Rst();
    DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);	// skip rom
    DS18B20_Write_Byte(0xbe);	// convert	        
    for(i=0;i<9;i++)
  {
    *(ptr+i)=DS18B20_Read_Byte();
  }
CPU_CRITICAL_EXIT();	//退出临界区	
  //退出临界状态
  
  if(*(ptr+8)==Cal_CRC(ptr,8))
  {
    if(ptr[1] & 0x80)
    {
      
      value = (-1)*((0xffff-((((uint16_t)ptr[1])<<8)+ptr[0]))*0.0625);
    }
    else
    {
      value = ptr[1]*16 + ptr[0]*0.0625;
    }
    return  value;
    
  }
  else return -1111;
}

 
