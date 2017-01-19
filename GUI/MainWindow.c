#include "MainWindow.h"
#include "ConfigWindow.h"
#include "CH_SetWindow.h"
#include "SampWindow.h"
#include "Data_Window.h"
#include "PassWd_SetWindow.h"
#include "SysInfo.h"
#include "image.h"

const unsigned char gImage_temp[60] = { /* 0X00,0X01,0X24,0X00,0X0C,0X00, */
  0XF0,0X7F,0XDF,0XFF,0XFF,0X77,0X78,0X01,0XFF,0XF0,0XB0,0X7B,0X77,0XFF,0XF4,0XF7,
  0X78,0X01,0XFF,0XF0,0XF0,0X7B,0X77,0XCF,0XFF,0X7F,0XFB,0X07,0XCF,0XF0,0XA0,0X3B,
  0XFF,0XFF,0XFA,0XEA,0XBA,0X03,0XFF,0XF0,0XCA,0XBB,0X7B,0XCF,0XFF,0XAA,0XBB,0XB7,
  0XCF,0XF0,0X6A,0XBB,0XCF,0XFF,0XF3,0XC0,0X16,0X31,0XFF,0XF0,};
const unsigned char gImage_press[60] = { /* 0X00,0X01,0X24,0X00,0X0C,0X00, */
  0XDF,0XFF,0XFF,0XFF,0XF0,0XC0,0X18,0X01,0XFF,0XFF,0XBF,0XFB,0XFF,0XFF,0XFF,0X40,
  0X3B,0XDF,0XFF,0XF0,0XFF,0XFB,0XDF,0XCF,0XF0,0X80,0X7B,0XDF,0XCF,0XFF,0XFF,0X7A,
  0X03,0XFF,0XFF,0XFF,0X7B,0XDF,0XFF,0XF0,0XFF,0X7B,0XD7,0XCF,0XFF,0XFF,0X5B,0XDB,
  0XCF,0XFF,0XFF,0X9B,0XDF,0XFF,0XFF,0XFF,0XD4,0X01,0XFF,0XFF,};
const unsigned char gImage_deg[24] = { /* 0X00,0X01,0X0C,0X00,0X0C,0X00, */
  0XBF,0XFF,0X58,0XBB,0XB7,0X3F,0XEF,0XBF,0XEF,0XF1,0XEF,0XFF,0XEF,0XF0,0XEF,0XDF,
  0XF7,0XBF,0XF8,0X7F,0XFF,0XFF,0XFF,0XFF,};
uint8_t sub_menu=1;
uint8_t state_disp=1;

