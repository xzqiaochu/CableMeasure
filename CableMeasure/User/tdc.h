#ifndef TDC_H__
#define TDC_H__

#include "main.h"

void TDC_Init();

uint8_t TDC_Measure(uint32_t *result, uint32_t timeout);

float TDC_to_ns(uint32_t val);

#endif // TDC_H__