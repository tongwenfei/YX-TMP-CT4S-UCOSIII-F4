/*******************************************************************************
 *CopyRight Reserved:	
 *Filename：			FM24CL64.c
 *Description：     	        实现对铁电的读写
 *Date:
 *Author:		
*******************************************************************************/

#include "fm24cl64.h"
#include  <os.h>

//命令设置
#define     FM24CL64_Addr     0xae    //定义器件在IIC总线中的从地址，硬件上CSB为高，取反为低


/****************************** FM24CL64B-G 函数定义*****************************/


/*
********************************************************************************
函数名称：void EE_I2C_Start(void) 
函数功能：I2C起始信号
入口参数：无
出口参数：无
********************************************************************************
*/
void EE_I2C_Start(void) 
{ 
    FM24_SDA_OUT();        
    FM24_SET_SDA();
    FM24_SET_SCL();
    Delay_Nus(1);
    FM24_CLR_SDA();
    Delay_Nus(1);
    FM24_CLR_SCL();    
} 

/*
********************************************************************************
函数名称：void EE_I2C_Stop(void)  
函数功能：I2C停止信号
入口参数：无
出口参数：无
********************************************************************************
*/
void EE_I2C_Stop(void) 
{ 
    FM24_SDA_OUT(); 
    FM24_CLR_SDA();
    FM24_SET_SCL();
    Delay_Nus(1);
    FM24_SET_SDA();
    Delay_Nus(1);
} 

/*
********************************************************************************
函数名称：void EE_I2C_SendACK(uint8_t ack) 
函数功能：I2C发送应答信号
入口参数：(0:ACK 1:NAK)
出口参数：无
********************************************************************************
*/
void EE_I2C_SendACK(uint8_t ack)  
{ 
    FM24_SDA_OUT(); 
    if(ack == 1)
    {
        FM24_SET_SDA(); 
    }
    if(ack == 0)
    {
        FM24_CLR_SDA(); 
    }
    FM24_SET_SCL();
    Delay_Nus(1);
    FM24_CLR_SCL();
    Delay_Nus(1);
} 

/*
********************************************************************************
函数名称：uint8_t EE_I2C_RecvACK(void)
函数功能：I2C接收应答信号
入口参数：无
出口参数：返回应答信号
********************************************************************************
*/
uint8_t EE_I2C_RecvACK(void)
{
    uint16_t rn = 0;
    FM24_CLR_SCL();                    //拉低时钟线
    FM24_SDA_IN();
    FM24_SET_SCL();                   //拉高时钟线
    Delay_Nus(1);                   //延时
    while(FM24_GET_SDA())
    {
        rn++;
        if(rn>1000)	  
        {
          return 1; 
        }
    }
    FM24_CLR_SCL();                   //拉低时钟线
    Delay_Nus(1);                  //延时
    return 0;
}
/*
********************************************************************************
函数名称：void EE_I2C_SendByte(uchar dat)
函数功能：I2C写入1字节数据
入口参数：写入的数据
出口参数：无
********************************************************************************
*/
void EE_I2C_SendByte(uint8_t dat)
{
    uint8_t Rn = 8;
    FM24_SDA_OUT(); 
    while(Rn--)
    {
        FM24_CLR_SCL();
        Delay_Nus(1); 
        if (dat & 0x80)
        {
            FM24_SET_SDA();
        }
        else
        {
            FM24_CLR_SDA();
        }
        dat <<= 1;  
        FM24_SET_SCL();
        Delay_Nus(1);
    }
    EE_I2C_RecvACK();
}

/*
********************************************************************************
函数名称：uint8_t EE_I2C_RecvByte (void)
函数功能：I2C接受字节数据
入口参数：无
出口参数：返回接收的数据
********************************************************************************
*/
uint8_t EE_I2C_RecvByte(void)
{
    uint8_t Rn=8,dat=0;
    FM24_SET_SDA();
    FM24_SDA_IN();
    while(Rn--)
    {
        dat <<= 1;
        FM24_CLR_SCL(); 
        Delay_Nus(1);
        FM24_SET_SCL();
        Delay_Nus(1);
        if(FM24_GET_SDA())
        {
            dat++;
        }
    }
    FM24_CLR_SCL(); 
    return dat;
}

/*
********************************************************************************
函数名称：void FM24C64_WRITE_BYTE (uint16_t addr,uint8_t data)
函数功能：向固定地址写入固定数据  （其他EEPROM可能有写时序擦除操作需要注意）
入口参数：addr-地址；0~8191 data-要写入的数据
出口参数：无
********************************************************************************
*/
void FM24C64_WRITE_BYTE (uint16_t addr,uint8_t data)
{ 
    uint8_t SlaveADDR; 
    
     CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();							
    
    SlaveADDR = (uint8_t)(addr >> 8);	         //先写高位
    EE_I2C_Start();
    EE_I2C_SendByte(FM24CL64_Addr); 
    
    EE_I2C_SendByte (SlaveADDR);                 //写高位地址
    EE_I2C_SendByte ((uint8_t)addr);               //写低位地址
    
    EE_I2C_SendByte (data);                      //写入数据
    EE_I2C_Stop(); 
    
CPU_CRITICAL_EXIT();							
}

