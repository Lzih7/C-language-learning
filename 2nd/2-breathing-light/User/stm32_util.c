#include <stdio.h>
#include "stm32_util.h"

void Delay_us(uint32_t xus)
{
    /**
     * SysTick->LOAD 是一个 24 位寄存器
     *
     * t周期= 1/72,000,000=13.88纳秒
     * t总时间=16777215×13.88纳秒=232,833,000纳秒==233毫秒
     * 当 SysTick->LOAD 设置为最大值时，延时的最大时间大约为 233 毫秒
     *
     */

    SysTick->CTRL = 0x00000004;
    SysTick->LOAD = 72 * xus;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x00000005;

    while (!(SysTick->CTRL & 0x00010000))
        ;
}
