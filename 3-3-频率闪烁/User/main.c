#include "stm32f10x.h" // 包含 STM32F10x 系列微控制器的设备头文件

// 简单的延时函数，通过空循环实现延时
void delay(int i)
{
    for (int a = 0; a < i; a++)
        ; // 循环 i 次以实现简单延时
}

int main(void)
{
    // 启用 GPIOA 外设时钟，确保 GPIOA 引脚可以正常使用
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 定义 GPIO 初始化结构体
    GPIO_InitTypeDef GPIO_InitStruct;

    // 将 GPIO 模式设置为推挽输出模式（PP），用于驱动 LED 或其他外部设备
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;

    // 设置 GPIO 引脚，使用 GPIOA 的第 0 引脚
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;

    // 设置 GPIO 输出速度为 50MHz，适用于高频率的操作
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    // 初始化 GPIOA 引脚，按照之前的配置进行设置
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 无限循环，LED 将在这里进行不断的闪烁
    while (1)
    {
        int sleep = 5000000; // 定义延时周期长度

        // 将 GPIOA 引脚 0 设置为低电平，点亮 LED（或其他外设）
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);

        // 延时一段时间
        delay(sleep);

        // 将 GPIOA 引脚 0 设置为高电平，熄灭 LED（或关闭外设）
        GPIO_SetBits(GPIOA, GPIO_Pin_0);

        // 再次延时一段时间
        delay(sleep);
    }
}
