# ADC DMA

• 加⼊ 反射式红外传感器 代替 按键1 ，在距离过近时启动 LED ，在距离过远时关闭 LED

问题：
◦ 介绍⼀下 ADC 的⼯作原理以及 ADC 的⼏种模式  
◦ ADC 经常要与 DMA 结合使⽤，简要介绍 ADC 是如何与 DMA 配合使⽤的  

---

## 硬件连接
PA0 PA1 接了2个LED灯。
PA6 接入了反射式红外传感器的数据输入

## 关键步骤
**初始化 ADC1**
PA6 设置为GPIO_Mode_AIN, PA6 对应的是ADC_Channel_6，把ADC_Channel_6 设置为ADC1 的第一路.
ADC1 的通道个数设为1, 所以 ADC1就只启用了ADC_Channel_6这一个通道。  

**初始化 DMA**
DMA设置为从&ADC1->DR 这个ADC1的基地址拿数据，
由于ADC1只有一个通道，所以DMA的BufferSize也设置为1，DMA从ADC1拿到数据后会存放到这个地址中 &AD_Value。
目前只需要拿一个数据，所以只需要定义一个整形变量AD_Value来接收即可。如果是要接收多个变量，就需要要用整形数组来接收，同时增大BufferSize。


```c
/*ADC DMA初始化 START-------------------------------------------------------------------------------------------------*/
ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_55Cycles5); /*规则组通道配置 PA6*/
UTIL_ADC_CFG(ADC1,
                ADC_Mode_Independent,      /*_ADC_Mode ;模式，选择独立模式，即单独使用ADC1*/
                ENABLE,                    /*_ADC_ScanConvMode ;扫描模式，使能，扫描规则组的序列，扫描数量由ADC_NbrOfChannel确定*/
                ENABLE,                    /*_ADC_ContinuousConvMode; 连续转换，使能，每转换一次规则组序列后立刻开始下一次转换*/
                ADC_ExternalTrigConv_None, /*_ADC_ExternalTrigConv; 外部触发，使用软件触发，不需要外部触发*/
                ADC_DataAlign_Right,       /*_ADC_DataAlign; 数据对齐，选择右对齐*/
                1                          /*_ADC_NbrOfChannel; 通道数1*/
);

UTIL_DMA_CFG(DMA1_Channel1,
                (uint32_t)&ADC1->DR,             /*DMA_PeripheralBaseAddr*/
                (uint32_t)&AD_Value,             /*DMA_MemoryBaseAddr*/
                DMA_DIR_PeripheralSRC,           /*DMA_DIR*/
                1,                               /*DMA_BufferSize*/
                DMA_PeripheralInc_Disable,       /*DMA_PeripheralInc*/
                DMA_MemoryInc_Disable,           /*DMA_MemoryInc*/
                DMA_PeripheralDataSize_HalfWord, /*DMA_PeripheralDataSize*/
                DMA_MemoryDataSize_HalfWord,     /*DMA_MemoryDataSize*/
                DMA_Mode_Circular,               /*DMA_Mode*/
                DMA_Priority_Medium,             /*DMA_Priority*/
                DMA_M2M_Disable                  /*DMA_M2M*/
);

DMA_Cmd(DMA1_Channel1, ENABLE); /*DMA1的通道1使能*/
ADC_DMACmd(ADC1, ENABLE);       /*ADC1触发DMA1的信号使能*/
ADC_Cmd(ADC1, ENABLE);          /*ADC1使能*/

/*ADC校准*/
ADC_ResetCalibration(ADC1); /*固定流程，内部有电路会自动执行校准*/
while (ADC_GetResetCalibrationStatus(ADC1) == SET)
    ;
ADC_StartCalibration(ADC1);
while (ADC_GetCalibrationStatus(ADC1) == SET)
    ;
/*ADC触发*/
ADC_SoftwareStartConvCmd(ADC1, ENABLE);
/*ADC DMA初始化 END ---------------------------------------------------------------------------------------------------*/
```

在main函数中根据AD_Value来计算远近实现关开灯动作.
```c
while (1)
{
    led_on = (AD_Value < 2000 ? 1 : 0);
    
    uint32_t currentTime = RTC_GetCounter(); 
    if ((currentTime - startTime) >= 1)
    {
        startTime = currentTime;
        OLED_ShowNum(1, 5, AD_Value, 4);/*用OLED观察远近的数据，每秒一次*/
    }

    if (led_mode == BREATHE)
    {
        Breathe_LED(); 
        Delay_us(500); 
    }
    else if (led_mode == BLINK)
    {
        LED_Blink();
    }
}
```

---

## Q1:介绍⼀下 ADC 的⼯作原理以及 ADC 的⼏种模式
### **1. ADC 的工作原理**

**ADC（Analog-to-Digital Converter，模数转换器）**用于将**模拟信号**（如电压）转换为**数字信号**（如二进制数据），以便处理器进行处理。ADC 的工作原理可以简单概括为以下步骤：

#### **1.1 工作流程**
1. **采样（Sample）**：
   - 采样电路捕获输入模拟信号在某一瞬间的值。  
   - 采样速率越高，捕捉的模拟信号变化越准确。

