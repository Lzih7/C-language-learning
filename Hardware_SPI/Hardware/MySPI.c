#include "stm32f10x.h"
#include "utility.h"

// 模式0

void MySPI_W_SS(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);
}

// void MySPI_W_SCK(uint8_t BitValue)
// {
//     GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);
// }

// void MySPI_W_MOSI(uint8_t BitValue)
// {
//     GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);
// }

// uint8_t MySPI_R_MISO(void)
// {
//     return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
// }

void MySPI_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    GPIO_CFG(GPIOA, GPIO_Pin_4, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
    GPIO_CFG(GPIOA, GPIO_Pin_5 | GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
    GPIO_CFG(GPIOA, GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_IPU);

    SPI_InitTypeDef SPI_InitStructure;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128; // 72MHz / 128 = 562.5KHz
    SPI_InitStructure.SPI_CPHA = 0;
    SPI_InitStructure.SPI_CPOL = 0;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_CRCPolynomial = 7;

    SPI_Init(SPI1, &SPI_InitStructure);
    SPI_Cmd(SPI1, ENABLE);

    MySPI_W_SS(1);
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
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET)
        ;
    SPI_I2S_SendData(SPI1, ByteSend);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET)
        ;
    return SPI_I2S_ReceiveData(SPI1);
}
