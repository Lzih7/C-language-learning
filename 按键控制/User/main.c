#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "KEY.h"

uint8_t KeyNum=0;

int main(void)
{
	LED_Init();
	Key_Init();
	while(1)
	{
		KeyNum=Key_GetNum();
		if (KeyNum==1)
		{
			LED0_ON();
			LED1_ON();
		}
		if(KeyNum==2)
		{
			LED0_OFF();
			LED1_OFF();
		}
	}
}
