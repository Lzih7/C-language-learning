# LED闪烁模式


• ⽬标：使⽤ PWM 控制 LED 以2Hz频率闪烁（对每次闪烁中的亮灯时⻓不做要求），  
  并新加⼊⼀个 按键2 实现呼吸灯和闪烁模式的切换。要求使⽤外部中断来实现 按键 的功能  
• 提⽰：使⽤ 按键 触发外部中断，在外部中断中实现两种模式的切换  

• 问题：  
◦ 外部中断⼤致的配置流程是怎样的？  
◦ 按键 是如何实现外部中断的？  
◦ 如何在外部中断中实现两种模式的切换？  

---

## **硬件连接**
   - **2个LED**：分别连接到 `PA0` 和 `PA1` 引脚。
   - **按键1**：连接到 `PB0` 引脚，用作控制 LED 呼吸灯的开关。
   - **按键2**：连接到 `PB10` 引脚，用作切换LED工作模式。
   
## **LED 以2Hz频率闪烁**
每秒闪烁2次，如下时序可以达到要求
`亮 -> delay 250ms -> 灭 -> delay 250ms`
`亮 -> delay 250ms -> 灭 -> delay 250ms`

```c
void LED_Blink(void)
{
    TIM_SetCompare1(TIM2, 999); // LED1 亮
    TIM_SetCompare2(TIM2, 999); // LED2 亮
    Delay_us(200 * 1000);       // Delay_us函数最大支持233ms,这里需要delay 250ms,分2步做delay
    Delay_us(50 * 1000);

    TIM_SetCompare1(TIM2, 0); // LED1 灭
    TIM_SetCompare2(TIM2, 0); // LED2 灭
    Delay_us(200 * 1000);
    Delay_us(50 * 1000);
}
```

---

## 问题
Q1:外部中断⼤致的配置流程是怎样的？
Q2:按键 是如何实现外部中断的？
Q3:如何在外部中断中实现两种模式的切换？

这3个问题下面用PB10的配置和中断处理回答
步骤:
**开启时钟：为 GPIO 和 AFIO 开启时钟。**
```c
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); /*使能 AFIO 时钟*/
```
**配置 GPIO：设置中断引脚为输入模式。**
```c
    UTIL_GPIO_CFG(GPIOB, GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_IPU);  /*PB10 为上拉输入，用于按键输入,BUTTON*/
```
**选择 PB10 作为中断源**
```c
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10); /*选择 PB10 作为中断源*/
```
**配置 EXTI：设置触发模式和启用 EXTI 线。**
```c
   UTIL_EXTI_CFG(EXTI_Line10,
                  EXTI_Mode_Interrupt, EXTI_Trigger_Falling, ENABLE); /*EXTI_Line10 与 GPIO 的第 10 号引脚（PA10、PB10 等）相互对应*/
```
**配置 NVIC：使能 NVIC 中断通道并设置优先级。**
```c
    UTIL_NVIC_CFG(EXTI15_10_IRQn, 0, 0, ENABLE);                      /*PreemptionPriority=0; SubPriority=0*/
```
**编写中断处理函数：处理中断并清除挂起位。**
```c
/**PB10 中断处理*/
void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line10) != RESET)
    {
        if (led_mode == BREATHE) /*切换模式*/
            led_mode = BLINK;
        else
            led_mode = BREATHE;

        EXTI_ClearITPendingBit(EXTI_Line10); /*清除中断标志*/
    }
}
```