/**
  ******************************************************************************
  * @file    Templates_LL/Src/main.c
  * @author  MCD Application Team
  * @brief   Main program body through the LL API
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "delay.h"
#include "TMH_scheduler.h"
#include "FreeRTOS.h"
#include "task.h"
void SystemClock_Config(void);

#define START_TSK_SIZE				128
#define START_TASK_PRO				1
TaskHandle_t	START_TASK_Handle;

#define TASK_1_SIZE						128
#define TASK_1_PRO						2
TaskHandle_t	TASK_1_Handle;

#define TASK_2_SIZE						128
#define TASK_2_PRO						3
TaskHandle_t	TASK_2_Handle;
void start_task( void * pvParameters );
void Task_1( void * pvParameters );
void Task_2( void * pvParameters );
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	__NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_3);
  /* Configure the system clock to 170 MHz */
  SystemClock_Config();
	delay_init();
//	LL_mDelay(100);
  Drv_LED_Init();
//	PWM_Out_Init();					//初始化PWM输出功能	
//	LL_mDelay(100);
//	Usart2_Init(115200);
//	CTxBuffer[0] = 'A';
//	CTxBuffer[1] = 'L';
//	CTxBuffer[2] = 'I';
//	CTxBuffer[3] = 'E';
//	CTxBuffer[4] = 'N';
//	CTxBuffer[5] = 'T';
//	CTxBuffer[6] = 'E';
//	CTxBuffer[7] = 'K';
//	CTxBuffer[8] = '@';
//	CTxBuffer[9] = 'A';
//	CTxBuffer[10] = 'T';
//	CTxBuffer[11] = '+';
//	CTxBuffer[12] = 'C';
//	CTxBuffer[13] = 'S';
//	CTxBuffer[14] = 'Q';
//	CTxBuffer[15] = 0x0D;
//	CTxBuffer[16] = 0x0A;
		Drv_AdcInit();
////	Mpu6050_init();
//  Drv_SPI2_Init();/*初始化板载SPI2*/
//	Drv_icm20602_Init_CS();/*icm20602片选初始化*/
////	flag.icm20602_Init_success_OK = Drv_icm20602_Reg_Init();
    xTaskCreate( (TaskFunction_t) start_task,
                 (char *        ) "start_task", 
                 (uint16_t 			) START_TSK_SIZE,
                 (void * 				)	NULL,
                 (UBaseType_t   ) START_TASK_PRO,
                 (TaskHandle_t *) &START_TASK_Handle );
		vTaskStartScheduler();
//	Scheduler_Setup();
//  /* Infinite loop */
//  while (1)
//  {
//   Scheduler_Run();
//  }
}
void start_task( void * pvParameters )
 {
		xTaskCreate( (TaskFunction_t) Task_1,
                 (char *        ) "Task_1", 
                 (uint16_t 			) TASK_1_SIZE,
                 (void * 				)	NULL,
                 (UBaseType_t   ) TASK_1_PRO,
                 (TaskHandle_t *) &TASK_1_Handle );
								 
    xTaskCreate( (TaskFunction_t) Task_2,
                 (char *        ) "Task_2", 
                 (uint16_t 			) TASK_2_SIZE,
                 (void * 				)	NULL,
                 (UBaseType_t   ) TASK_2_PRO,
                 (TaskHandle_t *) &TASK_2_Handle );	
		vTaskDelete(START_TASK_Handle);
    taskEXIT_CRITICAL();            //退出临界区								 
 }
 
void Task_1( void * pvParameters )
{
	 while(1)
	 {
		 	LL_GPIO_TogglePin(LED2_GPIO_Port,LL_GPIO_PIN_5);//500msLED闪烁一次
			vTaskDelay(500);
	 }
}
 
void Task_2( void * pvParameters )
{
	 while(1)
	 {
		 	AdcValue=Get_ADC(LL_ADC_CHANNEL_1);
			vTaskDelay(2);
	 }
}
 
/* ==============   BOARD SPECIFIC CONFIGURATION CODE BEGIN    ============== */
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 170000000
  *            HCLK(Hz)                       = 170000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 4
  *            PLL_N                          = 85
  *            PLL_P                          = 2
  *            PLL_Q                          = 2
  *            PLL_R                          = 2
  *            Flash Latency(WS)              = 8
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  /* Enable voltage range 1 boost mode for frequency above 150 Mhz */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  LL_PWR_EnableRange1BoostMode();
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* Set Flash Latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);

  /* HSI already enabled at reset */

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_4, 85, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };

  /* PLL system Output activation */
  LL_RCC_PLL_EnableDomain_SYS();

  /* Sysclk activation on the main PLL */
  /* Intermediate AHB prescaler 2 when target frequency clock is higher than 80 MHz */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_2);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };

  /* Insure 1μs transition state at intermediate medium speed clock based on DWT */
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT = 0;
  while(DWT->CYCCNT < 100);

  /* AHB prescaler 1 */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Set APB1 & APB2 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  /* Set systick to 1ms in using frequency set to 170MHz */
  /* This frequency can be calculated through LL RCC macro */
  /* ex: __LL_RCC_CALC_PLLCLK_FREQ(HSI_VALUE,
                                  LL_RCC_PLLM_DIV_4, 85, LL_RCC_PLLR_DIV_2) */
  LL_Init1msTick(170000000);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(170000000);
}
/* ==============   BOARD SPECIFIC CONFIGURATION CODE END      ============== */

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
