/*******************************************************************************
 *CopyRight Reserved:	
 *Filename：			functiontask.C
 *Description：     	        相关功能任务
 *Date:
 *Author:		
*******************************************************************************/

#include"include.h"

/*
********************************************************************************
函数名称：void FUNTask(void *pdata)
函数功能：FUN任务函数
入口参数：无
出口参数：无
********************************************************************************
*/
void FUNTask(void *pdata)
{
    pdata=pdata;
    while(1)
    {  
        g_Power = ReadADCAverageValue();
        if(g_Power.pb0_adc8_power > 13)
        {
            Power_flag = 1;
            PD2_BATCON_OFF();         //关闭电池供电气泵开关
        }
        else
        {
            Power_flag = 0;
            PD2_BATCON_ON();         //打开电池供电气泵开关
        }
        Display_Power(Power_flag);
        OSTimeDly(1);
    }
}

/*
********************************************************************************
函数名称：void CreateFUNTask(void)
函数功能：创建FUN任务函数
入口参数：无
出口参数：无
********************************************************************************
*/
void CreateFUNTask(void)
{
    OSTaskCreateExt(
                        FUNTask,
                        (void *)0,
                        &FUNTaskStk[TASK_FUN_STK_SIZE-1],
                        FUNTaskPrio,
                        0,
                        &FUNTaskStk[0],
                        TASK_FUN_STK_SIZE,
                        (void *)0,
                        OS_TASK_OPT_STK_CHK+OS_TASK_OPT_STK_CLR
                   );

}
