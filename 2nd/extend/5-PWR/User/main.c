/**
 *
 * ⽬标：加⼊ PWR 模块，在等待 蓝⽛ 接收数据时进⼊睡眠模式
 * 数据包格式是command+\n; e.g. "on\n" "off\n"
 *
 */
#include <string.h>
#include "stm32f10x.h"  // Device header
#include "stm32_util.h" // My Utility
#include "OLED.h"
#include "Delay.h"

static uint8_t bluetooth_has_data = 0;
static char rxBuffer[256] = {0}; /*receive buffer*/
static int bufferIndex = 0;

void LED_Blink(void);
void ProcessReceivedData(void);
void Resource_Init(void)
{
    /*GPIO 配置 START----------------------------------------------------------------------------------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_USART1,
                           ENABLE);

    /*利用宏拼接的简洁写法*/
    UTIL_GPIO_CFG_EX(A, 0, 50MHz, AF_PP); /*PA0 为复用推挽输出，用于 PWM 输出,LED*/
    UTIL_GPIO_CFG_EX(A, 1, 50MHz, AF_PP); /*PA1 为复用推挽输出，用于 PWM 输出,LED*/

    UTIL_GPIO_CFG_EX(A, 9, 50MHz, AF_PP);        /*配置 PA9 (TX)*/
    UTIL_GPIO_CFG_EX(A, 10, 50MHz, IN_FLOATING); /*配置 PA10 (RX)*/
    /*GPIO 配置 END------------------------------------------------------------------------------------------*/

    /*TIM 配置 START------------------------------------------------------------------------------------------*/
    /*TIM2 属于低速定时器，时钟源来自于 APB1 总线，通过 APB1 外设时钟使能*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    UTIL_TIM_BASE_EX(TIM2, 999, 71, DIV1, Up); /*配置定时器基本参数,目标是 TIM2*/

    /* 配置TIM2 PWM 模式;目标是 TIM2_CH1/2 设置为TIM_OCMode_PWM1模式，OCMode(Output Compare Mode) */
    UTIL_TIM_PWM_EX(TIM2, 1, /*PA0*/ PWM1, Enable, 0, High); /*TIM2_CH1 <=> PA0*/
    UTIL_TIM_PWM_EX(TIM2, 2, /*PA1*/ PWM1, Enable, 0, High); /*TIM2_CH2 <=> PA1*/

    TIM_Cmd(TIM2, ENABLE); /* 启动 TIM2*/
    /*TIM 配置 END----------------------------------------------------------------------------------------------*/

    /*UART START-----------------------------------------------------------------------------------------------*/
    UTIL_USART_CFG(9600, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, //
                   USART_HardwareFlowControl_None, USART_Mode_Rx | USART_Mode_Tx);
    USART_Cmd(USART1, ENABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); /*使能 USART1 接收中断*/

    UTIL_NVIC_CFG(USART1_IRQn, 1, 1, ENABLE); /*配置 NVIC，处理 UART 中断*/
    /*UART END-------------------------------------------------------------------------------------------------*/
}

/*串口中断处理*/
void USART1_IRQHandler(void)
{
    // 检查是否是接收中断
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        char receivedChar = USART_ReceiveData(USART1); /*读取接收到的数据 */
        rxBuffer[bufferIndex++] = receivedChar;        /*将接收到的数据存入缓冲区*/

        if (receivedChar == '\n') /*如果接收到换行符，认为数据包结束*/
        {
            rxBuffer[bufferIndex - 1] = '\0'; /* 把\n替换成\0结束符 */
            bufferIndex = 0;                  /* 重置缓冲区索引 */
            bluetooth_has_data = 1;
        }
    }
}

/*处理蓝牙通过串口发送过来的数据*/
void ProcessReceivedData(void)
{
    char *pt_recv = rxBuffer;

    if (strncmp(pt_recv, "off", 3) == 0)
    {
        TIM_SetCompare1(TIM2, 0); // LED1 亮
        TIM_SetCompare2(TIM2, 0); // LED2 亮
    }
    else if (strncmp(pt_recv, "on", 2) == 0)
    {
        TIM_SetCompare1(TIM2, 999); // LED1 亮
        TIM_SetCompare2(TIM2, 999); // LED2 亮
    }
}

int main(void)
{
    OLED_Init();
    Resource_Init();

    while (1)
    {
        if (bluetooth_has_data == 1)
        {
            OLED_Clear();
            OLED_ShowString(1, 1, "Has Data");
            Delay_ms(1000);
            ProcessReceivedData();
            bluetooth_has_data = 0;
        }

        OLED_Clear();
        OLED_ShowString(1, 1, "sleep");
        Delay_ms(500);
        __WFI();

        OLED_Clear();
        OLED_ShowString(1, 1, "WakeUp");
        Delay_ms(1000);
    }
}
