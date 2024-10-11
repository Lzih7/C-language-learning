#ifndef __STM32_UTIL_H
#define __STM32_UTIL_H
#include "stm32f10x.h" // Device header

void Delay_us(uint32_t xus);

/**
 * 简化了对 GPIO 引脚的初始化操作。传入 GPIO 端口、引脚号、模式和速度参数，快速初始化对应的 GPIO 引脚，而不必手动设置每个参数
 *
 * GPIO_InitTypeDef：这是 STM32 的标准库结构体，用来存储 GPIO 引脚的配置信息，如引脚编号、模式、速度等。
 *
 * _Pin     ：传入的 GPIO 引脚号，用于指定需要配置的引脚（如 GPIO_Pin_0, GPIO_Pin_1 等）。
 * _Mode    ：传入的 GPIO 引脚工作模式（如输入、输出、复用等），通过宏参数传入。
 * _Speed   ：传入的 GPIO 引脚速度等级，用于配置引脚信号的切换速率（如 GPIO_Speed_10MHz, GPIO_Speed_50MHz 等）。
 *
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

/**
 * 简化 GPIO 的初始化过程，用户只需传入 GPIO 端口（GPIOx）、引脚号（Pin）、模式（Mode）和速度（Speed）四个参数，
 * 便可完成对指定引脚的配置。这是UTIL_GPIO_CFG的简化版
 *
 *
 * GPIO_InitTypeDef     ：这是标准库中的结构体，用来配置 GPIO 引脚的各种属性，如引脚编号、模式和速度等。
 *
 * _Pin   ：将传入的 Pin 宏参数拼接成 GPIO_Pin_X 的格式，表示特定的 GPIO 引脚。
 *          例如，如果传入 Pin = 5，则生成 GPIO_Pin_5。
 * _Mode  ：将 Mode 参数拼接为 GPIO_Mode_X 格式，用于配置 GPIO 引脚的模式，如输入模式、输出模式等。
 * _Speed ：将 Speed 参数拼接为 GPIO_Speed_X 格式，设置 GPIO 引脚的速度，如低速、中速或高速。
 *
 */
#define UTIL_GPIO_CFG_EX(_GPIOx, _Pin, _Mode, _Speed)        \
    do                                                       \
    {                                                        \
        GPIO_InitTypeDef GPIO_InitStructure;                 \
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_##_Pin;       \
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_##_Mode;    \
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_##_Speed; \
        GPIO_Init(_GPIOx, &GPIO_InitStructure);              \
    } while (0)

/**
 * 通过传入定时器的周期、预分频器、时钟分频和计数模式，简化了定时器的基本配置操作
 *
 * _TIMX            ：这是 STM32 标准外设库中的结构体，用于配置定时器的基本参数，如周期、预分频器、时钟分频和计数模式。
 * _Period          ：设置定时器的自动重装载值，决定定时器的周期。计数器从 0 计数到 TIM_Period 值时会触发定时器事件，
 *                    然后重置为 0 重新计数。
 * _Prescaler       ：设置定时器的预分频器，用于将主时钟频率分频，以降低定时器的输入时钟频率。
 * _ClockDivision   ：设置定时器的时钟分频因子（如 TIM_CKD_DIV1, TIM_CKD_DIV2, TIM_CKD_DIV4），进一步调整定时器的时钟频率。
 * _CounterMode     ：指定定时器的计数模式，通常有 TIM_CounterMode_Up（向上计数）、TIM_CounterMode_Down（向下计数） ... *
 *
 */
#define UTIL_TIM_BASE_CFG(_TIMX, _Period, _Prescaler, _ClockDivision, _CounterMode) \
    do                                                                              \
    {                                                                               \
        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;                              \
        TIM_TimeBaseStructure.TIM_Period = _Period;                                 \
        TIM_TimeBaseStructure.TIM_Prescaler = _Prescaler;                           \
        TIM_TimeBaseStructure.TIM_ClockDivision = _ClockDivision;                   \
        TIM_TimeBaseStructure.TIM_CounterMode = _CounterMode;                       \
        TIM_TimeBaseInit(_TIMX, &TIM_TimeBaseStructure);                            \
    } while (0)

/**
 * 简化了 PWM 输出的配置。你可以通过传入定时器实例、通道编号、输出比较模式、输出状态、占空比和极性，快速设置定时器的 PWM 输出功能。
 * 该宏定义支持灵活地选择定时器的不同通道，并且通过拼接 _OCX，支持 OC1, OC2, OC3 或 OC4 通道的配置
 *
 *
 *
 * TIM_OCInitTypeDef：这是 STM32 的标准库结构体，用于配置定时器输出比较（OC）模式的参数，主要包括输出模式、输出状态、占空比和输出极性。
 * TIM_OCMode       ：输出比较模式，用于选择定时器的 PWM 模式，例如 TIM_OCMode_PWM1 或 TIM_OCMode_PWM2。
 * TIM_OutputState  ：指定输出状态（使能或禁用），用来决定 PWM 信号是否输出。例如 TIM_OutputState_Enable 可以启用 PWM 输出。
 * TIM_Pulse        ：设置 PWM 占空比，表示高电平持续的时间（脉宽），值越大占空比越高。
 * TIM_OCPolarity   ：设置 PWM 输出的极性，表示输出信号是高电平有效还是低电平有效（如 TIM_OCPolarity_High）。
 * TIM_OC##_OCX##Init()：根据指定的通道（_OCX）调用相应的初始化函数，例如 TIM_OC1Init, TIM_OC2Init 等。
 *      _OCX 是宏参数，可以拼接为 OC1, OC2, OC3, 或 OC4，根据不同的定时器通道选择不同的输出比较初始化函数。
 *
 */
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

