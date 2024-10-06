#include "stm32f10x.h" // 包含 STM32F10x 系列微控制器的设备头文件

// 简单的延时函数，通过空循环实现延时
void delay()
{
    int i = 0;
    for (i = 0; i < 500000; i++)
        ; // 空循环 500000 次实现延时
}

int main(void)
{
    // 启用 GPIOA 外设时钟，确保 GPIOA 引脚可以正常使用
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 定义 GPIO 初始化结构体
    GPIO_InitTypeDef GPIO_InitStruct;

    // 将 GPIO 模式设置为推挽输出模式（PP），用于驱动 LED
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;

    // 设置 GPIO 引脚，使用 GPIOA 的第 0 到 5 号引脚
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 //
			       | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;

    // 设置 GPIO 输出速度为 50MHz
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    // 初始化 GPIOA 引脚，按照之前的配置进行设置
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    while (1) // 主循环
    {
        // 关闭 GPIOA 第 0 到 5 号引脚，熄灭所有 LED
        GPIO_SetBits(GPIOA, (0x3F));//00111111

        // 使用循环控制流水灯效果，更简便的方式
        for (int i = 0; i < 6; i++)
        {
            // 将当前引脚（第 i 号引脚）设置为低电平，点亮 LED
            GPIO_ResetBits(GPIOA, (0x1 << i));
            delay(); // 延时

            // 将当前引脚（第 i 号引脚）设置为高电平，熄灭 LED
            GPIO_SetBits(GPIOA, (0x1 << i));
            delay(); // 延时
        }
    }
}
