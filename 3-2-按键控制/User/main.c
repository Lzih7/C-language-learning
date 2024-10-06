#include "stm32f10x.h" // 包含 STM32F10x 系列微控制器的设备头文件
#include "LED.h"       // 包含控制 LED 的相关函数和定义
#include "KEY.h"       // 包含按键的相关函数和定义

uint8_t KeyNum = 0; // 定义一个 8 位无符号整型变量，用于存储按键编号

int main(void)
{
    LED_Init(); // 初始化 LED，配置相关 GPIO 引脚
    Key_Init(); // 初始化按键，配置相关 GPIO 引脚

    while (1) // 主循环，程序将在此不断执行
    {
        KeyNum = Key_GetNum(); // 获取当前按下的按键编号

        // 如果按下的按键编号是 1
        if (KeyNum == 1)
        {
            LED0_ON(); // 打开 LED0
            LED1_ON(); // 打开 LED1
        }

        // 如果按下的按键编号是 2
        if (KeyNum == 2)
        {
            LED0_OFF(); // 关闭 LED0
            LED1_OFF(); // 关闭 LED1
        }
    }
}
