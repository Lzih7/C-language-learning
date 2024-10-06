#include "stm32f10x.h" // 包含 STM32F10x 系列微控制器的设备头文件
#include "Lighting.h"  // 包含 Lighting 初始化和状态获取函数的头文件

// 定义宏 P0_5，用于表示 GPIOA 的第 0 到 5 号引脚
#define P0_5 ((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5))

int main(void)
{
    // 启用 GPIOA 的时钟，确保 GPIOA 引脚可以正常使用
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 定义 GPIO 初始化结构体
    GPIO_InitTypeDef GPIO_InitStruct;

    // 将 GPIO 模式设置为推挽输出模式，用于控制 LED 或其他外设
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;

    // 设置 GPIO 引脚，使用 GPIOA 的第 0 到 5 引脚（通过 P0_5 宏定义）
    GPIO_InitStruct.GPIO_Pin = P0_5;

    // 设置 GPIO 输出速度为 50MHz，适合高频率的操作
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    // 初始化 GPIOA 引脚，按照之前的配置进行设置
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 将 GPIOA 第 0 到 5 引脚设置为高电平，关闭所有 LED（假设低电平点亮 LED）
    GPIO_SetBits(GPIOA, P0_5);

    // 调用 Lighting_Init 函数，初始化 Lighting 模块（例如按键或传感器）
    Lighting_Init();

    // 无限循环，持续监控 Lighting 状态并控制 LED
    while (1)
    {
        // 获取 Lighting 状态（例如按键的状态）
        int a = Lighting_Get();

        // 如果 Lighting 状态为 1（通常表示按下或触发），点亮 LED
        if (a == 1)
        {
            // 将 GPIOA 第 0 到 5 引脚拉低，点亮所有 LED
            GPIO_ResetBits(GPIOA, P0_5);
        }

        // 如果 Lighting 状态为 0（通常表示未按下或未触发），关闭 LED
        if (a == 0)
        {
            // 将 GPIOA 第 0 到 5 引脚拉高，关闭所有 LED
            GPIO_SetBits(GPIOA, P0_5);
        }
    }
}
