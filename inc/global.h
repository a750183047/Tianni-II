#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "includes.h"

/////////////////////////////////////////////////////
/**
OLED宏定义
*/

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

 #define XLevelL		0x00
 #define XLevelH		0x10
 #define XLevel		((XLevelH&0x0F)*16+XLevelL)
 #define Max_Column	128
 #define Max_Row		64
 #define	Brightness	0xCF

 #define asm __ASM
	 
 //////////////////////////////////////////////////////
 /**
 按键宏定义
 */
 
#define KEY_U  PAin(13)
#define KEY_D  PAin(12)
#define KEY_A  PAin(19)
#define KEY_B  PAin(11)

 
#define NO_KEY           	  (0x00)
#define KEY_SINGLE_U        (0x01)
#define KEY_SINGLE_D        (0x02)
#define KEY_SINGLE_A        (0x03)
#define KEY_SINGLE_B        (0x04)
//按键标志定义 
extern u8 KEY_;
 ///////////////////////////////////////////////////////
 
 void initAll(void);
 

 
#endif























