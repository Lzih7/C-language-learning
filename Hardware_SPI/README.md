# 硬件SPI
- TXE (Transmit Data Register Empty):当发送数据寄存器（USART_DR）中的数据被转移到发送移位寄存器（Shift Register）后，TXE标志位会被硬件置为1，表示发送数据寄存器为空，可以写入新的数据。
- RXNE (Receive Data Register Not Empty):当接收数据寄存器（USART_DR）接收到一字节数据时，RXNE标志位会被硬件置为1，表示有新数据可读。
1. 只有发送数据，才会触发时序，同时要接收数据
## 流程
1. 开启时钟(GPIO, SPI1)
2. 配置GPIO口和SPI1
3. 使能SPI1
4. 拉高SS
### 核心代码
```c
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET)
        ;
    SPI_I2S_SendData(SPI1, ByteSend);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET)
        ;
    return SPI_I2S_ReceiveData(SPI1);
}
```
