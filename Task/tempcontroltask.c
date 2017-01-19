/*
*********************************************************************************************************
*                                               
* File        : TempControlTask.c
* By          : Wenfei Tong
* Version     : V1.0
* Date        : 03-08-2016
* Description :
* ---------------
*   温度控制任务函数,温度范围(15℃~30℃)由PWM控制
*********************************************************************************************************
*/
#include "task.h"
#include "ads1248.h"
#include "global.h"
#include "tempPID.h"
OS_TCB TempControlTaskTCB;
//任务堆栈	
CPU_STK TEMPCONTROL_TASK_STK[TEMPCONTROL_STK_SIZE];
float last_PT100_Temp[2],res[2];
uint8_t testcount[2]={0};
uint32_t ads1248_buf[2]={0};
void TempControlTask(void *pdata)
{
  OS_ERR err;
  pdata=pdata;
  while(1)
  {
    float temp[2]={0};
    
     
     ads1248_buf[0]=ADS1248_ReadADC(TEM1);
     ads1248_buf[1]=ADS1248_ReadADC(TEM2);
	res[0]=ads1248_buf[0]/ 24672.376470588235294117647058824;
	res[1]=ads1248_buf[1]/ 24672.376470588235294117647058824;
     temp[0]=ADS1248_ResToTemp(res[0]);

     temp[1]=ADS1248_ResToTemp(res[1]);
     if(temp[0]>-50)
     {
       PT100_Temp[0]=temp[0];
       if(testcount[0]<5)
       {
	 last_PT100_Temp[0]=PT100_Temp[0];
	 testcount[0]++;
       }
     }
      if(temp[1]>-50)
     {
       PT100_Temp[1]=temp[1];
       if(testcount[1]<5)
       {
	 last_PT100_Temp[1]=PT100_Temp[1];
	 testcount[1]++;
       }
     }
     if(fabs(last_PT100_Temp[0]-PT100_Temp[0])>3)
     {
       
      PT100_Temp[0]=last_PT100_Temp[0];
     }
     if(fabs(last_PT100_Temp[1]-PT100_Temp[1])>3)
     {
      
      PT100_Temp[1]=last_PT100_Temp[1];
     }
     last_PT100_Temp[0]=PT100_Temp[0];
     last_PT100_Temp[1]=PT100_Temp[1];
     
    TEM_Compare(&TempPID_struct,PT100_Temp[0]);
    
   OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
  }
}

void CreateTempControlTask(void)
{
  OS_ERR err;
  OSTaskCreate((OS_TCB 	  *)&TempControlTaskTCB,		//任务控制块
               (CPU_CHAR  *)"TempControl Task", 		//任务名字
               (OS_TASK_PTR)TempControlTask, 			//任务函数
               (void      *)0,					//传递给任务函数的参数
               (OS_PRIO     )TEMPCONTROL_TASK_PRIO,     //任务优先级
               (CPU_STK   * )&TEMPCONTROL_TASK_STK[0],	//任务堆栈基地址
               (CPU_STK_SIZE)TEMPCONTROL_STK_SIZE/10,	//任务堆栈深度限位
               (CPU_STK_SIZE)TEMPCONTROL_STK_SIZE,		//任务堆栈大小
               (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
               (OS_TICK	    )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
               (void      *)0,					//用户补充的存储区
               (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
               (OS_ERR     *)&err);	
}