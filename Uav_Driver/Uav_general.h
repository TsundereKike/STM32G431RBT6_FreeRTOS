#ifndef _UAV_GENERAL_H_
#define _UAV_GENERAL_H_
#include "Drv_mpu6050.h"
void Mpu6050_offset_caculate(void);
typedef struct
{
	uint8_t icm20602_Init_success_OK;
	
	
}_flag_st;
extern _flag_st flag;
#endif
