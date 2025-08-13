#include "typedef.h"
#include "stm32f10x.h"
#define  AIN1 GPIO_Pin_1
#define  AIN2 GPIO_Pin_2
#define  PWM_Pin GPIO_Pin_3
#define  STBY GPIO_Pin_4

void TB6612FNG_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_CFG(GPIOA, AIN1 | AIN2 | STBY, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
    GPIO_CFG(GPIOA, PWM_Pin, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_BASE_CFG(TIM2, 1000 - 1, 72 - 1, TIM_CKD_DIV1, TIM_CounterMode_Up);
    TIM_PWM_CFG(TIM2, 4, TIM_OCMode_PWM1, TIM_OutputState_Enable, 0, TIM_OCPolarity_High);
    TIM_Cmd(TIM2, ENABLE);
}

void TB6612FNG_SetSpeed(uint16_t speed) {
    if(speed >= 1000) speed = 999;
    TIM_SetCompare4(TIM2, speed);
}

void TB6612FNG_SetDirection(int8_t direction) {
    if(direction == 1) {
        GPIO_SetBits(GPIOA, AIN1); // 正转
        GPIO_ResetBits(GPIOA, AIN2);
    } else if(direction == -1) {
        GPIO_SetBits(GPIOA, AIN2); // 反转
        GPIO_ResetBits(GPIOA, AIN1);
    } else if(direction == 0) {
        GPIO_ResetBits(GPIOA, AIN1); //刹车
        GPIO_ResetBits(GPIOA, AIN2);
    }
}
