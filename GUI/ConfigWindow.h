#ifndef __CONFIG_WINDOW__H
#define __CONFIG_WINDOW__H
#include "gui.h"
#include "CH_SetWindow.h"
extern uint8_t Config_Num;
void Disp_ConfigWindow(void);
void Disp_TimeSetWindow(void);
void Disp_BaudSetWindow(void);
void Config_Select(void);

void ConfigSub_Select(void);
void Disp_CalibrationWindow(void);
void Switch_CalibrationCH(CHn_Type CHn);
void Clear_LastArrow(uint8_t lastarrow);
void Switch_FlowCalibration(uint8_t flown,uint8_t last_flown);
void Disp_InputNum(void);
void Disp_NowFlow(CHn_Type Flow_CHn,uint8_t Flow_N,uint8_t Last_Flow_N);
#endif