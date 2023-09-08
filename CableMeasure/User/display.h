#ifndef DISPLAY_H__
#define DISPLAY_H__

#include "main.h"

void UART_write(const char* data);

uint8_t UART_read();

void show(const char* objname, const char* txt);

#endif // DISPLAY_H__