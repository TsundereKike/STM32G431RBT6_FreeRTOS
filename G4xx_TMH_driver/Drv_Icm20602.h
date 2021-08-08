#ifndef _DRV_ICM20602_H_
#define _DRV_ICM20602_H_
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_utils.h"
#define MPU_RA_PWR_MGMT_1       0x6B
#define MPUREG_WHOAMI           0x75
#define MPU_WHOAMI_20602		0x12
#define MPU_RA_SIGNAL_PATH_RESET    0x68
#define MPU_RA_USER_CTRL        0x6A
#define MPU_RA_PWR_MGMT_2       0x6C
#define MPU_RA_SMPLRT_DIV       0x19
#define MPU_RA_CONFIG           0x1A
#define ICM20602_LPF_250HZ       0
#define ICM20602_LPF_176HZ       1
#define ICM20602_LPF_92HZ        2
#define ICM20602_LPF_41HZ        3
#define ICM20602_LPF_20HZ        4
#define ICM20602_LPF_10HZ        5
#define ICM20602_LPF_5HZ         6
#define ICM20602_LPF_3281HZ      7
#define MPU_RA_GYRO_CONFIG      0x1B
#define MPU_RA_ACCEL_CONFIG     0x1C
#define MPUREG_ACCEL_XOUT_H     0x3B
extern void Drv_icm20602_Init_CS(void);
extern uint8_t Drv_icm20602_Reg_Init(void);
extern void Drv_Icm20602_Data_Get(void);
#endif
