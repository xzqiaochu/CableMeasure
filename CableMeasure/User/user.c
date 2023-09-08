#include "user.h"
#include "printf.h"

#include "tick.h"
#include "tdc.h"
#include "display.h"

#include "getL.h"
#include "getR.h"
#include "getC.h"

#define BASE_L 16.7 // 长度补偿，含义为结果减去的量

#define MAX_R 100 // 最大允许的电阻值
#define MIN_C 30 // 最小允许的电容值

#define CALC_L_T 1000 // 等待长度稳定的时间
#define CALC_R_T 1000 // 等待电阻稳定的时间
#define CALC_C_T 1000 // 等待电容稳定的时间

#define BUFFER_SIZE 50 // 字符串缓冲区大小

float g_l = 0;
float g_base_c = 0;

void blink() {
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);
    HAL_Delay(200);
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
    HAL_Delay(200);
}

void switchX(char x) {
    switch (x) {
        case 'L':
            HAL_GPIO_WritePin(SWITCH_R_GPIO_Port, SWITCH_R_Pin, 0);
            HAL_GPIO_WritePin(SWITCH_C_GPIO_Port, SWITCH_C_Pin, 0);
            HAL_GPIO_WritePin(SWITCH_L_GPIO_Port, SWITCH_L_Pin, 1);
            break;
        case 'R':
            HAL_GPIO_WritePin(SWITCH_C_GPIO_Port, SWITCH_C_Pin, 0);
            HAL_GPIO_WritePin(SWITCH_L_GPIO_Port, SWITCH_L_Pin, 0);
            HAL_GPIO_WritePin(SWITCH_R_GPIO_Port, SWITCH_R_Pin, 1);
            break;
        case 'C':
            HAL_GPIO_WritePin(SWITCH_L_GPIO_Port, SWITCH_L_Pin, 0);
            HAL_GPIO_WritePin(SWITCH_R_GPIO_Port, SWITCH_R_Pin, 0);
            HAL_GPIO_WritePin(SWITCH_C_GPIO_Port, SWITCH_C_Pin, 1);
            break;
        default:
            HAL_GPIO_WritePin(SWITCH_L_GPIO_Port, SWITCH_L_Pin, 0);
            HAL_GPIO_WritePin(SWITCH_R_GPIO_Port, SWITCH_R_Pin, 0);
            HAL_GPIO_WritePin(SWITCH_C_GPIO_Port, SWITCH_C_Pin, 0);
            break;
    }
}

// 长度检测
void handle1() {
    char buffer[BUFFER_SIZE];

    // 检测长度
    float base_l = getL() + BASE_L; // 空载长度

    switchX('L');
    HAL_Delay(CALC_L_T);
    float l = getL();
    switchX('N');

    l -= base_l;

    g_l = l;

    // 串口屏显示
    sprintf(buffer, "%.2f cm", l);
    show("len", buffer);


    // 测试下电容，给后面测电容作为基准
    switchX('C');
    HAL_Delay(CALC_C_T);
    g_base_c = getC();
    switchX('N');
}

// 负载检测
void handle2() {
    char buffer[BUFFER_SIZE];

    // 先尝试检测电阻
    switchX('R');
    HAL_Delay(CALC_R_T);
    float r = getR();
    switchX('N');

    r -= getBaseR(g_l);

    if (r <= MAX_R) {
        // 串口屏显示
        show("kind", "电阻");

        sprintf(buffer, "%.3f Ω", r);
        show("para", buffer);

        return;
    }

    // 再尝试检测电容
    switchX('C');
    HAL_Delay(CALC_C_T);
    float c = getC();
    switchX('N');

    c -= g_base_c;

    if (c >= MIN_C) {
        // 串口屏显示
        show("kind", "电容");

        sprintf(buffer, "%.2f pF", c);
        show("para", buffer);

        return;
    }

    // 电阻、电容均不满足阈值，则认为开路
    show("kind", "开路");
    show("para", "---");
}

void setup() {
    UART_printf("start\n");
    Tick_Init();
    TDC_Init();

    switchX('N');
}

void loop() {
//    blink();

//    switchX('L');
//    calTTask();
//    calLTask();
//    calRTask();
//    calCTask();


    uint8_t cmd;
    while ((cmd = UART_read()) == 0);
    if (cmd == 0x61) { // 长度检测
        show("status", "正在检测");
        handle1();
        show("status", "结果保持");
    } else if (cmd == 0x62) { // 负载检测
        show("status", "正在检测");
        handle2();
        show("status", "结果保持");
    }

    // 清空串口缓冲区
    while (UART_read() != 0);
}