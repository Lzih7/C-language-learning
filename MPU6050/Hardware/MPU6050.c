#include "stm32f10x.h"
#include "MyI2C.h"

#define MPU6050_ADDRESS 0xD0
void MPU6050_WritingReg(uint8_t RegAddress, uint8_t Data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Data);
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}

void MPU6050_Init(void)
{
	MyI2C_Init();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01); //读取从机数据
	MyI2C_ReceiveAck();
	uint8_t data;
	data=MyI2C_ReceiveByte();
	MyI2C_SendAck(1);
	MyI2C_Stop();
	return data;
}
