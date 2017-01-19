#include "PassWd_SetWindow.h"
#include "MainWindow.h"
#include "ConfigWindow.h"
void Disp_UncheckIcon(uint16_t x,uint16_t y)
{
  Clear_LCD(x-8,y-8,x+8,y+8);
  Draw_Circle(x,y,8);
}
void Disp_CheckedIcon(uint16_t x,uint16_t y)
{
  Draw_Circle(x,y,8);
  Fill_Circle(x,y,5);
}
void PassWd_SetDisp(void)
{
  state_disp=0;
  Main_flag=0;
  Clear_LCD(0,0,320,240);
  
  PrintGB(112,4,"密码设置");
    Fill_Rect(0,25,320,26);
  Show_Str(88,50,"原密码："); 
  Show_Str(88,90,"新密码："); 
  Show_Str(24,130,"再次输入新密码："); 
  Disp_CheckedIcon(264,58);
  Disp_UncheckIcon(264,98);
  Disp_UncheckIcon(264,138);
  //  Draw_Circle(260,58,8);
  //  Fill_Circle(260,58,5);
  //Draw_Pic(252,50,268,66,(u8*)gPassWd_checked,length(gPassWd_checked));
  Draw_Rect(150,48,250,68);
  Draw_Rect(150,88,250,108);
  Draw_Rect(150,128,250,148);
  Show_Str(92,220,"返回");
  Draw_Rect(90,218,124,236);
  Show_Str(192,220,"确定");
  Draw_Rect(188,218,224,236);
  PassWd_flag=1;
}
void Change_PassWd(void)
{
  uint8_t temp[3][6]={0};
  uint8_t key=bsp_keyRead();
//  OS_MSG_SIZE size;
//  OS_ERR err;
//  key=OSQPend((OS_Q*			)&KEY_Msg,   
//	      (OS_TICK			)0,
//	      (OS_OPT			)OS_OPT_PEND_NON_BLOCKING,
//	      (OS_MSG_SIZE*		)&size,		
//	      (CPU_TS*			)0,
//	      (OS_ERR*			)&err);
  if(PassWd_flag)
  {
    if(key==8)
    {
      if(PassWd_flag<3)PassWd_flag++;
      else PassWd_flag=1;
    }
    if(key==4)
    {
      if(PassWd_flag>1)PassWd_flag--;
      else PassWd_flag=3;
    }
    switch(PassWd_flag)
    {
    case 1:
      {
        Disp_CheckedIcon(264,58);
        Disp_UncheckIcon(264,98);
        Disp_UncheckIcon(264,138);
        
      }break;
    case 2:
      {
        Disp_UncheckIcon(264,58);
        Disp_CheckedIcon(264,98);
        Disp_UncheckIcon(264,138);
      }break;
    case 3:
      {
        Disp_UncheckIcon(264,58);
        Disp_UncheckIcon(264,98);
        Disp_CheckedIcon(264,138);
      }break;
    }
    switch(key)
    {
    case 1:
      {
        if(PassWd_flag==1)
        {
          if(PassWd_num[0]<6) PassWd_old[PassWd_num[0]++]=1;
        }
         
       if(PassWd_flag==2)
        {
          if(PassWd_num[1]<6) PassWd_new[PassWd_num[1]++]=1;
        }
        if(PassWd_flag==3)
        {
          if(PassWd_num[2]<6) PassWd_rep[PassWd_num[2]++]=1;
        }
      }break;
    case 2:
      {
        if(PassWd_flag==1)
        {
          if(PassWd_num[0]<6) PassWd_old[PassWd_num[0]++]=2;
        }
         
       if(PassWd_flag==2)
        {
          if(PassWd_num[1]<6) PassWd_new[PassWd_num[1]++]=2;
        }
        if(PassWd_flag==3)
        {
          if(PassWd_num[2]<6) PassWd_rep[PassWd_num[2]++]=2;
        }
      }break;
    case 3:
      {
         if(PassWd_flag==1)
        {
          if(PassWd_num[0]<6) PassWd_old[PassWd_num[0]++]=3;
        }
         
       if(PassWd_flag==2)
        {
          if(PassWd_num[1]<6) PassWd_new[PassWd_num[1]++]=3;
        }
        if(PassWd_flag==3)
        {
          if(PassWd_num[2]<6) PassWd_rep[PassWd_num[2]++]=3;
        }
      }break;
    case 5:
      {
         if(PassWd_flag==1)
        {
          if(PassWd_num[0]<6) PassWd_old[PassWd_num[0]++]=4;
        }
         
       if(PassWd_flag==2)
        {
          if(PassWd_num[1]<6) PassWd_new[PassWd_num[1]++]=4;
        }
        if(PassWd_flag==3)
        {
          if(PassWd_num[2]<6) PassWd_rep[PassWd_num[2]++]=4;
        }
      }break;
    case 6:
      {
        if(PassWd_flag==1)
        {
          if(PassWd_num[0]<6) PassWd_old[PassWd_num[0]++]=5;
        }
         
       if(PassWd_flag==2)
        {
          if(PassWd_num[1]<6) PassWd_new[PassWd_num[1]++]=5;
        }
        if(PassWd_flag==3)
        {
          if(PassWd_num[2]<6) PassWd_rep[PassWd_num[2]++]=5;
        }
      }break;
    case 7:
      {
        if(PassWd_flag==1)
        {
          if(PassWd_num[0]<6) PassWd_old[PassWd_num[0]++]=6;
        }
         
       if(PassWd_flag==2)
        {
          if(PassWd_num[1]<6) PassWd_new[PassWd_num[1]++]=6;
        }
        if(PassWd_flag==3)
        {
          if(PassWd_num[2]<6) PassWd_rep[PassWd_num[2]++]=6;
        }
      }break;
    case 9:
      {
        if(PassWd_flag==1)
        {
          if(PassWd_num[0]<6) PassWd_old[PassWd_num[0]++]=7;
        }
         
       if(PassWd_flag==2)
        {
          if(PassWd_num[1]<6) PassWd_new[PassWd_num[1]++]=7;
        }
        if(PassWd_flag==3)
        {
          if(PassWd_num[2]<6) PassWd_rep[PassWd_num[2]++]=7;
        }
      }break;
    case 10:
      {
         if(PassWd_flag==1)
        {
          if(PassWd_num[0]<6) PassWd_old[PassWd_num[0]++]=8;
        }
         
       if(PassWd_flag==2)
        {
          if(PassWd_num[1]<6) PassWd_new[PassWd_num[1]++]=8;
        }
        if(PassWd_flag==3)
        {
          if(PassWd_num[2]<6) PassWd_rep[PassWd_num[2]++]=8;
        }
      }break;
    case 11:
      {
         if(PassWd_flag==1)
        {
          if(PassWd_num[0]<6) PassWd_old[PassWd_num[0]++]=9;
        }
         
       if(PassWd_flag==2)
        {
          if(PassWd_num[1]<6) PassWd_new[PassWd_num[1]++]=9;
        }
        if(PassWd_flag==3)
        {
          if(PassWd_num[2]<6) PassWd_rep[PassWd_num[2]++]=9;
        }
      }break;
    case 14:
      {
         if(PassWd_flag==1)
        {
          if(PassWd_num[0]<6) PassWd_old[PassWd_num[0]++]=0;
        }
         
       if(PassWd_flag==2)
        {
          if(PassWd_num[1]<6) PassWd_new[PassWd_num[1]++]=0;
        }
        if(PassWd_flag==3)
        {
          if(PassWd_num[2]<6) PassWd_rep[PassWd_num[2]++]=0;
        }
      }break;
    case 12:
      {
          if(PassWd_flag==1)
        {
          if(PassWd_num[0]>0) PassWd_old[(PassWd_num[0]--)-1]='\0';
          if(PassWd_num[0]==0)PassWd_old[0]='\0';
          Show_Str(176+PassWd_num[0]*8,50," ");
        }
         
       if(PassWd_flag==2)
        {
          if(PassWd_num[1]>0) PassWd_new[(PassWd_num[1]--)-1]='\0';
          if(PassWd_num[1]==0)PassWd_new[0]='\0';
          Show_Str(176+PassWd_num[1]*8,90," ");
        }
        if(PassWd_flag==3)
        {
          if(PassWd_num[2]>0) PassWd_rep[(PassWd_num[2]--)-1]='\0';
          if(PassWd_num[2]==0)PassWd_rep[0]='\0';
          Show_Str(176+PassWd_num[2]*8,130," ");
        }
      }
    }
    if(key==15)
    {
      if((strncmp((char*)PassWd_old,(char*)PassWd_last,6)==0)&&(strncmp((char*)PassWd_new,(char*)PassWd_rep,6)==0))
      {
         Clear_LCD(0,27,320,240);
        Draw_Rect(64,80,256,160);
        Show_Str(100,120,"密码修改成功！");
        for(uint8_t i=0;i<6;i++)
        {
          PassWd_last[i]=PassWd_new[i];
        }
	PassWd_num[0]=0;
	PassWd_num[1]=0;
	PassWd_num[2]=0;
	memset(PassWd_old,0xff,6);
	memset(PassWd_new,0xff,6);
	memset(PassWd_rep,0xff,6);
        Delayms(100);
        Disp_MainWindow();
        
          return;
      }
     if((strncmp((char*)PassWd_old,(char*)PassWd_last,6)!=0))
     {
        Clear_LCD(0,27,320,240);
        Draw_Rect(64,80,256,160);
        Show_Str(100,120,"原密码输入错误！");
        Delayms(100);
        PassWd_SetDisp();
        
          return;
     }
     if(strncmp((char*)PassWd_new,(char*)PassWd_rep,6)!=0)
     {
        Clear_LCD(0,27,320,240);
        Draw_Rect(64,80,256,160);
        Show_Str(84,120,"两次输入密码不一致！");
        Delayms(100);
        PassWd_SetDisp();
         return;
     }
    }
    if(key==13)
    {
       Disp_MainWindow();
        PassWd_num[0]=0;
	PassWd_num[1]=0;
	PassWd_num[2]=0;
          return;
    }
    for(uint8_t i=0;i<PassWd_num[0];i++)temp[0][i]='*';
   // if(PassWd_num[0]==5)temp[0][5]='*';
    Show_Str(176,50,temp[0]);
    for(uint8_t i=0;i<PassWd_num[1];i++)temp[1][i]='*';
    //if(PassWd_num[1]==5)temp[1][5]='*';
    Show_Str(176,90,temp[1]);
    for(uint8_t i=0;i<PassWd_num[2];i++)temp[2][i]='*';
   // if(PassWd_num[2]==5)temp[2][5]='*';
    Show_Str(176,130,temp[2]);
    
  }
}