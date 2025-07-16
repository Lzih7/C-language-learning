#include "stm32f10x.h" // 包含 STM32F10x 系列微控制器的设备头文件

// 简单的延时函数，通过空循环实现延时
void delay(int i)
{
    for (int a = 0; a < i; a++)
        ; // 循环 i 次以实现简单延时
}

// 按键初始化函数，配置 GPIOB 的引脚用于按键输入
void Key_Init()
{
    // 使能 GPIOB 的时钟，确保 GPIOB 外设有电
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 定义 GPIO 初始化结构体，用于配置按键输入
    GPIO_InitTypeDef GPIO_Initstructure;

    // 将 GPIO 模式设置为上拉输入（IPU），用于按键检测
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;

    // 设置 GPIO 引脚，按键连接到 GPIOB 的第 0 引脚和第 11 引脚
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_11 ;

    // 设置 GPIO 的速度为 50MHz
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;

    // 初始化 GPIOB 引脚，按照之前的配置初始化
    GPIO_Init(GPIOB, &GPIO_Initstructure);
}

// 获取按键编号的函数，根据按键状态返回对应的按键编号
uint8_t Key_GetNum(void)
{
    static uint8_t KeyNum=0;

    if(KeyNum!=1){// 检查 GPIOB 第 0 引脚的电平状态，判断按键是否按下
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0) // 如果按键按下
		{
			delay(30000); // 进行去抖动处理，延时
			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
				;         // 等待按键松开
			delay(30000); // 再次延时以防止误检测
			KeyNum = 1;   // 按键编号设置为 1
		}
	}
    // 检查 GPIOB 第 11 引脚的电平状态，判断按键是否按下
	if(KeyNum==1){
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0) // 如果按键按下
		{
			delay(30000); // 进行去抖动处理，延时
			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
				;         // 等待按键松开
			delay(30000); // 再次延时以防止误检测
			KeyNum = 2;   // 按键编号设置为 2
		}
	}
    return KeyNum; // 返回按键编号
}
