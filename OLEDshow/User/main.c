#include "stm32f10x.h" 
#include "OLED.h"
int main(void)
{
	OLED_Init();
	
	OLED_ShowString(1,1,"2024090911009");
    
    while (1)
    {
		
    }
}
