#include "getR.h"
#include "tick.h"
#include "printf.h"

#define R1M 0.01
#define R2M 1

// 标定参数
// 频率标定
#define F_K 1.0048
#define F_B (-0.0501)
// 电容标定
#define C_K 1.003054914
#define C_B (-36.6104)
// 导线寄生电容
#define BASE_C_K 0.9527
#define BASE_C_B 1.4487

#define Q_SIZE 100

uint32_t ready = 0;
uint32_t last_tick = 0;
float freq = 0.0f; // NE555震荡频率

// 维护一个滑动窗口
float fq[Q_SIZE];
uint8_t head = 0;
uint8_t tail = 1;

void push(float f) {
    fq[tail] = f;
    tail = (tail + 1) % Q_SIZE;
    if ((tail + Q_SIZE - head + 1) % Q_SIZE == 0) { // 队列满
        head = (head + 1) % Q_SIZE;
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == FREQ_IN_Pin) {
        uint32_t tick = Get_Tick();

        // 第一次触发
        if (ready == 0) {
            ready = 1;
            last_tick = tick;
            return;
        }

        // 计算两次中断间系统时钟数的差值
        uint32_t tick_diff = Tick_Diff(last_tick, tick);

        // 计算外部信号的频率
        freq = (float) SystemCoreClock / (float) tick_diff;
        push(freq);

        last_tick = tick;
    }
}

float getF() {
    float sum = 0;
    float f_avg;

    // 对滑动窗口的值取平均
    for (int i = 0; i < Q_SIZE; i++) {
        sum += fq[i];
    }
    f_avg = sum / Q_SIZE;

    f_avg = f_avg * F_K + F_B; // 校准频率

    return f_avg;
}

float getC() {
    float f = getF();

    float c12 = 1e6 * 1.442695f / (R1M + 2 * R2M) / f;
    c12 = C_K * (c12 + C_B); // 校准电容
    if (c12 < 0)
        c12 = 0;

    return c12;
}

float getBaseC(float l) {
    return BASE_C_K * l + BASE_C_B;
}

void calFTask() {
    float f;
    while (1) {
        f = getF();
        UART_printf("%0.1f Hz\n", f);

        HAL_Delay(200);
    }
}

void calCTask() {
    float c12;
    while (1) {
        c12 = getC();
        UART_printf("%0.1f pF\n", c12);

        HAL_Delay(200);
    }
}