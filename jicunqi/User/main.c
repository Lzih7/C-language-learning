#include "stm32f10x.h" 
void DELAY(void){
	for(int i=0;i<20000;i++){
	
	}
}
int main(){
	RCC->APB2ENR|=0x00000010;  
	//将APB2ENR寄存器的第四位设为1，用"|"可保证其他位不被改变，开启GPIOC时钟(IOPCEN)
	GPIOC->CRH/*高位配置寄存器，PC8~PC15*/&=~0x00C00000;//清除CNF13位为00,推挽输出
	GPIOC->CRH|=0x00200000;//2MHz
	
	while(1){
		GPIOC->BSRR=0x20000000;  //将BSRR寄存器的BR13设为1
		DELAY();
		GPIOC->BSRR=0x00002000;  //将BSRR寄存器的BS13设为1
		DELAY();
	}
}

/*用寄存器实现板载灯闪烁*/
/*通过查看手册找到相应寄存器及每个为的作用，改变某个特定位的值即可实现相关功能*/

