#include "stm32f10x.h"                  // Device header
#include "Lighting.h"
int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5);
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_SetBits(GPIOA,(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5));
	Lighting_Init(); 
	
	while(1)
	{
		int a=Lighting_Get();
		if(a==1)
		{
			GPIO_ResetBits(GPIOA,(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5));
		}
		if(a==0)
		{
			GPIO_SetBits(GPIOA,(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5));
		}
	}
}
