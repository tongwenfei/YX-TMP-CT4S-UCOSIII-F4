#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "CH_SetWindow.h"
#include "global.h"
#include "flow_PID.h"
extern bool start[4];
   


void TIM6_Init(u16 arr,u16 psc);
void Start_Sampling(uint8_t CH);
void Pause_Sampling(uint8_t CH);
void Stop_Sampling(uint8_t CH);

void Multiple_Start_Sampling(FLOW_CHN CH);
void Multiple_Pause_Sampling(FLOW_CHN CH);
void Multiple_Stop_Sampling(FLOW_CHN CH);
#endif
