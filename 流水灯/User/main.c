#include "stm32f10x.h"                  // Device header
void delay(){
	int i=0;
	for(i=0;i<500000;i++);
}

int main(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);  //使能时钟
	
	
	while(1)
	{
		#if 0
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		delay();
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		delay();
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		delay();
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		delay();
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		delay();
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		delay();
		GPIO_SetBits(GPIOA,GPIO_Pin_5); //一般的点灯方式，略显繁琐
		#endif
		GPIO_SetBits(GPIOA,(0x3F));     //先关闭所有灯
		
//		GPIO_ResetBits(GPIOA,(1<<0)|(1<<2)|(1<<4));
		
		for(int i=0;i<6;i++){      //用循环这一更简便的方式实现流水灯
			GPIO_ResetBits(GPIOA,(0x1<<i));
			delay();
			GPIO_SetBits(GPIOA,(0x1<<i));
			delay();
			
		}
		
		
	}
}
