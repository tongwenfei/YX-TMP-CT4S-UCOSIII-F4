/*******************************************************************************
*CopyRight Reserved:	
*Filename：			DS1302.c
*Description：     	        实现对实时时钟的读写
*Date:
*Author:		
*******************************************************************************/
#include "ds1302.h"
#include "os.h"
Time_Typedef TimeValue = {16,4,19,2,11,27,25};
u8 ascii_time[7] = {0}; 	//保存ascii格式数据

u8 bcd_time[7] = {0};		//保存bcd码数据

static u8 AsciiToBcd(u8 asciiData)
{
  u8 bcdData = 0;
  bcdData = (((asciiData/10)<<4)|((asciiData%10)));
  return bcdData;
}
static u8 BcdToAscii(u8 bcdData)
{
  u8 asciiData = 0;
  asciiData = (((bcdData&0xf0)>>4)*10 + (bcdData&0x0f));
  return asciiData;
}

//IO口初始化
void Ds1302_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE, ENABLE);
  
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化TEM2_CS TEM2_START
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化TEM2_CS TEM2_START
  //CLK
 // Ds1302_Write(RAM_Address29+1,0x55);
  
  
}

//读取一个字节的时序
u8 Ds1302_ReadByte(void)
{
  u8 i = 0, dat = 0;
  DS1302_DAT_INPUT();
  delay_us(5);
   CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();
  for(i = 0; i <8; i++)
  {
    dat >>= 1;
    if(DS1302_DATIN == 1)dat |= 0x80;
    DS1302_CLK = 1;
    delay_us(2);
    DS1302_CLK = 0;
    delay_us(2);
  }
   CPU_CRITICAL_EXIT();
  return dat;
}

//写入一个字节的时序
void Ds1302_WriteByte(u8 dat)
{
  u8 i = 0, data = dat;
  DS1302_DAT_OUTPUT(); 
  DS1302_CLK = 0;
  delay_us(2);
   CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();
  for(i = 0; i < 8; i++)
  {
    DS1302_DATOUT = data&0x01;
    delay_us(2);
    DS1302_CLK = 1;
    delay_us(2);
    DS1302_CLK = 0;
    data >>= 1;
  }
   CPU_CRITICAL_EXIT();
}

//写入一个寄存器
void Ds1302_Write(u8 address,u8 dat)
{
  DS1302_RST = 0;
  DS1302_CLK = 0;
  DS1302_RST = 1;
  Ds1302_WriteByte(address);
  Ds1302_WriteByte(dat);
  DS1302_CLK = 1;
  DS1302_RST = 0;
}

//单个写入时间
void Ds1302_Write_Time_Singel(u8 address,u8 dat)
{
  DS1302_WP_Disable();	//取消写保护
  Ds1302_Write(address,dat);
  DS1302_WP_Enable();	//打开写保护
}

//一次完成所有时间更新
//start当前时钟运行还是停止
void Ds1302_Time_Init(void)
{
  Ds1302_GPIO_Init();
  DS1302_WP_Disable();		//取消写保护
  Ds1302_Write((0xc0|0x3c),0x55) ;
  Ds1302_Write(Address_second,(AsciiToBcd(TimeValue.second)|1));
  Ds1302_Write(Address_minute,AsciiToBcd(TimeValue.minute));
  Ds1302_Write(Address_hour,AsciiToBcd(TimeValue.hour));
  Ds1302_Write(Address_date,AsciiToBcd(TimeValue.date));
  Ds1302_Write(Address_month,AsciiToBcd(TimeValue.month));
  Ds1302_Write(Address_week,AsciiToBcd(TimeValue.week));
  Ds1302_Write(Address_year,AsciiToBcd(TimeValue.year));
  DS1302_WP_Enable();	//打开写保护
}


//读取一个字节
u8 Ds1302_Read(u8 address)
{
  u8 data = 0;
  DS1302_RST = 0;
  DS1302_CLK = 0;
  DS1302_RST = 1;
  Ds1302_WriteByte(address|0x01); //读取地址需要与0x01相或，最低为变成1
  data = Ds1302_ReadByte();
  DS1302_CLK = 1;
  DS1302_RST = 0;
  return data;
}

