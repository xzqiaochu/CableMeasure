#include "getR.h"
#include "adc.h"
#include "printf.h"

#define AVG_N 100
#define R 58.5 // 分压电阻

// 标定参数
// ADC电压标定
#define V_K 1.0072
#define V_B (-0.0007)
// 电阻标定
#define R_K 0.8615
#define R_B (-0.1298)
// 线缆寄生电阻
#define BASE_R_K 0.0014
#define BASE_R_B 0.0328

// 获得单次ADC测量的原始值
uint16_t getADC() {
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 50);   //等待转换完成，50为最大等待时间，单位为ms

    if (HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC)) {
        uint16_t ADC_Value = HAL_ADC_GetValue(&hadc1);
        return ADC_Value;
    } else {
        return 0;
    }
}

// 多次进行ADC测量，并转换为电压值
float getV() {
    uint32_t sum = 0;
    float avg_adc, v;

    // 获取多次ADC值取平均
    for (int i = 0; i < AVG_N; i++) {
        sum += getADC();
    }
    avg_adc = (float) sum / AVG_N;

    v = avg_adc * 3.3f / 4096; // 转换为电压值

    v = v * V_K + V_B; // 校准电压

    return v;
}

float getR() {
    float v = getV();
    float r = v / (3.3f - v) * R; // 分压法测电阻
    r = R_K * r + R_B; // 电阻标定

    return r;
}

float getBaseR(float l) {
    return BASE_R_K * l + BASE_R_B;
}

void calVTask() {
    float v;
    while (1) {
        v = getV();
        UART_printf("%0.3f V\n", v);

        HAL_Delay(200);
    }
}

void calRTask() {
    float r;
    while (1) {
        r = getR();
        UART_printf("%0.1f R\n", r);

        HAL_Delay(200);
    }
}