/*
*********************************************************************************************************
*                                               
* File        : KeyTask.c
* By          : Wenfei Tong
* Version     : V1.0
* Date        : 03-08-2016
* Description :
* ---------------
*   按键反馈任务函数
*********************************************************************************************************
*/
#include "task.h"
#include "global.h"
#include "key.h"
uint8_t last_key,now_key;

//任务控制块
OS_TCB KeyTaskTCB;
//任务堆栈	
CPU_STK KEY_TASK_STK[KEY_STK_SIZE];
#include "lcd.h"

//任务函数
void KeyTask(void *pdata);
void KeyTask(void *pdata)
{
  OS_ERR err;
  pdata=pdata;
  while(1)
  {
    Button_Detect();
    if(!LCD_BL_State)
    {
    if((KEY_FIFO.Read < KEY_FIFO.Write)&&KEY_FIFO.Write>0)
    {bsp_keyRead();
   OSTmrStop((OS_TMR		*)&tmr1,		//定时器1
		(OS_OPT		 )OS_OPT_TMR_PERIODIC, //周期模式
		(void	    *)0,			//参数为0
	        (OS_ERR	    *)&err);		//返回的错误码
	TIM_SetCompare3(TIM4,1000);
        LCD_BL_State=1;
    }
    }
    else
    {
      if((OSTmrStateGet(&tmr1,&err)==OS_TMR_STATE_RUNNING))
      {
        if((KEY_FIFO.Read < KEY_FIFO.Write)&&(KEY_FIFO.Write>0))
    {
        OSTmrStop((OS_TMR		*)&tmr1,		//定时器1
		(OS_OPT		 )OS_OPT_TMR_PERIODIC, //周期模式
		(void	    *)0,			//参数为0
	        (OS_ERR	    *)&err);		//返回的错误码
	TIM_SetCompare3(TIM4,1000);
        LCD_BL_State=1;
        OSTmrStart((OS_TMR		*)&tmr1,//定时器1
		   (OS_ERR	        *)&err);
    }
		//返回的错误码
      }
      else if((OSTmrStateGet(&tmr1,&err)==OS_TMR_STATE_UNUSED)||(OSTmrStateGet(&tmr1,&err)==OS_TMR_STATE_STOPPED))
      {
	OSTmrStart((OS_TMR		*)&tmr1,//定时器1
		   (OS_ERR	        *)&err);
		//返回的错误码
      }
      
    }
    
    OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
  }
}

void CreateKeyTask(void)
{
  OS_ERR err;
  OSTaskCreate((OS_TCB 	  *)&KeyTaskTCB,		//任务控制块
	       (CPU_CHAR  *)"Key Task", 		//任务名字
	       (OS_TASK_PTR)KeyTask, 			//任务函数
	       (void      *)0,					//传递给任务函数的参数
	       (OS_PRIO     )KEY_TASK_PRIO,     //任务优先级
	       (CPU_STK   * )&KEY_TASK_STK[0],	//任务堆栈基地址
	       (CPU_STK_SIZE)KEY_STK_SIZE/10,	//任务堆栈深度限位
	       (CPU_STK_SIZE)KEY_STK_SIZE,		//任务堆栈大小
	       (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
	       (OS_TICK	    )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
	       (void      *)0,					//用户补充的存储区
	       (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
	       (OS_ERR     *)&err);	
}