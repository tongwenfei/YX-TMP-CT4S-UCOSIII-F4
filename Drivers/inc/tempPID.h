#ifndef _TEMP_PID_H
#define _TEMP_PID_H
#include "flow_PID.h"
#include "sys.h"
#define HOT  0
#define COOL 1
#define CONST_COOL  500
#define CONST_HOT  500
void TEM_PID_ReSet(PID_STRUCT *pp); 
void TEM_PID_Configuration(PID_STRUCT *pp);
float TEM_PID_Calculation(PID_STRUCT *pp,float NowTem); 
void TEM_PWM_Init(void);
void TEM_SetDuty(uint8_t state,uint16_t duty);
void TEM_PWM_ReSet(void);                      
void TEM_Compare(PID_STRUCT *pp,float NowTem);
#endif