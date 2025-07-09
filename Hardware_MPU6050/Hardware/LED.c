#include "stm32f10x.h" // 包含 STM32F10x 系列微控制器的设备头文件

// 初始化 LED 的函数，配置 GPIOA 的引脚用于控制 LED
void LED_Init(void)
{
    // 使能 GPIOA 的时钟，确保 GPIOA 外设有电
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 定义 GPIO 初始化结构体，用于配置 LED 输出
    GPIO_InitTypeDef GPIO_Initstructure;

    // 将 GPIO 模式设置为推挽输出模式（PP），用于驱动 LED
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;

    // 设置 GPIO 引脚，LED 连接到 GPIOA 的第 0 和第 1 引脚
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;

    // 设置 GPIO 的速度为 50MHz
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;

    // 初始化 GPIOA 引脚，按照之前的配置初始化
    GPIO_Init(GPIOA, &GPIO_Initstructure);

    // 设置 GPIOA 引脚 0 和 1 为高电平，默认关闭 LED
    GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1);
}

// 打开 LED0（GPIOA 引脚 0）的函数
void LED0_ON(void)
{
    // 将 GPIOA 第 0 引脚拉低（0 电平），点亮 LED0
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);
}

// 关闭 LED0（GPIOA 引脚 0）的函数
void LED0_OFF(void)
{
    // 将 GPIOA 第 0 引脚拉高（1 电平），熄灭 LED0
    GPIO_SetBits(GPIOA, GPIO_Pin_0);
}

// 打开 LED1（GPIOA 引脚 1）的函数
void LED1_ON(void)
{
    // 将 GPIOA 第 1 引脚拉低（0 电平），点亮 LED1
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

// 关闭 LED1（GPIOA 引脚 1）的函数
void LED1_OFF(void)
{
    // 将 GPIOA 第 1 引脚拉高（1 电平），熄灭 LED1
    GPIO_SetBits(GPIOA, GPIO_Pin_1);
}
