/*
*********************************************************************************************************
*                                               
* File        : TemTask.c
* By          : Wenfei Tong
* Version     : V1.0
* Date        : 03-08-2016
* Description :
* ---------------
*   温度控制任务函数,温度范围(15℃~30℃)由PWM控制
*********************************************************************************************************
*/
#include "task.h"
#include "ds18b20.h"
#include "global.h"
#include "ads1118.h"
//任务控制块
OS_TCB TempTaskTCB;
//任务堆栈	
 CPU_STK TEMP_TASK_STK[TEMP_STK_SIZE];
//任务函数
void TempTask(void *p_arg);
float curr_data;


void TempTask(void *pdata)
{
   OS_ERR err;
  pdata=pdata;
  while(1)
  {
    Ambience_Temp=DS18B20_Get_Temp();//测量当前温度
    
    
    //curr_data=Filter(CURRENT_ADC,ADC_CH4);
    OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
  }
}

void CreateTempTask(void)
{
   OS_ERR err;
  OSTaskCreate((OS_TCB 	  *)&TempTaskTCB,		//任务控制块
               (CPU_CHAR  *)"Temp Task", 		//任务名字
               (OS_TASK_PTR)TempTask, 			//任务函数
               (void      *)0,					//传递给任务函数的参数
               (OS_PRIO     )TEMP_TASK_PRIO,     //任务优先级
               (CPU_STK   * )&TEMP_TASK_STK[0],	//任务堆栈基地址
               (CPU_STK_SIZE)TEMP_STK_SIZE/10,	//任务堆栈深度限位
               (CPU_STK_SIZE)TEMP_STK_SIZE,		//任务堆栈大小
               (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
               (OS_TICK	    )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
               (void      *)0,					//用户补充的存储区
               (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
               (OS_ERR     *)&err);				//存放该函数错误时的返回值
}