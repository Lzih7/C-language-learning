#include "stm32_util.h"

void Delay_us(uint32_t xus)
{
    SysTick->CTRL = 0x00000004;
    SysTick->LOAD = 72 * xus;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x00000005;

    while (!(SysTick->CTRL & 0x00010000))
        ;
}
