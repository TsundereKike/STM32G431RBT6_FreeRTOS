#include "Drv_i2c.h"

void Drv_i2c_Init(void)//模拟i2C初始化
{
	LL_GPIO_InitTypeDef i2c_GPIO_Init_structure;
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
	i2c_GPIO_Init_structure.Pin = LL_GPIO_PIN_8|LL_GPIO_PIN_9;
	i2c_GPIO_Init_structure.Mode = LL_GPIO_MODE_OUTPUT;
	i2c_GPIO_Init_structure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	i2c_GPIO_Init_structure.Pull = LL_GPIO_PULL_UP;
	i2c_GPIO_Init_structure.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	LL_GPIO_Init(GPIOC,&i2c_GPIO_Init_structure);
}
void i2c_start(void)
{
	SDA_OUT;
	SCL_H;
	SDA_H;
	delay_us(2);
	SDA_L;
	delay_us(2);
	SCL_L;
}

void i2c_stop(void)
{
	SDA_OUT;
	SDA_L;
	SCL_L;
	delay_us(2);
	SCL_H;
	delay_us(2);
	SDA_H;
	delay_us(2);
}
void i2c_send_ack(uint8_t ack_dat)
{
	SDA_OUT;
	SCL_L;
	delay_us(2);
	if(ack_dat)
	{
		SDA_L;
	}
	else
	{
		SDA_H;
	}
	delay_us(2);
	SCL_H;
	delay_us(2);
	SCL_L;
	delay_us(2);
}
static uint8_t i2c_wait_ack(void)
{
	SDA_IN;
	SCL_L;
	delay_us(2);
	SCL_H;
	delay_us(2);
	if(SDA_I)
	{
		SDA_OUT;
	  SCL_L;	
    return 0;		
	}
		SDA_OUT;
	  SCL_L;
  	delay_us(2);	
    return 1;		
}
void i2c_send_data(uint8_t c)
{
	uint8_t i=8;
	SDA_OUT;
	while(i--)
	{
		if(c&0x80) SDA_H;
		else	SDA_L;
		c<<=1;
		delay_us(2);
		SCL_H;
		delay_us(2);
		SCL_L;
	}
	i2c_wait_ack();
}
uint8_t i2c_read_data(uint8_t ack)
{
	uint8_t i=8;
	uint8_t c;
	SDA_OUT;
	SCL_L;
	delay_us(2);
	SDA_H;
	SDA_IN;
	while(i--)
	{
		delay_us(2);
		SCL_L;
		delay_us(2);
		SCL_H;
		delay_us(2);
		c<<=1;
		if(SDA_I) c+=1;
	}
	SDA_OUT;
	SCL_L;
	delay_us(2);
	if(ack==0)
	{
		i2c_send_ack(0);
	}
	else
	{
		i2c_send_ack(1);
	}
	return c;
}

void mpu6050_Write_Reg(uint8_t device_add,uint8_t reg,uint8_t data)
{
	i2c_start();
	i2c_send_data((device_add<<1) | 0x00);//向从机发送器件地址加写位
	i2c_send_data(reg);//发送从机寄存器地址
	i2c_send_data(data);//发送需要写入的数据
	i2c_stop();
}
uint8_t mpu6050_Read_Reg(uint8_t device_add,uint8_t reg)
{
	uint8_t data;
	i2c_start();
	i2c_send_data((device_add<<1) |0x00);//向从机发送器件地址加写位
	i2c_send_data(reg);//发送从机寄存器地址
	
	i2c_start();
	i2c_send_data((device_add<<1) |0x01);//向从机发送器件地址加写位
	data = i2c_read_data(0);//读数据
	i2c_stop();
	return data;
}

/***软件延时 ***/ 
void delay_us(int us)   //误差 -0.005555555556us
{
	while(us--)
	{
    unsigned char a;
    for(a=2;a>0;a--);
	}
}
