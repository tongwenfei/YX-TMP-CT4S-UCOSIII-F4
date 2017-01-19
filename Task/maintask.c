/*******************************************************************************
*CopyRight Reserved:	
*Filename：			maintask.c
*Description：     	        主任务
*Date:
*Author:		
*******************************************************************************/

#include "task.h"
#include "sys.h"
#include "global.h"
#include "port.h"
//任务优先级

//任务控制块
OS_TCB MainTaskTCB;
//任务堆栈	
 CPU_STK MAIN_TASK_STK[MAIN_STK_SIZE];
//任务函数
void MainTask(void *p_arg);
/*
********************************************************************************
函数名称：void MainTask(void *pdata)
函数功能：主任务函数
入口参数：无
出口参数：无
********************************************************************************
*/
extern SYSTEM_CALIBRATION Calibrate_buff;

uu Ushort_To_Double;
void MainTask(void *p_arg)
{
  OS_ERR err;
  
  p_arg = p_arg;
  
  
  //进行喂狗
  //  OS_CRITICAL_ENTER();	//进入临界区
  //  CreateRTCTask();
  //  CreateKeyTask();
  //  CreateTempControlTask();
  //  CreateTempPressTask();
  //  CreateTemTask();
  //  CreateGUITask();
  //  CreateADTask();
  //  CreatePOWERTask();
  //  OS_CRITICAL_EXIT();	//进入临界区
  //  Disp_SampWindow();
  //  Disp_Sys_Info();
  //  Disp_Data();
  //  Disp_DetailWindow();
  //  Disp_ConfigWindow();
  //  Disp_SetWindow();
  while(1)
  {
    
    GPIO_ToggleBits(GPIOC,GPIO_Pin_13);
    if(Calibration_Ch>0&&Calibration_Ch<=4)
    {
          
          for(uint8_t i=0;i<7;i++)
          {
            Ushort_To_Double.u[0]=usReg_CalibrationBuf[4*i+3];
            Ushort_To_Double.u[1]=usReg_CalibrationBuf[4*i+2];
            Ushort_To_Double.u[2]=usReg_CalibrationBuf[4*i+1];
            Ushort_To_Double.u[3]=usReg_CalibrationBuf[4*i];
            System_Calibration.Calibration_Point[Calibration_Ch-1][i]=Ushort_To_Double.d;
            //System_Calibration.Calibration_Point[Calibration_Ch-1][i]=(((uint64_t)usReg_CalibrationBuf[4*i]<<48)+((uint64_t)usReg_CalibrationBuf[4*i+1]<<32)+((uint64_t)usReg_CalibrationBuf[4*i+2]<<16)+((uint64_t)usReg_CalibrationBuf[4*i+3]));
          }
          
          FM24C64_WRITE_MUL(CALIBRATION_STORAGE_ADD+(Calibration_Ch-1)*56,(uint8_t *)&System_Calibration.Calibration_Point[Calibration_Ch-1][0],56);
          FM24C64_READ_MUL(CALIBRATION_STORAGE_ADD+(Calibration_Ch-1)*56,(uint8_t *)&Calibrate_buff.Calibration_Point[Calibration_Ch-1][0],56);
       Calibration_Ch=0;
     
    }
    //Feed_Dog();                 //进行喂狗
    OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
  }
}

/*
********************************************************************************
函数名称：void CreateMainTask(void)
函数功能：创建主任务
入口参数：无
出口参数：无
********************************************************************************
*/
void CreateMainTask(void)
{
  OS_ERR err;
  OSTaskCreate((OS_TCB 	  *)&MainTaskTCB,		//任务控制块
               (CPU_CHAR  *)"Main Task", 		//任务名字
               (OS_TASK_PTR)MainTask, 			//任务函数
               (void      *)0,					//传递给任务函数的参数
               (OS_PRIO     )MAIN_TASK_PRIO,     //任务优先级
               (CPU_STK   * )&MAIN_TASK_STK[0],	//任务堆栈基地址
               (CPU_STK_SIZE)MAIN_STK_SIZE/10,	//任务堆栈深度限位
               (CPU_STK_SIZE)MAIN_STK_SIZE,		//任务堆栈大小
               (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
               (OS_TICK	    )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
               (void      *)0,					//用户补充的存储区
               (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
               (OS_ERR     *)&err);				//存放该函数错误时的返回值
  
}