# OLED显示
## OLED：使用IIC通信协议
### IIC：

双线制通信：

+ 数据线（SDA）： 用于传输实际的数据。
+ 时钟线（SCL）： 由主设备生成的时钟信号，协调数据传输的节奏。
### 一些OLED函数
1. void OLED_Init(void)  //配置OLED
2. void OLED_Clear(void)  //清屏
3. void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)  //显示字符
4. void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)  //显示字符串
### 引脚配置

+ VCC -> 3.3V 或 5V
+ GND -> GND
+ SCL -> 通常是类似 PB6 或 PB8 之类的引脚
+ SDA -> 通常是类似 PB7 或 PB9 之类的引脚



