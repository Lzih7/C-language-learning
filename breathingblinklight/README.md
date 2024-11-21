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
    + 0~9：EXTIx_IRQn
    + 10~15：EXTI15_10_IRQn 
  



