#include "stm32f10x.h"                  // Device header

void delay(int i)
{
	for(int a=0;a<i;a++);
}

void Key_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_0;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum=0;
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
	{
		delay(30000);
		while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0);
		delay(30000);
		KeyNum=1;
	}
	
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
	{
		delay(30000);
		while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0);
		delay(30000);
		KeyNum=2;
	}
	return KeyNum;
}
