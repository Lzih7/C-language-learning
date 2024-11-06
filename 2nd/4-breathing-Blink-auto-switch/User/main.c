/**
 *
 * 目标:按下 按键2(PB10) 后 5s 内 LED 闪烁，之后⾃动切换为呼吸灯模式
 * 提示:使用TIM 的定时中断功能来实现 LED 闪烁
 *
 */
#include "stm32f10x.h"  // Device header
#include "stm32_util.h" // My Utility
#include "Delay.h"

const static uint8_t Positive = 0; /*LED变亮常量*/
const static uint8_t Negative = 1; /*LED变暗常量*/
const static uint8_t BLINK = 0;    /*闪烁常量*/
const static uint8_t BREATHE = 1;  /*呼吸常量*/

static uint8_t led_on = 1;              /*LED 开关状态*/
static uint16_t brightness = 0;         /*LED 当前的亮度*/
static uint8_t breathing_direction = 0; /*呼吸灯的方向*/
static uint8_t led_mode = BLINK;      /*LED当前的运行方式*/

void LED_Blink(void);

void Resource_Init(void)
{
    /*GPIO 配置 START----------------------------------------------------------------------------------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    /*利用宏拼接的简洁写法*/
    UTIL_GPIO_CFG_EX(A, 0, 50MHz, AF_PP); /*PA0 为复用推挽输出，用于 PWM 输出,LED*/
    UTIL_GPIO_CFG_EX(A, 1, 50MHz, AF_PP); /*PA1 为复用推挽输出，用于 PWM 输出,LED*/
    UTIL_GPIO_CFG_EX(B, 0, 50MHz, IPU);   /*PB0 为上拉输入，用于按键输入,BUTTON*/
    UTIL_GPIO_CFG_EX(B, 10, 50MHz, IPU);  /*PB10 为上拉输入，用于按键输入,BUTTON*/
    /*GPIO 配置 END------------------------------------------------------------------------------------------*/

    /*TIM 配置 START------------------------------------------------------------------------------------------*/
    /*TIM2 属于低速定时器，时钟源来自于 APB1 总线，通过 APB1 外设时钟使能*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    UTIL_TIM_BASE_EX(TIM2, 999, 71, DIV1, Up); /*配置定时器基本参数,目标是 TIM2*/

    /* 配置TIM2 PWM 模式;目标是 TIM2_CH1/2 设置为TIM_OCMode_PWM1模式，OCMode(Output Compare Mode) */
    UTIL_TIM_PWM_EX(TIM2, 1, /*PA0*/ PWM1, Enable, 0, High); /*TIM2_CH1 <=> PA0*/
    UTIL_TIM_PWM_EX(TIM2, 2, /*PA1*/ PWM1, Enable, 0, High); /*TIM2_CH2 <=> PA1*/

    TIM_Cmd(TIM2, ENABLE); /* 启动 TIM2*/

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); /*使能 TIM3 时钟*/
    /**
     * Prescaler = 7199 将时钟频率从 72 MHz 降低到10,000Hz = (72,000,000)/(7199+1)
     * 定时器的频率是 10 kHz（每秒钟计数 10,000 次）
     * 为了实现 5秒 的定时，定时器需要在 5 秒 内计数 5秒×10,000Hz=50,000次
     * 因此，自动重装载值（ARR）应设置为 50,000 - 1 = 49999。
     */
    UTIL_TIM_BASE_EX(TIM3, 49999, 7199, DIV1, Up); /*配置 TIM3，每 5 秒触发一次中断*/
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);     /*启用 TIM3 更新中断*/
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);    /*初始化时清除定时器中断标志，防止错误触发中断*/
    TIM_Cmd(TIM3, DISABLE);                        /*不启动TIM3*/
    /*TIM 配置 END----------------------------------------------------------------------------------------------*/

    /*中断配置 START---------------------------------------------------------------------------------------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); /*使能 AFIO 时钟*/

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0); /*选择 PB0 作为中断源*/
    UTIL_EXTI_EX(0, Interrupt, Falling, ENABLE);                /*EXTI_Line0 <==> (PA0、PB0);Interrupt;下降沿触发*/
    UTIL_NVIC_CFG(EXTI0_IRQn, 0, 0, ENABLE);                    /*配置中断优先级, 处理来自 GPIO 引脚 0（如 PA0、PB0）的中断事件*/

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10); /*选择 PB10 作为中断源*/
    UTIL_EXTI_EX(10, Interrupt, Falling, ENABLE);                /*EXTI_Line0 <==> (PA10、PB10);Interrupt;下降沿触发*/
    UTIL_NVIC_CFG(EXTI15_10_IRQn, 0, 0, ENABLE);                 /*PreemptionPriority=0; SubPriority=0*/

    UTIL_NVIC_CFG(TIM3_IRQn, 0, 0, ENABLE); /*使能 TIM3 中断通道*/
    /*中断配置 END-----------------------------------------------------------------------------------------------*/
}

void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        led_on = !led_on;                   // 切换 LED 开关状态
        EXTI_ClearITPendingBit(EXTI_Line0); // 清除中断标志
    }
}

/**按键 2 切换模式*/
void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line10) != RESET)
    {
        led_mode = BLINK;

        TIM_Cmd(TIM3, DISABLE);  /*停止定时器以确保重置*/
        TIM_SetCounter(TIM3, 0); /*重置计数器为0*/
        TIM_Cmd(TIM3, ENABLE);   /*重新启动定时器，开始新的5秒计时*/

        EXTI_ClearITPendingBit(EXTI_Line10); // 清除中断标志
    }
}

/**TIM3 中断处理*/
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        led_mode = BREATHE;
        TIM_Cmd(TIM3, DISABLE); // 停止定时器以确保重置
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

void LED_Blink(void)
{
    TIM_SetCompare1(TIM2, 999); // LED1 亮
    TIM_SetCompare2(TIM2, 999); // LED2 亮
    Delay_ms(250);

    TIM_SetCompare1(TIM2, 0); // LED1 灭
    TIM_SetCompare2(TIM2, 0); // LED2 灭
    Delay_ms(250);
}

void Breathe_LED(void)
{
    if (led_on)
    {
        if (breathing_direction == Positive)
        {
            brightness++;
            if (brightness >= 999)
                breathing_direction = Negative;
        }
        else
        {
            brightness--;
            if (brightness == 0)
                breathing_direction = Positive;
        }

        TIM_SetCompare1(TIM2, brightness); // 调整 TIM2 通道 1 的比较值，改变占空比
        TIM_SetCompare2(TIM2, brightness); // 调整 TIM2 通道 2 的比较值，改变占空比
    }
    else
    {
        // 如果 LED 关闭，停止 PWM 输出
        TIM_SetCompare1(TIM2, 0);
        TIM_SetCompare2(TIM2, 0);
    }
}

int main(void)
{
    Resource_Init();

    while (1)
    {
        if (led_mode == BREATHE)
        {
            Breathe_LED(); /*控制 LED 呼吸灯*/
            Delay_us(500); /**
                            * 目标是：1s 完成呼吸一次，暗变亮->亮变暗,
                            * 调整呼吸速度, main函数中 0.5ms(毫秒) 调度一次 Breathe_LED()
                            * 1s 调度2000次，占空比的变化是: 0->999 然后 999->0
                            */
        }
        else if (led_mode == BLINK)
        {
            LED_Blink();
        }
    }
}
