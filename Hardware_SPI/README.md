# 硬件SPI
- TXE (Transmit Data Register Empty)
- RXNE (Receive Data Register Not Empty)
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
