#include "stm32f10x.h" // Device header
#include "OLED.h"

int main(void)
{
  /*模块初始化*/
  OLED_Init(); // OLED初始化

  /*OLED显示*/
  OLED_ShowString(1, 1, "Hello World!"); // 1行1列显示字符串HelloWorld!

  // 无限循环，主程序将在这里持续运行
  while (1)
  {
  }
}
