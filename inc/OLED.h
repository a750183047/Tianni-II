/*
 * File:		nokia.h
 * Purpose:		Serial Input/Output routines
 *
 */

#ifndef _OELD_H
#define _OELD_H
#include "common.h"
#include "gpio.h"
#include "stdio.h"
#include "stdlib.h"

/********************************************************************/
/*-----------------------------------------------------------------------
LCD_init          : OLED初始化

编写日期          ：2012-11-01
最后修改日期      ：2012-11-01
-----------------------------------------------------------------------*/



 #define PTE28_OUT  PEout(28)
 #define PTE27_OUT  PEout(27)
 #define PTE26_OUT  PEout(26)
 #define PTE25_OUT  PEout(25)
 #define PTE24_OUT  PEout(24)


 #define OLED_SCL  PTE28_OUT                 // PTD1_OUT
 #define OLED_SDA  PTE27_OUT                //PTD3_OUT
 #define OLED_RST  PTE26_OUT                 //PTC15_OUT
 #define OLED_DC   PTE25_OUT                 //PTD2_OUT
 #define OLED_CS   PTE24_OUT                //PTD4_OUT

 #define asm __ASM


 void OLED_Init(void);
 void OLED_CLS(void);
 void OLED_P6x8Str(u8 x,u8 y,u8 ch[]);
 void OLED_P8x16Str(u8 x,u8 y,u8 ch[]);
 void OLED_P14x16Str(u8 x,u8 y,u8 ch[]);
 void OLED_Print(u8 x, u8 y, u8 ch[]);
 void OLED_PutPixel(u8 x,u8 y);
 void OLED_Rectangle(u8 x1,u8 y1,u8 x2,u8 y2,u8 gif);
 void OLED_Set_Pos(u8 x, u8 y);
 void OLED_WrDat(u8 data);
 void Draw_BMP(u8 x0,u8 y0,u8 x1,u8 y1,u8 bmp[]);
 void OLED_Fill(u8 dat);
 void Dly_ms(u16 ms);
 extern void LCD_Write_String(u8 x,u8 y,u8 ch[]);
 void LCD_Write_Number(u8 X,u8 Y,u32 number);




/********************************************************************/

#endif
