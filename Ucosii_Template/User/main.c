#include "stm32f10x.h"
#include "ucos_ii.h"
#include "utility.h"

OS_STK MyTaskStack[1024];

void MyTask(void* pdata){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_CFG(GPIOA, GPIO_Pin_0, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	while(1){
		OSTimeDly(10);
	}
}

int main(){
	OSInit();
	OSTaskCreate(MyTask, (void*) 0, &MyTaskStack[1023], 10);
	OSStart();
}
