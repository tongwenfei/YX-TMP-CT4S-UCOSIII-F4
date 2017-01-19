/*******************************************************************************
 *CopyRight Reserved:	
 *Filename：			guitask.h
 *Description：     	        GUI界面任务
 *Date:
 *Author:		
*******************************************************************************/

#include "task.h"
#include "MainWindow.h"
#include "ConfigWindow.h"
#include "SysInfo.h"
#include "PassWd_SetWindow.h"
#include "Data_Window.h"
#include "CH_SetWindow.h"
#include "SampWindow.h"
/*
********************************************************************************
函数名称：void GUITask(void *pdata)
函数功能：GUI任务函数
入口参数：无
出口参数：无
********************************************************************************
*/

//任务控制块
OS_TCB GUITaskTCB;
//任务堆栈	
 CPU_STK GUI_TASK_STK[GUI_STK_SIZE];
//任务函数
void GUITask(void *p_arg);
void GUITask(void *pdata)
{
     OS_ERR err;
    pdata=pdata;
    while(1)
    {  

      if(state_disp)
      {
        DispState_time=0;
        Disp_State();
      }
      if(PassWd_flag)Change_PassWd();
      else if(Main_flag)Change_menu();
     else if(HW_flag) Config_Select();

      else if(Data_Flag)Data_Select();
      else if(Channel_flag)Channel_Select();
      else if(Exit_flag)Samp_Select();
      else if(Info_flag)Sys_Exit();
      else if(Time_flag)ConfigSub_Select();
      else if(Help_flag)Exit_HelpWindows();
        OSTimeDlyHMSM(0,0,0,70,OS_OPT_TIME_HMSM_STRICT,&err); 
    }
}

/*
********************************************************************************
函数名称：void CreateGUITask(void)
函数功能：创建GUI任务函数
入口参数：无
出口参数：无
********************************************************************************
*/
void CreateGUITask(void)
{
    OS_ERR err;
  OSTaskCreate((OS_TCB 	  *)&GUITaskTCB,		//任务控制块
               (CPU_CHAR  *)"GUI Task", 		//任务名字
               (OS_TASK_PTR)GUITask, 			//任务函数
               (void      *)0,					//传递给任务函数的参数
               (OS_PRIO     )GUI_TASK_PRIO,     //任务优先级
               (CPU_STK   * )&GUI_TASK_STK[0],	//任务堆栈基地址
               (CPU_STK_SIZE)GUI_STK_SIZE/10,	//任务堆栈深度限位
               (CPU_STK_SIZE)GUI_STK_SIZE,		//任务堆栈大小
               (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
               (OS_TICK	    )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
               (void      *)0,					//用户补充的存储区
               (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
               (OS_ERR     *)&err);	

}
