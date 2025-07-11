#ifndef __UTILITY_H
#define __UTILITY_H

#define GPIO_CFG(GPIOx, _Pin, _Speed, _Mode) \
    do                                            \
    {                                             \
        GPIO_InitTypeDef GPIO_InitStructure;      \
        GPIO_InitStructure.GPIO_Pin = _Pin;       \
        GPIO_InitStructure.GPIO_Mode = _Mode;     \
        GPIO_InitStructure.GPIO_Speed = _Speed;   \
        GPIO_Init(GPIOx, &GPIO_InitStructure);    \
    } while (0)

#define TIM_BASE_CFG(_TIMX, _Period, _Prescaler, _ClockDivision, _CounterMode) \
    do                                                                              \
    {                                                                               \
        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;                              \
        TIM_TimeBaseStructure.TIM_Period = _Period;                                 \
        TIM_TimeBaseStructure.TIM_Prescaler = _Prescaler;                           \
        TIM_TimeBaseStructure.TIM_ClockDivision = _ClockDivision;                   \
        TIM_TimeBaseStructure.TIM_CounterMode = _CounterMode;                       \
        TIM_TimeBaseInit(_TIMX, &TIM_TimeBaseStructure);                            \
    } while (0)

#define TIM_PWM_CFG(_TIMX, _OCX, _OCMode, _OutputState, _Pulse, _OCPolarity) \
    do                                                                            \
    {                                                                             \
        TIM_OCInitTypeDef TIM_OCInitStructure;                                    \
        TIM_OCInitStructure.TIM_OCMode = _OCMode;                                 \
        TIM_OCInitStructure.TIM_OutputState = _OutputState;                       \
        TIM_OCInitStructure.TIM_Pulse = _Pulse;                                   \
        TIM_OCInitStructure.TIM_OCPolarity = _OCPolarity;                         \
        TIM_OC##_OCX##Init(_TIMX, &TIM_OCInitStructure);                          \
    } while (0)

#define EXTI_CFG(_LINE, _MODE, _Trigger, _LineCmd) \
    do                                                  \
    {                                                   \
        EXTI_InitTypeDef EXTI_InitStructure;            \
        EXTI_InitStructure.EXTI_Line = _LINE;           \
        EXTI_InitStructure.EXTI_Mode = _MODE;           \
        EXTI_InitStructure.EXTI_Trigger = _Trigger;     \
        EXTI_InitStructure.EXTI_LineCmd = _LineCmd;     \
        EXTI_Init(&EXTI_InitStructure);                 \
    } while (0)	

#define NVIC_CFG(_Channel, _PreemptionPriority, _SubPriority, _Cmd)            \
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
