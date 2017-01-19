/*******************************************************************************
 *CopyRight Reserved:	
 *Filename：			key.h
 *Description：     	        矩阵键盘驱动
 *Date:
 *Author:		
*******************************************************************************/

#ifndef __KEY_H__
#define __KEY_H__
#include "sys.h"
#define BUTTON_FILTER_TIME         5  
#define BUTTON_LONG_TIME         50                /* 持续1秒，认为长按事件 */  
#define  KEY_FIFO_SIZE            20
/* 
        每个按键对应1个全局的结构体变量。 
        其成员变量是实现滤波和多种按键状态所必须的 
*/  
typedef struct  
{  
        /* 下面是一个函数指针，指向判断按键手否按下的函数 */  
        unsigned char  IsKeyDown; /* 按键按下的判断指标,1表示按下 */  
   
        unsigned char  Count;                        /* 滤波器计数器 */  
        unsigned char  FilterTime;                /* 滤波时间(最大255,表示2550ms) */  
        unsigned short LongCount;                /* 长按计数器 */  
        unsigned short LongTime;                /* 按键按下持续时间, 0表示不检测长按 */  
        unsigned char   State;                        /* 按键当前状态（按下还是弹起） */  
        unsigned char  KeyCodeUp;                /* 按键弹起的键值代码, 0表示不检测按键弹起 */  
        unsigned char  KeyCodeDown;        /* 按键按下的键值代码, 0表示不检测按键按下 */  
        unsigned char  KeyCodeLong;        /* 按键长按的键值代码, 0表示不检测长按 */  
        unsigned char  RepeatSpeed;        /* 连续按键周期 */  
        unsigned char  RepeatCount;        /* 连续按键计数器 */  
}KEY_T;  
typedef struct
{
	unsigned char Buf[KEY_FIFO_SIZE];		               /* 键值缓冲区 */
	unsigned char Read;					       /* 缓冲区读指针 */
	unsigned char  Write;					       /* 缓冲区写指针 */
	
}KEY_FIFO_T;
extern KEY_FIFO_T  KEY_FIFO;
typedef enum  
{  
        KEY_NONE = 0,                        /* 0 表示按键事件 */  
   
        KEY_DOWN,                        /* 按键键按下 */  
        KEY_UP,                        /* 按键键弹起 */  
        KEY_LONG,                        /* 按键键长按 */  
 
}KEY_ENUM;  
extern KEY_T s_KEY[16];
void Key_Init(void);
void TIM7_Init(u16 arr,u16 psc);
uint8_t Key_Scan(void);
uint8_t Get_KeyVaule(void);
uint8_t bsp_keyRead( void );
void Button_Detect(void);
void  PanakeyVar_Init(void) ;
#endif