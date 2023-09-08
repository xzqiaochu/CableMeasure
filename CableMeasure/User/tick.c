#include "tick.h"

#define  DWT_CR      *(uint32_t *)0xE0001000
#define  DWT_CYCCNT  *(uint32_t *)0xE0001004
#define  DEM_CR      *(uint32_t *)0xE000EDFC

#define  DEM_CR_TRCENA                   (1 << 24)
#define  DWT_CR_CYCCNTENA                (1 <<  0)

/* 初始化时间戳 */
void Tick_Init(void) {
    /* 使能DWT外设 */
    DEM_CR |= (uint32_t) DEM_CR_TRCENA;

    /* DWT CYCCNT寄存器计数清0 */
    DWT_CYCCNT = (uint32_t) 0u;

    /* 使能Cortex-M3 DWT CYCCNT寄存器 */
    DWT_CR |= (uint32_t) DWT_CR_CYCCNTENA;
}

uint32_t Get_Tick(void) {
    return ((uint32_t) DWT_CYCCNT);
}

uint32_t Tick_Diff(uint32_t tick1, uint32_t tick2) {
    uint32_t diff1, diff2;
    if (tick1 >= tick2) {
        diff1 = tick1 - tick2;
        diff2 = UINT32_MAX - tick1 + tick2;
    } else {
        diff1 = tick2 - tick1;
        diff2 = UINT32_MAX - tick2 + tick1;
    }
    if (diff1 <= diff2)
        return diff1;
    else
        return diff2;
}
