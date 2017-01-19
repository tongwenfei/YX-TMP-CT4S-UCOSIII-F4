 /*
 *CopyRight Reserved:	宇星科技
 *Filename：		adtask.c
 *Description：     	AD采集任务         
 *Date:
 *Author:				
*/

#include "task.h"
#include "port.h"
#include "mb.h"
#include "global.h"
//任务控制块
OS_TCB MODBUSTaskTCB;
//任务堆栈	
 CPU_STK MODBUS_TASK_STK[MODBUS_STK_SIZE];
//任务函数
void MODBUSTask(void *p_arg);



void MODBUSTask(void *pdata)
{
   OS_ERR err;
  pdata=pdata;
  while(1)
  {
    
    eMBPoll(); 
//    usRegAd_VauleBuf[0]=*(uint16_t *)&testfloat[0];
//    usRegAd_VauleBuf[1]=*(((uint16_t *)&testfloat[0])+1);
    OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
  }
}

void CreateMODBUSTask(void)
{
   OS_ERR err;
  OSTaskCreate((OS_TCB 	  *)&MODBUSTaskTCB,		//任务控制块
               (CPU_CHAR  *)"MODBUS Task", 		//任务名字
               (OS_TASK_PTR)MODBUSTask, 			//任务函数
               (void      *)0,					//传递给任务函数的参数
               (OS_PRIO     )MODBUS_TASK_PRIO,     //任务优先级
               (CPU_STK   * )&MODBUS_TASK_STK[0],	//任务堆栈基地址
               (CPU_STK_SIZE)MODBUS_STK_SIZE/10,	//任务堆栈深度限位
               (CPU_STK_SIZE)MODBUS_STK_SIZE,		//任务堆栈大小
               (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
               (OS_TICK	    )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
               (void      *)0,					//用户补充的存储区
               (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
               (OS_ERR     *)&err);				//存放该函数错误时的返回值
}
















