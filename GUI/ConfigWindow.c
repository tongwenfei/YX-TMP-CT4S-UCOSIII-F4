#include "ConfigWindow.h"
#include "MainWindow.h"
#include "ConfigWindow.h"
#include "fm24cl64.h"
#include "polyfit.h"
extern unsigned char gImage_triangle_re[60];
extern unsigned char gImage_triangle_le[60];
extern unsigned char gImage_triangle_rf[60];
extern unsigned char gImage_triangle_lf[60];
extern SYSTEM_CALIBRATION Calibrate_buff;
Time_Typedef Time_Set_Vaule;
uint8_t Config_Num=1,Time_Set_Num=1,Uart_Set_Num=1,uart_cnt=0,uart_parity_cnt=0;
uint8_t CalibrationCH=1,Last_CalibrationCH=4,CalibrationFlow=0,Last_CalibrationFlow=11;
uint8_t NumOfCalibrationChar[4][11]={0},CalibrationChar[4][11][4];
uint16_t CalibrationVaule[4][11]={0};
uint32_t Uart_Baud_Save=115200,Uart_Bits_Save=8,Uart_Stop_Save=1,Uart_Parity_Save=0;
const uint32_t Uart_Baud[]={1200,2400,4800,9600,14400,19200,38400,56000,115200,128000,256000};
const uint8_t Uart_Bits[]={8,9};
const uint8_t Uart_Stop[]={1,2};
bool isUart_8Bits=true,isUart_1Stop=true,Calibrate_Flag=false;
void Disp_ConfigWindow(void)
{
  Clear_LCD(0,0,320,240);
  Config_Num=1;
  
  PrintGB(112,4,"硬件设置");
  Fill_Rect(0,25,320,26);
  LCD_Invert(1);
  Show_Str(100,35,"1.时间设置");
  LCD_Invert(0);
  Show_Str(100,70,"2.串口设置");
  Show_Str(100,105,"3.参数校准");
  Show_Str(100,140,"4.清空采样数据");
  Show_Str(100,175,"5.恢复出厂设置");
  Show_Str(100,210,"6.系统升级");
  //Disp_TimeSetWindow();
}
void Config_Select(void)
{
  uint8_t key=bsp_keyRead();
  //  OS_MSG_SIZE size;
  //  OS_ERR err;
  //  key=OSQPend((OS_Q*			)&KEY_Msg,   
  //	      (OS_TICK			)0,
  //	      (OS_OPT			)OS_OPT_PEND_NON_BLOCKING,
  //	      (OS_MSG_SIZE*		)&size,		
  //	      (CPU_TS*			)0,
  //	      (OS_ERR*			)&err);
  
  
  
  switch(key)
  {
  case 4:
    {
      Updata_flag=0;
      if(Config_Num>1)
	Config_Num--;
      else Config_Num=6;
    }break;
  case 8:
    {
      Updata_flag=0;
      if(Config_Num<6)
	Config_Num++;
      else Config_Num=1;
    }break;
  case 13:
    {
      Updata_flag=0;
      Config_Num=1;
      HW_flag=0;
      state_disp=1;
      Main_flag=1;
      Disp_MainWindow();
      return;
    }break;
  case 15:
    {
      Updata_flag=1;
      switch(Config_Num)
      {
      case 1:
	{
	  HW_flag=0;
	  Time_flag=1;
	  Disp_TimeSetWindow();
	}break;
      case 2:
	{
	  HW_flag=0;
	  Time_flag=2;
	  Disp_BaudSetWindow();
	}break;
      case 3:
	{
	  HW_flag=0;
	  Time_flag=3;
	  Disp_CalibrationWindow();
	}break;
      case 4:
	{
	  Time_flag=4;
	  
	  
	}break;
      case 5:
	{
	  Time_flag=5;
	}break;
      case 6:
	{
	  Time_flag=6;
	}break;
      }
    }
  }
  if(Updata_flag==0)
  {
    //    if(key==4)
    //    {
    //      if(Config_Num>1)
    //	Config_Num--;
    //      else Config_Num=6;
    //    }
    //    if(key==8)
    //    {
    //      if(Config_Num<6)
    //	Config_Num++;
    //      else Config_Num=1;
    //    }
    //    if(key==13)
    //    {
    //      Config_Num=1;
    //      HW_flag=0;
    //      state_disp=1;
    //      Main_flag=1;
    //      Disp_MainWindow();
    //      return;
    //    }
    
    
    switch(Config_Num)
    {
    case 1:
      {
	LCD_Invert(1);
	Show_Str(100,35,"1.时间设置");
	LCD_Invert(0);
	Show_Str(100,70,"2.串口设置");
	Show_Str(100,105,"3.参数校准");
	Show_Str(100,140,"4.清空采样数据");
	Show_Str(100,175,"5.恢复出厂设置");
	Show_Str(100,210,"6.系统升级");
	
      }break;
    case 2:
      {
	
	Show_Str(100,35,"1.时间设置");
	
	LCD_Invert(1);
	Show_Str(100,70,"2.串口设置");
	LCD_Invert(0);
	Show_Str(100,105,"3.参数校准");
	Show_Str(100,140,"4.清空采样数据");
	Show_Str(100,175,"5.恢复出厂设置");
	Show_Str(100,210,"6.系统升级");
      }break;
    case 3:
      {
	
	Show_Str(100,35,"1.时间设置");
	
	Show_Str(100,70,"2.串口设置");
	LCD_Invert(1);
	Show_Str(100,105,"3.参数校准");
	LCD_Invert(0);
	Show_Str(100,140,"4.清空采样数据");
	Show_Str(100,175,"5.恢复出厂设置");
	Show_Str(100,210,"6.系统升级");
      }break;
    case 4:
      {
	
	Show_Str(100,35,"1.时间设置");
	LCD_Invert(0);
	Show_Str(100,70,"2.串口设置");
	Show_Str(100,105,"3.参数校准");
	LCD_Invert(1);
	Show_Str(100,140,"4.清空采样数据");
	LCD_Invert(0);
	Show_Str(100,175,"5.恢复出厂设置");
	Show_Str(100,210,"6.系统升级");
      }break;
    case 5:
      {
	
	Show_Str(100,35,"1.时间设置");
	
	Show_Str(100,70,"2.串口设置");
	Show_Str(100,105,"3.参数校准");
	Show_Str(100,140,"4.清空采样数据");
	LCD_Invert(1);
	Show_Str(100,175,"5.恢复出厂设置");
	LCD_Invert(0);
	Show_Str(100,210,"6.系统升级");
      }break;
    case 6:
      {
	
	Show_Str(100,35,"1.时间设置");
	
	Show_Str(100,70,"2.串口设置");
	Show_Str(100,105,"3.参数校准");
	Show_Str(100,140,"4.清空采样数据");
	Show_Str(100,175,"5.恢复出厂设置");
	LCD_Invert(1);
	Show_Str(100,210,"6.系统升级");
	LCD_Invert(0);
      }break;
    }
  }
}


