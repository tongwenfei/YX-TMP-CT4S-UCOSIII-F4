#ifndef __MAIN_WINDOW_H
#define __MAIN_WINDOW_H
#include "gui.h"
#include "stdio.h"
#include "global.h"
#include "ds1302.h"
#include "key.h"
#define length(A) sizeof(A)/sizeof(A[0])
extern uint8_t sub_menu,state_disp;

void Disp_MainWindow(void);
void Disp_State(void);
void Change_menu(void);
#endif