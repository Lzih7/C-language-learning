#ifndef _MY_SPI
#define _My_SPI

void MySPI_W_SS(uint8_t BitValue);
void MySPI_W_SCK(uint8_t BitValue);
void MySPI_W_MOSI(uint8_t BitValue);
uint8_t MySPI_R_MISO(void);
void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_End(void);
uint8_t MySPI_SwapByte(uint8_t ByteSend);

#endif