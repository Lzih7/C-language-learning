#include "stm32f10x.h"

uint16_t MyDMA_Size;
void MyDMA_Init(uint32_t AddrA,uint32_t AddrB,uint16_t size)
{
	MyDMA_Size=size;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_BufferSize=size;
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_M2M=DMA_M2M_Enable; // 软件触发
	DMA_InitStructure.DMA_MemoryBaseAddr=AddrB;
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode=DMA_Mode_Normal; // 单次减到0
	DMA_InitStructure.DMA_PeripheralBaseAddr=AddrA;
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Enable;
	DMA_InitStructure.DMA_Priority=DMA_Priority_VeryHigh;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1,DISABLE);
}

void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1,MyDMA_Size);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1)!=SET);
	DMA_ClearFlag(DMA1_FLAG_TC1);
}
