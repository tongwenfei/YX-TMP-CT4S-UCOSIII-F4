#include "CH_SetWindow.h"
#include "MainWindow.h"
#include "ConfigWindow.h"
#include "CH_Set_image.h"
#include "SampWindow.h"
SAMPLING_MODE Sampling_Mode;
uint8_t CH_SetSelect=0,lastCH_SetSelect=3;
CHn_Type CH_N=CH1,lastCH_N=CH4;
uint16_t Temperatur_Temp=0,Flow_Temp[4]={0};
uint32_t Flow_VolumeTemp[4]={0},Definite_TimeTemp[4]={0},Intervals_TimeTemp[4]={0};
uint8_t Flow_VolumeChar[4][5]={0},NumOfFlow_VolumeChar[4]={0},Definite_TimeChar[4][5]={0},NumOfDefinite_TimeChar[4]={0},Intervals_TimeChar[4][5]={0},NumOfIntervals_TimeChar[4]={0};
bool isFixed_Volume[4]={true},isManually[4]={true},isCH_Save[4]={true};
static uint8_t Calc_BitsOfNum(uint32_t data)
{
uint8_t i=0;
	while(data!=0)
	{
	data/=10;
	i++;
	}
	return i;
}
static void Split_ToChar(uint32_t src_num,uint8_t* dest_char,uint8_t bits_of_num)
{
  while(bits_of_num)
  {
    *(dest_char+bits_of_num-1)=src_num%10;
    src_num/=10;
    bits_of_num--;
  }
}
void Disp_SetWindow(void)
{
  uint8_t temp_buf[8];
  CH_N=CH1;
  Temperatur_Temp=(uint16_t)(TempPID_struct.SetPoint*10);
  Flow_Temp[0]=(uint16_t)(FlowPID_struct[0].SetPoint*1000);
  Flow_Temp[1]=(uint16_t)(FlowPID_struct[1].SetPoint*1000);
  Flow_Temp[2]=(uint16_t)(FlowPID_struct[2].SetPoint*1000);
  Flow_Temp[3]=(uint16_t)(FlowPID_struct[3].SetPoint*1000);
  CH_SetSelect=0;
  memcpy(isFixed_Volume,Sampling_Mode.isFixed_Volume,sizeof(isFixed_Volume));
  
  memcpy(isManually,Sampling_Mode.isManually,sizeof(isManually));
  memset(isCH_Save,true,sizeof(isCH_Save));
  //isCH_Save=true;
  for(uint8_t i=0;i<4;i++)
  {
    if(isFixed_Volume[i]==true)
    {
 	 NumOfFlow_VolumeChar[i]=Sampling_Mode.NumOfFlow_Volume[i];
	Flow_VolumeTemp[i]=Sampling_Mode.Flow_Volume[i];
	NumOfDefinite_TimeChar[i]=0;
	if(NumOfFlow_VolumeChar[i]==0)memset(Flow_VolumeChar[i],0,sizeof(Flow_VolumeChar[i]));
	 else Split_ToChar(Flow_VolumeTemp[i],Flow_VolumeChar[i],NumOfFlow_VolumeChar[i]);
    }
    else
    {
      NumOfDefinite_TimeChar[i]=Sampling_Mode.NumOfDefinite_Time[i];
       Definite_TimeTemp[i]=Sampling_Mode.Definite_Time[i];
       NumOfFlow_VolumeChar[i]=0;
       if(NumOfDefinite_TimeChar[i]==0)memset(Definite_TimeChar[i],0,sizeof(Definite_TimeChar[i]));
       else Split_ToChar(Definite_TimeTemp[i],Definite_TimeChar[i],NumOfDefinite_TimeChar[i]);
    }
  }
  for(uint8_t i=0;i<4;i++)
  {
    if(isManually[i])
    {
      Intervals_TimeTemp[i]=0;
      memset(Intervals_TimeChar[i],0,sizeof(Intervals_TimeChar[i]));
      NumOfIntervals_TimeChar[i]=0;
    }
    else
    {
      Intervals_TimeTemp[i]=Sampling_Mode.Intervals_Time[i];
      NumOfIntervals_TimeChar[i]=Sampling_Mode.NumOfIntervals_Time[i];
      if(NumOfIntervals_TimeChar[i]==0)memset(Intervals_TimeChar[i],0,sizeof(Intervals_TimeChar[i]));
      else Split_ToChar(Intervals_TimeTemp[i],Intervals_TimeChar[i],NumOfIntervals_TimeChar[i]);
      
    }
  }
  
//  NumOfIntervals_TimeChar=0;
//  Intervals_TimeTemp=0;
//  for(uint8_t i=0;i<4;i++)
//  {
//    if(NumOfFlow_VolumeChar[i]!=0)
//  	memset(Flow_VolumeChar[i],0,sizeof(Flow_VolumeChar[i]));
//  }
  
  memset(Intervals_TimeChar,0,5);
  Clear_LCD(0,0,320,240);
  PrintGB(112,4,"通道管理");
  Fill_Rect(0,25,320,26);
  Disp_Set_State(CH_N);
  
  Show_Str(72,35,"温度设置:");
  Draw_Rect(155,33,196,52);
  sprintf((char*)temp_buf,"%.1f",(float)(Temperatur_Temp/10.0));
  Show_Str(160,35,temp_buf);
  Show_Str(200,35,"℃");
  
  Show_Str(72,65,"速度设置:");
  Draw_Rect(155,63,196,82);
  sprintf((char*)temp_buf,"%04d",Flow_Temp[CH_N-1]);
  Show_Str(160,65,temp_buf);
  Show_Str(200,65,"ml/min");
  
  Show_Str(72,95,"模式设置:");
  Show_Str(172,95,"定容");
  Show_Str(240,95,"时间");
  if(isFixed_Volume[CH_N-1])
  {
    CH_Checked(158,103);
    CH_Uncheck(226,103);
    Clear_LCD(170,118,244,136);
    sprintf((char*)temp_buf,"%05d",Flow_VolumeTemp[CH_N-1]);
    Show_Str(172,120,temp_buf);
    Show_Str(220,120,"ml");
    Draw_Rect(170,118,214,136);
  }
  else
  {
    CH_Uncheck(158,103);
    CH_Checked(226,103);
    Clear_LCD(170,118,244,136);
    sprintf((char*)temp_buf,"%05d",Definite_TimeTemp[CH_N-1]);
    Show_Str(172,120,temp_buf);
    Show_Str(220,120,"min");
    Draw_Rect(170,118,214,136);
  }
  
  
  Show_Str(72,150,"启动模式:");
  if(isManually[CH_N-1])
      {
	CH_Checked(156,158);
	CH_Uncheck(226,158);
	Clear_LCD(170,173,244,191);
      }
  else
  {
    CH_Uncheck(156,158);
	CH_Checked(226,158);
	sprintf((char*)temp_buf,"%05d",Intervals_TimeTemp[CH_N-1]);
	Show_Str(172,175,temp_buf);
	Show_Str(220,175,"min");
	Draw_Rect(170,173,214,191);
    
  }
  //Draw_Pic(151,151,165,165,(u8*)gImage_checked,length(gImage_checked));
  Show_Str(172,150,"手动");
 
  //Draw_Pic(224,151,238,165,(u8*)gImage_uncheck,length(gImage_uncheck));
  Show_Str(240,150,"定时");
  
  Show_Str(72,200,"取消");
  Draw_Rect(70,198,105,217);  
  Draw_Rect(178,198,213,217);
  Show_Str(180,200,"确定");
  
  
  
}
void Channel_Select(void)
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
  uint8_t temp_buf[8]={0};
  if(key==13)
  {
    
    Channel_flag=0;
    state_disp=1;
    Main_flag=1;
      if(!isManually[CH_N-1])
	  memset(&Intervals_TimeChar[CH_N-1],0,sizeof(Intervals_TimeChar[CH_N-1]));
	  if(isFixed_Volume[CH_N-1])
	  memset(&Flow_VolumeChar[CH_N-1],0,sizeof(Flow_VolumeChar));
	  else
	    memset(&Definite_TimeChar[CH_N-1],0,sizeof(Definite_TimeChar));
    Disp_MainWindow();
    return;
  }
  else if(key==4)
  {  
    if(CH_SetSelect>0)CH_SetSelect--;  
  }
  else if(key==8)
  {
    if(CH_SetSelect<5)CH_SetSelect++; 
  }
  else
  {
  switch(CH_SetSelect)
  {
  case 0:
    {
      
      if(key==12)
      {
	if(CH_N>CH1)CH_N--;
	
      }
      else if(key==16)
      {
	if(CH_N<CH4)CH_N++;
	
      }
      if(lastCH_N!=CH_N)
	
	Disp_Set_State(CH_N);
      Clear_LCD(50,33,70,53);
      Clear_LCD(50,63,70,83);
      Clear_LCD(50,93,70,113);
      Clear_LCD(50,148,70,168);
      Show_Str(180,200,"确定");
      Draw_Rect(70,198,105,217);  
      Draw_Rect(178,198,213,217);
      Show_Str(72,200,"取消");
      lastCH_N=CH_N;
    }break;
  case 1:
    {
      if(key==12)
      {
	
	if(Temperatur_Temp>150)Temperatur_Temp-=10;
	else Temperatur_Temp=150;
      }
      else if(key==16)
      {
	
	if(Temperatur_Temp<300)Temperatur_Temp+=10;
	else Temperatur_Temp=300;
      }
      sprintf((char*)temp_buf,"%.1f",(float)(Temperatur_Temp/10.0));
      Show_Str(160,35,temp_buf);
      
      Clear_LCD(50,63,70,83);
      Clear_LCD(50,93,70,113);
      Clear_LCD(50,148,70,168);
      Draw_Pic(50,33,70,53,(u8*)gImage_triangle_rf,length(gImage_triangle_rf));
      Show_Str(180,200,"确定");
      Draw_Rect(70,198,105,217);  
      Draw_Rect(178,198,213,217);
      Show_Str(72,200,"取消");
      
    }break;
  case 2:
    {
      if(key==12)
      {
	switch(CH_N)
	{
	case CH1:
	  {
	    if(Flow_Temp[CH_N-1]>0)Flow_Temp[CH_N-1]-=100;
	else Flow_Temp[CH_N-1]=0;
	  }break;
	case CH2:
	  {
	    if(Flow_Temp[CH_N-1]>0)Flow_Temp[CH_N-1]-=100;
	else Flow_Temp[CH_N-1]=0;
	  }break;
	case CH3:
	  {
	    if(Flow_Temp[CH_N-1]>0)Flow_Temp[CH_N-1]-=100;
	else Flow_Temp[CH_N-1]=0;
	  }break;
	case CH4:
	  {
	    if(Flow_Temp[CH_N-1]>0)Flow_Temp[CH_N-1]-=100;
	else Flow_Temp[CH_N-1]=0;
	  }break;
	}
	
      }
      else if(key==16)
      {
	switch(CH_N)
	{
	case CH1:
	  {
	    if(Flow_Temp[CH_N-1]<1000)Flow_Temp[CH_N-1]+=100;
	else Flow_Temp[CH_N-1]=1000;
	  }break;
	case CH2:
	  {
	    if(Flow_Temp[CH_N-1]<1000)Flow_Temp[CH_N-1]+=100;
	else Flow_Temp[CH_N-1]=1000;
	  }break;
	case CH3:
	  {
	    if(Flow_Temp[CH_N-1]<1000)Flow_Temp[CH_N-1]+=100;
	else Flow_Temp[CH_N-1]=1000;
	  }break;
	case CH4:
	  {
	    if(Flow_Temp[CH_N-1]<1000)Flow_Temp[CH_N-1]+=100;
	else Flow_Temp[CH_N-1]=1000;
	  }break;
	}
	
      }
      sprintf((char*)temp_buf,"%04d",Flow_Temp[CH_N-1]);
      Show_Str(160,65,temp_buf);
      Clear_LCD(50,33,70,53);
      
      Clear_LCD(50,93,70,113);
      Clear_LCD(50,148,70,168);
      Draw_Pic(50,63,70,83,(u8*)gImage_triangle_rf,length(gImage_triangle_rf));
      Show_Str(180,200,"确定");
      Draw_Rect(70,198,105,217);  
      Draw_Rect(178,198,213,217);
      Show_Str(72,200,"取消");
    }break;
  case 3:
    {
      
      switch(key)
      {
      case 1:
	{
	  if(isFixed_Volume[CH_N-1])
	  {
	    if(NumOfFlow_VolumeChar[CH_N-1]<5)
	  {
	    Flow_VolumeChar[CH_N-1][NumOfFlow_VolumeChar[CH_N-1]]=1;
	    NumOfFlow_VolumeChar[CH_N-1]++;
	  }
	  }
	  else
	  {
	     if(NumOfDefinite_TimeChar[CH_N-1]<5)
	  {
	    Definite_TimeChar[CH_N-1][NumOfDefinite_TimeChar[CH_N-1]]=1;
	    NumOfDefinite_TimeChar[CH_N-1]++;
	  }
	  }
	  
	}break;
      case 2:
	{
	  if(isFixed_Volume[CH_N-1])
	  {
	    if(NumOfFlow_VolumeChar[CH_N-1]<5)
	  {
	    Flow_VolumeChar[CH_N-1][NumOfFlow_VolumeChar[CH_N-1]]=2;
	    NumOfFlow_VolumeChar[CH_N-1]++;
	  }
	  }
	  else
	  {
	     if(NumOfDefinite_TimeChar[CH_N-1]<5)
	  {
	    Definite_TimeChar[CH_N-1][NumOfDefinite_TimeChar[CH_N-1]]=2;
	    NumOfDefinite_TimeChar[CH_N-1]++;
	  }
	  }
	}break;
      case 3:
	{
	 if(isFixed_Volume[CH_N-1])
	  {
	    if(NumOfFlow_VolumeChar[CH_N-1]<5)
	  {
	    Flow_VolumeChar[CH_N-1][NumOfFlow_VolumeChar[CH_N-1]]=3;
	    NumOfFlow_VolumeChar[CH_N-1]++;
	  }
	  }
	  else
	  {
	     if(NumOfDefinite_TimeChar[CH_N-1]<5)
	  {
	    Definite_TimeChar[CH_N-1][NumOfDefinite_TimeChar[CH_N-1]]=3;
	    NumOfDefinite_TimeChar[CH_N-1]++;
	  }
	  }
	}break;
      case 5:
	{
	if(isFixed_Volume[CH_N-1])
	  {
	    if(NumOfFlow_VolumeChar[CH_N-1]<5)
	  {
	    Flow_VolumeChar[CH_N-1][NumOfFlow_VolumeChar[CH_N-1]]=4;
	    NumOfFlow_VolumeChar[CH_N-1]++;
	  }
	  }
	  else
	  {
	     if(NumOfDefinite_TimeChar[CH_N-1]<5)
	  {
	    Definite_TimeChar[CH_N-1][NumOfDefinite_TimeChar[CH_N-1]]=4;
	    NumOfDefinite_TimeChar[CH_N-1]++;
	  }
	  }
	}break;
      case 6:
	{
	  if(isFixed_Volume[CH_N-1])
	  {
	    if(NumOfFlow_VolumeChar[CH_N-1]<5)
	  {
	    Flow_VolumeChar[CH_N-1][NumOfFlow_VolumeChar[CH_N-1]]=5;
	    NumOfFlow_VolumeChar[CH_N-1]++;
	  }
	  }
	  else
	  {
	     if(NumOfDefinite_TimeChar[CH_N-1]<5)
	  {
	    Definite_TimeChar[CH_N-1][NumOfDefinite_TimeChar[CH_N-1]]=5;
	    NumOfDefinite_TimeChar[CH_N-1]++;
	  }
	  }
	}break;
      case 7:
	{
	  if(isFixed_Volume[CH_N-1])
	  {
	    if(NumOfFlow_VolumeChar[CH_N-1]<5)
	  {
	    Flow_VolumeChar[CH_N-1][NumOfFlow_VolumeChar[CH_N-1]]=6;
	    NumOfFlow_VolumeChar[CH_N-1]++;
	  }
	  }
	  else
	  {
	     if(NumOfDefinite_TimeChar[CH_N-1]<5)
	  {
	    Definite_TimeChar[CH_N-1][NumOfDefinite_TimeChar[CH_N-1]]=6;
	    NumOfDefinite_TimeChar[CH_N-1]++;
	  }
	  }
	}break;
      case 9:
	{
	  if(isFixed_Volume[CH_N-1])
	  {
	    if(NumOfFlow_VolumeChar[CH_N-1]<5)
	  {
	    Flow_VolumeChar[CH_N-1][NumOfFlow_VolumeChar[CH_N-1]]=7;
	    NumOfFlow_VolumeChar[CH_N-1]++;
	  }
	  }
	  else
	  {
	     if(NumOfDefinite_TimeChar[CH_N-1]<5)
	  {
	    Definite_TimeChar[CH_N-1][NumOfDefinite_TimeChar[CH_N-1]]=7;
	    NumOfDefinite_TimeChar[CH_N-1]++;
	  }
	  }
	}break;
      case 10:
	{
	 if(isFixed_Volume[CH_N-1])
	  {
	    if(NumOfFlow_VolumeChar[CH_N-1]<5)
	  {
	    Flow_VolumeChar[CH_N-1][NumOfFlow_VolumeChar[CH_N-1]]=8;
	    NumOfFlow_VolumeChar[CH_N-1]++;
	  }
	  }
	  else
	  {
	     if(NumOfDefinite_TimeChar[CH_N-1]<5)
	  {
	    Definite_TimeChar[CH_N-1][NumOfDefinite_TimeChar[CH_N-1]]=8;
	    NumOfDefinite_TimeChar[CH_N-1]++;
	  }
	  }
	}break;
      case 11:
	{
	  if(isFixed_Volume[CH_N-1])
	  {
	    if(NumOfFlow_VolumeChar[CH_N-1]<5)
	  {
	    Flow_VolumeChar[CH_N-1][NumOfFlow_VolumeChar[CH_N-1]]=9;
	    NumOfFlow_VolumeChar[CH_N-1]++;
	  }
	  }
	  else
	  {
	     if(NumOfDefinite_TimeChar[CH_N-1]<5)
	  {
	    Definite_TimeChar[CH_N-1][NumOfDefinite_TimeChar[CH_N-1]]=9;
	    NumOfDefinite_TimeChar[CH_N-1]++;
	  }
	  }
	}break;
      case 14:
	{
	  if(isFixed_Volume[CH_N-1])
	  {
	    if(NumOfFlow_VolumeChar[CH_N-1]<5)
	  {
	    Flow_VolumeChar[CH_N-1][NumOfFlow_VolumeChar[CH_N-1]]=0;
	    NumOfFlow_VolumeChar[CH_N-1]++;
	  }
	  }
	  else
	  {
	     if(NumOfDefinite_TimeChar[CH_N-1]<5)
	  {
	    Definite_TimeChar[CH_N-1][NumOfDefinite_TimeChar[CH_N-1]]=0;
	    NumOfDefinite_TimeChar[CH_N-1]++;
	  }
	  }
	}break;
      case 12:
	{
	   if(isFixed_Volume[CH_N-1])
	  {
	  if(NumOfFlow_VolumeChar[CH_N-1]>1)
	  {
	    Flow_VolumeChar[CH_N-1][NumOfFlow_VolumeChar[CH_N-1]-1]=0;
	    NumOfFlow_VolumeChar[CH_N-1]--;
	  }
	  else if(NumOfFlow_VolumeChar[CH_N-1]==1)
	  {
	    Flow_VolumeChar[CH_N-1][NumOfFlow_VolumeChar[CH_N-1]-1]=0;
	    NumOfFlow_VolumeChar[CH_N-1]=0;
	  }
	  }
	  else
	  {
	    if(NumOfDefinite_TimeChar[CH_N-1]>1)
	  {
	    Definite_TimeChar[CH_N-1][NumOfDefinite_TimeChar[CH_N-1]-1]=0;
	    NumOfDefinite_TimeChar[CH_N-1]--;
	  }
	  else if(NumOfDefinite_TimeChar[CH_N-1]==1)
	  {
	    Definite_TimeChar[CH_N-1][NumOfDefinite_TimeChar[CH_N-1]-1]=0;
	    NumOfDefinite_TimeChar[CH_N-1]=0;
	  }
	  }
	}break;
      case 16:
	{
	  //memset(Flow_VolumeChar,0,sizeof(Flow_VolumeChar));
	  //NumOfFlow_VolumeChar[CH_N-1]=0;
	  if(isFixed_Volume[CH_N-1]==false) 
	  {
	    isFixed_Volume[CH_N-1]=true;
	  }
	  else 
	  {
	    isFixed_Volume[CH_N-1]=false;
	  }
	}break;
      }
      if(isFixed_Volume[CH_N-1])
      {
	CH_Checked(158,103);
	CH_Uncheck(226,103);
//	if(Flow_VolumeTemp[CH_N-1]!=0)
//	memcpy(Flow_VolumeChar[CH_N-1],&Flow_VolumeTemp[CH_N-1],sizeof(Flow_VolumeChar[CH_N-1]));
	Flow_VolumeTemp[CH_N-1]=Flow_VolumeChar[CH_N-1][0]*10000+Flow_VolumeChar[CH_N-1][1]*1000+Flow_VolumeChar[CH_N-1][2]*100+Flow_VolumeChar[CH_N-1][3]*10+Flow_VolumeChar[CH_N-1][4];
	Clear_LCD(236,120,244,136);
	sprintf((char*)temp_buf,"%05d",Flow_VolumeTemp[CH_N-1]);
	Show_Str(172,120,temp_buf);
	Show_Str(220,120,"ml");
	Draw_Rect(170,118,214,136);
      }
      else
      {
	CH_Uncheck(158,103);
	CH_Checked(226,103);
//	if(Definite_TimeTemp[CH_N-1]!=0)
//	memcpy(Flow_VolumeChar[CH_N-1],&Definite_TimeTemp[CH_N-1],sizeof(Flow_VolumeChar[CH_N-1]));
	Definite_TimeTemp[CH_N-1]=Definite_TimeChar[CH_N-1][0]*10000+Definite_TimeChar[CH_N-1][1]*1000+Definite_TimeChar[CH_N-1][2]*100+Definite_TimeChar[CH_N-1][3]*10+Definite_TimeChar[CH_N-1][4];
	sprintf((char*)temp_buf,"%05d",Definite_TimeTemp[CH_N-1]);
	Show_Str(172,120,temp_buf);
	Show_Str(220,120,"min");
	Draw_Rect(170,118,214,136);
      }
      Clear_LCD(50,33,70,53);
      Clear_LCD(50,63,70,83);
      
      Clear_LCD(50,148,70,168);
      Draw_Pic(50,93,70,113,(u8*)gImage_triangle_rf,length(gImage_triangle_rf));
      Show_Str(180,200,"确定");
      Draw_Rect(70,198,105,217);  
      Draw_Rect(178,198,213,217);
      Show_Str(72,200,"取消");
    }break;
    
  case 4:
    {
      
      
      if(key==16)
      {
	
//	memset(Intervals_TimeChar,0,5);
//	NumOfIntervals_TimeChar=0;
	if(isManually[CH_N-1]==false) 
	{
	  isManually[CH_N-1]=true;
	}
	else 
	{
	  isManually[CH_N-1]=false;
	}
	
      }
      if(isManually[CH_N-1])
      {
	CH_Checked(156,158);
	CH_Uncheck(226,158);
	Clear_LCD(170,173,244,191);
      }
      else
      {
	switch(key)
	{
	case 0:break;
	case 1:
	  {
	    if(NumOfIntervals_TimeChar[CH_N-1]<5)
	    {
	      Intervals_TimeChar[CH_N-1][NumOfIntervals_TimeChar[CH_N-1]]=1;
	      NumOfIntervals_TimeChar[CH_N-1]++;
	    }
	  }break;
	case 2:
	  {
	    if(NumOfIntervals_TimeChar[CH_N-1]<5)
	    {
	      Intervals_TimeChar[CH_N-1][NumOfIntervals_TimeChar[CH_N-1]]=2;
	      NumOfIntervals_TimeChar[CH_N-1]++;
	    }
	  }break;
	case 3:
	  {
	    if(NumOfIntervals_TimeChar[CH_N-1]<5)
	    {
	      Intervals_TimeChar[CH_N-1][NumOfIntervals_TimeChar[CH_N-1]]=3;
	      NumOfIntervals_TimeChar[CH_N-1]++;
	    }
	  }break;
	case 5:
	  {
	    if(NumOfIntervals_TimeChar[CH_N-1]<5)
	    {
	      Intervals_TimeChar[CH_N-1][NumOfIntervals_TimeChar[CH_N-1]]=4;
	      NumOfIntervals_TimeChar[CH_N-1]++;
	    }
	  }break;
	case 6:
	  {
	    if(NumOfIntervals_TimeChar[CH_N-1]<5)
	    {
	      Intervals_TimeChar[CH_N-1][NumOfIntervals_TimeChar[CH_N-1]]=5;
	      NumOfIntervals_TimeChar[CH_N-1]++;
	    }
	  }break;
	case 7:
	  {
	    if(NumOfIntervals_TimeChar[CH_N-1]<5)
	    {
	      Intervals_TimeChar[CH_N-1][NumOfIntervals_TimeChar[CH_N-1]]=6;
	      NumOfIntervals_TimeChar[CH_N-1]++;
	    }
	  }break;
	case 9:
	  {
	    if(NumOfIntervals_TimeChar[CH_N-1]<5)
	    {
	      Intervals_TimeChar[CH_N-1][NumOfIntervals_TimeChar[CH_N-1]]=7;
	      NumOfIntervals_TimeChar[CH_N-1]++;
	    }
	  }break;
	case 10:
	  {
	    if(NumOfIntervals_TimeChar[CH_N-1]<5)
	    {
	      Intervals_TimeChar[CH_N-1][NumOfIntervals_TimeChar[CH_N-1]]=8;
	      NumOfIntervals_TimeChar[CH_N-1]++;
	    }
	  }break;
	case 11:
	  {
	    if(NumOfIntervals_TimeChar[CH_N-1]<5)
	    {
	      Intervals_TimeChar[CH_N-1][NumOfIntervals_TimeChar[CH_N-1]]=9;
	      NumOfIntervals_TimeChar[CH_N-1]++;
	    }
	  }break;
	case 14:
	  {
	    if(NumOfIntervals_TimeChar[CH_N-1]<5)
	    {
	      Intervals_TimeChar[CH_N-1][NumOfIntervals_TimeChar[CH_N-1]]=0;
	      NumOfIntervals_TimeChar[CH_N-1]++;
	    }
	  }break;
	case 12:
	  {
	    if(NumOfIntervals_TimeChar[CH_N-1]>1)
	    {
	      Intervals_TimeChar[CH_N-1][NumOfIntervals_TimeChar[CH_N-1]-1]=0;
	      NumOfIntervals_TimeChar[CH_N-1]--;
	    }
	    else if(NumOfIntervals_TimeChar[CH_N-1]==1)
	    {
	      Intervals_TimeChar[CH_N-1][NumOfIntervals_TimeChar[CH_N-1]-1]=0;
	      NumOfIntervals_TimeChar[CH_N-1]=0;
	    }
	    
	  }break;
	}
	CH_Uncheck(156,158);
	CH_Checked(226,158);
	Intervals_TimeTemp[CH_N-1]=Intervals_TimeChar[CH_N-1][0]*10000+Intervals_TimeChar[CH_N-1][1]*1000+Intervals_TimeChar[CH_N-1][2]*100+Intervals_TimeChar[CH_N-1][3]*10+Intervals_TimeChar[CH_N-1][4];
	sprintf((char*)temp_buf,"%05d",Intervals_TimeTemp[CH_N-1]);
	Show_Str(172,175,temp_buf);
	Show_Str(220,175,"min");
	Draw_Rect(170,173,214,191);
      }
      Clear_LCD(50,33,70,53);
      Clear_LCD(50,63,70,83);
      Clear_LCD(50,93,70,113);
      
      
      Draw_Pic(50,148,70,168,(u8*)gImage_triangle_rf,length(gImage_triangle_rf));
      Show_Str(180,200,"确定");
      Draw_Rect(70,198,105,217);  
      Draw_Rect(178,198,213,217);
      Show_Str(72,200,"取消");
    }break;
  case 5:
    {
      if(key==12)
      {
	isCH_Save[CH_N-1]=false;
      }
      else if(key==16)
      {
	isCH_Save[CH_N-1]=true;	
      }
      if(isCH_Save[CH_N-1])
      {
	
	Show_Str(72,200,"取消");
	Draw_Rect(70,198,105,217);  
	Draw_Rect(178,198,213,217);
	LCD_Invert(1);
	Show_Str(180,200,"确定");
	LCD_Invert(0);
	if(key==15)
	{
	  FlowPID_struct[CH_N-1].SetPoint =(float)(Flow_Temp[CH_N-1]/1000.0);
	  TempPID_struct.SetPoint=(float)(Temperatur_Temp/10.0);
	  if(isFixed_Volume[CH_N-1])
	  {
	    
	    Sampling_Mode.Flow_Volume[CH_N-1]=Flow_VolumeTemp[CH_N-1];
	    Sampling_Mode.isFixed_Volume[CH_N-1]=isFixed_Volume[CH_N-1];
	    Sampling_Mode.NumOfFlow_Volume[CH_N-1]=Calc_BitsOfNum(Sampling_Mode.Flow_Volume[CH_N-1]);
	  
	  }
	  else
	  {
	    Sampling_Mode.Definite_Time[CH_N-1]=Definite_TimeTemp[CH_N-1];
	    Sampling_Mode.NumOfDefinite_Time[CH_N-1]=Calc_BitsOfNum(Sampling_Mode.Definite_Time[CH_N-1]);
	     Sampling_Mode.isFixed_Volume[CH_N-1]=isFixed_Volume[CH_N-1];
	  }
	  if(isManually[CH_N-1])
	  {
	    Sampling_Mode.isManually[CH_N-1]=isManually[CH_N-1];
	    Sampling_Mode.Intervals_Time[CH_N-1]=0;
	    Sampling_Mode.NumOfIntervals_Time[CH_N-1]=0;
	  }
	  else
	  {
	    Sampling_Mode.isManually[CH_N-1]=isManually[CH_N-1];
	    Sampling_Mode.Intervals_Time[CH_N-1]=Intervals_TimeTemp[CH_N-1];
	    Sampling_Mode.NumOfIntervals_Time[CH_N-1]=Calc_BitsOfNum(Intervals_TimeTemp[CH_N-1]);
	  }
	  
	  Clear_LCD(0,0,320,240);
	  Draw_Rect(64,80,256,160);
	  Show_Str(100,120,"通道修改成功");
	  Delayms(500);
	  Channel_flag=0;
	  Exit_flag=1;
	  Main_flag=0;
	  state_disp=1;
	  Disp_SampWindow();
	  return;
	}
      }
      else
      {
	if(key==15)
	{
	  Channel_flag=0;
	  if(!isManually[CH_N-1])
	  memset(&Intervals_TimeChar[CH_N-1],0,sizeof(Intervals_TimeChar[CH_N-1]));
	  if(isFixed_Volume[CH_N-1])
	  memset(&Flow_VolumeChar[CH_N-1],0,sizeof(Flow_VolumeChar));
	  else
	    memset(&Definite_TimeChar[CH_N-1],0,sizeof(Definite_TimeChar));
	    
	    
	  state_disp=1;
	  Main_flag=1;
	  Disp_MainWindow();
	  return;
	}
	Show_Str(180,200,"确定");
	Draw_Rect(70,198,105,217);  
	Draw_Rect(178,198,213,217);
	LCD_Invert(1);
	Show_Str(72,200,"取消");
	LCD_Invert(0);
      }
      Clear_LCD(50,33,70,53);
      Clear_LCD(50,63,70,83);
      Clear_LCD(50,93,70,113);
      Clear_LCD(50,148,70,168);
    }break;
  }
  
  lastCH_SetSelect=CH_SetSelect;
  }
}
void Disp_Set_State(CHn_Type CHn)
{
  Clear_LCD(0,0,320,26);
  uint8_t temp_buf[8]={0};
  switch(CHn)
  {
  case CH1:
    {
      
      Show_Str(112,4,"第一通道设置");
       sprintf((char*)temp_buf,"%04d",Flow_Temp[CH_N-1]);
  	Show_Str(160,65,temp_buf);
      Draw_Line(104,2,104,20);
      Draw_Pic(85,2,105,22,(u8*)gImage_triangle_le,length(gImage_triangle_le));
      Draw_Pic(210,2,230,22,(u8*)gImage_triangle_rf,length(gImage_triangle_rf));
      Fill_Rect(0,24,320,26);
    }break;
  case CH2:
    {
       sprintf((char*)temp_buf,"%04d",Flow_Temp[CH_N-1]);
  	Show_Str(160,65,temp_buf);
      Show_Str(112,4,"第二通道设置");
      Draw_Pic(85,2,105,22,(u8*)gImage_triangle_lf,length(gImage_triangle_lf));
      Draw_Pic(210,2,230,22,(u8*)gImage_triangle_rf,length(gImage_triangle_rf));
      Fill_Rect(0,24,320,26);
    }break;
  case CH3:
    {
       sprintf((char*)temp_buf,"%04d",Flow_Temp[CH_N-1]);
  	Show_Str(160,65,temp_buf);
      Show_Str(112,4,"第三通道设置");
      Draw_Pic(85,2,105,22,(u8*)gImage_triangle_lf,length(gImage_triangle_lf));
      Draw_Pic(210,2,230,22,(u8*)gImage_triangle_rf,length(gImage_triangle_rf));
      Fill_Rect(0,24,320,26);
    }break;
  case CH4:
    {
       sprintf((char*)temp_buf,"%04d",Flow_Temp[CH_N-1]);
  	Show_Str(160,65,temp_buf);
      Show_Str(112,4,"第四通道设置");  
      Draw_Pic(85,2,105,22,(u8*)gImage_triangle_lf,length(gImage_triangle_lf));
      Draw_Pic(210,2,230,22,(u8*)gImage_triangle_re,length(gImage_triangle_re));
      Fill_Rect(0,24,320,26);
    }break;
  }
   if(isFixed_Volume[CH_N-1])
  {
    CH_Checked(158,103);
    CH_Uncheck(226,103);
    Clear_LCD(170,118,244,136);
    sprintf((char*)temp_buf,"%05d",Flow_VolumeTemp[CH_N-1]);
    Show_Str(172,120,temp_buf);
    Show_Str(220,120,"ml");
    Draw_Rect(170,118,214,136);
  }
  else
  {
    CH_Uncheck(158,103);
    CH_Checked(226,103);
    Clear_LCD(170,118,244,136);
    sprintf((char*)temp_buf,"%05d",Definite_TimeTemp[CH_N-1]);
    Show_Str(172,120,temp_buf);
    Show_Str(220,120,"min");
    Draw_Rect(170,118,214,136);
  }
}
void CH_Checked(uint16_t x,uint16_t y)
{
  Draw_Circle(x,y,6);
  Fill_Circle(x,y,4);
}
void CH_Uncheck(uint16_t x,uint16_t y)
{
  Clear_LCD(x-6,y-6,x+6,y+6);
  Draw_Circle(x,y,6);
}
