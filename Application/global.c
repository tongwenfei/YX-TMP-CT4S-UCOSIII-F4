/*******************************************************************************
 *CopyRight Reserved:	
 *Filename：			Global.c
 *Description：     	        定义全局变量
 *Date:
 *Author:		
*******************************************************************************/


#include "global.h"
/******************************定义全局变量******************************/



volatile SYSTEM_TEMP_RH g_TEMP_RH;          //定义全局变量温度
uint8_t Calibration_Ch=0;
uint8_t LCD_BL_State=1;
SYSTEM_CALIBRATION System_Calibration={1.0};
SYSTEM_STORAGE  g_StorageData;
DEFAULT_STORAGE g_DefaultData;
SYSTEM_POWER System_Power;                        //定义电压值读取
uint8_t Power_flag;                            //定义电压源的输入标志
uint8_t Batter_flag;                           //定义电池的输入标志
uint8_t Batter_add;                            //定义电池充电某格标志
uint8_t Batter_add_flag0;                      //定义电池充电0格处理标志
uint8_t Batter_add_flag1;                      //定义电池充电1格处理标志
uint8_t Batter_add_flag2;                      //定义电池充电2格处理标志
uint8_t Batter_add_flag3;                      //定义电池充电3格处理标志
uint8_t Batter_add_flag4;                      //定义电池充电4格处理标志
uint8_t DEBUG_MODE[4];

//TXBUFF TxBuffer;			     //发送缓冲区
//RXBUFF RxBuffer;			     //接收缓冲区
volatile float Ambience_Temp;                 //定义环境温度值
volatile float PT100_Temp[2]={0};                   //定义两个PT100温度值
volatile float MS5611_Temp,MS5611_Press;           //定义气压和温度值
uint8_t PassWd_flag,HW_flag,Data_Flag,Info_flag,Channel_flag,Exit_flag,Main_flag;                            //定义密码设置标志
uint8_t PassWd_last[6],PassWd_old[6],PassWd_new[6],PassWd_rep[6]; //定义密码值
uint8_t PassWd_num[3];
uint8_t key_vaule,DispState_time=0;
uint8_t Time_flag,Uart_flag,Param_flag,Clean_flag,Factory_flag,Updata_flag,Help_flag;


PID_STRUCT FlowPID_struct[4],TempPID_struct;
SAMPLING_STATE Sampling_State[4];
SAMPLING_STATE Calibrate_State[4];
uint8_t Intervals_State[4]={false};
void FloatToUshort(float input,uint16_t *output)
{
    output[0]=*(uint16_t *)&input;
    output[1]=*(((uint16_t *)&input)+1);
}