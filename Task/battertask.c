/*******************************************************************************
 *CopyRight Reserved:	
 *Filename：			battertask.C
 *Description：     	        电池任务
 *Date:
 *Author:		
*******************************************************************************/

#include"include.h"
#include "include.h"


//任务控制块
OS_TCB BatterTaskTCB;
//任务堆栈	
 CPU_STK BATTER_TASK_STK[BATTER_STK_SIZE];
//任务函数
void BatterTask(void *pdata);
/*
********************************************************************************
函数名称：void BATTERTask(void *pdata)
函数功能：BATTER任务函数
入口参数：无
出口参数：无
********************************************************************************
*/
void BatterTask(void *pdata)
{
  OS_ERR err;
    pdata=pdata;
    while(1)
    {  
      System_Power=ReadADCAverageValue();
        if(Batter_flag == 1)
        {
            //判断是否有电源，决定是充电还是电池供电,用来延时，提供充电效果延时
            if(Power_flag == 1)
            {
                /***************对电池进行充电,某一格电量满，才进下一格，所以从10.6V开始******************/
                if((Batter_add_flag1 == 0) && (Batter_add_flag2 == 0) && (Batter_add_flag3 == 0))
                {
                    //无一个电池，空电量
                    if(System_Power.pc1_adc11_batter <= 10.6)    
                    {
                        Batter_add_flag0 = 1;
                    }
                    if(Batter_add_flag0 == 1)
                    {
                        Batter_add++;
                        if(Batter_add == 6)
                        {
                            Batter_add = 0;
                            Batter_add_flag0 = 0;
                        }
                    }
                }
                if((Batter_add_flag0 == 0) && (Batter_add_flag2 == 0) && (Batter_add_flag3 == 0))
                {
                    //有充足一格电量，进入第二电量
                    if((System_Power.pc1_adc11_batter > 10.6) && (System_Power.pc1_adc11_batter <= 11.2))   //每一格电量为0.6v
                    {
                        Batter_add_flag1 = 1;
                    }
                    if(Batter_add_flag1 == 1)
                    {
                        Batter_add++;
                        if(Batter_add == 5)
                        {
                            Batter_add = 0;
                            Batter_add_flag1 = 0;
                        }
                    }
                }
                if((Batter_add_flag0 == 0) && (Batter_add_flag1 == 0) && (Batter_add_flag3 == 0))
                {
                    //有充足二格电量，进入第三电量
                    if((System_Power.pc1_adc11_batter > 11.2) && (System_Power.pc1_adc11_batter <= 11.8))
                    {
                        Batter_add_flag2 = 1;
                    }
                    if(Batter_add_flag2 == 1)
                    {
                        Batter_add++;
                        if(Batter_add == 4)
                        {
                            Batter_add = 0;
                            Batter_add_flag2 = 0;
                        }
                    }
                }
                if((Batter_add_flag0 == 0) && (Batter_add_flag1 == 0) && (Batter_add_flag2 == 0))
                {
                    //有充足三格电量，进入第四电量
                    if((System_Power.pc1_adc11_batter > 11.8) && (System_Power.pc1_adc11_batter <= 12))
                    {
                        Batter_add_flag3 = 1;
                    }
                    if(Batter_add_flag3 == 1)
                    {
                        Batter_add++;
                        if(Batter_add == 3)
                        {
                            Batter_add = 0;
                            Batter_add_flag3 = 0;
                        }
                    }
                }
                if(System_Power.pc1_adc11_batter > 12)
                {
                    Batter_add_flag4 = 1;
                }
                else
                {
                    Batter_add_flag4 = 0;
                }
            }
            else
            {
                Batter_add = 0;
                Batter_add_flag0 = 0;
                Batter_add_flag1 = 0;
                Batter_add_flag2 = 0;
                Batter_add_flag3 = 0;
            }
        }
       OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
    }
}

/*
********************************************************************************
函数名称：void CreateBATTERTask(void)
函数功能：创建BATTER任务函数
入口参数：无
出口参数：无
********************************************************************************
*/
void CreateBATTERTask(void)
{
    OS_ERR err;
  OSTaskCreate((OS_TCB 	  *)&BatterTaskTCB,		//任务控制块
               (CPU_CHAR  *)"Batter Task", 		//任务名字
               (OS_TASK_PTR)BatterTask, 			//任务函数
               (void      *)0,					//传递给任务函数的参数
               (OS_PRIO     )BATTER_TASK_PRIO,     //任务优先级
               (CPU_STK   * )&BATTER_TASK_STK[0],	//任务堆栈基地址
               (CPU_STK_SIZE)BATTER_STK_SIZE/10,	//任务堆栈深度限位
               (CPU_STK_SIZE)BATTER_STK_SIZE,		//任务堆栈大小
               (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
               (OS_TICK	    )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
               (void      *)0,					//用户补充的存储区
               (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
               (OS_ERR     *)&err);	

}
