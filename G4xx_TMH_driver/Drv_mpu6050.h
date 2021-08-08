#ifndef _DRV_MPU6050_H_
#define _DRV_MPU6050_H_
#include "Drv_i2c.h"
#include "stm32g4xx_ll_utils.h"
enum 
{
	X = 0,
	Y = 1,
	Z = 2,
	VEC_XYZ,
};
typedef struct
{
	uint8_t Acc_Caculate_Offset_Calibrate;
	uint8_t Gyr_Caculate_Offset_Calibrate;
	int16_t Mpu6050_Acc_Original[VEC_XYZ];
	int16_t Mpu6050_Gyro_Original[VEC_XYZ];
	int16_t Icm20602_Acc_Original[VEC_XYZ];
	int16_t Icm20602_Gyro_Original[VEC_XYZ];
	int32_t Acc_Offset[VEC_XYZ];
	int32_t Gyro_Offset[VEC_XYZ];
	float Acc_ref[VEC_XYZ];
	float Gyro_ref[VEC_XYZ];
	int16_t Tempreature;
	float   Tempreature_C;
}_sensor_st;
extern _sensor_st sensor;
#define MPU6050_ADRESS  (0x68)   /*mpu6050设备地址*/
#define MPU6050_DEV_ADDR  0XD0>>1 /*i2c写入时的地址字节数据，+1为读取*/

#define Mpu6050_WR(reg,value)  mpu6050_Write_Reg(MPU6050_DEV_ADDR,reg,value)
#define Mpu6050_RD(reg)  mpu6050_Read_Reg(MPU6050_DEV_ADDR,reg)

#define MPU_PWR_MGMT1_REG		0X6B	//电源管理寄存器1
#define MPU_GYRO_CFG_REG		0X1B	//陀螺仪配置寄存器
#define MPU_ACCEL_CFG_REG		0X1C	//加速度计配置寄存器
#define MPU_SAMPLE_RATE_REG		0X19	//采样频率分频器
#define MPU_CFG_REG				0X1A	//配置寄存器
#define MPU_DEVICE_ID_REG		0X75	//器件ID寄存器

#define MPU_ACCEL_XOUTH_REG		0X3B	//加速度值,X轴高8位寄存器
#define MPU_ACCEL_XOUTL_REG		0X3C	//加速度值,X轴低8位寄存器
#define MPU_ACCEL_YOUTH_REG		0X3D	//加速度值,Y轴高8位寄存器
#define MPU_ACCEL_YOUTL_REG		0X3E	//加速度值,Y轴低8位寄存器
#define MPU_ACCEL_ZOUTH_REG		0X3F	//加速度值,Z轴高8位寄存器
#define MPU_ACCEL_ZOUTL_REG		0X40	//加速度值,Z轴低8位寄存器

#define MPU_GYRO_XOUTH_REG		0X43	//陀螺仪值,X轴高8位寄存器
#define MPU_GYRO_XOUTL_REG		0X44	//陀螺仪值,X轴低8位寄存器
#define MPU_GYRO_YOUTH_REG		0X45	//陀螺仪值,Y轴高8位寄存器
#define MPU_GYRO_YOUTL_REG		0X46	//陀螺仪值,Y轴低8位寄存器
#define MPU_GYRO_ZOUTH_REG		0X47	//陀螺仪值,Z轴高8位寄存器
#define MPU_GYRO_ZOUTL_REG		0X48	//陀螺仪值,Z轴低8位寄存器
extern uint8_t Mpu6050_init(void);
int16_t Get_data(uint8_t reg_address);
extern void Mpu6050_Original_data_Get(void);


#endif
