#include "stm32f10x.h"
#include "MySPI.h"
#include "W25Q64_Ins.h"

void W25Q64_Init(void)
{
    MySPI_Init();
}

void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
    MySPI_Start();
    MySPI_SwapByte(W25Q64_JEDEC_ID);
    *MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    *DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    *DID <<= 8;
    *DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    MySPI_End();
}

void W25Q64_WriteEnable(void)
{
    MySPI_Start();
    MySPI_SwapByte(0x06);
    MySPI_End();
}

void W25Q64_WaitBusy(void)
{
    MySPI_Start();
    MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
    uint32_t Timeout;
    while ((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)
    {
        Timeout--;
        if (Timeout == 0)
            break;
    }
    MySPI_End();
}

void W25Q64_PageProgram(uint32_t Address, uint8_t *Data, uint16_t Count)
{
    W25Q64_WriteEnable();
    MySPI_Start();
    uint16_t i;
    MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
    MySPI_SwapByte(Address >> 16);
    MySPI_SwapByte(Address >> 8);
    MySPI_SwapByte(Address);
    for (i = 0; i < Count; i++)
    {
        MySPI_SwapByte(Data[i]);
    }
    MySPI_End();

    W25Q64_WaitBusy();
}

void W25Q64_SectorErase(uint32_t Address)
{
    W25Q64_WriteEnable();
    MySPI_Start();
    MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
    MySPI_SwapByte(Address >> 16);
    MySPI_SwapByte(Address >> 8);
    MySPI_SwapByte(Address);
    MySPI_End();

    W25Q64_WaitBusy();
}

void W25Q64_ReadData(uint32_t Address, uint8_t *Data, uint16_t Count)
{
    uint16_t i;
    MySPI_Start();
    MySPI_SwapByte(0x03);
    MySPI_SwapByte(Address >> 16);
    MySPI_SwapByte(Address >> 8);
    MySPI_SwapByte(Address);
    for (i = 0; i < Count; i++)
    {
        Data[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    }
    MySPI_End();
}
