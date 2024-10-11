# OLED驱动显⽰学号

• ⽬标：驱动 OLED显⽰屏 ，并显⽰你的学号
• 提⽰：直接使⽤他⼈提供的函数完成即可


![电路](files/OLED显示屏.jpg)

OLED SCL 接在PB8
OLED SDA 接在PB9

---


## OLED 相关介绍

**SCL** 和 **SDA** 是与 **I²C**（Inter-Integrated Circuit）通信协议相关的引脚名称，常用于像 **OLED 显示屏** 等外设与主控器件（如微控制器）之间的通信。

### 1. **SCL（Serial Clock Line）**：
- **SCL** 是 I²C 协议中的时钟信号线，用于同步数据的传输。
- 它由主设备（主机）产生，并用于协调数据在 SDA 线上的传输。每个时钟周期会同步传输一位数据。
- 在连接 OLED 时，SCL 控制数据传输的节奏，确保数据以特定的速度传输给显示器。

### 2. **SDA（Serial Data Line）**：
- **SDA** 是 I²C 总线上的数据线，用于传输实际的数据。
- 数据是通过 SDA 在 SCL 时钟信号的同步下进行双向传输的。SDA 线上可以传输数据位，也可以传输命令信息给 OLED 屏幕。
- SDA 线在主设备与从设备（如 OLED）之间传递数据。

### 3. **I²C 通信协议**：
- I²C 是一种用于短距离通信的串行协议，通常用于主设备（如微控制器）与多个从设备（如传感器、OLED 屏幕）之间的通信。
- I²C 只需要 **两根线**：SCL（时钟）和 SDA（数据），这使得它非常适合资源有限的应用。

### 4. **典型 OLED 接口说明**：
当你连接一个基于 I²C 的 OLED 显示屏时，通常会看到以下引脚：
- **GND**：接地。
- **VCC**：电源，通常为 3.3V 或 5V。
- **SCL**：串行时钟线。
- **SDA**：串行数据线。

OLED 显示屏通过 I²C 接口接收来自主控制器的指令，控制屏幕上的内容显示。SCL 和 SDA 引脚确保数据可以以同步方式传递，维持数据传输的顺序和时序。


- **SCL** 是 I²C 总线的时钟线。
- **SDA** 是 I²C 总线的数据线，用于传输数据。
- 它们常用于 OLED 显示屏等设备与微控制器之间的通信。

---

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