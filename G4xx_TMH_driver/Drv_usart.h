#ifndef _USART_H
#define _USART_H

#include "stdint.h"
#include "stm32g4xx_ll_usart.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_rcc.h"
void Usart2_Init(uint32_t br_num);
void Usart2_IRQ(void);
void Usart2_Send(unsigned char *DataToSend ,uint8_t data_num);
void ANO_DT_Data_Receive_Prepare(uint8_t data);
extern  uint8_t DT_RxBuffer[28];
extern  uint8_t CTxBuffer[17];
#endif
