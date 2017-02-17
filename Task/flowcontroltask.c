/*
*********************************************************************************************************
*                                               
* File        : FlowControlTask.c
* By          : Wenfei Tong
* Version     : V1.0
* Date        : 03-08-2016
* Description :
* ---------------
*   温度控制任务函数,温度范围(15℃~30℃)由PWM控制
*********************************************************************************************************
*/
#include "task.h"
#include "ads1118.h"
#include "flow_PID.h"
#include "global.h"
#include "port.h"
#include "CH_SetWindow.h"
#include "timer.h"
extern SYSTEM_CALIBRATION Calibrate_buff;
extern uint32_t Intervals_Count[4];
//任务控制块
OS_TCB FlowControlTaskTCB;
//任务堆栈	
CPU_STK FLOWCONTROL_TASK_STK[FLOWCONTROL_STK_SIZE];
//任务函数
void FlowControlTask(void *pdata);
float flow_vaule[4];
void Cal_FlowValue(void)
{
  flow_vaule[0]=Filter(FLOW_ADC,ADC_CH1);
  flow_vaule[1]=Filter(FLOW_ADC,ADC_CH2);
  flow_vaule[2]=Filter(FLOW_ADC,ADC_CH3);
  flow_vaule[3]=Filter(FLOW_ADC,ADC_CH4);
  FlowPID_struct[0].Value=flow_vaule[1];
  FlowPID_struct[1].Value=flow_vaule[0];
  FlowPID_struct[2].Value=flow_vaule[2];
  FlowPID_struct[3].Value=flow_vaule[3];
  for(uint8_t i=0;i<4;i++)
  {
    
    if((FlowPID_struct[i].SetPoint*1000>0)&&((Sampling_State[i]==Runing)||(Calibrate_State[i]==Runing)))
    {
      if(Calibrate_State[i]==Runing)
      {
        //        if((FlowPID_struct[i].Value>0.9)&&(FlowPID_struct[i].Value<=1.6227))
        //          FlowPID_struct[i].Flow_Value = (-165.6360339191206*pow(FlowPID_struct[i].Value,3)+787.8484037677059*pow(FlowPID_struct[i].Value,2)-1151.749492134806*FlowPID_struct[i].Value+533.0304628920129);
        //        else if((FlowPID_struct[i].Value>1.6227)&&(FlowPID_struct[i].Value<=2.3662))
        //          FlowPID_struct[i].Flow_Value = (124.9144241259995*FlowPID_struct[i].Value-138.8127422869870);
        //        else if((FlowPID_struct[i].Value>2.3662)&&(FlowPID_struct[i].Value<=2.9957))  
        //          FlowPID_struct[i].Flow_Value = (158.2985590021515*FlowPID_struct[i].Value-217.8510736407507);
        //        else if((FlowPID_struct[i].Value>2.9957)&&(FlowPID_struct[i].Value<=3.3339))    
        //          FlowPID_struct[i].Flow_Value=(229.6942070936586*FlowPID_struct[i].Value-429.9121881772697);
        //        else if((FlowPID_struct[i].Value>3.339)&&(FlowPID_struct[i].Value<=3.8536))
        //          FlowPID_struct[i].Flow_Value=(241.9640309129243*FlowPID_struct[i].Value-471.1934969206055);
        //        else if((FlowPID_struct[i].Value>3.8536)&&(FlowPID_struct[i].Value<=4.2185))
        //          FlowPID_struct[i].Flow_Value= (302.1335228772812*pow(FlowPID_struct[i].Value,3)-3515.553694289767*pow(FlowPID_struct[i].Value,2)+13869.28655485954*FlowPID_struct[i].Value-18070.29049096129);
        //        else if((FlowPID_struct[i].Value>4.2185)&&(FlowPID_struct[i].Value<=4.525))
        //          FlowPID_struct[i].Flow_Value= (326.5077706341161*FlowPID_struct[i].Value-821.4283010169315);
        //        else if((FlowPID_struct[i].Value>4.525)&&(FlowPID_struct[i].Value<=4.735))
        //          FlowPID_struct[i].Flow_Value= (479.6135794851961*FlowPID_struct[i].Value-1513.416832901239);
        //        else if((FlowPID_struct[i].Value>4.735)&&(FlowPID_struct[i].Value<=4.8896))  
        //          FlowPID_struct[i].Flow_Value = (-3609.691079232182*pow(FlowPID_struct[i].Value,3)+54299.36390846583*pow(FlowPID_struct[i].Value,2)-271105.1331874162*FlowPID_struct[i].Value+450243.2072600146);
        //        else if((FlowPID_struct[i].Value>4.8896)&&(FlowPID_struct[i].Value<=4.9631)  )
        //          FlowPID_struct[i].Flow_Value= (1284.137642632644*FlowPID_struct[i].Value-5425.134662345077);  
        //        else if((FlowPID_struct[i].Value>4.9631)&&(FlowPID_struct[i].Value<=5.0411))  
        //          FlowPID_struct[i].Flow_Value= (1145.039335023927*FlowPID_struct[i].Value-4716.213845549683);  
        //FloatToUshort(FlowPID_struct[i].Value,&usRegAd_VauleBuf[i*2]);
        //FlowPID_struct[i].SetPoint=usRegFlowSetBuf[i]/1000.0;
        
        
        
        //        FlowPID_struct[i].Flow_Value = 6.408320683852675*pow(FlowPID_struct[i].Value,6)\
        //                                      -111.8440311985473*pow(FlowPID_struct[i].Value,5)\
        //                                      +789.3057051733712*pow(FlowPID_struct[i].Value,4)\
        //                                      -2865.533837029761*pow(FlowPID_struct[i].Value,3)\
        //                                      +5642.592013462648*pow(FlowPID_struct[i].Value,2)\
        //                                      -5585.834292463589*FlowPID_struct[i].Value\
        //                                      +2124.909312422997;
        
        
        
        
        
        //         if((FlowPID_struct[i].Value>0.9)&&(FlowPID_struct[i].Value<=1.6227))
        //          FlowPID_struct[i].Flow_Value = (-165.6360339191206*pow(FlowPID_struct[i].Value,3)+787.8484037677059*pow(FlowPID_struct[i].Value,2)-1151.749492134806*FlowPID_struct[i].Value+533.0304628920129);
        //        else if((FlowPID_struct[i].Value>1.6227)&&(FlowPID_struct[i].Value<=2.1366))
        //          FlowPID_struct[i].Flow_Value = (124.0012738642338*FlowPID_struct[i].Value-137.1694277798844);
        //        else if((FlowPID_struct[i].Value>2.1366)&&(FlowPID_struct[i].Value<=2.8771))  
        //          FlowPID_struct[i].Flow_Value = (147.8150071037069*FlowPID_struct[i].Value-190.7196643982324);
        //        else if((FlowPID_struct[i].Value>2.8771)&&(FlowPID_struct[i].Value<=3.2973))    
        //          FlowPID_struct[i].Flow_Value=(218.2278744874792*FlowPID_struct[i].Value-393.4369628136138);
        //        else if((FlowPID_struct[i].Value>3.2973)&&(FlowPID_struct[i].Value<=3.7432))
        //          FlowPID_struct[i].Flow_Value=(240.5194765025169*FlowPID_struct[i].Value-465.8573142447534);
        //        else if((FlowPID_struct[i].Value>3.7432)&&(FlowPID_struct[i].Value<=4.1333))
        //          FlowPID_struct[i].Flow_Value=(241.5803355276242*FlowPID_struct[i].Value-470.5375892997762);
        //        else if((FlowPID_struct[i].Value>4.1333)&&(FlowPID_struct[i].Value<=4.447))
        //          FlowPID_struct[i].Flow_Value= (315.6362066434168*FlowPID_struct[i].Value-774.6922021034570);
        //        else if((FlowPID_struct[i].Value>4.447)&&(FlowPID_struct[i].Value<=4.6833))
        //          FlowPID_struct[i].Flow_Value= (436.2807542632382*FlowPID_struct[i].Value-1313.515951108509);
        //        else if((FlowPID_struct[i].Value>4.6833)&&(FlowPID_struct[i].Value<=4.847))  
        //          FlowPID_struct[i].Flow_Value= (577.4570807628410*FlowPID_struct[i].Value-1975.21335925510);
        //        else if((FlowPID_struct[i].Value>4.847)&&(FlowPID_struct[i].Value<=4.9432)  )
        //          FlowPID_struct[i].Flow_Value= (1002.945617223990*FlowPID_struct[i].Value-4036.573567603976);  
        //        else if((FlowPID_struct[i].Value>4.9432)&&(FlowPID_struct[i].Value<=5.0411))  
        //          FlowPID_struct[i].Flow_Value= (1190.462906083756*FlowPID_struct[i].Value-4943.689718725041);  
        
      }
      if(DEBUG_MODE[i]==1)
      {
        DEBUG_MODE[i]+=1;
        Sampling_State[i]=Runing;
        FlowPID_struct[i].PWM_Vaule=480;
      }
      else 
      {
        //        if((FlowPID_struct[i].Value>0.9)&&(FlowPID_struct[i].Value<=1.6227))
        //          FlowPID_struct[i].Flow_Value = (-165.6360339191206*pow(FlowPID_struct[i].Value,3)+787.8484037677059*pow(FlowPID_struct[i].Value,2)-1151.749492134806*FlowPID_struct[i].Value+533.0304628920129);
        //        else if((FlowPID_struct[i].Value>1.6227)&&(FlowPID_struct[i].Value<=2.1366))
        //          FlowPID_struct[i].Flow_Value = (124.0012738642338*FlowPID_struct[i].Value-137.1694277798844)*Calibrate_buff.Calibration_Point[i][0];
        //        else if((FlowPID_struct[i].Value>2.1366)&&(FlowPID_struct[i].Value<=2.8771))  
        //          FlowPID_struct[i].Flow_Value = (147.8150071037069*FlowPID_struct[i].Value-190.7196643982324)*Calibrate_buff.Calibration_Point[i][1];
        //        else if((FlowPID_struct[i].Value>2.8771)&&(FlowPID_struct[i].Value<=3.2973))    
        //          FlowPID_struct[i].Flow_Value=(218.2278744874792*FlowPID_struct[i].Value-393.4369628136138)*Calibrate_buff.Calibration_Point[i][2];
        //        else if((FlowPID_struct[i].Value>3.2973)&&(FlowPID_struct[i].Value<=3.7432))
        //          FlowPID_struct[i].Flow_Value=(240.5194765025169*FlowPID_struct[i].Value-465.8573142447534)*Calibrate_buff.Calibration_Point[i][3];
        //        else if((FlowPID_struct[i].Value>3.7432)&&(FlowPID_struct[i].Value<=4.1333))
        //          FlowPID_struct[i].Flow_Value=(241.5803355276242*FlowPID_struct[i].Value-470.5375892997762)*Calibrate_buff.Calibration_Point[i][4];
        //        else if((FlowPID_struct[i].Value>4.1333)&&(FlowPID_struct[i].Value<=4.447))
        //          FlowPID_struct[i].Flow_Value= (315.6362066434168*FlowPID_struct[i].Value-774.6922021034570)*Calibrate_buff.Calibration_Point[i][5];
        //        else if((FlowPID_struct[i].Value>4.447)&&(FlowPID_struct[i].Value<=4.6833))
        //          FlowPID_struct[i].Flow_Value= (436.2807542632382*FlowPID_struct[i].Value-1313.515951108509)*Calibrate_buff.Calibration_Point[i][6];
        //        else if((FlowPID_struct[i].Value>4.6833)&&(FlowPID_struct[i].Value<=4.847))  
        //          FlowPID_struct[i].Flow_Value= (577.4570807628410*FlowPID_struct[i].Value-1975.21335925510)*Calibrate_buff.Calibration_Point[i][7];
        //        else if((FlowPID_struct[i].Value>4.847)&&(FlowPID_struct[i].Value<=4.9432)  )
        //          FlowPID_struct[i].Flow_Value= (1002.945617223990*FlowPID_struct[i].Value-4036.573567603976)*Calibrate_buff.Calibration_Point[i][8]; 
        //        else if((FlowPID_struct[i].Value>4.9432)&&(FlowPID_struct[i].Value<=5.0411))  
        //          FlowPID_struct[i].Flow_Value= (1190.462906083756*FlowPID_struct[i].Value-4943.689718725041)*Calibrate_buff.Calibration_Point[i][9];  
        
        
        if(DEBUG_MODE[i]!=2)
        {
          if((FlowPID_struct[i].Value>1.5)&&(FlowPID_struct[i].Value<=5.1))
          {
            
            
            
            
            FlowPID_struct[i].Flow_Value=Calibrate_buff.Calibration_Point[i][0]*pow(FlowPID_struct[i].Value,6)+\
              Calibrate_buff.Calibration_Point[i][1]*pow(FlowPID_struct[i].Value,5)+\
                Calibrate_buff.Calibration_Point[i][2]*pow(FlowPID_struct[i].Value,4)+\
                  Calibrate_buff.Calibration_Point[i][3]*pow(FlowPID_struct[i].Value,3)+\
                    Calibrate_buff.Calibration_Point[i][4]*pow(FlowPID_struct[i].Value,2)+\
                      Calibrate_buff.Calibration_Point[i][5]*FlowPID_struct[i].Value+\
                        Calibrate_buff.Calibration_Point[i][6];                                      
          }
          else if((FlowPID_struct[i].Value>5.1)&&(FlowPID_struct[i].Value<=5.2)) FlowPID_struct[i].Flow_Value=1100;
          else if((FlowPID_struct[i].Value>5.2)&&(FlowPID_struct[i].Value<=5.3)) FlowPID_struct[i].Flow_Value=1200;
          else if((FlowPID_struct[i].Value>5.3)&&(FlowPID_struct[i].Value<=5.4)) FlowPID_struct[i].Flow_Value=1300;
          else if((FlowPID_struct[i].Value>5.4)) FlowPID_struct[i].Flow_Value=1400;
        }
        
        
        
        
        
      }
      
      
      
      if(FlowPID_struct[i].Flow_Value<0)FlowPID_struct[i].Flow_Value=0;
      if((FlowPID_struct[i].Flow_Value>(FlowPID_struct[i].SetPoint*1010))||(FlowPID_struct[i].Flow_Value<(FlowPID_struct[i].SetPoint*990))||(DEBUG_MODE[i]==2))
      {
        uint16_t pwm_vaule=0;
	if(DEBUG_MODE[i]!=2)
        {
          FlowPID_struct[i].Clac_Value= Flow_PID_Calculation(&FlowPID_struct[i],FlowPID_struct[i].Flow_Value/1000.0);
          if(FlowPID_struct[i].Clac_Value<=0)FlowPID_struct[i].Clac_Value=0;
          else if(FlowPID_struct[i].Clac_Value>2.5)FlowPID_struct[i].Clac_Value=2.5;
          FlowPID_struct[i].PWM_Vaule=300+200*FlowPID_struct[i].Clac_Value;
          pwm_vaule=FlowPID_struct[i].PWM_Vaule;
        }
        else if(DEBUG_MODE[i]==2) pwm_vaule=FlowPID_struct[i].PWM_Vaule;
	switch(i)
	{
	case 0:
	  {
	    
	    TIM_SetCompare4(TIM3,pwm_vaule);
            PUMP3_ON();
	    
	  }break;
	case 1:
	  {
	    
	    TIM_SetCompare1(TIM3,pwm_vaule);
            PUMP1_ON();
	  }break;
	case 2:
	  {
	    PUMP4_ON(); 
	    TIM_SetCompare2(TIM3,pwm_vaule);
	  }break;
	case 3:
	  {
            
	    TIM_SetCompare3(TIM3,pwm_vaule);
            PUMP2_ON();
	  }break;
	  
	}
      }
    }
    else
    {
      switch(i)
      {
      case 0:
	{
          PUMP3_OFF();
	  TIM_SetCompare4(TIM3,0);
	  
	  
	}break;
      case 1:
	{
          PUMP1_OFF();
	  TIM_SetCompare1(TIM3,0);
	  
	}break;
      case 2:
	{
          PUMP4_OFF();
	  TIM_SetCompare2(TIM3,0);
	  
	}break;
      case 3:
	{
          PUMP2_OFF();
	  TIM_SetCompare3(TIM3,0);
	  
	}break;
	
	
      }
    }
    if(Definite_Count[i]/600.0>=Sampling_Mode.Definite_Time[i])//采样时间大于定时时间
    {
      
      Stop_Sampling(i+1);
      if((Sampling_Mode.Intervals_Time[i]>0)&&(Sampling_Mode.isManually==false))
      {
        Intervals_State[i]=true;
      }
      else
      {
        Intervals_State[i]=false;
        Sampling_Mode.Definite_Time[i]=0;
      }
    }
    if((Sampling_State[i]==Stop)&&(Sampling_Mode.Definite_Time[i]>0)&&(Sampling_Mode.Intervals_Time[i]>0)&&(Sampling_Mode.isManually==false))//采样停止状态，定时时间大于0，处于间隔采样状态
    {
      if(Intervals_Count[i]/600.0>Sampling_Mode.Intervals_Time[i])
      {
        Intervals_State[i]=false;
        Definite_Count[i]=0;
        Start_Sampling(i+1);
      }
    }
  }
  
}

void FlowControlTask(void *pdata)
{
  OS_ERR err;
  pdata=pdata;
  
  
  while(1)
  {
    
    
    
    
    
    Cal_FlowValue();
    
    OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
  }
}

void CreateFlowControlTask(void)
{
  OS_ERR err;
  OSTaskCreate((OS_TCB 	  *)&FlowControlTaskTCB,		//任务控制块
	       (CPU_CHAR  *)"FlowControl Task", 		//任务名字
	       (OS_TASK_PTR)FlowControlTask, 			//任务函数
	       (void      *)0,					//传递给任务函数的参数
	       (OS_PRIO     )FLOWCONTROL_TASK_PRIO,     //任务优先级
	       (CPU_STK   * )&FLOWCONTROL_TASK_STK[0],	//任务堆栈基地址
	       (CPU_STK_SIZE)FLOWCONTROL_STK_SIZE/10,	//任务堆栈深度限位
	       (CPU_STK_SIZE)FLOWCONTROL_STK_SIZE,		//任务堆栈大小
	       (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
	       (OS_TICK	    )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
	       (void      *)0,					//用户补充的存储区
	       (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
	       (OS_ERR     *)&err);	
}