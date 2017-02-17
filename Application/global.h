/*******************************************************************************
*CopyRight Reserved:	
*Filename：			Global.h
*Description：     	        定义全局变量外部使用
*Date:
*Author:		
*******************************************************************************/

#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include "flow_PID.h"
#include "GUI.H"
//
//#ifdef MAITASK_C
//#define MAINEXT 
//#else
//#define MAINEXT extern
//#endif

//结构体定义
//定义三组温度结构体


typedef struct 
{
  float p_temperature;
  
}SYSTEM_TEMP_RH;



//定义三组温度结构体
typedef struct 
{
  float pc0_adc10_power;           //PB0
  float pc1_adc11_batter;        //PC0
  float pc2_adc12_power;          //PB1
  
}SYSTEM_POWER;
typedef enum
{
  DISCHARGE=0,
  CHARGING=!DISCHARGE
}Charge_State;


/******************************定义铁电存储******************************/
typedef struct
{
  uint8_t  Default_State;
  
  uint8_t  Instrument_Modle[16];
  uint8_t  Channel_N;
  uint16_t Flow_Range;
  uint16_t SW_Version;
  uint16_t HW_Version;
  uint16_t Storage;
  
  uint32_t Baud_Rate;
  uint8_t  Data_Bits;
  uint8_t  Parity_Bits;
  uint8_t  Stop_Bits;
  
  uint8_t  Sys_Year;
  uint8_t  Sys_Month;
  uint8_t  Sys_Data;
  uint8_t  Sys_Week;
  uint8_t  Sys_Hour;
  uint8_t  Sys_Minute;
  uint8_t  Sys_Second;
  float    Sys_RT_Flow[4][11];	
  uint8_t  Sys_PassWord[6];
}DEFAULT_STORAGE;
//定义通讯设置的铁电存储区
#define     DEFAULT                  0x00
#define CALIBRATION_STORAGE_ADD  0x200
//定义文件存储区
#define     STORAGE_NUMBER      0x123             //定义文件的已经使用了的存储号码
#define     STORAGE_START       0x124            //定义文件存储起始位置

extern uint8_t LCD_BL_State;
#define ADVALUE_CNT	30			//每个缓冲区大小
#define ADCHANAL		2			//缓冲区个数
#define ADBUFFLENGHT	ADVALUE_CNT*ADCHANAL	//缓冲区总量大小
extern uint8_t Calibration_Ch;
extern uint8_t Change_Flag;
extern uint8_t Raw_Flag;
//extern OS_EVENT* TP_ValueMbox;		//气压温度值邮箱
//extern OS_EVENT* TEMP_ValueMbox;	//温度值邮箱
//extern OS_EVENT* Vol_ValueMbox;	//温补后测量值
//定义180组大气采样器的数据结构,共需要43个字节存储
typedef struct
{
  //存储区编号
  uint8_t number;                  
  
  //当前时间
  uint8_t now_year;                //设定当前时间---年
  uint8_t now_month;               //设定当前时间---月
  uint8_t now_day;                 //设定当前时间---日
  uint8_t now_hour;                //设定当前时间---时
  uint8_t now_minute;              //设定当前时间---分
  uint8_t now_second;              //设定当前时间---秒
  uint8_t now_week;                //设定当前时间---星期
  
  float pressure;                  //检测的气压值
  
  //温度值
  float heattemp;               //检测的加热区温度值
  float now_temp;               //检测的环境温度值
  float cool_temp;                 //检测的制冷片温度值
  
  //设定的采集时间
  uint16_t sampling_set_minute[4];   			 //设定4通道的采集时间---分
  uint16_t sampling_set_volume[4];   			 //设定4通道的采集体积---毫升
  uint16_t sampling_interval_minute[4];        //设定4通道的间隔采集时间---分
  uint16_t sampling_total_minute[4];           //4通道的累计采集时间---分
  uint16_t sampling_total_volume[4];   		 //4通道的累计采集体积---毫升
  uint8_t  sampling_state[4]; 				 //4通道的采集状态
  uint16_t sampling_set_flow[4];				 //设置4通道采集速率
  
  
  //流量值
  uint16_t  RT_flow[4];            //4通道实时流量值
  
  //采样标况体积值
  float standard_volume[4];      //4通道标况体积
  
}SYSTEM_STORAGE;
typedef struct
{
  double Calibration_Point[4][7]; 
  uint16_t Calibration_Flow[4][4];
}SYSTEM_CALIBRATION;
typedef enum
{
   Stop=0,
   Pause,
   Runing,
   Finish, 
}SAMPLING_STATE;
typedef union 
{
double d;
uint16_t u[4];
}uu;

/******************************全局变量外部声明******************************/




extern SYSTEM_POWER System_Power;                        //定义电压值读取
extern uint8_t Power_flag;                            //定义电压源的输入标志
extern uint8_t Batter_flag;                           //定义电池的输入标志
extern uint8_t Batter_add;                            //定义电池充电某格标志
extern uint8_t Batter_add_flag0;                      //定义电池充电0格处理标志
extern uint8_t Batter_add_flag1;                      //定义电池充电1格处理标志
extern uint8_t Batter_add_flag2;                      //定义电池充电2格处理标志
extern uint8_t Batter_add_flag3;                      //定义电池充电3格处理标志
extern uint8_t Batter_add_flag4;                      //定义电池充电4格处理标志

extern SYSTEM_CALIBRATION System_Calibration;

extern volatile uint8_t Timer_second;                 //定义定时器倒计时，为恢复采样等待
extern uint8_t DEBUG_MODE[4];

extern uint8_t g_Unfinish_Flag;                       //定义未完成标志
//extern TXBUFF TxBuffer;			            //发送缓冲区
//extern RXBUFF RxBuffer;			            //接收缓冲区
extern volatile float Ambience_Temp;                  //环境温度
extern volatile float PT100_Temp[2];                        //PT100温度
extern volatile float      MS5611_Temp,MS5611_Press;           //定义气压和温度值
extern uint8_t key_vaule,DispState_time;
extern uint8_t PassWd_num[3];

extern PID_STRUCT FlowPID_struct[4],TempPID_struct;


extern uint8_t PassWd_flag,HW_flag,Data_Flag,Info_flag,Channel_flag,Exit_flag,Main_flag;                            //定义密码设置标志
extern uint8_t PassWd_last[6],PassWd_old[6],PassWd_new[6],PassWd_rep[6]; //定义密码值
extern uint8_t Time_flag,Uart_flag,Param_flag,Clean_flag,Factory_flag,Updata_flag,Help_flag;
extern uint32_t Definite_Count[4];
extern SYSTEM_STORAGE g_StorageData;
extern DEFAULT_STORAGE g_DefaultData;
extern SAMPLING_STATE Sampling_State[4];
extern SAMPLING_STATE Calibrate_State[4];
extern uint8_t Intervals_State[4];
/******************************ucos相关定义******************************/
void FloatToUshort(float input,uint16_t *output);


#endif
