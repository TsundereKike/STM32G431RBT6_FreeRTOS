#include "Drv_Icm20602.h"
#include "Drv_Spi.h"
#include "Drv_mpu6050.h"
void Drv_icm20602_Init_CS(void)
{
	LL_GPIO_InitTypeDef Icm20602_GPIO_structure;
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
	/*
		SPI2_Icm20602_CS = GPIOB->LL_GPIO_PIN_8
	*/
	Icm20602_GPIO_structure.Pin = LL_GPIO_PIN_8;
	Icm20602_GPIO_structure.Mode = LL_GPIO_MODE_OUTPUT;
	Icm20602_GPIO_structure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	Icm20602_GPIO_structure.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	Icm20602_GPIO_structure.Pull = LL_GPIO_PULL_NO;
	Icm20602_GPIO_structure.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOB,&Icm20602_GPIO_structure);
	LL_GPIO_SetOutputPin(GPIOB,LL_GPIO_PIN_8);
}
static void icm20602_CS_enable(uint8_t en)
{
	if(en)
	{
		LL_GPIO_ResetOutputPin(GPIOB,LL_GPIO_PIN_8);
	}
	if(!en)
	{
		LL_GPIO_SetOutputPin(GPIOB,LL_GPIO_PIN_8);
	}
}

static uint8_t icm20602_writebyte(uint8_t reg,uint8_t data)
{
	uint8_t status;
	icm20602_CS_enable(1);
	status = Drv_Spi2_RW(reg);
	Drv_Spi2_RW(data);
	icm20602_CS_enable(0);
	return status;
}
static void icm20602_readbuff(uint8_t reg,uint8_t data_length,uint8_t *data)
{
	icm20602_CS_enable(1);
	Drv_Spi2_RW(reg|0x80);
	Drv_Spi2_receive_data(data,data_length);
	icm20602_CS_enable(0);
}
uint8_t Drv_icm20602_Reg_Init(void)
{
	uint8_t res;
	icm20602_writebyte(MPU_RA_PWR_MGMT_1,0x80);
	LL_mDelay(50);
	icm20602_writebyte(MPU_RA_PWR_MGMT_1,0x01);
	LL_mDelay(50);
	
	icm20602_readbuff(MPUREG_WHOAMI,1,&res);
	if(res != MPU_WHOAMI_20602)
	{
		return 0;
	}
	icm20602_writebyte(MPU_RA_SIGNAL_PATH_RESET,0x03);
	LL_mDelay(10);
	icm20602_writebyte(MPU_RA_USER_CTRL,0x01);
	LL_mDelay(10);
	
	icm20602_writebyte(0x70,0x40);
	LL_mDelay(10);
	icm20602_writebyte(MPU_RA_PWR_MGMT_2,0x00);
	LL_mDelay(10);
	icm20602_writebyte(MPU_RA_SMPLRT_DIV,0x00);
	LL_mDelay(10);
	
	icm20602_writebyte(MPU_RA_CONFIG,ICM20602_LPF_20HZ);
	LL_mDelay(10);
	icm20602_writebyte(MPU_RA_GYRO_CONFIG,3<<3);
	LL_mDelay(10);
	icm20602_writebyte(MPU_RA_ACCEL_CONFIG,3<<3);
	LL_mDelay(10);
/*加速度计低通滤波20HZ*/
	icm20602_writebyte(0x1D,0x04);
	LL_mDelay(10);
	/*关闭低功耗*/
	icm20602_writebyte(0x1E,0x00);
	LL_mDelay(10);
/*关闭FIFO*/
	icm20602_writebyte(0x23,0x00);
	LL_mDelay(10);	
	return 1;
}
uint8_t icm20602_buf[14];
void Drv_Icm20602_Data_Get(void)
{
	icm20602_readbuff(MPUREG_ACCEL_XOUT_H,14,icm20602_buf);
	int16_t temp[2][3];
	temp[0][X] = (int16_t)( (((uint16_t)icm20602_buf[0])<<8) | icm20602_buf[1]);
	temp[0][X] = (int16_t)( (((uint16_t)icm20602_buf[2])<<8) | icm20602_buf[3]);
	temp[0][X] = (int16_t)( (((uint16_t)icm20602_buf[4])<<8) | icm20602_buf[5]);
	
	temp[1][X] = (int16_t)( (((uint16_t)icm20602_buf[8])<<8) | icm20602_buf[9]);
	temp[1][Y] = (int16_t)( (((uint16_t)icm20602_buf[10])<<8) | icm20602_buf[11]);
	temp[1][Z] = (int16_t)( (((uint16_t)icm20602_buf[12])<<8) | icm20602_buf[13]);
	//Icm20602温度	
	sensor.Tempreature  = (int16_t)( (((uint16_t)icm20602_buf[6])<<8) | icm20602_buf[7]);
	sensor.Tempreature_C = sensor.Tempreature/326.8f + 25;
	//调整物理坐标轴与软件坐标轴方向定义一致	
	sensor.Icm20602_Acc_Original[X] = temp[0][X];
	sensor.Icm20602_Acc_Original[Y] = temp[0][Y];
	sensor.Icm20602_Acc_Original[Z] = temp[0][Z];
	
	sensor.Icm20602_Gyro_Original[X] = temp[1][X];
	sensor.Icm20602_Gyro_Original[Y] = temp[1][Y];
	sensor.Icm20602_Gyro_Original[Z] = temp[1][Z];	
}










