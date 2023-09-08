#ifndef TICK_H_
#define TICK_H_

#include "main.h"

#define  DWT_CR      *(uint32_t *)0xE0001000
#define  DWT_CYCCNT  *(uint32_t *)0xE0001004
#define  DEM_CR      *(uint32_t *)0xE000EDFC

#define  DEM_CR_TRCENA                   (1 << 24)
#define  DWT_CR_CYCCNTENA                (1 <<  0)

/* 初始化时间戳 */
void Tick_Init(void);

uint32_t Get_Tick(void);

uint32_t Tick_Diff(uint32_t tick1, uint32_t tick2);

#endif // TICK_H_