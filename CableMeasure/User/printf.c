#include "printf.h"

#include "usart.h"
#include <stdio.h>
#include <stdarg.h>

uint8_t UART_printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    uint8_t length;
    char buffer[128];

    length = vsnprintf(buffer, 128, fmt, ap);

    HAL_UART_Transmit(&huart1, (uint8_t *) buffer, length, HAL_MAX_DELAY);

    va_end(ap);
    return length;
}
