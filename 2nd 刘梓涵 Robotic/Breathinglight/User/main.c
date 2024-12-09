#include "stm32f10x.h" 
#include "Key.h"
#include "Delay.h"

static int led_on=1;
void TIM_PWM_Init(uint16_t arr,uint16_t psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_ClockDivision=0;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period=arr;
	TIM_TimeBaseStructure.TIM_Prescaler=psc;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
}
void Set_PWM_DutyCycle(uint16_t duty)
{
	TIM_SetCompare1(TIM2,duty);
}
static uint16_t brightness=0;
static uint8_t direction=1;
void Breathing_Light(void)
{
	if(led_on){
		if(direction){
			brightness++;
			if(brightness>=1000){
				direction=0;
			}
		}else{
			brightness--;
			if(brightness==0){
				direction=1;
			}
		}
		
		Set_PWM_DutyCycle(brightness);
	}else{
		brightness=0;
		Set_PWM_DutyCycle(brightness);
		direction=1;
	}
}

int main(void)
{
	Key_Init();
	TIM_PWM_Init(1000-1,72-1);
    while (1)
    {
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==0){
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==0);
			led_on=!led_on;
		}
		Breathing_Light();
		Delay_us(500);
    }
}
