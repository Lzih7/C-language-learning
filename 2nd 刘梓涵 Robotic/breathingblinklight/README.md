# 按键切换模式
## 呼吸灯(见呼吸灯)
## 闪烁
设置CCR=arr，delay函数延时，再改变CCR值为0，实现关灯
```
void LED_BLINK(void){
	TIM_SetCompare1(TIM2,999);
	TIM_SetCompare2(TIM2,999);
	Delay_ms(250);
	TIM_SetCompare1(TIM2,0);
	TIM_SetCompare2(TIM2,0);
	Delay_ms(250);
}
```
## 模式切换
### 标志：mode
+ 宏定义blink,breath
+ mode=blink =>闪烁；mode=breath =>呼吸
### EXTI(external interrupt)中断
1. 复用引脚
   ```
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
   //打开AFIO时钟
   ```
	**启用 APB2 总线上 AFIO 外设的时钟**

2. 选择中断源
   ```
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10); //PB10为中断源
   ```
3. 外部中断

   **宏定义EXTI初始化函数**
   ```
   #define EXTI_CFG(_LINE, _MODE, _Trigger, _LineCmd) \
    do                                                  \
    {                                                   \
        EXTI_InitTypeDef EXTI_InitStructure;            \
        EXTI_InitStructure.EXTI_Line = _LINE;           \
        EXTI_InitStructure.EXTI_Mode = _MODE;           \
        EXTI_InitStructure.EXTI_Trigger = _Trigger;     \
        EXTI_InitStructure.EXTI_LineCmd = _LineCmd;     \
        EXTI_Init(&EXTI_InitStructure);                 \
    } while (0)	

* "\\"表示不换行
* 用do-while包装，可确保EXTI_CFG整体执行
  ```
  EXTI_CFG(EXTI_Line10,EXTI_Mode_Interrupt,EXTI_Trigger_Falling,ENABLE);
  ```
  * Line10 =>Pin10
  * _Falling:下降沿触发，表示引脚电平由1变为0后触发中断
  * ENABLE使能中断

  **宏定义NVIC初始化函数**
  ```
  #define NVIC_CFG(_Channel, _PreemptionPriority, _SubPriority, _Cmd)            \
      do                                                                              \
      {                                                                               \
          NVIC_InitTypeDef NVIC_InitStructure;                                        \
          NVIC_InitStructure.NVIC_IRQChannel = _Channel;                              \
          NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = _PreemptionPriority; \
          NVIC_InitStructure.NVIC_IRQChannelSubPriority = _SubPriority;               \
          NVIC_InitStructure.NVIC_IRQChannelCmd = _Cmd;                               \
          NVIC_Init(&NVIC_InitStructure);                                             \
      } while (0)	
  ```
  * NVIC用于配置优先级
  * _Channel为EXTI通道
    + 0~4：EXTIx_IRQn
    + 5~9：EXTI9_5_IRQn
    + 10~15：EXTI15_10_IRQn
4. 外部中断函数
```
void EXTI15_10_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line10)==SET){
		if(mode==blink) mode=breath;
		else if(mode==breath) mode=blink;
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
}
```
+ 固定函数名
+ 函数介绍
  1. EXTI_GetITStatus(EXTI_Line10)：
 
     + 返回值：ITStatus  //SET或RESET
     	* ITStatus的定义：
     ```
       typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
  2. EXTI_ClearITPendingBit(EXTI_Line10);
     + 清除中断标志

进入中断函数执行中断程序后**模式切换**
### 开关灯
Pin0引脚按钮用于开关控制
1. EXTI中断
2. 标志：led_on,每进入中断函数变为！led_on
3. 改变呼吸灯函数，实现led_on控制
   ```
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
	}
   }
   ```