/*
********************************************************************************
函数名称：void FM24C64_WRITE_MUL(uint16_t StartAddr, uint8_t *RdData, uint16_t Numbers)
函数功能：多地址写入数据（其他EEPROM可能有写时序擦除操作需要注意）
入口参数：StartAddr：铁电起始地址0~8191  *RdData：要写入的数据地址   Numbers：数据个数 
出口参数：无
********************************************************************************
*/
void FM24C64_WRITE_MUL(uint16_t StartAddr, uint8_t *RdData, uint16_t Numbers)
{ 
    uint8_t SlaveADDR;
    
    CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();
    
    SlaveADDR = (uint8_t)(StartAddr >> 8);
    EE_I2C_Start();
    EE_I2C_SendByte(FM24CL64_Addr);         // E2PROM 片选
    EE_I2C_SendByte(SlaveADDR);                  //写高8位地址
    EE_I2C_SendByte(StartAddr);                  //写底8位地址
    while(Numbers--)
    {
        EE_I2C_SendByte(*RdData);
        RdData++;
    }
    EE_I2C_Stop();  
    //退出临界状态
CPU_CRITICAL_EXIT();							//进入中断
}
/*
********************************************************************************
函数名称：uint8_t FM24C64_READ_BYTE (uint16_t addr)
函数功能：向固定地址读出数据（选择地址随意读）
入口参数：addr：读出的地址
出口参数：返回读取地址的数据
********************************************************************************
*/
uint8_t FM24C64_READ_BYTE (uint16_t addr)
{ 
    uint8_t SlaveADDR,DATA_R;
    
    //进入临界状态
    CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();						//进入中断
    
    SlaveADDR = (uint8_t)(addr >> 8);
    EE_I2C_Start();
    EE_I2C_SendByte(FM24CL64_Addr);
    EE_I2C_SendByte(SlaveADDR);
    EE_I2C_SendByte(addr);

    EE_I2C_Start ();
    EE_I2C_SendByte (FM24CL64_Addr+1);
    DATA_R = EE_I2C_RecvByte();
    EE_I2C_SendACK(1);
    EE_I2C_Stop();
    //退出临界状态
    CPU_CRITICAL_EXIT();						//进入中断
    
    return DATA_R;
}

/*
********************************************************************************
函数名称：void FM24C64_READ_MUL(uint16_t StartAddr, uint8_t *RdData, uint16_t Numbers)
函数功能：从固定地址读出多个数据
入口参数：StartAddr-起始地址；RdData-数据存放缓冲区
出口参数：无
********************************************************************************
*/
void FM24C64_READ_MUL(uint16_t StartAddr, uint8_t *RdData, uint16_t Numbers)
{ 
    uint8_t SlaveADDR;
    
    //进入临界状态
    CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();							//进入中断
    
    SlaveADDR=(uint8_t)(StartAddr >> 8);
    EE_I2C_Start();
    EE_I2C_SendByte(FM24CL64_Addr);                //片选
    EE_I2C_SendByte(SlaveADDR);  
    EE_I2C_SendByte(StartAddr);                         //ROM首地址(0-1FFF)
    
    EE_I2C_Start();
    EE_I2C_SendByte(FM24CL64_Addr+1);              //读
    while(Numbers>1)
    {   
        *RdData =EE_I2C_RecvByte();
        EE_I2C_SendACK(0);                              //应答
        Numbers--;   
        RdData++;
    }    
    *RdData =EE_I2C_RecvByte();
    EE_I2C_SendACK(1);                                  //非应答
    EE_I2C_Stop ();
    //退出临界状态
    CPU_CRITICAL_EXIT();						//进入中断
}

/*
********************************************************************************
函数名称：uint8_t FM24C64_Check(void)
函数功能：实现FM24CL64的检测
入口参数：无
出口参数：1：正确   0：错误
********************************************************************************
*/
uint8_t FM24C64_Check(void)
{
    uint16_t ADDRESS;
    uint8_t j,DATAW = 0x55;
    uint8_t DATAR = 0; 
    for(ADDRESS = 0; ADDRESS < 8192; ADDRESS++)
    {
        for(j=0;j<2;j++)                                    //写0xaa和0x55
        {
            FM24C64_WRITE_BYTE(ADDRESS,DATAW);              //写入0x55
            DATAR=FM24C64_READ_BYTE(ADDRESS);               //读出0x55
            if(DATAR!=DATAW)                                //写入和读出的不相同
            {
                return 0;
            }
            DATAW = ~DATAW;                                 //取反写入0xaa，再比较
        }
    }   
    return 1;  
}
/*
********************************************************************************
函数名称：void FM24C64_Init(void)
函数功能：实现SCL的初始化
入口参数：无
出口参数：无
********************************************************************************
*/
void FM24C64_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化TEM2_CS TEM2_START
  
}


///*
//********************************************************************************
//函数名称：void FM24C64_Data_Storage(uint8_t storage_number,uint8_t type)
//函数功能：大气采样器200组数据存储
//入口参数：storage_number：1~200    type:  0,为读操作，1为写操作
//出口参数：无
//********************************************************************************
//*/
//void FM24C64_Data_Storage(uint8_t storage_number,uint8_t type)
//{   
//  
//    if(type == 1)
//    {
//
//       if(storage_number > 80)
//       {
//            storage_number = 1;
//        }
//        FM24C64_WRITE_MUL(STORAGE_NUMBER, (uint8_t*)&storage_number, 1);         //写入现在存储了多少个文件
//        
//       
//        
//        //保存存储区编号
//        FM24C64_WRITE_MUL((STORAGE_START + ((storage_number-1)*100)), (uint8_t*)&g_StorageData, sizeof(g_StorageData));       //存储区编号
//
//    }
//    else
//    {
//        //保存存储区编号
//        FM24C64_READ_MUL((STORAGE_START + ((storage_number-1)*100)), (uint8_t*)&g_StorageData, sizeof(g_StorageData));       //存储区编号
//    }
//
//}