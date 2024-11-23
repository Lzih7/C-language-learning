# 定时切换
在上节的基础上，通过TIM3模块实现定时5秒切换
## 定时模块的使用
### 1.配置TIM3
基本流程：使能时钟->配置GPIO口->配置TIM3->TIM中断->NVIC

**先将TIM3失能，需要时使能**

**注**：*TIM2、TIM3都在APB1总线上*
```
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_BASE_CFG(TIM3,50000-1,7200-1,TIM_CKD_DIV1,TIM_CounterMode_Up);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //预先清除中断位
	TIM_Cmd(TIM3,DISABLE);
	NVIC_CFG(TIM3_IRQn,0,0,ENABLE);
}
```
#### 关于arr,psc的相关计算
计数频率：72MHz/psc   psc起分频作用

arr/(72MHz/psc) 为秒数
### 2.TIM3的中断函数
基本步骤：按下按键->breath变为blink->使能TIM3，开始计时->计时完成触发中断->blink变为breath
```
void TIM3_IRQHandler(void){
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET){
		mode=breath;
		TIM_Cmd(TIM3,DISABLE);
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}
```





