#ifndef __STM32_UTIL_H
#define __STM32_UTIL_H
#include "stm32f10x.h" // Device header

void Delay_us(uint32_t xus);

/*
该宏简化了 GPIO 初始化过程，只需传入 GPIO 端口、引脚号、模式和速度，即可完成配置。
将宏参数 Pin 转换为 GPIO_Pin_X 格式
将宏参数 Mode 转换为 GPIO_Mode_X 格式
将宏参数 Speed 转换为 GPIO_Speed_X 格式
使用指定的配置初始化对应的 GPIO 端口 GPIOx ̰
*/
#define UTIL_GPIO_CFG(GPIOx, _Pin, _Mode, _Speed) \
    do                                            \
    {                                             \
        GPIO_InitTypeDef GPIO_InitStructure;      \
        GPIO_InitStructure.GPIO_Pin = _Pin;       \
        GPIO_InitStructure.GPIO_Mode = _Mode;     \
        GPIO_InitStructure.GPIO_Speed = _Speed;   \
        GPIO_Init(GPIOx, &GPIO_InitStructure);    \
    } while (0)

#define UTIL_GPIO_CFG_EX(GPIOx, Pin, Mode, Speed)           \
    do                                                      \
    {                                                       \
        GPIO_InitTypeDef GPIO_InitStructure;                \
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_##Pin;       \
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_##Mode;    \
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_##Speed; \
        GPIO_Init(GPIOx, &GPIO_InitStructure);              \
    } while (0)

#define UTIL_TIM_BASE_CFG(TIMX, _Period, _Prescaler, _ClockDivision, _CounterMode) \
    do                                                                             \
    {                                                                              \
        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;                             \
        TIM_TimeBaseStructure.TIM_Period = _Period;                                \
        TIM_TimeBaseStructure.TIM_Prescaler = _Prescaler;                          \
        TIM_TimeBaseStructure.TIM_ClockDivision = _ClockDivision;                  \
        TIM_TimeBaseStructure.TIM_CounterMode = _CounterMode;                      \
        TIM_TimeBaseInit(TIMX, &TIM_TimeBaseStructure);                            \
    } while (0)

#define UTIL_TIM_PWM_CFG(_TIMX, _OCX, _OCMode, _OutputState, _Pulse, _OCPolarity) \
    do                                                                            \
    {                                                                             \
        TIM_OCInitTypeDef TIM_OCInitStructure;                                    \
        TIM_OCInitStructure.TIM_OCMode = _OCMode;                                 \
        TIM_OCInitStructure.TIM_OutputState = _OutputState;                       \
        TIM_OCInitStructure.TIM_Pulse = _Pulse;                                   \
        TIM_OCInitStructure.TIM_OCPolarity = _OCPolarity;                         \
        TIM_OC##_OCX##Init(_TIMX, &TIM_OCInitStructure);                          \
    } while (0)

#define UTIL_EXTI_CFG(_LINE, _MODE, _Trigger, _LineCmd)               \
    do                                                             \
    {                                                              \
        EXTI_InitTypeDef EXTI_InitStructure;                       \
        EXTI_InitStructure.EXTI_Line = _LINE;              \
        EXTI_InitStructure.EXTI_Mode = _MODE;          \
        EXTI_InitStructure.EXTI_Trigger = _Trigger; \
        EXTI_InitStructure.EXTI_LineCmd = _LineCmd;                \
        EXTI_Init(&EXTI_InitStructure);                            \
    } while (0)
		
#define UTIL_EXTI_CFG_EX(_X, _MODE, _Trigger, _LineCmd)               \
    do                                                             \
    {                                                              \
        EXTI_InitTypeDef EXTI_InitStructure;                       \
        EXTI_InitStructure.EXTI_Line = EXTI_Line##_X;              \
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_##_MODE;          \
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_##_Trigger; \
        EXTI_InitStructure.EXTI_LineCmd = _LineCmd;                \
        EXTI_Init(&EXTI_InitStructure);                            \
    } while (0)

#define UTIL_NVIC_CFG(_Channel, _PreemptionPriority, _SubPriority, _Cmd)            \
    do                                                                              \
    {                                                                               \
        NVIC_InitTypeDef NVIC_InitStructure;                                        \
        NVIC_InitStructure.NVIC_IRQChannel = _Channel;                              \
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = _PreemptionPriority; \
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = _SubPriority;               \
        NVIC_InitStructure.NVIC_IRQChannelCmd = _Cmd;                               \
        NVIC_Init(&NVIC_InitStructure);                                             \
    } while (0)

#endif
