#ifndef _ISR_H_
#define _ISR_H_
#include "includes.h"

extern u32 now_10ms;
extern float xbh;
extern float ChlValue[3];

extern void PIT_ISR(void);
extern void DMA_PulseCountInit(uint32_t dmaChl, uint32_t instance, uint32_t pinIndex);
extern void PIT_ISR2(void);
extern void PIT_ISR3(void);
extern void PIT_ISR4(void);

#endif










