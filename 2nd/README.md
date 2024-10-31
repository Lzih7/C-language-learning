## 说明
##子文件夹中的项目都是Keil项目**

**有些项目中有`stm32_util.h` `stm32_util.c`**
`stm32_util.h` 包含了GPIO、 TIM、 EXTI ... 的简单写法,用宏包装,这样代码看起来比较整洁。

## Pin 对照表


| 引脚号 | 引脚名称            | 类型   | I/O口电平 | 主功能         | 默认复用功能                                  | 重定义功能                          |
|-----|-----------------|------|--------|-------------|-----------------------------------------|--------------------------------|
| 1   | VBAT            | S    |        | VBAT        |                                         |                                |
| 2   | PC13-TAMPER-RTC | I/O  |        | PC13        | TAMPER-RTC                              |                                |
| 3   | PC14-OSC32_IN   | I/O  |        | PC14        | OSC32_IN                                |                                |
| 4   | PC15-OSC32_OUT  | I/O  |        | PC15        | OSC32_OUT                               |                                |
| 5   | OSC_IN          | I    |        | OSC_IN      |                                         |                                |
| 6   | OSC_OUT         | O    |        | OSC_OUT     |                                         |                                |
| 7   | NRST            | I/O  |        | NRST        |                                         |                                |
| 8   | VSSA            | S    |        | VSSA        |                                         |                                |
| 9   | VDDA            | S    |        | VDDA        |                                         |                                |
| 10  | PA0-WKUP        | I/O  |        | PA0         | WKUP/USART2_CTS/ADC12_IN0/TIM2_CH1_ETR  |                                |
| 11  | PA1             | I/O  |        | PA1         | USART2_RTS/ADC12_IN1/TIM2_CH2           |                                |
| 12  | PA2             | I/O  |        | PA2         | USART2_TX/ADC12_IN2/TIM2_CH3            |                                |
| 13  | PA3             | I/O  |        | PA3         | USART2_RX/ADC12_IN3/TIM2_CH4            |                                |
| 14  | PA4             | I/O  |        | PA4         | SPI1_NSS/USART2_CK/ADC12_IN4            |                                |
| 15  | PA5             | I/O  |        | PA5         | SPI1_SCK/ADC12_IN5                      |                                |
| 16  | PA6             | I/O  |        | PA6         | SPI1_MISO/ADC12_IN6/TIM3_CH1            | TIM1_BKIN                      |
| 17  | PA7             | I/O  |        | PA7         | SPI1_MOSI/ADC12_IN7/TIM3_CH2            | TIM1_CH1N                      |
| 18  | PB0             | I/O  |        | PB0         | ADC12_IN8/TIM3_CH3                      | TIM1_CH2N                      |
| 19  | PB1             | I/O  |        | PB1         | ADC12_IN9/TIM3_CH4                      | TIM1_CH3N                      |
| 20  | PB2             | I/O  | FT     | PB2/BOOT1   |                                         |                                |
| 21  | PB10            | I/O  | FT     | PB10        | I2C2_SCL/USART3_TX                      | TIM2_CH3                       |
| 22  | PB11            | I/O  | FT     | PB11        | I2C2_SDA/USART3_RX                      | TIM2_CH4                       |
| 23  | VSS_1           | S    |        | VSS_1       |                                         |                                |
| 24  | VDD_1           | S    |        | VDD_1       |                                         |                                |
| 25  | PB12            | I/O  | FT     | PB12        | SPI2_NSS/I2C2_SMBAI/USART3_CK/TIM1_BKIN |                                |
| 26  | PB13            | I/O  | FT     | PB13        | SPI2_SCK/USART3_CTS/TIM1_CH1N           |                                |
| 27  | PB14            | I/O  | FT     | PB14        | SPI2_MISO/USART3_RTS/TIM1_CH2N          |                                |
| 28  | PB15            | I/O  | FT     | PB15        | SPI2_MOSI/TIM1_CH3N                     |                                |
| 29  | PA8             | I/O  | FT     | PA8         | USART1_CK/TIM1_CH1/MCO                  |                                |
| 30  | PA9             | I/O  | FT     | PA9         | USART1_TX/TIM1_CH2                      |                                |
| 31  | PA10            | I/O  | FT     | PA10        | USART1_RX/TIM1_CH3                      |                                |
| 32  | PA11            | I/O  | FT     | PA11        | USART1_CTS/USBDM/CAN_RX/TIM1_CH4        |                                |
| 33  | PA12            | I/O  | FT     | PA12        | USART1_RTS/USBDP/CAN_TX/TIM1_ETR        |                                |
| 34  | PA13            | I/O  | FT     | JTMS/SWDIO  |                                         | PA13                           |
| 35  | VSS_2           | S    |        | VSS_2       |                                         |                                |
| 36  | VDD_2           | S    |        | VDD_2       |                                         |                                |
| 37  | PA14            | I/O  | FT     | JTCK/SWCLK  |                                         | PA14                           |
| 38  | PA15            | I/O  | FT     | JTDI        |                                         | TIM2_CH1_ETR/PA15/SPI1_NSS     |
| 39  | PB3             | I/O  | FT     | JTDO        |                                         | PB3/TRACESWO/TIM2_CH2/SPI1_SCK |
| 40  | PB4             | I/O  | FT     | NJTRST      |                                         | PB4/TIM3_CH1/SPI1_MISO         |
| 41  | PB5             | I/O  |        | PB5         | I2C1_SMBAI                              | TIM3_CH2/SPI1_MOSI             |
| 42  | PB6             | I/O  | FT     | PB6         | I2C1_SCL/TIM4_CH1                       | USART1_TX                      |
| 43  | PB7             | I/O  | FT     | PB7         | I2C1_SDA/TIM4_CH2                       | USART1_RX                      |
| 44  | BOOT0           | I    |        | BOOT0       |                                         |                                |
| 45  | PB8             | I/O  | FT     | PB8         | TIM4_CH3                                | I2C1_SCL/CAN_RX                |
| 46  | PB9             | I/O  | FT     | PB9         | TIM4_CH4                                | I2C1_SDA/CAN_TX                |
| 47  | VSS_3           | S    |        | VSS_3       |                                         |                                |
| 48  | VDD_3           | S    |        | VDD_3       |