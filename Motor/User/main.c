#include "stm32f10x.h"
#include "TB6612FNG.h"
#include "OLED.h"
#include "typedef.h"

int8_t direction = 1;

int main() {
    OLED_Init();

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_CFG(GPIOA, GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_IPU);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);
    EXTI_CFG(EXTI_Line6, EXTI_Mode_Interrupt, EXTI_Trigger_Falling, ENABLE);
    NVIC_CFG(EXTI9_5_IRQn, 0, 0, ENABLE);

    OLED_ShowString(1, 1, "Start!");
    TB6612FNG_Init();
    TB6612FNG_SetSpeed(1000); // 设置速度为1000

    TB6612FNG_SetDirection(direction);
    while(1) {
        
    }
}

void EXTI9_5_IRQHandler(void) {
    direction = -direction;
    TB6612FNG_SetDirection(direction);
    EXTI_ClearITPendingBit(EXTI_Line6); // 清除中断标志
}
