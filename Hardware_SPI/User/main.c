#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "W25Q64.h"

uint8_t MID;
uint16_t DID;

uint8_t ArrWrite[4]={0x01,0x02,0x03,0x04};
uint8_t ArrRead[4];

int main(void)
{
    OLED_Init();
    W25Q64_Init();

    W25Q64_ReadID(&MID, &DID);
    OLED_ShowHexNum(1, 1, MID, 2);
    OLED_ShowHexNum(1, 5, DID, 4);

    W25Q64_SectorErase(0x000000);
    W25Q64_PageProgram(0x000000,ArrWrite,4);
    W25Q64_ReadData(0x000000,ArrRead,4);
    OLED_ShowHexNum(2,1,ArrRead[0],2);
    OLED_ShowHexNum(2,5,ArrRead[1],2);
    OLED_ShowHexNum(3,1,ArrRead[2],2);
    OLED_ShowHexNum(3,5,ArrRead[3],2);
    while (1)
    {
    }
}
