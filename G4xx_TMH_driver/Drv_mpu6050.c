#include "Drv_mpu6050.h"
_sensor_st sensor;
uint8_t Mpu6050_init(void)
{
	uint8_t res;
	Drv_i2c_Init();
	Mpu6050_WR(MPU_PWR_MGMT1_REG,0x80);//��λMpu6050
	LL_mDelay(10);
	Mpu6050_WR(MPU_PWR_MGMT1_REG,0x00);//����Mpu6050
	LL_mDelay(10);
	Mpu6050_WR(MPU_PWR_MGMT1_REG,0x01);//����CLKSEL,PLL,X��Ϊ�ο�
	LL_mDelay(10);
	Mpu6050_WR(MPU_GYRO_CFG_REG,3<<3);//��������������,��2000dps
	LL_mDelay(10);
	Mpu6050_WR(MPU_ACCEL_CFG_REG,3<<3);//���ü��ٶȼ�����,��16g
	LL_mDelay(10);
	Mpu6050_WR(MPU_SAMPLE_RATE_REG,0x00);//����Mpu6050����Ƶ�ʣ�1KHZ
	LL_mDelay(10);
  Mpu6050_WR(MPU_CFG_REG,0x04);//�������ֵ�ͨ�˲�����20HZ
	LL_mDelay(10);
	
	res = Mpu6050_RD(MPU_DEVICE_ID_REG);
	if(res==MPU6050_ADRESS)
	{
		return 0;
	}
	else
	{
		return 1;
	}
	
}

int16_t Get_data(uint8_t reg_address)
{
	uint8_t H,L;
	H = Mpu6050_RD(reg_address);
	L = Mpu6050_RD(reg_address+1);
	return (int16_t)((((uint16_t)H)<<8) | L);
}
void Mpu6050_Original_data_Get(void)
{
	sensor.Mpu6050_Acc_Original[X] = Get_data(MPU_ACCEL_XOUTH_REG);//��ȡ���ٶȼ�����ԭʼֵ
	sensor.Mpu6050_Acc_Original[Y] = Get_data(MPU_ACCEL_YOUTH_REG);
	sensor.Mpu6050_Acc_Original[Z] = Get_data(MPU_ACCEL_ZOUTH_REG);	
	
	sensor.Mpu6050_Gyro_Original[X] = Get_data(MPU_GYRO_XOUTH_REG);	//��ȡ����������ԭʼֵ
	sensor.Mpu6050_Gyro_Original[Y] = Get_data(MPU_GYRO_YOUTH_REG);
	sensor.Mpu6050_Gyro_Original[Z] = Get_data(MPU_GYRO_ZOUTH_REG);	
}
