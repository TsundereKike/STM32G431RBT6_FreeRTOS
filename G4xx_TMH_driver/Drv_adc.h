#ifndef _DRV_ADC_H_
#define _DRV_ADC_H_
#include "stdint.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_adc.h"
#include "stm32g4xx_ll_utils.h"
extern  uint16_t AdcValue;

void Drv_AdcInit(void);
extern uint16_t Get_ADC(uint32_t ch);
#endif
