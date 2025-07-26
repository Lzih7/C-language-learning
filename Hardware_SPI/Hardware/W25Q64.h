#ifndef _W25Q64
#define _W25Q64

#include "stdio.h"

void W25Q64_Init(void);
void W25Q64_ReadID(uint8_t *WID,uint16_t *DID);
void W25Q64_PageProgram(uint32_t Address, uint8_t *Data, uint16_t Count);
void W25Q64_SectorErase(uint32_t Address);
void W25Q64_ReadData(uint32_t Address, uint8_t *Data, uint16_t Count);

#endif
