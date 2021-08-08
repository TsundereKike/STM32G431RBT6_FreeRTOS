/******************** (C) COPYRIGHT 2017 ANO Tech ********************************
 * 作者    ：匿名科创
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
 * 描述    ：PWM输出
**********************************************************************************/
#include "Drv_pwm_out.h"

void PWM_Out_Init () //17000hz
{
	LL_TIM_InitTypeDef	TIM_TimeBaseStructure;
	LL_TIM_OC_InitTypeDef	TIM_OCInitStructure;
	LL_GPIO_InitTypeDef GPIO_InitStructure;
	
	LL_TIM_StructInit(&TIM_TimeBaseStructure);
	LL_TIM_OC_StructInit(&TIM_OCInitStructure);
	LL_GPIO_StructInit(&GPIO_InitStructure);
	
//	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);//
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
	  /* GPIO Ports Clock Enable */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
//	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);//
	GPIO_InitStructure.Pin = /*LL_GPIO_PIN_5*/LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_2|LL_GPIO_PIN_3;
	GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;
	LL_GPIO_Init(GPIOC/*GPIOA*/,&GPIO_InitStructure);
	LL_GPIO_SetAFPin_0_7(GPIOC/*GPIOA*/,/*LL_GPIO_PIN_5,LL_GPIO_AF_1*/LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_2|LL_GPIO_PIN_3,LL_GPIO_AF_2);
	
	TIM_TimeBaseStructure.Prescaler = 10-1;
	TIM_TimeBaseStructure.CounterMode =	LL_TIM_COUNTERMODE_UP;
	TIM_TimeBaseStructure.ClockDivision =	LL_TIM_CLOCKDIVISION_DIV1;
	TIM_TimeBaseStructure.Autoreload =	1000-1;
	TIM_TimeBaseStructure.RepetitionCounter = 0x00000000U;
	LL_TIM_Init(TIM1/*TIM2*/,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.OCMode = LL_TIM_OCMODE_PWM1;
	TIM_OCInitStructure.OCState = LL_TIM_OCSTATE_ENABLE;
	TIM_OCInitStructure.OCNState = LL_TIM_OCSTATE_DISABLE;
	TIM_OCInitStructure.CompareValue = 0;
	TIM_OCInitStructure.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
	TIM_OCInitStructure.OCNPolarity = LL_TIM_OCPOLARITY_LOW;
	TIM_OCInitStructure.OCIdleState = LL_TIM_OCIDLESTATE_HIGH;
	TIM_OCInitStructure.OCNIdleState = LL_TIM_OCIDLESTATE_LOW;
	LL_TIM_OC_Init(TIM1/*TIM2*/,LL_TIM_CHANNEL_CH1,&TIM_OCInitStructure);
	
	TIM_OCInitStructure.CompareValue = 0;
	LL_TIM_OC_Init(TIM1/*TIM2*/,LL_TIM_CHANNEL_CH2,&TIM_OCInitStructure);
	
	TIM_OCInitStructure.CompareValue = 0;
	LL_TIM_OC_Init(TIM1/*TIM2*/,LL_TIM_CHANNEL_CH3,&TIM_OCInitStructure);
	
	TIM_OCInitStructure.CompareValue = 0;
	LL_TIM_OC_Init(TIM1/*TIM2*/,LL_TIM_CHANNEL_CH4,&TIM_OCInitStructure);
	
	LL_TIM_EnableAllOutputs(TIM1/*TIM2*/);
	LL_TIM_EnableARRPreload(TIM1/*TIM2*/);
	LL_TIM_EnableCounter(TIM1/*TIM2*/);
	
}


void SetPwm ()
{
	TIM1/*TIM2*/->CCR1 = 999;
	TIM1/*TIM2*/->CCR2 = 300;
	TIM1/*TIM2*/->CCR3 = 500;
	TIM1/*TIM2*/->CCR4 = 800;
}
