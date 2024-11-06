/**
 *
 * 加⼊ 反射式红外传感器 代替 按键1 ，在距离过近时启动 LED ，在距离过远时关闭 LEDƒ
 *
 */
#include "stm32f10x.h"  // Device header
#include "stm32_util.h" // My Utility
#include "OLED.h"

const static uint8_t Positive = 0; /*LED变亮常量*/
const static uint8_t Negative = 1; /*LED变暗常量*/
const static uint8_t BLINK = 0;    /*闪烁常量*/
const static uint8_t BREATHE = 1;  /*呼吸常量*/

static uint8_t led_on = 1;              /*LED 开关状态*/
static uint16_t brightness = 0;         /*LED 当前的亮度*/
static uint8_t breathing_direction = 0; /*呼吸灯的方向*/
static uint8_t led_mode = BREATHE;      /*LED当前的运行方式*/
static uint16_t AD_Value = 0;

void LED_Blink(void);

void Resource_Init(void)
{
    /*GPIO 配置 START----------------------------------------------------------------------------------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); /** 使能 ADC1 */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);   /** 使能 DMA1 */

    /*利用宏拼接的简洁写法*/
    UTIL_GPIO_CFG_EX(A, 0, 50MHz, AF_PP); /*PA0 为复用推挽输出，用于 PWM 输出,LED*/
    UTIL_GPIO_CFG_EX(A, 1, 50MHz, AF_PP); /*PA1 为复用推挽输出，用于 PWM 输出,LED*/
    UTIL_GPIO_CFG_EX(A, 6, 50MHz, AIN);   /*PA3 为模拟输入*/
    UTIL_GPIO_CFG_EX(B, 0, 50MHz, IPU);   /*PB0 为上拉输入，用于按键输入,BUTTON*/
    UTIL_GPIO_CFG_EX(B, 10, 50MHz, IPU);  /*PB10 为上拉输入，用于按键输入,BUTTON*/
    /*GPIO 配置 END------------------------------------------------------------------------------------------*/

    /*TIM 配置 START------------------------------------------------------------------------------------------*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); /*TIM2 属于低速定时器，时钟源来自于 APB1 总线*/

    UTIL_TIM_BASE_EX(TIM2, 999, 71, DIV1, Up); /*配置定时器基本参数,目标是 TIM2*/

    /* 配置TIM2 PWM 模式;目标是 TIM2_CH1/2 设置为TIM_OCMode_PWM1模式，OCMode(Output Compare Mode) */
    UTIL_TIM_PWM_EX(TIM2, 1, /*PA0*/ PWM1, Enable, 0, High); /*TIM2_CH1 <=> PA0*/
    UTIL_TIM_PWM_EX(TIM2, 2, /*PA1*/ PWM1, Enable, 0, High); /*TIM2_CH2 <=> PA1*/

    TIM_Cmd(TIM2, ENABLE); /* 启动 TIM2*/
    /*TIM 配置 END----------------------------------------------------------------------------------------------*/

    /*ADC DMA初始化 START-------------------------------------------------------------------------------------------------*/
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_55Cycles5); /*规则组通道配置 PA6*/
    UTIL_ADC_CFG(ADC1,
                 ADC_Mode_Independent,      /*_ADC_Mode ;模式，选择独立模式，即单独使用ADC1*/
                 ENABLE,                    /*_ADC_ScanConvMode ;扫描模式，使能，扫描规则组的序列，扫描数量由ADC_NbrOfChannel确定*/
                 ENABLE,                    /*_ADC_ContinuousConvMode; 连续转换，使能，每转换一次规则组序列后立刻开始下一次转换*/
                 ADC_ExternalTrigConv_None, /*_ADC_ExternalTrigConv; 外部触发，使用软件触发，不需要外部触发*/
                 ADC_DataAlign_Right,       /*_ADC_DataAlign; 数据对齐，选择右对齐*/
                 1                          /*_ADC_NbrOfChannel; 通道数1*/
    );

    UTIL_DMA_CFG(DMA1_Channel1,
                 (uint32_t)&ADC1->DR,             /*DMA_PeripheralBaseAddr*/
                 (uint32_t)&AD_Value,             /*DMA_MemoryBaseAddr*/
                 DMA_DIR_PeripheralSRC,           /*DMA_DIR*/
                 1,                               /*DMA_BufferSize*/
                 DMA_PeripheralInc_Disable,       /*DMA_PeripheralInc*/
                 DMA_MemoryInc_Disable,           /*DMA_MemoryInc*/
                 DMA_PeripheralDataSize_HalfWord, /*DMA_PeripheralDataSize*/
                 DMA_MemoryDataSize_HalfWord,     /*DMA_MemoryDataSize*/
                 DMA_Mode_Circular,               /*DMA_Mode*/
                 DMA_Priority_Medium,             /*DMA_Priority*/
                 DMA_M2M_Disable                  /*DMA_M2M*/
    );

    DMA_Cmd(DMA1_Channel1, ENABLE); /*DMA1的通道1使能*/
    ADC_DMACmd(ADC1, ENABLE);       /*ADC1触发DMA1的信号使能*/
    ADC_Cmd(ADC1, ENABLE);          /*ADC1使能*/

    /*ADC校准*/
    ADC_ResetCalibration(ADC1); /*固定流程，内部有电路会自动执行校准*/
    while (ADC_GetResetCalibrationStatus(ADC1) == SET)
        ;
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET)
        ;
    /*ADC触发*/
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    /*ADC DMA初始化 END ---------------------------------------------------------------------------------------------------*/

    /*RTC配置 START---------------------------------------------------------------------------------------------*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); /** 启用 PWR 时钟 **/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE); /** 启用 BKP 时钟 **/

    PWR_BackupAccessCmd(ENABLE); /** 允许访问备份寄存器 **/
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {
        RCC_LSICmd(ENABLE);
        while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) != SET)
            ;

        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
        RCC_RTCCLKCmd(ENABLE);

        RTC_WaitForSynchro();
        RTC_WaitForLastTask();

        RTC_SetPrescaler(40000 - 1);
        RTC_WaitForLastTask();

        // MyRTC_SetTime();

        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
    }
    else
    {
        RCC_LSICmd(ENABLE);
        while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) != SET)
            ;

        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
        RCC_RTCCLKCmd(ENABLE);

        RTC_WaitForSynchro();
        RTC_WaitForLastTask();
    }
    /*RTC配置 END-----------------------------------------------------------------------------------------------*/

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
        if (led_mode == BREATHE)
        {
            led_mode = BLINK;

            TIM_Cmd(TIM3, DISABLE);  /*停止定时器以确保重置*/
            TIM_SetCounter(TIM3, 0); /*重置计数器为0*/
            TIM_Cmd(TIM3, ENABLE);   /*重新启动定时器，开始新的5秒计时*/
        }
        else
        {
            led_mode = BREATHE;
        }
    }

    EXTI_ClearITPendingBit(EXTI_Line10); // 清除中断标志
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
    SystemInit();    /** 配置系统时钟 **/
    Resource_Init(); /** 配置系统用到的所有资源 **/
    OLED_Init();     /*OLED初始化*/

    uint32_t startTime = RTC_GetCounter(); /** 记录开始时间 **/

    while (1)
    {
        led_on = (AD_Value < 2000 ? 1 : 0);
        uint32_t currentTime = RTC_GetCounter(); /** 获取当前时间 **/
        if ((currentTime - startTime) >= 1)
        {
            startTime = currentTime;
            OLED_ShowNum(1, 5, AD_Value, 4);
        }

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
