#ifndef _DRV_SPI_H_
#define _DRV_SPI_H_

#include "stm32g4xx_ll_spi.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_bus.h"
void Drv_SPI2_Init(void);
extern uint8_t Drv_Spi2_RW(uint8_t dat);
extern void Drv_Spi2_receive_data(uint8_t *pData,uint16_t size);

#endif
