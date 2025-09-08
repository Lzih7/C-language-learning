# STM32 ADC+DMA配置详解

## 目录
1. [项目概述](#项目概述)
2. [ADC基础知识](#adc基础知识)
3. [DMA基础知识](#dma基础知识)
4. [硬件配置](#硬件配置)
5. [代码实现分析](#代码实现分析)
6. [配置流程详解](#配置流程详解)
7. [关键技术要点](#关键技术要点)
8. [常见问题与优化](#常见问题与优化)

## 项目概述

本项目演示了STM32F10x系列微控制器中ADC（模数转换器）与DMA（直接内存访问）的联合使用，实现多通道模拟信号的连续采集和自动数据传输。

### 主要特性
- **多通道采集**：同时采集4个ADC通道（PA0-PA3）
- **连续转换模式**：自动连续进行ADC转换
- **DMA自动传输**：无需CPU干预的数据传输
- **扫描模式**：按序列扫描多个通道
- **高效率**：减少CPU负载，提高系统性能

## ADC基础知识

### 1. ADC工作原理
ADC（Analog-to-Digital Converter）将连续的模拟信号转换为离散的数字信号。

**转换过程：**
```
模拟电压 → 采样保持 → 量化 → 编码 → 数字输出
```

### 2. STM32 ADC特性
- **分辨率**：12位（0-4095）
- **转换时间**：最快1μs
- **输入电压范围**：0V - VREF+（通常为3.3V）
- **通道数量**：最多16个外部通道
- **转换模式**：单次、连续、扫描

### 3. ADC时钟配置
```c
// ADC时钟 = PCLK2 / 分频系数
RCC_ADCCLKConfig(RCC_PCLK2_Div6); // 72MHz / 6 = 12MHz
```

**时钟要求：**
- ADC时钟频率：≤ 14MHz
- 推荐频率：12MHz（最佳性能）

### 4. 转换时间计算
```
转换时间 = 采样时间 + 12.5个ADC时钟周期
例：55.5 + 12.5 = 68个时钟周期
实际时间 = 68 / 12MHz ≈ 5.67μs
```

## DMA基础知识

### 1. DMA工作原理
DMA（Direct Memory Access）允许外设直接访问内存，无需CPU参与数据传输。

**传输过程：**
```
外设寄存器 → DMA控制器 → 内存缓冲区
```

### 2. DMA优势
- **高效率**：减少CPU负载
- **实时性**：无中断延迟
- **连续性**：支持连续数据流传输
- **自动化**：无需软件干预

### 3. DMA传输模式
- **单次传输**：传输完成后停止
- **循环传输**：自动重新开始传输
- **存储器到存储器**：内存间数据复制
- **外设到存储器**：外设数据到内存

## 硬件配置

### 1. 引脚配置
```c
// 配置PA0-PA3为模拟输入模式
GPIO_CFG(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3, 
         GPIO_Speed_50MHz, GPIO_Mode_AIN);
```

**引脚功能：**
- **PA0**：ADC1_IN0（通道0）
- **PA1**：ADC1_IN1（通道1）
- **PA2**：ADC1_IN2（通道2）
- **PA3**：ADC1_IN3（通道3）

### 2. 时钟使能
```c
// 使能ADC1和GPIOA时钟
RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
```

## 代码实现分析

### 1. 全局变量定义
```c
// ADC转换结果存储数组
uint16_t AD_Value[4];
```

**数组说明：**
- 存储4个通道的ADC转换结果
- 数据类型：16位无符号整数
- 取值范围：0-4095（12位ADC）

### 2. ADC初始化函数
```c
void AD_Init(void)
{
    // 1. 时钟配置
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6); // 12MHz
    
    // 2. DMA初始化
    MyDMA_Init((uint32_t)&ADC1->DR, (uint32_t)AD_Value, 4);
    
    // 3. GPIO配置
    GPIO_CFG(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3,
             GPIO_Speed_50MHz, GPIO_Mode_AIN);
    
    // 4. ADC通道配置
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
    
    // 5. ADC参数配置
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;           // 独立模式
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;       // 右对齐
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 软件触发
    ADC_InitStructure.ADC_NbrOfChannel = 4;                     // 4个通道
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;          // 连续转换
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;                // 扫描模式
    ADC_Init(ADC1, &ADC_InitStructure);
    
    // 6. 使能ADC和DMA
    ADC_Cmd(ADC1, ENABLE);
    ADC_DMACmd(ADC1, ENABLE);
    
    // 7. ADC校准
    ADC_ResetCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1) == SET);
    
    // 8. 启动转换
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
```

### 3. DMA配置分析
```c
// DMA初始化函数调用
MyDMA_Init((uint32_t)&ADC1->DR, (uint32_t)AD_Value, 4);
```

**参数说明：**
- **源地址**：`&ADC1->DR` - ADC1数据寄存器地址
- **目标地址**：`AD_Value` - 存储数组地址
- **传输长度**：`4` - 传输4个数据

**典型DMA配置：**
```c
void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size)
{
    // 使能DMA1时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;           // 外设地址
    DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;               // 内存地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;          // 外设作为源
    DMA_InitStructure.DMA_BufferSize = Size;                    // 传输大小
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // 外设地址不递增
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;     // 内存地址递增
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 16位
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         // 16位
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;             // 循环模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;       // 中等优先级
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;               // 非内存到内存
    
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel1, ENABLE);
}
```

## 配置流程详解

### 1. 初始化流程图
```
开始
  ↓
使能时钟（ADC1、GPIOA、DMA1）
  ↓
配置ADC时钟分频
  ↓
初始化DMA传输
  ↓
配置GPIO为模拟输入
  ↓
配置ADC通道和采样时间
  ↓
配置ADC工作模式
  ↓
使能ADC和DMA
  ↓
ADC校准
  ↓
启动软件触发转换
  ↓
结束
```

### 2. 数据流向
```
模拟信号(PA0-PA3) → ADC1 → ADC1->DR → DMA1_CH1 → AD_Value[4]
```

### 3. 转换序列
```
通道0(PA0) → 通道1(PA1) → 通道2(PA2) → 通道3(PA3) → 循环
```

## 关键技术要点

### 1. ADC配置要点

#### 工作模式选择
```c
ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  // 独立模式
```
- **独立模式**：ADC1独立工作
- **双重模式**：ADC1和ADC2同步工作

#### 数据对齐方式
```c
ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // 右对齐
```
- **右对齐**：数据在低12位，高4位为0
- **左对齐**：数据在高12位，低4位为0

#### 触发方式
```c
ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 软件触发
```
- **软件触发**：程序控制转换开始
- **硬件触发**：定时器或外部信号触发

#### 转换模式
```c
ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  // 连续转换
ADC_InitStructure.ADC_ScanConvMode = ENABLE;        // 扫描模式
```
- **连续模式**：自动重复转换
- **扫描模式**：按序列转换多个通道

### 2. DMA配置要点

#### 传输方向
```c
DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; // 外设到内存
```

#### 地址递增
```c
DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // 外设地址固定
DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;          // 内存地址递增
```

#### 数据宽度
```c
DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 16位
DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         // 16位
```

#### 传输模式
```c
DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; // 循环模式
```
- **普通模式**：传输完成后停止
- **循环模式**：自动重新开始传输

### 3. 采样时间配置
```c
ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
```

**采样时间选项：**
- `ADC_SampleTime_1Cycles5`：1.5个时钟周期
- `ADC_SampleTime_7Cycles5`：7.5个时钟周期
- `ADC_SampleTime_13Cycles5`：13.5个时钟周期
- `ADC_SampleTime_28Cycles5`：28.5个时钟周期
- `ADC_SampleTime_41Cycles5`：41.5个时钟周期
- `ADC_SampleTime_55Cycles5`：55.5个时钟周期（推荐）
- `ADC_SampleTime_71Cycles5`：71.5个时钟周期
- `ADC_SampleTime_239Cycles5`：239.5个时钟周期

**选择原则：**
- 高阻抗信号源：选择较长采样时间
- 快速变化信号：选择较短采样时间
- 一般应用：55.5周期是良好的折中选择

### 4. ADC校准
```c
// ADC校准序列
ADC_ResetCalibration(ADC1);                        // 复位校准
while(ADC_GetCalibrationStatus(ADC1) == SET);      // 等待复位完成
ADC_StartCalibration(ADC1);                        // 开始校准
while(ADC_GetCalibrationStatus(ADC1) == SET);      // 等待校准完成
```

**校准目的：**
- 消除ADC内部偏移误差
- 提高转换精度
- 每次上电后必须执行

## 常见问题与优化

### 1. 常见问题

#### 问题1：ADC转换结果不稳定
**原因分析：**
- 采样时间过短
- 信号源阻抗过高
- 电源噪声干扰

**解决方案：**
```c
// 增加采样时间
ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);

// 添加硬件滤波电路
// 使用更稳定的参考电压
```

#### 问题2：DMA传输数据错误
**原因分析：**
- DMA通道配置错误
- 数据宽度不匹配
- 缓冲区大小不正确

**解决方案：**
```c
// 确保数据宽度匹配
DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;

// 检查缓冲区大小
uint16_t AD_Value[4]; // 确保数组大小与通道数匹配
```

#### 问题3：转换速度过慢
**原因分析：**
- ADC时钟频率过低
- 采样时间过长
- 通道数量过多

**解决方案：**
```c
// 优化ADC时钟
RCC_ADCCLKConfig(RCC_PCLK2_Div4); // 提高到18MHz（注意不超过14MHz限制）

// 减少采样时间
ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_7Cycles5);
```

### 2. 性能优化

#### 优化1：中断处理
```c
// 使能DMA传输完成中断
void DMA1_Channel1_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC1))
    {
        DMA_ClearITPendingBit(DMA1_IT_TC1);
        // 处理转换完成的数据
        ProcessADCData();
    }
}
```

#### 优化2：数据处理
```c
// 数字滤波
uint16_t FilterADCValue(uint16_t newValue, uint16_t oldValue)
{
    // 简单的一阶低通滤波
    return (oldValue * 7 + newValue) / 8;
}

// 电压转换
float ADCToVoltage(uint16_t adcValue)
{
    return (float)adcValue * 3.3f / 4095.0f;
}
```

#### 优化3：多通道管理
```c
// 通道数据结构
typedef struct {
    uint16_t rawValue;      // 原始ADC值
    float voltage;          // 转换后的电压值
    uint16_t filteredValue; // 滤波后的值
} ADC_ChannelData_t;

ADC_ChannelData_t channelData[4];

// 数据更新函数
void UpdateChannelData(void)
{
    for(int i = 0; i < 4; i++)
    {
        channelData[i].rawValue = AD_Value[i];
        channelData[i].voltage = ADCToVoltage(AD_Value[i]);
        channelData[i].filteredValue = FilterADCValue(AD_Value[i], channelData[i].filteredValue);
    }
}
```

### 3. 调试技巧

#### 调试1：数据监控
```c
// 使用串口输出ADC值
void PrintADCValues(void)
{
    printf("CH0: %d, CH1: %d, CH2: %d, CH3: %d\r\n", 
           AD_Value[0], AD_Value[1], AD_Value[2], AD_Value[3]);
}
```

#### 调试2：状态检查
```c
// 检查ADC和DMA状态
void CheckADCStatus(void)
{
    if(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
    {
        printf("ADC转换完成\r\n");
    }
    
    if(DMA_GetFlagStatus(DMA1_FLAG_TC1))
    {
        printf("DMA传输完成\r\n");
    }
}
```

## 总结

STM32的ADC+DMA配置是一个强大的组合，能够实现高效的多通道模拟信号采集：

### 主要优势
1. **高效率**：DMA自动传输，减少CPU负载
2. **实时性**：连续转换模式，无延迟
3. **多通道**：同时采集多个信号
4. **精确性**：12位分辨率，校准功能

### 应用场景
- 传感器数据采集
- 电压监测系统
- 信号处理应用
- 数据记录设备

### 学习要点
1. 理解ADC和DMA的工作原理
2. 掌握时钟配置和时序要求
3. 熟悉各种工作模式的选择
4. 学会调试和优化技巧

通过本项目的学习，可以深入理解STM32外设的配置方法，为后续的嵌入式开发打下坚实基础。