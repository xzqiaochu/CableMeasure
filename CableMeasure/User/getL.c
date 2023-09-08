#include "getL.h"
#include "tdc.h"
#include "printf.h"

#define TDC_TIMEOUT 10
#define AVG_N 100

#define MIN_L 100 // 最小允许测量长度，单位厘米
#define MAX_L 7000 // 最大允许测量长度，单位厘米

// 校准参数
#define Ce8 2.01546 // 铜中的光速

// 获取TDC测量原始结果
float getTDC() {
    uint32_t tdc;
    uint8_t flag;

    flag = TDC_Measure(&tdc, TDC_TIMEOUT);
    if (flag == 1) // 测量超时
        tdc = 0;

    return tdc;
}

float getL() {
    uint32_t sum = 0;
    uint32_t cnt = 0;
    float l;

    for (uint32_t i = 0; i < AVG_N; i++) {
        float tdc = getTDC();
        float ns = TDC_to_ns(tdc);
        float len = ns * Ce8 / 2 * 10;

        if (len < MIN_L || len > MAX_L)
            continue;

        sum += tdc;
        cnt++;
    }

    if (cnt != 0) {
        uint32_t avg = (uint32_t) (sum / cnt + 0.5);
        float ns = TDC_to_ns(avg);
        l = ns * Ce8 / 2 * 10;
        if (l < 0)
            l = 0;
    }
    else
        l = 0;

    return l;
}

void calTTask() {
    uint32_t tdc;
    float ns, l;
    while (1) {
        TDC_Measure(&tdc, TDC_TIMEOUT);
        ns = TDC_to_ns(tdc);
        l = ns * Ce8 / 2 * 10;

        UART_printf("0x%08 x \t %.2fns \t %.1f cm\n", tdc, ns, l);

        HAL_Delay(200);
    }
}

void calLTask() {
    float l;
    while(1) {
        l = getL();
        UART_printf("%.1f cm\n", l);

        HAL_Delay(200);
    }
}
