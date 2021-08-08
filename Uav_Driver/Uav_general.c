#include "Uav_general.h"
_flag_st flag;
void Mpu6050_offset_caculate(void)
{
	static uint8_t Acc_Caculate_cnt,Gyro_Caculate_cnt,i;
	if(sensor.Acc_Caculate_Offset_Calibrate|sensor.Gyr_Caculate_Offset_Calibrate)
	{
/*加速度计校准*/		
			if(sensor.Acc_Caculate_Offset_Calibrate ==1)
		{
				Acc_Caculate_cnt++;
				if(Acc_Caculate_cnt<=50)
			{
				for(i=0;i<3;i++)
				{
					sensor.Acc_Offset[i] += sensor.Mpu6050_Acc_Original[i];
				}
			}
				else
			{			
					for(i=0;i<3;i++)
				{
					sensor.Acc_ref[i] = (float)sensor.Acc_Offset[i]/50; 
				}
					sensor.Acc_Caculate_Offset_Calibrate = 0;
					Acc_Caculate_cnt = 0;
			}
		}
/*陀螺仪校准*/		
			if(sensor.Gyr_Caculate_Offset_Calibrate ==1)
		{
				Gyro_Caculate_cnt++;
				if(Gyro_Caculate_cnt<=50)
			{
				for(i=0;i<3;i++)
				{
					sensor.Gyro_Offset[i] += sensor.Icm20602_Gyro_Original[i];
				}
			}
				else
			{			
					for(i=0;i<3;i++)
				{
					sensor.Gyro_ref[i] = (float)sensor.Gyro_Offset[i]/50;
				}
					sensor.Gyr_Caculate_Offset_Calibrate = 0;
					Gyro_Caculate_cnt = 0;
			}
		}
	}

}
