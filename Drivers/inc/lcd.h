/*
********************************************************************************
 *CopyRight Reserved:	宇星科技
 *Filename：		LCD.h
 *Description：     LCD.C头文件    
 *Date:
 *Author:		heshenghui
********************************************************************************
*/

#include "target.h"

#ifndef LCD_H
#define LCD_H

#define SET_LCD_LED()	GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define CLR_LCD_LED()	GPIO_ResetBits(GPIOB,GPIO_Pin_8)

#define SET_LCD_RST()	GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define CLR_LCD_RST()	GPIO_ResetBits(GPIOA,GPIO_Pin_12)

#define SET_LCD_WR()	GPIO_SetBits(GPIOC,GPIO_Pin_10)
#define CLR_LCD_WR()	GPIO_ResetBits(GPIOC,GPIO_Pin_10)

#define SET_LCD_RD()	GPIO_SetBits(GPIOC,GPIO_Pin_11)
#define CLR_LCD_RD()	GPIO_ResetBits(GPIOC,GPIO_Pin_11)

#define SET_LCD_CS()	GPIO_SetBits(GPIOC,GPIO_Pin_12)
#define CLR_LCD_CS()	GPIO_ResetBits(GPIOC,GPIO_Pin_12)

#define SET_LCD_A1()	GPIO_SetBits(GPIOA,GPIO_Pin_11)
#define CLR_LCD_A1()	GPIO_ResetBits(GPIOA,GPIO_Pin_11)		//sunlis:selecting lcd register


//#define DATAOUT(x)     { GPIOD->ODR=(((x>>1)&0x7f)|0x80);PCout(12)=(x&1); }

#define RED     0xf800
#define GREEN   0x07e0
#define BLUE    0x001f
#define YELLOW  0xffe0
#define CYAN    0x07ff
#define MAGENTA 0xf81f
#define BLACK   0x0000
#define WHITE   0xffff


void LCD_Init(void);
void PrintGB(uint16_t X, uint16_t Y, uint8_t *pstr);
void PrintASCII(uint16_t X, uint16_t Y, uint8_t *pstr);

void ClrLCD(void);
void ClrRangeLCD(uint16_t startx,uint16_t starty,uint16_t endx,uint16_t endy);
void Draw_Line(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void Fill_Circle(uint16_t x,uint16_t y,uint8_t r);
void Draw_Circle(uint16_t x,uint16_t y,uint8_t r);
void Draw_Rect(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void Fill_Rect(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void Draw_Pixel(uint16_t x,uint16_t y);
void SetFgColor(uint16_t color);
void SetFontFgColor(uint16_t color);
void SetFontBgColor(uint16_t color);
void SetGradation(uint8_t FontFg,uint8_t FontBg );
void Draw_Window(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void Draw_Arrow(uint16_t x,uint16_t y);
void Clear_Arrow(uint16_t x,uint16_t y);
void Draw_Pic(u16 sx,u16 sy,u16 ex,u16 ey,u8 *pic,u16 len);
void Clear_LCD(uint16_t  x1,uint16_t y1,uint16_t x2,uint16_t y2);
void Show_Str(uint16_t X, uint16_t Y, uint8_t *pstr);
void PrintGB_NUM(uint16_t X, uint16_t Y, uint8_t *pstr);
void PrintGB_ROW(uint16_t X, uint16_t Y, uint8_t *pstr);
void LCD_Invert(uint8_t Invert );
void TIM4_PWM_Init(uint32_t arr,uint32_t psc);
#endif /*LCD_H*/
