#include "display.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

#define UART_TIMEOUT 10 // 串口超时时间
#define BUFFER_SIZE 50 // 字符串缓冲区大小

// 串口发送一个数组，以字符串末尾\x00的方式判断结尾
void UART_write(const char* data) {
    HAL_UART_Transmit(&huart3, (uint8_t *) data, strlen(data), UART_TIMEOUT);
}

// 串口接收一个字节，超时返回0
uint8_t UART_read() {
    uint8_t data = 0;
    HAL_UART_Receive(&huart3, &data, 1, UART_TIMEOUT);
    return data;
}

// 串口屏显示
void show(const char* objname, const char* txt) {
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "%s.txt=\"%s\"\xff\xff\xff", objname, txt);
    UART_write(buffer);
}