void Ds1302_Set_Time(Time_Typedef *time)
{
  DS1302_WP_Disable();		//取消写保护
  Ds1302_Write(Address_second,(AsciiToBcd(time->second)|1));
  Ds1302_Write(Address_minute,AsciiToBcd(time->minute));
  Ds1302_Write(Address_hour,AsciiToBcd(time->hour));
  Ds1302_Write(Address_date,AsciiToBcd(time->date));
  Ds1302_Write(Address_month,AsciiToBcd(time->month));
  Ds1302_Write(Address_week,AsciiToBcd(time->week));
  Ds1302_Write(Address_year,AsciiToBcd(time->year));
  DS1302_WP_Enable();	//打开写保护
}
//读取时间的时候默认让时间走起来
void Ds1302_Read_Time(void)
{
  TimeValue.second = BcdToAscii(Ds1302_Read(Address_second));  //秒
  TimeValue.minute = BcdToAscii(Ds1302_Read(Address_minute));  //分
  TimeValue.hour = BcdToAscii(Ds1302_Read(Address_hour));	//小时
  TimeValue.date = BcdToAscii(Ds1302_Read(Address_date)); //日
  TimeValue.month = BcdToAscii(Ds1302_Read(Address_month)); //月
  TimeValue.week = BcdToAscii(Ds1302_Read(Address_week));	//星期几
  TimeValue.year = BcdToAscii(Ds1302_Read(Address_year)); //年
}

u8 DS1302_Check(void)
{
  u8 test_value;
  
  
  test_value = Ds1302_Read(RAM_Address29 + 1);	//读出最后一个RAM地址里的数据
  
  if(0x55 == test_value)	//判断数据是否对
  {
    return 0;	//设备正常，不是第一次上电
  }
  else return 1;	//不是第一次上电或者设备异常		
  
  
}

/******************************************************************************
* Function Name --> 主电源对备用电池充电设置
* Description   --> 如果备用电池接的是可充电的锂电池或者其他可充电电池的时候，
*                   可以打开DS1302的充电电路，利用主供电对电池进行充电，免的换电池的麻烦
* Input         --> *CHG_dat：寄存器控制指针
* Output        --> none
* Reaturn       --> none
******************************************************************************/
void DS1302_Charge_Manage(Charge_Typedef* CHG_dat)
{
	u8 CHG_Value;

    CHG_Value = (CHG_dat->TCSx << 4) | (CHG_dat->DSx << 2) | CHG_dat->RSx;  

	DS1302_WP_Disable();	//取消写保护
	Ds1302_Write(Trickle_Charger_Address,CHG_Value);
	DS1302_WP_Enable();	//打开写保护
}

 /******************************************************************************
* Function Name --> DS1302内置的RAM读写操作
* Description   --> none
* Input         --> *pBuff：读写数据存放区
*                   WRadd：读写起始地址，范围在RAM_Address0 ~ RAM_Address28之间，最后一位地址有其他用途
*                   num：读写字节数据的数量，范围在1 ~ 28之间
*                   RW：读写判断位。0x00为写操作，0x01为读操作
* Output        --> none
* Reaturn       --> none
******************************************************************************/
void DS1302_RAM_WriteRead_Data(u8* pBuff,u8 WRadd,u8 num,u8 RW)
{															 
	u8 i;	

	if(WRadd == RAM_Address29)	return;	//要写入数据的RAM地址是最后一个，直接退出
										//因为最后一个字节是用来检测DS1302的
	if(RW == 0x00)	//写数据操作
	{
		for(i = 0;i < num;i++)
		{
			DS1302_WP_Disable();	//取消写保护
			Ds1302_Write(WRadd+(i<<1),pBuff[i]);
			DS1302_WP_Enable();	//打开写保护
		}
	}
	else
	{
		for(i = 0;i < num;i++)
		{
			DS1302_WP_Disable();	//取消写保护
			pBuff[i] = Ds1302_Read(WRadd+1+(i<<1));
			DS1302_WP_Enable();	//打开写保护
		}
	}
}