void Disp_MainWindow(void)
{
  PassWd_flag=0;
  HW_flag=0;
  Data_Flag=0;
  Info_flag=0;
  Channel_flag=0;
  Exit_flag=0;                            //定义密码设置标志
  state_disp=1;
  Main_flag=1;
  Clear_LCD(0,0,320,240);
  Disp_State();
  Draw_Pic(35,35,95,95,(u8*)gImage_config,length(gImage_config));
  Draw_Rect(34,34,96,96);
  // LCD_Invert(1);
  PrintGB(36,101,"硬件设置");
  // LCD_Invert(0);
  Draw_Pic(130,35,190,95,(u8*)gImage_data,length(gImage_data));
  Draw_Rect(129,34,191,96);
  
  PrintGB(128,101,"数据查询");
  Draw_Pic(225,35,285,95,(u8*)gImage_channel,length(gImage_channel));
  Draw_Rect(224,34,286,96);
  PrintGB(224,101,"通道管理");
  Draw_Pic(35,140,95,200,(u8*)gImage_passwd,length(gImage_passwd));
  Draw_Rect(34,139,96,201);
  PrintGB(36,206,"密码设置");
  Draw_Pic(130,140,190,200,(u8*)gImage_system,length(gImage_system));
  Draw_Rect(129,139,189,201);
  PrintGB(128,206,"系统信息");
  Draw_Pic(225,140,285,200,(u8*)gImage_exit,length(gImage_exit));
  Draw_Rect(224,139,284,201);
  PrintGB(224,206,"采样状态");
  Change_menu();
  //delay_ms(10);
  
}
void Change_menu(void)
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
  if(key==12)
  {
    if(sub_menu>1)
      sub_menu--;
    else sub_menu=6;
  }
  if((key==16))
  {
    if(sub_menu<6)
      sub_menu++;
    else sub_menu=1;
  }
  else if(key==4)
  {
     if(sub_menu>3)
      sub_menu-=3;
    
  }
   else if(key==8)
  {
    if(sub_menu<4)
      sub_menu+=3;
  }
  else if(key==15)
  {
    switch(sub_menu)
    {
    case 1:
      {
	HW_flag=1;
	Main_flag=0;
	state_disp=0;
	Disp_ConfigWindow();
	return;
      }break;
    case 2:
      {
	Data_Flag=1;
	Main_flag=0;
	state_disp=0;
	Disp_Data();
	return;
	
      }break;
    case 3:
      {
	Channel_flag=1;
	Main_flag=0;
	state_disp=0;
	Disp_SetWindow();
	return;
      }break;
    case 4:
      {
	PassWd_flag=1;
	state_disp=0;
	Main_flag=0;
	PassWd_SetDisp();
	return;
      }break;
    case 5:
      {
	Info_flag=1;
	Main_flag=0;
	state_disp=0;
	Disp_Sys_Info();
	return;
      }break;
    case 6:
      {
	Exit_flag=1;
	Main_flag=0;
	state_disp=1;
	Disp_SampWindow();
	return;
      }break;
    }
  }
  switch(sub_menu)
  {
  case 1:
    {
      LCD_Invert(1);
      PrintGB(36,101,"硬件设置");
      LCD_Invert(0); 
      PrintGB(128,101,"数据查询");
      PrintGB(224,101,"通道管理");
      PrintGB(36,206,"密码设置");
      PrintGB(128,206,"系统信息");
      PrintGB(224,206,"采样状态");
    }break;
  case 2:
    {
      
      PrintGB(36,101,"硬件设置");
      
      LCD_Invert(1);
      PrintGB(128,101,"数据查询");
      LCD_Invert(0); 
      PrintGB(224,101,"通道管理");
      PrintGB(36,206,"密码设置");
      PrintGB(128,206,"系统信息");
      PrintGB(224,206,"采样状态");
    }break;
  case 3:
    {
      
      PrintGB(36,101,"硬件设置");
      PrintGB(128,101,"数据查询");
      LCD_Invert(1);
      PrintGB(224,101,"通道管理");
      LCD_Invert(0); 
      PrintGB(36,206,"密码设置");
      PrintGB(128,206,"系统信息");
      PrintGB(224,206,"采样状态");
    }break;
  case 4:
    {
      
      PrintGB(36,101,"硬件设置");
      
      PrintGB(128,101,"数据查询");
      PrintGB(224,101,"通道管理");
      LCD_Invert(1);
      PrintGB(36,206,"密码设置");
      LCD_Invert(0); 
      PrintGB(128,206,"系统信息");
      PrintGB(224,206,"采样状态");
    }break;
  case 5:
    {
      
      PrintGB(36,101,"硬件设置");
      PrintGB(128,101,"数据查询");
      PrintGB(224,101,"通道管理");
      PrintGB(36,206,"密码设置");
      LCD_Invert(1);
      PrintGB(128,206,"系统信息");
      LCD_Invert(0); 
      PrintGB(224,206,"采样状态");
    }break;
  case 6:
    {
      
      PrintGB(36,101,"硬件设置");
      PrintGB(128,101,"数据查询");
      PrintGB(224,101,"通道管理");
      PrintGB(36,206,"密码设置");
      PrintGB(128,206,"系统信息");
      LCD_Invert(1);
      PrintGB(224,206,"采样状态");
      LCD_Invert(0); 
    }break;
  default :
    {
      LCD_Invert(1);
      PrintGB(36,101,"硬件设置");
      LCD_Invert(0); 
      PrintGB(128,101,"数据查询");
      PrintGB(224,101,"通道管理");
      PrintGB(36,206,"密码设置");
      PrintGB(128,206,"系统信息");
      PrintGB(224,206,"采样状态");
    }break;
  }
}
void Disp_State(void)
{
  
  uint8_t temp[10],pres[15],time1[10],time2[12];     //测试用温度和气压数据，连接到外部传感器时更改为外部实时数据
  
  
  sprintf((char*)temp,"  %.1f",Ambience_Temp);
  sprintf((char*)pres,"%.2fkPa",MS5611_Press);
  sprintf((char*)time1,"%02d:%02d:%02d",TimeValue.hour,TimeValue.minute,TimeValue.second);
  sprintf((char*)time2,"%4d-%02d-%02d",(TimeValue.year+2000),TimeValue.month,TimeValue.date);
  //LCD_Invert(0);
  
  //  if(DispState_time==0)
  //  {
  PrintGB(112,4,"宇星科技");
  //Clear_LCD(70,0,110,12);
  Draw_Pic(4,0,40,12,(u8*)gImage_temp,length(gImage_temp));
  Draw_Pic(4,12,40,24,(u8*)gImage_press,length(gImage_press));
  Draw_Pic(88,0,100,12,(u8*)gImage_deg,length(gImage_deg));
  //  }
  
  PrintASCII(36,2,temp);
  
  PrintASCII(36,14,pres);
  PrintASCII(196,2,time1);
  PrintASCII(188,12,time2);
  
  
  Fill_Rect(0,25,320,26);
  Draw_Rect(284,4,314,20);
  Draw_Rect(282,8,284,16);
  Fill_Rect(286,6,291,18);
  Fill_Rect(293,6,298,18);
  Fill_Rect(300,6,305,18);
  Fill_Rect(307,6,312,18);
  //  if(DispState_time>100)DispState_time=1;
  //   else DispState_time++;
}
