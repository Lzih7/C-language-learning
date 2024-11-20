#include "stm32f10x.h" 
#include "Key.h"
#include "Delay.h"
#include "typedef.h"
#include "OLED.h"
#include "USART.h"

#define blink 0
#define breath 1

static int mode=breath;
static int led_on=1;
void prepare(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_CFG(GPIOA,GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);
	GPIO_CFG(GPIOA,GPIO_Pin_1,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);
	GPIO_CFG(GPIOB,GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_IPU);
	//配置GPIO口
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_BASE_CFG(TIM2,999,71,TIM_CKD_DIV1,TIM_CounterMode_Up);
	
	TIM_PWM_CFG(TIM2,1,TIM_OCMode_PWM1,TIM_OutputState_Enable,0,TIM_OCPolarity_High); //PA0
	TIM_PWM_CFG(TIM2,2,TIM_OCMode_PWM1,TIM_OutputState_Enable,0,TIM_OCPolarity_High); //PA1
	
	TIM_Cmd(TIM2,ENABLE);//配置TIM2用于PWM
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0); //PB0为中断源
	EXTI_CFG(EXTI_Line0,EXTI_Mode_Interrupt,EXTI_Trigger_Falling,ENABLE);
	NVIC_CFG(EXTI0_IRQn,0,0,ENABLE);
	//配置GPIO中断
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_BASE_CFG(TIM3,50000-1,7200-1,TIM_CKD_DIV1,TIM_CounterMode_Up);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	TIM_Cmd(TIM3,DISABLE);
	
	NVIC_CFG(TIM3_IRQn,0,0,ENABLE);
	//配置TIM3中断
	
	GPIO_CFG(GPIOA,GPIO_Pin_9,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);
	GPIO_CFG(GPIOA,GPIO_Pin_10,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);
	USART1_CFG();
}

void EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0)==SET){
		Delay_ms(50);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0);
		led_on=!led_on;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void LED_BLINK(void){
	TIM_SetCompare1(TIM2,999);
	TIM_SetCompare2(TIM2,999);
	Delay_ms(250);
	TIM_SetCompare1(TIM2,0);
	TIM_SetCompare2(TIM2,0);
	Delay_ms(250);
}

void TIM3_IRQHandler(void){
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET){
		mode=breath;
		TIM_Cmd(TIM3,DISABLE);
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
} //TIM3中断函数

void USART_IRQHandler(void){
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET){
		char receive=USART_ReceiveData(USART1);
		if(receive==1){
			OLED_ShowChar(1,1,1);
			mode=blink;
			TIM_Cmd(TIM3,ENABLE);		
		}
		else{
			OLED_ShowChar(1,1,receive);
		}
	}
}

static int direction=1;
static int brightness=0;

void BREATHING_LIGHT(void){
	if(led_on){
		if(direction){
			brightness++;
			if(brightness>=1000){
				direction=0;
			}
		}
		
		if(direction==0){
			if(brightness==0){
				direction=1;
			}
			brightness--;
		}
		TIM_SetCompare1(TIM2,brightness);
		TIM_SetCompare2(TIM2,brightness);
	}
	else{
		TIM_SetCompare1(TIM2,0);
		TIM_SetCompare2(TIM2,0);
		TIM_SetCounter(TIM2,0);
	}
}

int main(){
	prepare();
	OLED_Init();
	
	while(1){
		if(mode==breath){
			BREATHING_LIGHT();
			Delay_us(600);
		}
		if(mode==blink){
			LED_BLINK();
		}
	}
}
