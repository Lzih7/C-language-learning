#include "stm32f10x.h"
#include "utility.h"
#include "MyDMA.h"

uint16_t AD_Value[4];
void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); // 12MHz
	
	MyDMA_Init((uint32_t)&ADC1->DR,(uint32_t)AD_Value,4);
	
	GPIO_CFG(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3,GPIO_Speed_50MHz,GPIO_Mode_AIN); // 模拟输入模式
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5); // AD通道配置
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None; //有内部软件触发，不需外部触发
	ADC_InitStructure.ADC_NbrOfChannel=4;
	ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;
	ADC_InitStructure.ADC_ScanConvMode=ENABLE;
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_Cmd(ADC1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
	
	// 校准
	ADC_ResetCalibration(ADC1); // 软件拉高
	while(ADC_GetCalibrationStatus(ADC1)==SET); // 等待硬件拉低
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1)==SET);
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}
