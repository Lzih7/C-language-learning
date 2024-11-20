#include "stm32f10x.h"
#include "typedef.h"

void USART1_CFG(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_CFG(GPIOA,GPIO_Pin_9,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);
	GPIO_CFG(GPIOA,GPIO_Pin_10,GPIO_Speed_50MHz,GPIO_Mode_IN_FLOATING);
	
	USART_InitTypeDef USART_Initstructure;
	USART_Initstructure.USART_BaudRate=9600;
	USART_Initstructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Initstructure.USART_WordLength=USART_WordLength_8b;
	USART_Initstructure.USART_StopBits=USART_StopBits_1;
	USART_Initstructure.USART_Parity=USART_Parity_No ;
	USART_Initstructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Init(USART1,&USART_Initstructure);
	
	USART_Cmd(USART1,ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//RXNE?
	NVIC_CFG(USART1_IRQn, 1, 1, ENABLE);
}