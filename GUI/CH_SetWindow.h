#ifndef __CH_SET_WINDOW__H
#define __CH_SET_WINDOW__H
#include "gui.h"
#include "lcd.h"
typedef enum 
{
  CH1=1,
  CH2=2,
  CH3=3,
  CH4=4
}CHn_Type;
typedef struct
{
  uint32_t Flow_Volume[4];
  uint32_t Definite_Time[4];
  uint8_t  NumOfFlow_Volume[4];
  uint8_t  NumOfDefinite_Time[4];
  bool isFixed_Volume[4];//定时 定容
  bool isManually[4];//间隔 手动
  uint8_t Intervals_Counts[4];//采样次数
  uint32_t Intervals_Time[4];//间隔时间
  uint8_t  NumOfIntervals_Time[4];
}SAMPLING_MODE;
extern SAMPLING_MODE Sampling_Mode;
void Disp_Set_State(CHn_Type CHn);
void Disp_SetWindow(void);
void Channel_Select(void);
void CH_Checked(uint16_t x,uint16_t y);
void CH_Uncheck(uint16_t x,uint16_t y);
#endif