/******************** (C) COPYRIGHT 2017 ANO Tech ********************************
 * 作者    ：匿名科创
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
 * 描述    ：LED驱动
**********************************************************************************/
#include "Drv_led.h"



void Drv_LED_Init()
{
	LL_GPIO_InitTypeDef GPIO_InitStructure;
	LL_GPIO_StructInit(&GPIO_InitStructure);
	
  /* GPIO Ports Clock Enable */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

	GPIO_InitStructure.Pin = LED2_Pin;
	GPIO_InitStructure.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStructure.Pull   = LL_GPIO_PULL_NO;
	LL_GPIO_Init(LED2_GPIO_Port, &GPIO_InitStructure);
	
}




