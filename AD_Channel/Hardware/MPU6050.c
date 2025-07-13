#include "stm32f10x.h"
#include "MPU6050_Reg.h"
#include "utility.h"

#define MPU6050_ADDRESS 0xD0
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
	I2C_GenerateSTART(I2C2,ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT)!=SUCCESS);
	I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!=SUCCESS);
	I2C_SendData(I2C2,RegAddress); // 在从机地址传世完成后触发
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING)!=SUCCESS);
	I2C_SendData(I2C2,Data); // 在DR为空时触发
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED)!=SUCCESS);
	I2C_GenerateSTOP(I2C2,ENABLE); // 在数据传输完成后触发
}

void MPU6050_Init(void)
{
	//硬件I2C的初始化
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_CFG(GPIOB,GPIO_Pin_10 | GPIO_Pin_11,GPIO_Speed_50MHz,GPIO_Mode_AF_OD); // 复用开漏
	
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Mode=I2C_Mode_I2C;
	I2C_InitStructure.I2C_ClockSpeed=50000;
	I2C_InitStructure.I2C_DutyCycle=I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Ack=I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_OwnAddress1=0x00;
	I2C_Init(I2C2,&I2C_InitStructure);
	I2C_Cmd(I2C2,ENABLE);
	
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);
	MPU6050_WriteReg(MPU6050_CONFIG,0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);
	
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t data;
	I2C_GenerateSTART(I2C2,ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT)!=SUCCESS);
	I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!=SUCCESS); //第一步还是先发送寄存器的地址数据
	I2C_SendData(I2C2,RegAddress);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED)!=SUCCESS);
	
	I2C_GenerateSTART(I2C2,ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT)!=SUCCESS);
	I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Receiver);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)!=SUCCESS);
	I2C_AcknowledgeConfig(I2C2,DISABLE);
	I2C_GenerateSTOP(I2C2,ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED)!=SUCCESS);
	data=I2C_ReceiveData(I2C2);
	I2C_AcknowledgeConfig(I2C2,ENABLE);
	
	return data;
}

void MPU6050_GetData(int16_t* AccX,int16_t* AccY,int16_t* AccZ,
			int16_t* GyroX,int16_t* GyroY,int16_t* GyroZ)
{
	uint8_t DataH,DataL;
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H); //high
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L); //low
	*AccX=(DataH << 8) | DataL;
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY=(DataH << 8) | DataL;
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ=(DataH << 8) | DataL;
	DataH=MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX=(DataH << 8) | DataL;
	DataH=MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY=(DataH << 8) | DataL;
	DataH=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ=(DataH << 8) | DataL;
}

uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}
