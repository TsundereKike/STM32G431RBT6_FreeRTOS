#ifndef _PWM_OUT_H_
#define _PWM_OUT_H_

#include "stm32g4xx_ll_tim.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_bus.h"
void PWM_Out_Init(void);
void SetPwm(void);

#endif