2. **保持（Hold）**：
   - 采样后的信号被保持不变，以供后续的量化和编码使用。这一过程称为 **采样保持（S/H, Sample and Hold）**。

3. **量化（Quantization）**：
   - 将模拟信号的连续值转换为离散的数字值。量化的精度取决于 ADC 的 **分辨率**，如 8 位、12 位、16 位等。

4. **编码（Encoding）**：
   - 将量化后的离散值编码为数字信号。比如，12 位的 ADC 会将量化值转换为 0 ~ 4095 之间的整数。



### **2. ADC 的常见模式**

STM32 的 ADC 提供了多种模式来适应不同的应用场景，包括 **单次转换模式**、**连续转换模式**、**扫描模式** 等。



#### **2.1 单次转换模式（Single Conversion Mode）**
- **工作原理**：ADC 只转换一次，然后停止。
- **应用场景**：不需要连续读取的场合，如按钮状态检测。
- **触发方式**：可以通过 **软件** 或 **外部事件**触发。

**示例**：读取一次温度传感器的值。


#### **2.2 连续转换模式（Continuous Conversion Mode）**
- **工作原理**：ADC 在完成一次转换后，自动开始下一次转换，直到被停止。
- **应用场景**：需要实时连续采样的场合，如音频信号采集或传感器监测。
- **优点**：无需每次手动触发，提高了系统响应速度。

**示例**：连续读取电池电压，监测其变化。



#### **2.3 扫描模式（Scan Mode）**
- **工作原理**：ADC 按顺序扫描多个输入通道，依次转换它们的值。
- **应用场景**：需要采集多个传感器数据的场景。
- **实现方式**：结合 DMA 使用，可以自动将转换结果存入数组。

**示例**：采集多个通道的数据，如温度、湿度和光强传感器。



#### **2.4 注入模式（Injected Mode）**
- **工作原理**：注入模式允许在**常规转换**的基础上，插入高优先级的转换任务。  
- **应用场景**：需要对某些关键信号（如过载信号）进行快速采样时使用。
- **优点**：不影响正常的转换过程，可以实现优先级处理。

**示例**：在监测多个传感器时，当检测到电流超限时，立即插入紧急采样任务。



#### **2.5 差分模式（Differential Mode）**
- **工作原理**：差分模式读取两个输入信号之间的差值，而不是绝对电压。
- **应用场景**：适用于需要抑制噪声的场合，如测量远距离传感器的信号。



#### **2.6 模拟看门狗（Analog Watchdog）**
- **工作原理**：ADC 会监控输入信号，当信号超出设定的阈值范围时，触发中断。
- **应用场景**：用于检测异常信号，如电压过高或过低时触发报警。



### **3. STM32 中 ADC 的常见配置方式**

1. **软件触发**：由程序控制，手动启动 ADC 转换。
2. **定时器触发**：由定时器定时启动 ADC 转换，适用于定时采样场景。
3. **DMA（Direct Memory Access）**：通过 DMA 将转换结果自动传输到内存，减轻 CPU 的负担。


### **4. 总结**

- **ADC** 将模拟信号转换为数字信号，是处理传感器数据的关键模块。
- 不同的 **转换模式** 适用于不同的应用场景：
  - 单次模式：适用于不连续的数据采集。
  - 连续模式：适用于实时信号采集。
  - 扫描模式：适用于采集多个通道的数据。
  - 注入模式：用于处理高优先级的采样任务。

---

## Q2:ADC 经常要与 DMA 结合使⽤，简要介绍 ADC 是如何与 DMA 配合使⽤的
### **ADC 与 DMA 配合使用的原理与流程**

在嵌入式系统中，**ADC（模数转换器）**经常与 **DMA（Direct Memory Access，直接内存访问）**模块结合使用，以提高数据采集的效率，减少 CPU 的负担。下面是 ADC 与 DMA 配合使用的基本原理、工作流程以及优势。



### **1. ADC + DMA 工作原理**

- **ADC** 将采集的模拟信号转换为数字信号。
- 使用 **DMA** 将转换后的数据直接传输到 **内存（RAM）** 中，而不需要 CPU 的干预。
- 当 **DMA 缓冲区**填满或传输完成时，可以触发中断通知 CPU 处理。


### **2. ADC + DMA 工作流程**

1. **启动 ADC 转换**：
   - ADC 开始采样模拟信号，完成转换后，将数据存入 ADC 数据寄存器（`ADC_DR`）。

2. **DMA 传输数据**：
   - DMA 自动将 **ADC 数据寄存器**的值传输到指定的内存地址中（如数组）。

3. **循环模式（可选）**：
   - 如果启用循环模式（`DMA_Mode_Circular`），ADC 会不断采样，DMA 自动更新内存中的数据。

4. **中断通知**：
   - 当 DMA 缓冲区填满时，可以触发中断，通知 CPU 数据传输完成。


### **3. ADC + DMA 使用的优点**

1. **减少 CPU 负担**：
   - 使用 DMA 后，数据采集和存储由 DMA 处理，CPU 可以专注于其他任务。

2. **实时性强**：
   - DMA 可以实现高速数据传输，提高系统的实时性。

3. **适合多通道扫描**：
   - ADC 在扫描模式下可以采集多个通道的数据，DMA 将采集的数据自动存入内存中的数组。


