# OLED驱动显⽰学号

• ⽬标：驱动 OLED显⽰屏 ，并显⽰你的学号
• 提⽰：直接使⽤他⼈提供的函数完成即可


![电路](files/OLED显示屏.jpg)

## 从外部引入OLED 的驱动
共有3个文件
**OLED.h OLED.c OLED_Font.h**  

有如下API可以用
```c
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
```

主函数的用法比较简单
```c
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
```