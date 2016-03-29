#include "gpio.h"
#include "common.h"
#include "uart.h"
#include "dma.h"
#include "dma.h"
#include "pit.h"


#ifndef __ENCODER_H__
#define __ENCODER_H__
#endif

static void DMA_PulseCountInit(uint32_t dmaChl, uint32_t instance, uint32_t pinIndex);
static void PIT_ISR(void);
int encoder(void);




