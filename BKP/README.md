# BKP
- Backup Registers，备份寄存器
- APB1总线上
- BKP可用于存储用户应用程序数据。当VDD（2.0\~3.6V）电源被切断，他们仍然由**VBAT**（1.8\~3.6V）维持供电。当系统在待机模式下被唤醒，或系统复位或电源复位时，他们也不会被复位。
- 寄存器：BKP_DR1, BKP_DR2
## 使用场景
在设备**断电后**，需要**保留**一些关键的系统参数或用户设置，例如设备 ID、校准数据、用户偏好设置等。
## PWR(电源管理单元)
要**解锁备份域的写访问**，必须通过 PWR 模块的控制寄存器（具体是 PWR_CR 寄存器的 28DBP 位）启用备份域访问。
这一步需要 PWR 模块处于工作状态，而 PWR 模块的工作依赖于其时钟信号。
### 时钟使能
- STM32 的外设模块（如 PWR、BKP、UART、I2C 等）通过 **RCC**（Reset and Clock Control，重置与时钟控制） 模块提供时钟信号。
- PWR 模块的寄存器（如 PWR_CR）需要时钟信号才能正常工作。
## RTC引脚
输出RTC校准时钟、RTC闹钟脉冲或者秒脉冲
- RTC 是备份域中的一个硬件模块，用于提供时间、日期和闹钟功能

## 实例代码
```c
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

uint8_t KeyNum;					//定义用于接收按键键码的变量

uint16_t ArrayWrite[] = {0x1234, 0x5678};	//定义要写入数据的测试数组
uint16_t ArrayRead[2];						//定义要读取数据的测试数组

int main(void)
{
	/*模块初始化*/
	OLED_Init();				//OLED初始化
	Key_Init();					//按键初始化
	
	/*显示静态字符串*/
	OLED_ShowString(1, 1, "W:");
	OLED_ShowString(2, 1, "R:");
	
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);		//开启PWR的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);		//开启BKP的时钟
	
	/*备份寄存器访问使能*/
	PWR_BackupAccessCmd(ENABLE);							//使用PWR开启对备份寄存器的访问
	
	while (1)
	{
		KeyNum = Key_GetNum();		//获取按键键码
		
		if (KeyNum == 1)			//按键1按下
		{
			ArrayWrite[0] ++;		//测试数据自增
			ArrayWrite[1] ++;
			
			BKP_WriteBackupRegister(BKP_DR1, ArrayWrite[0]);	//写入测试数据到备份寄存器
			BKP_WriteBackupRegister(BKP_DR2, ArrayWrite[1]);
			
			OLED_ShowHexNum(1, 3, ArrayWrite[0], 4);		//显示写入的测试数据
			OLED_ShowHexNum(1, 8, ArrayWrite[1], 4);
		}
		
		ArrayRead[0] = BKP_ReadBackupRegister(BKP_DR1);		//读取备份寄存器的数据
		ArrayRead[1] = BKP_ReadBackupRegister(BKP_DR2);
		
		OLED_ShowHexNum(2, 3, ArrayRead[0], 4);				//显示读取的备份寄存器数据
		OLED_ShowHexNum(2, 8, ArrayRead[1], 4);
	}
}

```
