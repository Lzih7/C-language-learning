# RTC
实时时钟

- RTC是一个独立的定时器
- 系统复位时RTC数据不清零，断电后由**VBAT**供电
## 核心组成
1. 32位可编程计数器，每秒自增1
2. 20位可编程预分频器，适配不同频率的时钟源(低速时钟)
