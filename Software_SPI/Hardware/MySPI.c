#include "stm32f10x.h"
#include "utility.h"

// 模式0

void MySPI_W_SS(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);
}

void MySPI_W_SCK(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);
}

void MySPI_W_MOSI(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);
}

uint8_t MySPI_R_MISO(void)
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

void MySPI_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_CFG(GPIOA, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
    GPIO_CFG(GPIOA, GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_IPU);

    MySPI_W_SS(1);
    MySPI_W_SCK(0);
}

void MySPI_Start(void)
{
    MySPI_W_SS(0);
}

void MySPI_End(void)
{
    MySPI_W_SS(1);
}

uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
    uint8_t i, ByteReceive = 0x00;
    for (i = 0; i < 8; i++)
    {
        MySPI_W_MOSI(ByteSend & (0x80 >> i));
        MySPI_W_SCK(1); // 移出数据
        if (MySPI_R_MISO() == 1)
        {
            ByteReceive |= 0x80 >> i;
        }
        MySPI_W_SCK(0); // 移入数据
    }
    return ByteReceive;
}