/**
 * 简化了 EXTI 的初始化过程。用户只需提供 EXTI 线路编号、工作模式、触发条件以及启用/禁用状态，宏会完成 EXTI 的初始化。
 * 这个配置适用于处理外部 GPIO 触发的中断或事件，例如按键检测、传感器输入等
 *
 * 用法：
 *      UTIL_EXTI_CFG_EX(0, Interrupt, Rising, ENABLE);  // 配置 EXTI0 为上升沿触发中断
 *
 * EXTI_InitTypeDef ：这是 STM32 的标准库结构体，用于配置外部中断（EXTI）的参数，包括中断线路、模式、触发条件等。
 * EXTI_Line        ：指定 EXTI 线路。每个 EXTI 线路与具体的 GPIO 引脚对应，如 EXTI_Line0 对应 PA0。
 * EXTI_Mode        ：设置 EXTI 的模式，可以是中断模式 (EXTI_Mode_Interrupt) 或事件模式 (EXTI_Mode_Event)。
 * EXTI_Trigger     ：设置触发条件，定义外部中断在何种条件下触发，如上升沿触发 (EXTI_Trigger_Rising)、
 *                   下降沿触发 (EXTI_Trigger_Falling)、或双边沿触发 (EXTI_Trigger_Rising_Falling)。
 * EXTI_LineCmd     ：启用或禁用指定的 EXTI 线路。ENABLE 表示启用，DISABLE 表示禁用。
 */
#define UTIL_EXTI_CFG(_LINE, _MODE, _Trigger, _LineCmd) \
    do                                                  \
    {                                                   \
        EXTI_InitTypeDef EXTI_InitStructure;            \
        EXTI_InitStructure.EXTI_Line = _LINE;           \
        EXTI_InitStructure.EXTI_Mode = _MODE;           \
        EXTI_InitStructure.EXTI_Trigger = _Trigger;     \
        EXTI_InitStructure.EXTI_LineCmd = _LineCmd;     \
        EXTI_Init(&EXTI_InitStructure);                 \
    } while (0)

/**
 * 简化了 EXTI 的初始化配置，并提供了更多灵活性。通过传入 EXTI 线路编号（_X）、模式（_MODE）、触发条件（_Trigger），
 * 以及启用/禁用状态（_LineCmd），可以快速配置外部中断的工作模式。
 * 宏使用参数拼接功能自动生成相应的模式和触发条件，非常适合处理中断请求，比如按键检测、传感器信号等
 *
 *
 * _X       ：拼接 _X 参数，用于生成 EXTI 线路号（如 EXTI_Line0, EXTI_Line1 等）。
 *            _X 是一个数值，用于指定 EXTI 线路与具体的 GPIO 引脚对应。
 * _MODE    ：拼接 _MODE 参数，生成 EXTI 的模式（如 EXTI_Mode_Interrupt 或 EXTI_Mode_Event）。
 *            _MODE 通过宏参数传入，可以是中断模式或事件模式。
 * _Trigger ：拼接 _Trigger 参数，生成 EXTI 的触发条件
 *            如 EXTI_Trigger_Rising, EXTI_Trigger_Falling, EXTI_Trigger_Rising_Falling
 *            根据触发条件来确定中断的触发时机。
 * _LineCmd ：直接传入用于启用或禁用 EXTI 线路的宏参数，通常是 ENABLE 或 DISABLE。
 *
 */
#define UTIL_EXTI_CFG_EX(_X, _MODE, _Trigger, _LineCmd)            \
    do                                                             \
    {                                                              \
        EXTI_InitTypeDef EXTI_InitStructure;                       \
        EXTI_InitStructure.EXTI_Line = EXTI_Line##_X;              \
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_##_MODE;          \
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_##_Trigger; \
        EXTI_InitStructure.EXTI_LineCmd = _LineCmd;                \
        EXTI_Init(&EXTI_InitStructure);                            \
    } while (0)

/**
 * 简化了 NVIC 的初始化配置。用户可以通过传入中断通道号、抢占优先级、子优先级以及启用/禁用状态，快速配置和启用/禁用中断
 *
 *
 * NVIC_InitTypeDef     ：这是 STM32 标准外设库中的结构体，用于配置 NVIC（嵌套向量中断控制器）的参数，包括中断通道、优先级和启用状态。
 * _Channel             ：指定中断通道号，定义哪个中断将被配置或管理。不同的外设或 GPIO 可能对应不同的中断通道。
 * _PreemptionPriority  ：设置该中断的抢占优先级。抢占优先级用于决定不同中断的优先处理顺序。数值越小，优先级越高
 * _SubPriority         ：设置子优先级，主要在抢占优先级相同时用于进一步的排序。数值越小，优先级越高。
 * _Cmd                 ：用于启用或禁用该中断通道，通常传递 ENABLE 或 DISABLE。
 *
 */
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
