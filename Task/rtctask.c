/*******************************************************************************
 *CopyRight Reserved:	
 *Filename：			rtctask.c
 *Description：     	        实时时钟任务
 *Date:
 *Author:		
*******************************************************************************/

#include"task.h"
#include "ds1302.h"
//任务控制块
OS_TCB RTCTaskTCB;
//任务堆栈	
 CPU_STK RTC_TASK_STK[RTC_STK_SIZE];
//任务函数
void RTCTask(void *p_arg);
/*
********************************************************************************
函数名称：void RTCTask(void *pdata)
函数功能：RTC任务函数
入口参数：无
出口参数：无
********************************************************************************
*/
void RTCTask(void *pdata)
{
   OS_ERR err;
    pdata=pdata;
    while(1)
    {
       // g_RTCTime = PCF8563_Read_Time(); 
      Ds1302_Read_Time();//读取时间
      OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
    }
}

/*
********************************************************************************
函数名称：void CreateRTCTask(void)
函数功能：创建温度气压任务函数
入口参数：无
出口参数：无
********************************************************************************
*/
void CreateRTCTask(void)
{
     OS_ERR err;
  OSTaskCreate((OS_TCB 	  *)&RTCTaskTCB,		//任务控制块
               (CPU_CHAR  *)"RTC Task", 		//任务名字
               (OS_TASK_PTR)RTCTask, 			//任务函数
               (void      *)0,					//传递给任务函数的参数
               (OS_PRIO     )RTC_TASK_PRIO,     //任务优先级
               (CPU_STK   * )&RTC_TASK_STK[0],	//任务堆栈基地址
               (CPU_STK_SIZE)RTC_STK_SIZE/10,	//任务堆栈深度限位
               (CPU_STK_SIZE)RTC_STK_SIZE,		//任务堆栈大小
               (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
               (OS_TICK	    )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
               (void      *)0,					//用户补充的存储区
               (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
               (OS_ERR     *)&err);	

}