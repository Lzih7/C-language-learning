#include "stm32f10x.h" // Device header

int main(void)
{
    // 启用 GPIOC 的时钟，确保 GPIOC 外设有电
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // 定义 GPIO 初始化结构体
    GPIO_InitTypeDef GPIO_InitStruct;

    // 将 GPIO 模式设置为推挽输出模式
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;

    // 将 GPIO 引脚设置为 13 号引脚（PC13）
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;

    // 将 GPIO 速度设置为 50MHz，适合高频率的操作
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    // 初始化 GPIOC 引脚，按照之前的配置初始化
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    // 无限循环，主程序将在这里持续运行
    while (1)
    {
    }
}
