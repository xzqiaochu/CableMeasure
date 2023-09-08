#ifndef PRINTF_H__
#define PRINTF_H__

#include "main.h"
#include "usart.h"
#include <stdio.h>
#include <stdarg.h>

uint8_t UART_printf(const char *fmt, ...);

#endif // PRINTF_H__