void ConfigSub_Select(void)
{
  uint8_t key=bsp_keyRead();
  //  OS_MSG_SIZE size;
  //  OS_ERR err;
  //  key=OSQPend((OS_Q*			)&KEY_Msg,   
  //	      (OS_TICK			)0,
  //	      (OS_OPT			)OS_OPT_PEND_NON_BLOCKING,
  //	      (OS_MSG_SIZE*		)&size,		
  //	      (CPU_TS*			)0,
  //	      (OS_ERR*			)&err);
  if(key==13)
  {
    const double flow_buff[4]={200,300,600,900}; 
   
    HW_flag=1;
    Updata_flag=0;
    Time_flag=0;
    Clear_LCD(0,0,320,240);
    PrintGB(112,4,"硬件设置");
    Fill_Rect(0,25,320,26);
    if(Calibrate_Flag)
    {
       double calibrate_flow_buff[4][4]={0};
      for(uint8_t i=0;i<4;i++)
      {
        Calibrate_State[i]=Stop;
        FlowPID_struct[i].SetPoint=0;
        calibrate_flow_buff[i][0]=System_Calibration.Calibration_Flow[i][0];
        calibrate_flow_buff[i][1]=System_Calibration.Calibration_Flow[i][1];
        calibrate_flow_buff[i][2]=System_Calibration.Calibration_Flow[i][2];
        calibrate_flow_buff[i][3]=System_Calibration.Calibration_Flow[i][3];
        polyfit(flow_buff,calibrate_flow_buff[i],4,4,System_Calibration.Calibration_Point[i]);
       
      }
      FM24C64_WRITE_MUL(CALIBRATION_STORAGE_ADD,(uint8_t *)&System_Calibration,160);
      Calibrate_Flag=false;
      CalibrationFlow=0;
      FM24C64_READ_MUL(CALIBRATION_STORAGE_ADD,(uint8_t *)&Calibrate_buff,160);
    }
    
    return;
  }
  switch(Time_flag)
  {
    uint8_t time1[8];
  case 1:
    {
      if(key==12)
      {
	if(Time_Set_Num>1)Time_Set_Num--;
	else Time_Set_Num=8;
      }
      else if(key==16)
      {
	if(Time_Set_Num<8)Time_Set_Num++;
	else Time_Set_Num=1;
      }
      
      switch(Time_Set_Num)
      {
      case 1:
	{
	  if(key==4)
	  {
	    if(Time_Set_Vaule.hour>0)Time_Set_Vaule.hour--;
	    else Time_Set_Vaule.hour=0;
	  }
	  else if(key==8)
	  {
	    if(Time_Set_Vaule.hour<23)Time_Set_Vaule.hour++;
	    else Time_Set_Vaule.hour=23;
	  }
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.hour);
	  LCD_Invert(1);
	  Show_Str(116,89,time1);
	  LCD_Invert(0);
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.minute);
	  Show_Str(156,89,time1);
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.second);
	  Show_Str(196,89,time1);
	  
	  sprintf((char*)time1,"%04d",(Time_Set_Vaule.year+2000));
	  Show_Str(116,149,time1);
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.month));
	  Show_Str(172,149,time1);
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.date));
	  Show_Str(212,149,time1);
	  
	  Show_Str(80,200,"取消");
	  Show_Str(188,200,"确定");
	}break;
      case 2:
	{
	  if(key==4)
	  {
	    if(Time_Set_Vaule.minute>0)Time_Set_Vaule.minute--;
	    else Time_Set_Vaule.minute=0;
	  }
	  else if(key==8)
	  {
	    if(Time_Set_Vaule.minute<59)Time_Set_Vaule.minute++;
	    else Time_Set_Vaule.minute=59;
	  }
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.hour);
	  Show_Str(116,89,time1);
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.minute);
	  LCD_Invert(1);
	  Show_Str(156,89,time1);
	  LCD_Invert(0);
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.second);
	  Show_Str(196,89,time1);
	  
	  sprintf((char*)time1,"%04d",(Time_Set_Vaule.year+2000));
	  Show_Str(116,149,time1);
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.month));
	  Show_Str(172,149,time1);
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.date));
	  Show_Str(212,149,time1);
	  
	  Show_Str(80,200,"取消");
	  Show_Str(188,200,"确定");
	}break;
      case 3:
	{
	  if(key==4)
	  {
	    if(Time_Set_Vaule.second>0)Time_Set_Vaule.second--;
	    else Time_Set_Vaule.second=0;
	  }
	  else if(key==8)
	  {
	    if(Time_Set_Vaule.second<59)Time_Set_Vaule.second++;
	    else Time_Set_Vaule.second=59;
	  }
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.hour);
	  
	  Show_Str(116,89,time1);
	  
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.minute);
	  Show_Str(156,89,time1);
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.second);
	  LCD_Invert(1);
	  Show_Str(196,89,time1);
	  LCD_Invert(0);
	  
	  sprintf((char*)time1,"%04d",(Time_Set_Vaule.year+2000));
	  Show_Str(116,149,time1);
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.month));
	  Show_Str(172,149,time1);
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.date));
	  Show_Str(212,149,time1);
	  
	  Show_Str(80,200,"取消");
	  Show_Str(188,200,"确定");
	}break;
      case 4:
	{
	  if(key==4)
	  {
	    if(Time_Set_Vaule.year>0)Time_Set_Vaule.year--;
	    else Time_Set_Vaule.year=0;
	  }
	  else if(key==8)
	  {
	    if(Time_Set_Vaule.year<99)Time_Set_Vaule.year++;
	    else Time_Set_Vaule.year=99;
	  }
	  if((Time_Set_Vaule.year!=0)&&((Time_Set_Vaule.year%4)!=0)&&(Time_Set_Vaule.month==2))
	  {
	    if(Time_Set_Vaule.date==29)Time_Set_Vaule.date=28;
	  }
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.hour);
	  
	  Show_Str(116,89,time1);
	  
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.minute);
	  
	  Show_Str(156,89,time1);
	  
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.second);
	  Show_Str(196,89,time1);
	  
	  sprintf((char*)time1,"%04d",(Time_Set_Vaule.year+2000));
	  LCD_Invert(1);
	  Show_Str(116,149,time1);
	  LCD_Invert(0);
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.month));
	  Show_Str(172,149,time1);
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.date));
	  Show_Str(212,149,time1);
	  
	  Show_Str(80,200,"取消");
	  Show_Str(188,200,"确定");
	}break;
      case 5:
	{
	  if(key==4)
	  {
	    if(Time_Set_Vaule.month>1)Time_Set_Vaule.month--;
	    else Time_Set_Vaule.month=1;
	  }
	  else if(key==8)
	  {
	    if(Time_Set_Vaule.month<12)Time_Set_Vaule.month++;
	    else Time_Set_Vaule.month=12;
	  }
	  if((Time_Set_Vaule.year!=0)&&((Time_Set_Vaule.year%4)!=0)&&(Time_Set_Vaule.month==2))
	  {
	    if(Time_Set_Vaule.date==29)Time_Set_Vaule.date=28;
	  }
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.hour);
	  
	  Show_Str(116,89,time1);
	  
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.minute);
	  
	  Show_Str(156,89,time1);
	  
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.second);
	  Show_Str(196,89,time1);
	  
	  sprintf((char*)time1,"%04d",(Time_Set_Vaule.year+2000));
	  Show_Str(116,149,time1);
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.month));
	  LCD_Invert(1);
	  Show_Str(172,149,time1);
	  LCD_Invert(0);
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.date));
	  Show_Str(212,149,time1);
	  
	  Show_Str(80,200,"取消");
	  Show_Str(188,200,"确定");
	}break;
      case 6:
	{
	  if(key==4)
	  {
	    
	    if(Time_Set_Vaule.date>1)Time_Set_Vaule.date--;
	    else Time_Set_Vaule.date=1;
	    
	  }
	  else if(key==8)
	  {
	    if((Time_Set_Vaule.month==1)||(Time_Set_Vaule.month==3)||(Time_Set_Vaule.month==5)||(Time_Set_Vaule.month==7)||(Time_Set_Vaule.month==8)||(Time_Set_Vaule.month==10)||(Time_Set_Vaule.month==12))
	    {
	      if(Time_Set_Vaule.date<31)Time_Set_Vaule.date++;
	      else Time_Set_Vaule.date=31;
	    }
	    else if((Time_Set_Vaule.month==4)||(Time_Set_Vaule.month==6)||(Time_Set_Vaule.month==9)||(Time_Set_Vaule.month==11))
	    {
	      if(Time_Set_Vaule.date<30)Time_Set_Vaule.date++;
	      else Time_Set_Vaule.date=30;
	    }
	    else if(Time_Set_Vaule.month==2)
	    {
	      if((Time_Set_Vaule.year==0)||((Time_Set_Vaule.year%4)==0))
	      {
		if(Time_Set_Vaule.date<29)Time_Set_Vaule.date++;
		else Time_Set_Vaule.date=29;
	      }
	      else
	      {
		if(Time_Set_Vaule.date<28)Time_Set_Vaule.date++;
		else Time_Set_Vaule.date=28;
	      }
	    }
	  }
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.hour);
	  
	  Show_Str(116,89,time1);
	  
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.minute);
	  Show_Str(156,89,time1);
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.second);
	  Show_Str(196,89,time1);
	  
	  sprintf((char*)time1,"%04d",(Time_Set_Vaule.year+2000));
	  Show_Str(116,149,time1);
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.month));
	  
	  Show_Str(172,149,time1);
	  
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.date));
	  LCD_Invert(1);
	  Show_Str(212,149,time1);
	  LCD_Invert(0);
	  
	  Show_Str(80,200,"取消");
	  Show_Str(188,200,"确定");
	}break;
      case 7:
	{
	  if(key==15)
	  {
	    
	    HW_flag=1;
	    Updata_flag=0;
	    Time_flag=0;
	    Clear_LCD(0,0,320,240);
	    PrintGB(112,4,"硬件设置");
	    Fill_Rect(0,25,320,26);
	    return;
	  }
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.hour);
	  
	  Show_Str(116,89,time1);
	  
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.minute);
	  Show_Str(156,89,time1);
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.second);
	  Show_Str(196,89,time1);
	  
	  sprintf((char*)time1,"%04d",(Time_Set_Vaule.year+2000));
	  Show_Str(116,149,time1);
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.month));
	  Show_Str(172,149,time1);
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.date));
	  Show_Str(212,149,time1);
	  LCD_Invert(1);
	  Show_Str(80,200,"取消");
	  LCD_Invert(0);
	  Show_Str(188,200,"确定");
	}break;
      case 8:
	{
	  if(key==15)
	  {
	    Ds1302_Set_Time(&Time_Set_Vaule);
	    Clear_LCD(0,0,320,240);
	    Draw_Rect(64,80,256,160);
	    Show_Str(100,120,"时间修改成功");
	    Delayms(500);
	    HW_flag=1;
	    Time_flag=0;
	    Updata_flag=0;
	    Clear_LCD(0,0,320,240);
	    PrintGB(112,4,"硬件设置");
	    Fill_Rect(0,25,320,26);
	    return;
	  }
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.hour);
	  
	  Show_Str(116,89,time1);
	  
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.minute);
	  Show_Str(156,89,time1);
	  sprintf((char*)time1,"%02d",Time_Set_Vaule.second);
	  Show_Str(196,89,time1);
	  
	  sprintf((char*)time1,"%04d",(Time_Set_Vaule.year+2000));
	  Show_Str(116,149,time1);
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.month));
	  Show_Str(172,149,time1);
	  sprintf((char*)time1,"%02d",(Time_Set_Vaule.date));
	  Show_Str(212,149,time1);
	  
	  Show_Str(80,200,"取消");
	  LCD_Invert(1);
	  Show_Str(188,200,"确定");
	  LCD_Invert(0);
	}break;
      }
      
    }break;
  case 2:
    {
      if(key==4)
      {
	if(Uart_Set_Num>1)Uart_Set_Num--;
	else Uart_Set_Num=6;
      }
      else if(key==8)
      {
	if(Uart_Set_Num<6)Uart_Set_Num++;
	else Uart_Set_Num=1;
      }
      switch(Uart_Set_Num)
      {
      case 1:
	{
	  if(key==12)
	  {
	    if(uart_cnt>0)uart_cnt--;
	    
	    Uart_Baud_Save=Uart_Baud[uart_cnt];
	  }
	  else if(key==16)
	  {
	    if(uart_cnt<10)uart_cnt++;
	    
	    Uart_Baud_Save=Uart_Baud[uart_cnt];
	  }
	  sprintf((char*)time1,"%06d",Uart_Baud_Save);
	  LCD_Invert(1);
	  Show_Str(120,50,time1);
	  LCD_Invert(0);
	  sprintf((char*)time1,"%d",Uart_Bits_Save);
	  Show_Str(120,90,time1);
	  sprintf((char*)time1,"%d",Uart_Stop_Save);
	  Show_Str(120,130,time1);
	  switch(Uart_Parity_Save)
	  {
	  case 0:
	    {
	      Show_Str(120,170,"NONE");
	    }break;
	  case 1:
	    {
	      Show_Str(120,170,"ODD ");
	    }break;
	  case 2:
	    {
	      Show_Str(120,170,"EVEN");
	    }break;
	  }
	  Show_Str(80,200,"取消");
	  Show_Str(188,200,"确定");
	}break;
      case 2:
	{
	  if(key==12)
	  {
	    if(isUart_8Bits)
	    {
	      isUart_8Bits=false;
	      Uart_Bits_Save=Uart_Bits[1];
	    }
	    
	  }
	  else if(key==16)
	  {
	    if(!isUart_8Bits)
	    {
	      isUart_8Bits=false;
	      Uart_Bits_Save=Uart_Bits[0];
	    }
	    
	  }
	  
	  sprintf((char*)time1,"%06d",Uart_Baud_Save);
	  
	  Show_Str(120,50,time1);
	  
	  sprintf((char*)time1,"%d",Uart_Bits_Save);
	  LCD_Invert(1);
	  Show_Str(120,90,time1);
	  LCD_Invert(0);
	  sprintf((char*)time1,"%d",Uart_Stop_Save);
	  Show_Str(120,130,time1);
	  switch(Uart_Parity_Save)
	  {
	  case 0:
	    {
	      Show_Str(120,170,"NONE");
	    }break;
	  case 1:
	    {
	      Show_Str(120,170,"ODD ");
	    }break;
	  case 2:
	    {
	      Show_Str(120,170,"EVEN");
	    }break;
	  }
	  Show_Str(80,200,"取消");
	  Show_Str(188,200,"确定");
	}break;
      case 3:
	{
	  if(key==12)
	  {
	    if(isUart_1Stop)
	    {
	      isUart_1Stop=false;
	      Uart_Stop_Save=Uart_Stop[1];
	    }
	  }
	  else if(key==16)
	  {
	    if(!isUart_1Stop)
	    {
	      isUart_1Stop=true;
	      Uart_Stop_Save=Uart_Stop[0];
	    }
	    
	  }
	  
	  sprintf((char*)time1,"%06d",Uart_Baud_Save);
	  
	  Show_Str(120,50,time1);
	  
	  sprintf((char*)time1,"%d",Uart_Bits_Save);
	  
	  Show_Str(120,90,time1);
	  
	  sprintf((char*)time1,"%d",Uart_Stop_Save);
	  LCD_Invert(1);
	  Show_Str(120,130,time1);
	  LCD_Invert(0);
	  switch(Uart_Parity_Save)
	  {
	  case 0:
	    {
	      Show_Str(120,170,"NONE");
	    }break;
	  case 1:
	    {
	      Show_Str(120,170,"ODD ");
	    }break;
	  case 2:
	    {
	      Show_Str(120,170,"EVEN");
	    }break;
	  }
	  Show_Str(80,200,"取消");
	  Show_Str(188,200,"确定");
	}break;
      case 4:
	{
	  if(key==12)
	  {
	    if(uart_parity_cnt>0)uart_parity_cnt--;
	    Uart_Parity_Save=uart_parity_cnt;
	  }
	  else if(key==16)
	  {
	    if(uart_parity_cnt<2)uart_parity_cnt++;
	    Uart_Parity_Save=uart_parity_cnt;
	  }
	  
	  
	  sprintf((char*)time1,"%06d",Uart_Baud_Save);
	  
	  Show_Str(120,50,time1);
	  
	  sprintf((char*)time1,"%d",Uart_Bits_Save);
	  
	  Show_Str(120,90,time1);
	  
	  sprintf((char*)time1,"%d",Uart_Stop_Save);
	  
	  Show_Str(120,130,time1);
	  
	  LCD_Invert(1);
	  switch(Uart_Parity_Save)
	  {
	  case 0:
	    {
	      Show_Str(120,170,"NONE");
	    }break;
	  case 1:
	    {
	      Show_Str(120,170,"ODD ");
	    }break;
	  case 2:
	    {
	      Show_Str(120,170,"EVEN");
	    }break;
	  }
	  LCD_Invert(0);
	  Show_Str(80,200,"取消");
	  Show_Str(188,200,"确定");
	}break;
      case 5:
	{
	  sprintf((char*)time1,"%06d",Uart_Baud_Save);
	  
	  Show_Str(120,50,time1);
	  
	  sprintf((char*)time1,"%d",Uart_Bits_Save);
	  
	  Show_Str(120,90,time1);
	  
	  sprintf((char*)time1,"%d",Uart_Stop_Save);
	  
	  Show_Str(120,130,time1);
	  
	  
	  switch(Uart_Parity_Save)
	  {
	  case 0:
	    {
	      Show_Str(120,170,"NONE");
	    }break;
	  case 1:
	    {
	      Show_Str(120,170,"ODD ");
	    }break;
	  case 2:
	    {
	      Show_Str(120,170,"EVEN");
	    }break;
	  }
	  
	  LCD_Invert(1);
	  Show_Str(80,200,"取消");
	  LCD_Invert(0);
	  Show_Str(188,200,"确定");
	  if(key==15)
	  {
	    
	    HW_flag=1;
	    Updata_flag=0;
	    Time_flag=0;
	    Clear_LCD(0,0,320,240);
	    PrintGB(112,4,"硬件设置");
	    Fill_Rect(0,25,320,26);
	    return;
	  }
	}break;
      case 6:
	{
	  sprintf((char*)time1,"%06d",Uart_Baud_Save);
	  
	  Show_Str(120,50,time1);
	  
	  sprintf((char*)time1,"%d",Uart_Bits_Save);
	  
	  Show_Str(120,90,time1);
	  
	  sprintf((char*)time1,"%d",Uart_Stop_Save);
	  
	  Show_Str(120,130,time1);
	  
	  
	  switch(Uart_Parity_Save)
	  {
	  case 0:
	    {
	      Show_Str(120,170,"NONE");
	    }break;
	  case 1:
	    {
	      Show_Str(120,170,"ODD ");
	    }break;
	  case 2:
	    {
	      Show_Str(120,170,"EVEN");
	    }break;
	  }
	  
	  
	  Show_Str(80,200,"取消");
	  
	  LCD_Invert(1);
	  Show_Str(188,200,"确定");
	  LCD_Invert(0);
	  if(key==15)
	  {
	    Clear_LCD(0,0,320,240);
	    Draw_Rect(64,80,256,160);
	    Show_Str(100,120,"串口修改成功");
	    Delayms(500);
	    HW_flag=1;
	    Updata_flag=0;
	    Time_flag=0;
	    Clear_LCD(0,0,320,240);
	    PrintGB(112,4,"硬件设置");
	    Fill_Rect(0,25,320,26);
	    return;
	  }
	}break;
      }
    }break;
  case 3:
    {
      Calibrate_Flag=true;
      switch(key)
      {
      case 1:
	{
	  if((CalibrationFlow>0)&&(CalibrationFlow<10)&&NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<3)
	  {
	    CalibrationChar[CalibrationCH-1][CalibrationFlow][NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]]=1;
	    NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]++;
	  }
	  else if((CalibrationFlow==10)&&(NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<4))
	  {
	    CalibrationChar[CalibrationCH-1][10][NumOfCalibrationChar[CalibrationCH-1][10]]=1;
	    NumOfCalibrationChar[CalibrationCH-1][10]++;
	  }
	}break;
      case 2:
	{
	  if((CalibrationFlow>0)&&(CalibrationFlow<10)&&NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<3)
	  {
	    CalibrationChar[CalibrationCH-1][CalibrationFlow][NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]]=2;
	    NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]++;
	  }
	  else if((CalibrationFlow==10)&&(NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<4))
	  {
	    CalibrationChar[CalibrationCH-1][10][NumOfCalibrationChar[CalibrationCH-1][10]]=2;
	    NumOfCalibrationChar[CalibrationCH-1][10]++;
	  }
	}break;
      case 3:
	{
	  if((CalibrationFlow>0)&&(CalibrationFlow<10)&&NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<3)
	  {
	    CalibrationChar[CalibrationCH-1][CalibrationFlow][NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]]=3;
	    NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]++;
	  }
	  else if((CalibrationFlow==10)&&(NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<4))
	  {
	    CalibrationChar[CalibrationCH-1][10][NumOfCalibrationChar[CalibrationCH-1][10]]=3;
	    NumOfCalibrationChar[CalibrationCH-1][10]++;
	  }
	}break;
      case 5:
	{
	  if((CalibrationFlow>0)&&(CalibrationFlow<10)&&NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<3)
	  {
	    CalibrationChar[CalibrationCH-1][CalibrationFlow][NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]]=4;
	    NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]++;
	  }
	  else if((CalibrationFlow==10)&&(NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<4))
	  {
	    CalibrationChar[CalibrationCH-1][10][NumOfCalibrationChar[CalibrationCH-1][10]]=4;
	    NumOfCalibrationChar[CalibrationCH-1][10]++;
	  }
	}break;
      case 6:
	{
	  if((CalibrationFlow>0)&&(CalibrationFlow<10)&&NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<3)
	  {
	    CalibrationChar[CalibrationCH-1][CalibrationFlow][NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]]=5;
	    NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]++;
	  }
	  else if((CalibrationFlow==10)&&(NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<4))
	  {
	    CalibrationChar[CalibrationCH-1][10][NumOfCalibrationChar[CalibrationCH-1][10]]=5;
	    NumOfCalibrationChar[CalibrationCH-1][10]++;
	  }
	}break;
      case 7:
	{
	  if((CalibrationFlow>0)&&(CalibrationFlow<10)&&NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<3)
	  {
	    CalibrationChar[CalibrationCH-1][CalibrationFlow][NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]]=6;
	    NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]++;
	  }
	  else if((CalibrationFlow==10)&&(NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<4))
	  {
	    CalibrationChar[CalibrationCH-1][10][NumOfCalibrationChar[CalibrationCH-1][10]]=6;
	    NumOfCalibrationChar[CalibrationCH-1][10]++;
	  }
	}break;
      case 9:
	{
	  if((CalibrationFlow>0)&&(CalibrationFlow<10)&&NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<3)
	  {
	    CalibrationChar[CalibrationCH-1][CalibrationFlow][NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]]=7;
	    NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]++;
	  }
	  else if((CalibrationFlow==10)&&(NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<4))
	  {
	    CalibrationChar[CalibrationCH-1][10][NumOfCalibrationChar[CalibrationCH-1][10]]=7;
	    NumOfCalibrationChar[CalibrationCH-1][10]++;
	  }
	}break;
      case 10:
	{
	  if((CalibrationFlow>0)&&(CalibrationFlow<10)&&NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<3)
	  {
	    CalibrationChar[CalibrationCH-1][CalibrationFlow][NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]]=8;
	    NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]++;
	  }
	  else if((CalibrationFlow==10)&&(NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<4))
	  {
	    CalibrationChar[CalibrationCH-1][10][NumOfCalibrationChar[CalibrationCH-1][10]]=8;
	    NumOfCalibrationChar[CalibrationCH-1][10]++;
	  }
	}break;
      case 11:
	{
	  if((CalibrationFlow>0)&&(CalibrationFlow<10)&&NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<3)
	  {
	    CalibrationChar[CalibrationCH-1][CalibrationFlow][NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]]=9;
	    NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]++;
	  }
	  else if((CalibrationFlow==10)&&(NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<4))
	  {
	    CalibrationChar[CalibrationCH-1][10][NumOfCalibrationChar[CalibrationCH-1][10]]=9;
	    NumOfCalibrationChar[CalibrationCH-1][10]++;
	  }
	}break;
      case 14:
	{
	  if((CalibrationFlow>0)&&(CalibrationFlow<10)&&NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<3)
	  {
	    CalibrationChar[CalibrationCH-1][CalibrationFlow][NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]]=0;
	    NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]++;
	  }
	  else if((CalibrationFlow==10)&&(NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]<4))
	  {
	    CalibrationChar[CalibrationCH-1][10][NumOfCalibrationChar[CalibrationCH-1][10]]=0;
	    NumOfCalibrationChar[CalibrationCH-1][10]++;
	  }
	}break;
      case 4:
	{
	  if(CalibrationFlow>0)CalibrationFlow--;
	}break;
      case 8:
	{
	  if(CalibrationFlow<10)CalibrationFlow++;
	}break;
      case 12:
	{
	  if(CalibrationFlow==0)
	  {
	    if(CalibrationCH>1)CalibrationCH--;
	  }
	  else if(CalibrationFlow<11)
	  {
	    if(NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]>1)
	    {
              CalibrationChar[CalibrationCH-1][CalibrationFlow][NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]-1]=0;
              NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]--;
	    }
	    else if(NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]==1) 
            {
              CalibrationChar[CalibrationCH-1][CalibrationFlow][NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]-1]=0;
              NumOfCalibrationChar[CalibrationCH-1][CalibrationFlow]=0;
            }
	  }
	}break;
      case 16:
	{
	  if(CalibrationFlow==0)
	  {
	    if(CalibrationCH<4)CalibrationCH++;
	  }
	  else if(CalibrationFlow<6)
	  {
	    CalibrationFlow+=5;
	  }  
	  else if(CalibrationFlow<11)
	  {
	    CalibrationFlow-=5;
	  }
	}break;
      case 15:
	{
          if(CalibrationVaule[CalibrationCH-1][CalibrationFlow]>0)
            switch(CalibrationFlow)
            {
            case 1:
              {
                
                //System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1]=CalibrationVaule[CalibrationCH-1][CalibrationFlow]/100.0;
                //FM24C64_WRITE_MUL(CALIBRATION_STORAGE_ADD+(CalibrationCH-1)*10*4+(CalibrationFlow-1)*4,(uint8_t *)&System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1],4);
              }break;
	    case 2:
              {
                
                System_Calibration.Calibration_Flow[CalibrationCH-1][0]=CalibrationVaule[CalibrationCH-1][2];
                //System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1]=CalibrationVaule[CalibrationCH-1][CalibrationFlow]/200.0;
                //FM24C64_WRITE_MUL(CALIBRATION_STORAGE_ADD+(CalibrationCH-1)*10*4+(CalibrationFlow-1)*4,(uint8_t *)&System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1],4);
              }break;
	    case 3:
              {
                 System_Calibration.Calibration_Flow[CalibrationCH-1][1]=CalibrationVaule[CalibrationCH-1][3];
                //System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1]=CalibrationVaule[CalibrationCH-1][CalibrationFlow]/300.0;
                //FM24C64_WRITE_MUL(CALIBRATION_STORAGE_ADD+(CalibrationCH-1)*10*4+(CalibrationFlow-1)*4,(uint8_t *)&System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1],4);
              }break;
	    case 4:
              {
                //System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1]=CalibrationVaule[CalibrationCH-1][CalibrationFlow]/400.0;
                //FM24C64_WRITE_MUL(CALIBRATION_STORAGE_ADD+(CalibrationCH-1)*10*4+(CalibrationFlow-1)*4,(uint8_t *)&System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1],4);
              }break;
	    case 5:
              {
                //System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1]=CalibrationVaule[CalibrationCH-1][CalibrationFlow]/500.0;
                //FM24C64_WRITE_MUL(CALIBRATION_STORAGE_ADD+(CalibrationCH-1)*10*4+(CalibrationFlow-1)*4,(uint8_t *)&System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1],4);
              }break;
	    case 6:
              {
                 System_Calibration.Calibration_Flow[CalibrationCH-1][2]=CalibrationVaule[CalibrationCH-1][6];
                //System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1]=CalibrationVaule[CalibrationCH-1][CalibrationFlow]/600.0;
                //FM24C64_WRITE_MUL(CALIBRATION_STORAGE_ADD+(CalibrationCH-1)*10*4+(CalibrationFlow-1)*4,(uint8_t *)&System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1],4);
              }break;
	    case 7:
              {
                //System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1]=CalibrationVaule[CalibrationCH-1][CalibrationFlow]/700.0;
                //FM24C64_WRITE_MUL(CALIBRATION_STORAGE_ADD+(CalibrationCH-1)*10*4+(CalibrationFlow-1)*4,(uint8_t *)&System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1],4);
              }break;
	    case 8:
              {
                //System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1]=CalibrationVaule[CalibrationCH-1][CalibrationFlow]/800.0;
                //FM24C64_WRITE_MUL(CALIBRATION_STORAGE_ADD+(CalibrationCH-1)*10*4+(CalibrationFlow-1)*4,(uint8_t *)&System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1],4);
              }break;
	    case 9:
              {
                 System_Calibration.Calibration_Flow[CalibrationCH-1][3]=CalibrationVaule[CalibrationCH-1][9];
                //System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1]=CalibrationVaule[CalibrationCH-1][CalibrationFlow]/900.0;
                //FM24C64_WRITE_MUL(CALIBRATION_STORAGE_ADD+(CalibrationCH-1)*10*4+(CalibrationFlow-1)*4,(uint8_t *)&System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1],4);
              }break;
	    case 10:
              {
                //System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1]=CalibrationVaule[CalibrationCH-1][CalibrationFlow]/1000.0;
                //FM24C64_WRITE_MUL(CALIBRATION_STORAGE_ADD+(CalibrationCH-1)*10*4+(CalibrationFlow-1)*4,(uint8_t *)&System_Calibration.Calibration_Point[CalibrationCH-1][CalibrationFlow-1],4);
              }break;
            }
	}break;
      }
      
      if(Last_CalibrationCH!=CalibrationCH)Switch_CalibrationCH((CHn_Type)CalibrationCH);
      if(CalibrationFlow!=Last_CalibrationFlow)Switch_FlowCalibration(CalibrationFlow,Last_CalibrationFlow);
      Disp_InputNum();
      Disp_NowFlow((CHn_Type)CalibrationCH,CalibrationFlow,Last_CalibrationFlow);
      Last_CalibrationFlow=CalibrationFlow;
      Last_CalibrationCH=CalibrationCH;
    }break;
  }
}
void Disp_TimeSetWindow(void)
{
  uint8_t time1[6];
  memcpy(&Time_Set_Vaule,&TimeValue,sizeof(TimeValue));
  Time_Set_Num=1;
  //  sprintf((char*)time1,"%02d : %02d : %02d",TimeValue.hour,TimeValue.minute,TimeValue.second);
  //  sprintf((char*)time2,"%4d - %02d - %02d",(TimeValue.year+2000),TimeValue.month,TimeValue.date);
  Clear_LCD(0,0,320,240);
  Fill_Rect(0,25,320,26);
  Show_Str(108,4,"系统时间设置");
  Show_Str(80,90,"时间");
  Show_Str(80,150,"日期"); 
  sprintf((char*)time1,"%02d",TimeValue.hour);
  LCD_Invert(1);
  Show_Str(116,89,time1);
  LCD_Invert(0);
  Show_Str(140,89,":");
  sprintf((char*)time1,"%02d",TimeValue.minute);
  Show_Str(156,89,time1);
  Show_Str(180,89,":");
  sprintf((char*)time1,"%02d",TimeValue.second);
  Show_Str(196,89,time1);
  
  Draw_Rect(114,87,133,106);
  Draw_Rect(154,87,173,106);
  Draw_Rect(194,87,213,106);
  sprintf((char*)time1,"%04d",(TimeValue.year+2000));
  Show_Str(116,149,time1);
  Show_Str(156,149,"-");
  sprintf((char*)time1,"%02d",(TimeValue.month));
  Show_Str(172,149,time1);
  Show_Str(196,149,"-");
  sprintf((char*)time1,"%02d",(TimeValue.date));
  Show_Str(212,149,time1);
  Draw_Rect(114,147,149,166);
  Draw_Rect(170,147,189,166);
  Draw_Rect(210,147,229,166);
  
  Show_Str(80,200,"取消");
  Draw_Rect(78,198,113,217);  
  Draw_Rect(186,198,221,217);
  Show_Str(188,200,"确定");
  
  
}
void Disp_BaudSetWindow(void)
{
  uint8_t temp[8];
  Clear_LCD(0,0,320,240);
  Fill_Rect(0,25,320,26);
  Show_Str(104,4,"串口设置"); 
  
  sprintf((char*)temp,"%06d",Uart_Baud_Save);
  Show_Str(60,50,"波特率");
  LCD_Invert(1);
  Show_Str(120,50,temp);
  LCD_Invert(0);
  Draw_Rect(118,48,169,67);
  sprintf((char*)temp,"%d",Uart_Bits_Save);
  Show_Str(60,90,"数据位");
  Show_Str(120,90,temp);
  Draw_Rect(118,88,129,107);
  sprintf((char*)temp,"%d",Uart_Stop_Save);
  Show_Str(60,130,"停止位");
  Show_Str(120,130,temp);
  Draw_Rect(118,128,129,147);
  
  switch(Uart_Parity_Save)
  {
  case 0:
    {
      Show_Str(120,170,"NONE");
    }break;
  case 1:
    {
      Show_Str(120,170,"ODD ");
    }break;
  case 2:
    {
      Show_Str(120,170,"EVEN");
    }
  }
  Show_Str(72,170,"校验");
  
  Draw_Rect(118,168,153,187);
  
  
  
  
  Show_Str(80,200,"取消");
  Draw_Rect(78,198,113,217);  
  Draw_Rect(186,198,221,217);
  Show_Str(188,200,"确定");
}
void Disp_CalibrationWindow(void)
{
  Clear_LCD(0,0,320,240);
  Switch_CalibrationCH((CHn_Type)CalibrationCH);
  PrintGB(28,32,"输出");
  PrintGB(188,32,"输出");
  PrintGB(124,32,"实时");
  PrintGB(88,32,"校正");
  PrintGB(248,32,"校正");
  PrintGB(284,32,"实时");
  PrintGB_NUM(28,52,"100");
  PrintGB_NUM(28,92,"200");
  PrintGB_NUM(28,132,"300");
  PrintGB_NUM(28,172,"400");
  PrintGB_NUM(28,212,"500");
  PrintGB_NUM(188,52,"600");
  PrintGB_NUM(188,92,"700");
  PrintGB_NUM(188,132,"800");
  PrintGB_NUM(188,172,"900");
  PrintGB_NUM(180,212,"1000");
  
  PrintGB_NUM(88,52,"000");
  PrintGB_NUM(88,92,"000");
  PrintGB_NUM(88,132,"000");
  PrintGB_NUM(88,172,"000");
  PrintGB_NUM(88,212,"000");
  PrintGB_NUM(248,52,"000");
  PrintGB_NUM(248,92,"000");
  PrintGB_NUM(248,132,"000");
  PrintGB_NUM(248,172,"000");
  PrintGB_NUM(240,212,"0000");
  
  Draw_Rect(86,50,113,69);
  Draw_Rect(86,90,113,109);
  Draw_Rect(86,130,113,149);
  Draw_Rect(86,170,113,189);
  Draw_Rect(86,210,113,229);
  Draw_Rect(246,50,273,69);
  Draw_Rect(246,90,273,109);
  Draw_Rect(246,130,273,149);
  Draw_Rect(246,170,273,189);
  Draw_Rect(238,210,273,229);
  
}
void Switch_CalibrationCH(CHn_Type CHn)
{
  Clear_LCD(0,0,320,26);
  switch(CHn)
  {
  case CH1:
    {
      
      PrintGB(112,4,"第一通道校准");
      Draw_Line(104,2,104,20);
      Draw_Pic(85,2,105,22,(u8*)gImage_triangle_le,length(gImage_triangle_le));
      Draw_Pic(210,2,230,22,(u8*)gImage_triangle_rf,length(gImage_triangle_rf));
      Fill_Rect(0,24,320,26);
      
    }break;
  case CH2:
    {
      
      PrintGB(112,4,"第二通道校准");
      Draw_Pic(85,2,105,22,(u8*)gImage_triangle_lf,length(gImage_triangle_lf));
      Draw_Pic(210,2,230,22,(u8*)gImage_triangle_rf,length(gImage_triangle_rf));
      Fill_Rect(0,24,320,26);
    }break;
  case CH3:
    {
      
      PrintGB(112,4,"第三通道校准");
      Draw_Pic(85,2,105,22,(u8*)gImage_triangle_lf,length(gImage_triangle_lf));
      Draw_Pic(210,2,230,22,(u8*)gImage_triangle_rf,length(gImage_triangle_rf));
      Fill_Rect(0,24,320,26);
    }break;
  case CH4:
    {
      
      PrintGB(112,4,"第四通道校准");  
      Draw_Pic(85,2,105,22,(u8*)gImage_triangle_lf,length(gImage_triangle_lf));
      Draw_Pic(210,2,230,22,(u8*)gImage_triangle_re,length(gImage_triangle_re));
      Fill_Rect(0,24,320,26);
    }break;
  }
}
void Switch_FlowCalibration(uint8_t flown,uint8_t last_flown)
{
  
  switch(flown)
  {
  case 0:
    {
      Clear_LastArrow(last_flown);
      for(uint8_t i=0;i<4;i++)
      {
        Calibrate_State[i]=Stop;
        FlowPID_struct[i].SetPoint=0;
      }
      
      
    }break;
  case 1:
    {
      Draw_Arrow(10,60);
      Clear_LastArrow(last_flown);
      
      Calibrate_State[CalibrationCH-1]=Runing;
      FlowPID_struct[CalibrationCH-1].SetPoint=0.1;
    }break;
  case 2:
    {
      Draw_Arrow(10,100);
      Clear_LastArrow(last_flown);
      Calibrate_State[CalibrationCH-1]=Runing;
      FlowPID_struct[CalibrationCH-1].SetPoint=0.2;
    }break;
  case 3:
    {
      Draw_Arrow(10,140);
      Clear_LastArrow(last_flown);
      Calibrate_State[CalibrationCH-1]=Runing;
      FlowPID_struct[CalibrationCH-1].SetPoint=0.3;
    }break;
  case 4:
    {
      Draw_Arrow(10,180);
      Clear_LastArrow(last_flown);
      Calibrate_State[CalibrationCH-1]=Runing;
      FlowPID_struct[CalibrationCH-1].SetPoint=0.4;
    }break;
  case 5:
    {
      Draw_Arrow(10,220);
      Clear_LastArrow(last_flown);
      Calibrate_State[CalibrationCH-1]=Runing;
      FlowPID_struct[CalibrationCH-1].SetPoint=0.5;
    }break;
  case 6:
    {
      Draw_Arrow(170,60);
      Clear_LastArrow(last_flown);
      Calibrate_State[CalibrationCH-1]=Runing;
      FlowPID_struct[CalibrationCH-1].SetPoint=0.6;
    }break;
  case 7:
    {
      Draw_Arrow(170,100);
      Clear_LastArrow(last_flown);
      Calibrate_State[CalibrationCH-1]=Runing;
      FlowPID_struct[CalibrationCH-1].SetPoint=0.7;
    }break;
  case 8:
    {
      Draw_Arrow(170,140);
      Clear_LastArrow(last_flown);
      Calibrate_State[CalibrationCH-1]=Runing;
      FlowPID_struct[CalibrationCH-1].SetPoint=0.8;
    }break;
  case 9:
    {
      Draw_Arrow(170,180);
      Clear_LastArrow(last_flown);
      Calibrate_State[CalibrationCH-1]=Runing;
      FlowPID_struct[CalibrationCH-1].SetPoint=0.9;
    }break;
  case 10:
    {
      Draw_Arrow(170,220);
      Clear_LastArrow(last_flown);
      Calibrate_State[CalibrationCH-1]=Runing;
      FlowPID_struct[CalibrationCH-1].SetPoint=1.0;
    }break;
  }
  
}
void Clear_LastArrow(uint8_t lastarrow)
{
  if((lastarrow>0)&&(lastarrow<11))
  {
    switch(lastarrow)
    {
    case 1:
      {
	Clear_Arrow(10,60);
      }break;
    case 2:
      {
	Clear_Arrow(10,100);
      }break;
    case 3:
      {
	Clear_Arrow(10,140);
      }break;
    case 4:
      {
	Clear_Arrow(10,180);
      }break;
    case 5:
      {
	Clear_Arrow(10,220);
      }break;
    case 6:
      {
	Clear_Arrow(170,60);
      }break;
    case 7:
      {
	Clear_Arrow(170,100);
      }break;
    case 8:
      {
	Clear_Arrow(170,140);
      }break;
    case 9:
      {
	Clear_Arrow(170,180);
      }break;
    case 10:
      {
	Clear_Arrow(170,220);
      }break;
    }
  }
}
void Disp_InputNum(void)
{
  uint8_t buff[6]={'0','0','0','\0','\0','\0'};
  for(uint8_t i=1;i<10;i++)
  {
    CalibrationVaule[CalibrationCH-1][i]=CalibrationChar[CalibrationCH-1][i][0]*100+CalibrationChar[CalibrationCH-1][i][1]*10+CalibrationChar[CalibrationCH-1][i][2];
  }
  CalibrationVaule[CalibrationCH-1][10]=CalibrationChar[CalibrationCH-1][10][0]*1000+CalibrationChar[CalibrationCH-1][10][1]*100+CalibrationChar[CalibrationCH-1][10][2]*10+CalibrationChar[CalibrationCH-1][10][3];
  
  sprintf((char*)buff,"%03d",CalibrationVaule[CalibrationCH-1][1]);
  PrintGB_NUM(88,52,buff);
  sprintf((char*)buff,"%03d",CalibrationVaule[CalibrationCH-1][2]);
  PrintGB_NUM(88,92,buff);
  sprintf((char*)buff,"%03d",CalibrationVaule[CalibrationCH-1][3]);
  PrintGB_NUM(88,132,buff);
  sprintf((char*)buff,"%03d",CalibrationVaule[CalibrationCH-1][4]);
  PrintGB_NUM(88,172,buff);
  sprintf((char*)buff,"%03d",CalibrationVaule[CalibrationCH-1][5]);
  PrintGB_NUM(88,212,buff);
  sprintf((char*)buff,"%03d",CalibrationVaule[CalibrationCH-1][6]);
  PrintGB_NUM(248,52,buff);
  sprintf((char*)buff,"%03d",CalibrationVaule[CalibrationCH-1][7]);
  PrintGB_NUM(248,92,buff);
  sprintf((char*)buff,"%03d",CalibrationVaule[CalibrationCH-1][8]);
  PrintGB_NUM(248,132,buff);
  sprintf((char*)buff,"%03d",CalibrationVaule[CalibrationCH-1][9]);
  PrintGB_NUM(248,172,buff);
  sprintf((char*)buff,"%04d",CalibrationVaule[CalibrationCH-1][10]);
  PrintGB_NUM(240,212,buff);
}
void Disp_NowFlow(CHn_Type Flow_CHn,uint8_t Flow_N,uint8_t Last_Flow_N)
{
  uint8_t temp_buf[6]={0};
  
  sprintf((char*)temp_buf,"%04d",(uint16_t)FlowPID_struct[Flow_CHn-1].Flow_Value);
  if((Flow_N>=1)&&(Flow_N<=5))PrintGB_NUM(124,52+(Flow_N-1)*40,temp_buf);
  else if((Flow_N>=6)&&(Flow_N<=10))PrintGB_NUM(280,52+(Flow_N-6)*40,temp_buf);
  if(Last_Flow_N!=Flow_N)
  {
    memset(temp_buf,0x20,4);
    if((Last_Flow_N>=1)&&(Last_Flow_N<=5))Clear_LCD(124,52+(Last_Flow_N-1)*40,156,68+(Last_Flow_N-1)*40);
      
    else if((Last_Flow_N>=6)&&(Last_Flow_N<=10))Clear_LCD(280,52+(Last_Flow_N-6)*40,312,68+(Last_Flow_N-1)*40);
  }
  
  
}