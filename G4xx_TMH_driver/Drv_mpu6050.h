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
#define MPU6050_ADRESS  (0x68)   /*mpu6050�豸��ַ*/
#define MPU6050_DEV_ADDR  0XD0>>1 /*i2cд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ*/

#define Mpu6050_WR(reg,value)  mpu6050_Write_Reg(MPU6050_DEV_ADDR,reg,value)
#define Mpu6050_RD(reg)  mpu6050_Read_Reg(MPU6050_DEV_ADDR,reg)

#define MPU_PWR_MGMT1_REG		0X6B	//��Դ����Ĵ���1
#define MPU_GYRO_CFG_REG		0X1B	//���������üĴ���
#define MPU_ACCEL_CFG_REG		0X1C	//���ٶȼ����üĴ���
#define MPU_SAMPLE_RATE_REG		0X19	//����Ƶ�ʷ�Ƶ��
#define MPU_CFG_REG				0X1A	//���üĴ���
#define MPU_DEVICE_ID_REG		0X75	//����ID�Ĵ���

#define MPU_ACCEL_XOUTH_REG		0X3B	//���ٶ�ֵ,X���8λ�Ĵ���
#define MPU_ACCEL_XOUTL_REG		0X3C	//���ٶ�ֵ,X���8λ�Ĵ���
#define MPU_ACCEL_YOUTH_REG		0X3D	//���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU_ACCEL_YOUTL_REG		0X3E	//���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU_ACCEL_ZOUTH_REG		0X3F	//���ٶ�ֵ,Z���8λ�Ĵ���
#define MPU_ACCEL_ZOUTL_REG		0X40	//���ٶ�ֵ,Z���8λ�Ĵ���

#define MPU_GYRO_XOUTH_REG		0X43	//������ֵ,X���8λ�Ĵ���
#define MPU_GYRO_XOUTL_REG		0X44	//������ֵ,X���8λ�Ĵ���
#define MPU_GYRO_YOUTH_REG		0X45	//������ֵ,Y���8λ�Ĵ���
#define MPU_GYRO_YOUTL_REG		0X46	//������ֵ,Y���8λ�Ĵ���
#define MPU_GYRO_ZOUTH_REG		0X47	//������ֵ,Z���8λ�Ĵ���
#define MPU_GYRO_ZOUTL_REG		0X48	//������ֵ,Z���8λ�Ĵ���
extern uint8_t Mpu6050_init(void);
int16_t Get_data(uint8_t reg_address);
extern void Mpu6050_Original_data_Get(void);


#endif
