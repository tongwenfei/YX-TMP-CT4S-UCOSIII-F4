/*
*********************************************************************************************************
*                                               
* File        : TempPressPressTask.c
* By          : Wenfei Tong
* Version     : V1.0
* Date        : 03-08-2016
* Description :
* ---------------
*   获取MS5611传感器的气压值和温度值
*********************************************************************************************************
*/
#include "task.h"
#include "ms5611.h"
#include "global.h"
//任务控制块
OS_TCB TempPressTaskTCB;
//任务堆栈	
 CPU_STK TEMPPRESS_TASK_STK[TEMPPRESS_STK_SIZE];
//任务函数
void TempPressTask(void *p_arg);
void TempPressTask(void *pdata)
{
  OS_ERR err;
  pdata=pdata;
  while(1)
  {
   
    MS5611_Temp=MS561101BA_Temperature_Read();  
    MS5611_Press=MS561101BA_Pressure_Read();
   
    
    
     OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
  }
}

void CreateTempPressTask(void)
{
  OS_ERR err;
  OSTaskCreate((OS_TCB 	  *)&TempPressTaskTCB,		//任务控制块
               (CPU_CHAR  *)"TempPress Task", 		//任务名字
               (OS_TASK_PTR)TempPressTask, 			//任务函数
               (void      *)0,					//传递给任务函数的参数
               (OS_PRIO     )TEMPPRESS_TASK_PRIO,     //任务优先级
               (CPU_STK   * )&TEMPPRESS_TASK_STK[0],	//任务堆栈基地址
               (CPU_STK_SIZE)TEMPPRESS_STK_SIZE/10,	//任务堆栈深度限位
               (CPU_STK_SIZE)TEMPPRESS_STK_SIZE,		//任务堆栈大小
               (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
               (OS_TICK	    )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
               (void      *)0,					//用户补充的存储区
               (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
               (OS_ERR     *)&err);	
}