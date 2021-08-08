#include "TMH_scheduler.h"
uint32_t Signal_strength=0;
uint8_t aliyun_buf[28]={0};
static void Loop_1000Hz(void)	//1ms执行一次信号强度数据解析，1ms执行一次信号强度Json格式编码
{
		aliyun_buf[0] = '{';
		aliyun_buf[1] = '"';
		aliyun_buf[2] = 'p';
		aliyun_buf[3] = 'a';
		aliyun_buf[4] = 'r';
		aliyun_buf[5] = 'a';
		aliyun_buf[6] = 'm';
		aliyun_buf[7] = 's';
		aliyun_buf[8] = '"';
		aliyun_buf[9] = ':';
		aliyun_buf[10] = '{';
		aliyun_buf[11] = '"';
		aliyun_buf[12] = '4';
		aliyun_buf[13] = 'G';
		aliyun_buf[14] = '_';
		aliyun_buf[15] = 'q';
		aliyun_buf[16] = 'i';
		aliyun_buf[17] = 'a';
		aliyun_buf[18] = 'n';
		aliyun_buf[19] = 'g';
		aliyun_buf[20] = 'd';
		aliyun_buf[21] = 'u';
		aliyun_buf[22] = '"';
		aliyun_buf[23] = ':';
		if(DT_RxBuffer[16]=='0')
		{
			Signal_strength = DT_RxBuffer[16]-'0';
		}
		else 
		{
			Signal_strength = 113-((DT_RxBuffer[16]-'0')*10+DT_RxBuffer[20]-'0')*2;
		}
		aliyun_buf[24] = DT_RxBuffer[16];

		if(DT_RxBuffer[16]=='0')
		{
			aliyun_buf[25] = 0;
		}
		else 
		{
			aliyun_buf[25] = DT_RxBuffer[20];
		}
		aliyun_buf[26] = '}';
		aliyun_buf[27] = '}';

}

static void Loop_500Hz(void)	//2ms执行一次
{	
	AdcValue=Get_ADC(LL_ADC_CHANNEL_1);
	SetPwm ();
}

static void Loop_200Hz(void)	//5ms执行一次
{	
//	Mpu6050_Original_data_Get();
//	Drv_Icm20602_Data_Get();
	
}

static void Loop_100Hz(void)	//10ms执行一次
{


}

static void Loop_50Hz(void)	//20ms执行一次
{	

}
uint8_t Trans_cnt=0;
static void Loop_20Hz(void)	//50ms执行一次
{	
		Trans_cnt++;
	if(Trans_cnt==6)
	{
		Trans_cnt = 0;
		Usart2_Send(CTxBuffer,17);//300ms发送一次信号强度查询指令
	}

}

static void Loop_2Hz(void)	//500ms执行一次
{
	LL_GPIO_TogglePin(LED2_GPIO_Port,LL_GPIO_PIN_5);//500msLED闪烁一次
	if(Trans_cnt==2)
	{
		Usart2_Send(aliyun_buf,28);//1S执行一次Json格式的数据传到阿里云
	}
}


static sched_task_t sched_tasks[] = 
{
	{Loop_1000Hz,1000,  0, 0},
	{Loop_500Hz , 500,  0, 0},
	{Loop_200Hz , 200,  0, 0},
	{Loop_100Hz , 100,  0, 0},
	{Loop_50Hz  ,  50,  0, 0},
	{Loop_20Hz  ,  20,  0, 0},
	{Loop_2Hz   ,   2,  0, 0},
};

#define TASK_NUM (sizeof(sched_tasks)/sizeof(sched_task_t))

void Scheduler_Setup(void)
{
	uint8_t index = 0;
	
	for(index=0;index < TASK_NUM;index++)
	{
		
		sched_tasks[index].interval_ticks = TICK_PER_SECOND/sched_tasks[index].rate_hz;

		if(sched_tasks[index].interval_ticks < 1)
		{
			sched_tasks[index].interval_ticks = 1;
		}
	}
}

void Scheduler_Run(void)
{
	uint8_t index = 0;
	uint32_t tnow=0;

	for(index=0;index < TASK_NUM;index++)
	{
	
	   tnow = SysTick_GetTick();

		if(tnow - sched_tasks[index].last_run >= sched_tasks[index].interval_ticks)
		{
			
			sched_tasks[index].last_run = tnow;
			
			sched_tasks[index].task_func();

		}	 
	}
	

}

	

