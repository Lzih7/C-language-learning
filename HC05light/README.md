# 蓝牙通信
用上位机代替按键实现模式切换
---
## USART外设
本项目使用**USART通信协议**
USART是*通用同步/异步收发器*，是*STM32内部集成的硬件外设*

TX和RX引脚交叉连接，数据由TX发送至RX
### USART串口参数的配置
1. 波特率：串口通信的速率，一般为9600、38400、115200
2. 起始位：低电平
3. 数据位
4. 校验位：检查信息传递是否正确
5. 停止位：高电平，有不同长度
### 初始化USART1
```
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
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	NVIC_CFG(USART1_IRQn, 1, 1, ENABLE);
}
```
基本步骤：使能时钟(APB2总线上)->配置GPIO口->初始化USART->使能USART->配置USART中断->NVIC优先级

        接线时遵循TXD与RXD交叉连接的原则，即 TXD--PA10，RXD--PA9
### USART中断函数
**接收到上位机发送的字节后breath->blink,并开启TIM3定时**
```
void USART1_IRQHandler(void){
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET){
		char receive=USART_ReceiveData(USART1);
		if(receive=='1'){
			OLED_Clear();
			OLED_ShowChar(1,1,'1');
			mode=blink;
			TIM_SetCounter(TIM3,0);
			TIM_Cmd(TIM3,ENABLE);		
		}
		else{
			OLED_Clear();
			OLED_ShowChar(1,1,receive);
		}
	}
}
```
此函数只可显示一个字符，可通过构建字符数组来实现显示字符串
## 相关应用
可在手机上下载SPP蓝牙串口助手发送数据

+ 需将模式改为us-ascii模式



  



