#ifndef _TMH_SCHEDULER_H_
#define _TMH_SCHEDULER_H_
#include "stdint.h"
#include "stm32g4xx_it.h"
#include "Drv_led.h"
#include "Drv_adc.h"
#include "Drv_pwm_out.h"
#include "Drv_usart.h"
#include "Drv_mpu6050.h"
#include "Drv_Icm20602.h"
#include "Drv_Spi.h"
#include "Uav_general.h"
#define TICK_PER_SECOND	1000
typedef struct
{
void(*task_func)(void);
uint16_t rate_hz;
uint16_t interval_ticks;
uint32_t last_run;
}sched_task_t;
void Scheduler_Setup(void);
void Scheduler_Run(void);
#endif
