#ifndef _DRV_I2C_H_
#define _DRV_I2C_H_

#include "stdint.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_bus.h"

#define SCL_H  LL_GPIO_SetOutputPin(GPIOC,LL_GPIO_PIN_8)
#define SCL_L  LL_GPIO_ResetOutputPin(GPIOC,LL_GPIO_PIN_8)
#define SDA_H  LL_GPIO_SetOutputPin(GPIOC,LL_GPIO_PIN_9)
#define SDA_L  LL_GPIO_ResetOutputPin(GPIOC,LL_GPIO_PIN_9)

#define SDA_I  LL_GPIO_IsInputPinSet(GPIOC,LL_GPIO_PIN_9)
#define SDA_OUT LL_GPIO_SetPinMode(GPIOC,LL_GPIO_PIN_9,LL_GPIO_MODE_OUTPUT)
#define SDA_IN  LL_GPIO_SetPinMode(GPIOC,LL_GPIO_PIN_9,LL_GPIO_MODE_INPUT)
void Drv_i2c_Init(void);
void delay_us(int us);
void i2c_start(void);
void i2c_stop(void);
void i2c_send_ack(uint8_t ack_dat);
static uint8_t i2c_wait_ack(void);
void i2c_send_data(uint8_t c);
uint8_t i2c_read_data(uint8_t ack);
extern void mpu6050_Write_Reg(uint8_t device_add,uint8_t reg,uint8_t data);
extern uint8_t mpu6050_Read_Reg(uint8_t device_add,uint8_t reg);
#endif
