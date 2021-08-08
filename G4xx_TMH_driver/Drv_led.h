#ifndef _LED_H_
#define	_LED_H_
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_bus.h"
/***************LED GPIO定义******************/
#define LED2_Pin LL_GPIO_PIN_5
#define LED2_GPIO_Port GPIOA
/*********************************************/


void Drv_LED_Init(void);



#endif
