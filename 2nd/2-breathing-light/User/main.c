#include "stm32f10x.h" // Device header
#include "stm32_util.h"

static uint8_t FORWARD = 0;
static uint8_t BACKWARD = 1;

static uint8_t led_enabled = 1; // LED 开关状态
static uint16_t pwm_value = 0;
static uint8_t breathing_direction = 0;

void TIM2_PWM_Init()
{
    /*TIM2 属于低速定时器，时钟源来自于 APB1 总线，通过 APB1 外设时钟使能*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /*
     * 配置定时器基本参数
     *
     * STM32 的时钟频率为72 MHz，预分频器通常设为 71
     * 目标是 TIM2
     * Period=999 自动重装载值,选择 1kHz的PWM频率，这样在1s内可以有1000个调节点
     * Prescaler=71
     * TIM_CKD_DIV1 设置定时器不进行任何时钟分频，使其直接使用原始时钟频率。对于精确的时间计数或者快速响应的应用场景.
     * TIM_CounterMode_Up :设置定时器的计数模式为向上计数模式
     */
    UTIL_TIM_BASE_CFG(TIM2,
                      /* TIM_TimeBaseStructure */
                      999, 71, TIM_CKD_DIV1, TIM_CounterMode_Up);

    /*
     * 配置 PWM 模式
     * 目标是 TIM2, channel = 1
     *
     * TIM_OCMode=TIM_OCMode_PWM1;在 PWM 模式 1 下，输出比较寄存器（CCR）的值决定了信号的占空比
     * TIM_OutputState=TIM_OutputState_Enable
     * TIM_Pulse = 0
     * TIM_OCPolarity=TIM_OCPolarity_High
     *
     */
    UTIL_TIM_PWM_CFG(TIM2, 1,
                     /* TIM_OCInitStructure */
                     TIM_OCMode_PWM1, TIM_OutputState_Enable, 900, TIM_OCPolarity_High);

    TIM_Cmd(TIM2, ENABLE); /* 启动 TIM2*/
}

void GPIO_REF_Init(void)
{
    // 使能 GPIO 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    // 配置 PA0 为复用推挽输出，用于 PWM 输出
    UTIL_GPIO_CFG(GPIOA,
                  /* GPIO_InitTypeDef */
                  GPIO_Pin_0, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);

    // 配置 PB11 为上拉输入，用于按键输入
    UTIL_GPIO_CFG(GPIOB,
                  /* GPIO_InitTypeDef */
                  GPIO_Pin_11, GPIO_Mode_IPU, GPIO_Speed_50MHz);
}

void EXTI_Config(void)
{
    /*使能 AFIO 时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    /*选择 PB11 作为中断源*/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);

    /**
     * EXTI_Line=EXTI_Line11;
     * EXTI_Mode = Interrupt;
     * EXTI_Trigger = Falling;下降沿触发
     */
    UTIL_EXTI_CFG(EXTI_Line11,
                  /* EXTI_InitTypeDef */
                  EXTI_Mode_Interrupt, EXTI_Trigger_Falling, ENABLE);

    /**
     * 配置中断优先级
     *
     * NVIC_IRQChannel=EXTI15_10_IRQn; ̰ ̰
     * ChannelPreemptionPriority = 0;
     * ChannelSubPriority = 0;
     */
    UTIL_NVIC_CFG(EXTI15_10_IRQn, 0, 0, ENABLE);
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line11) != RESET)
    {
        led_enabled = !led_enabled;          // 切换 LED 开关状态
        EXTI_ClearITPendingBit(EXTI_Line11); // 清除中断标志
    }
}

void Breathe_LED(void)
{
    if (led_enabled)
    {
        if (breathing_direction == FORWARD)
        {
            pwm_value++;
            if (pwm_value >= 999)
                breathing_direction = BACKWARD;
        }
        else
        {
            pwm_value--;
            if (pwm_value == 0)
                breathing_direction = FORWARD;
        }

        // 调整 TIM2 通道 1 的比较值，改变占空比
        // TIM_SetCompare1(TIM2, pwm_value);
    }
    else
    {
        // 如果 LED 关闭，停止 PWM 输出
        TIM_SetCompare1(TIM2, 0);
    }
}

int main(void)
{
    GPIO_REF_Init(); // 初始化GPIO
    TIM2_PWM_Init(); // 初始化TIM2的PWM，1kHz的PWM频率
    EXTI_Config();   // 配置按键外部中断

    while (1)
    {
        Breathe_LED();      // 控制 LED 呼吸灯
        Delay_us(1 * 1000); // 调整呼吸速度
    }
}
