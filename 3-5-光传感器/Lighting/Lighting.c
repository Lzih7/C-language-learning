#include "stm32f10x.h" // 包含 STM32F10x 系列微控制器的设备头文件

// 初始化照明（或按键）GPIO 引脚的函数
void Lighting_Init(void)
{
    // 使能 GPIOB 的时钟，确保 GPIOB 外设有电
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 定义 GPIO 初始化结构体
    GPIO_InitTypeDef GPIO_Initstruct;

    // 设置 GPIO 模式为上拉输入模式（IPU），用于读取外部信号（如按键或传感器）
    GPIO_Initstruct.GPIO_Mode = GPIO_Mode_IPU;

    // 设置 GPIO 引脚，使用 GPIOB 的第 13 引脚
    GPIO_Initstruct.GPIO_Pin = GPIO_Pin_13;

    // 设置 GPIO 引脚的速度为 50MHz，适合高频率信号
    GPIO_Initstruct.GPIO_Speed = GPIO_Speed_50MHz;

    // 初始化 GPIOB 引脚，按照之前的配置初始化
    GPIO_Init(GPIOB, &GPIO_Initstruct);
}

// 获取照明状态的函数
uint8_t Lighting_Get(void)
{
    // 读取 GPIOB 第 13 引脚的电平状态，返回传感器信号
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}
