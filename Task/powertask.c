/*******************************************************************************
*CopyRight Reserved:	
*Filename：			powertask.C
*Description：     	        电源任务
*Date:
*Author:		
*******************************************************************************/

#include "include.h"

/*
********************************************************************************
函数名称：void POWERTask(void *pdata)
函数功能：POWER任务函数
入口参数：无
出口参数：无
********************************************************************************
*/
void POWERTask(void *pdata)
{
  
  pdata=pdata;
  while(1)
  {  
    System_Power=ReadADCAverageValue();
    //判断有无电源
    if(System_Power.pc1_adc11_power > 14)
    {
      Power_flag = 1;           //电源存在标志
    }
    else
    {
      Power_flag = 0;
    }
    if(System_Power.pc1_adc11_power > 11)Batter_flag=1;
    else Batter_flag=0;
    OSTimeDly(200);
    
  }
}

/*
********************************************************************************
函数名称：void CreatePOWERTask(void)
函数功能：创建POWER任务函数
入口参数：无
出口参数：无
********************************************************************************
*/
void CreatePOWERTask(void)
{
  OSTaskCreateExt(
                  POWERTask,
                  (void *)0,
                  &POWERTaskStk[TASK_POWER_STK_SIZE-1],
                  POWERTaskPrio,
                  0,
                  &POWERTaskStk[0],
                  TASK_POWER_STK_SIZE,
                  (void *)0,
                  OS_TASK_OPT_STK_CHK+OS_TASK_OPT_STK_CLR
                    );
  
}
