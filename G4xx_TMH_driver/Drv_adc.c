/******************** (C) COPYRIGHT 2017 ANO Tech ********************************
 * 作者    ：匿名科创
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
 * 描述    ：ADC驱动
**********************************************************************************/
#include "Drv_adc.h"

uint16_t AdcValue = 0;

void Drv_AdcInit(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStructure;
	LL_ADC_CommonInitTypeDef ADC_CommonInitStruct;
	LL_ADC_InitTypeDef ADC_InitStruct;
	LL_ADC_REG_InitTypeDef ADC_REG_InitStruct;
	  /* GPIO Ports Clock Enable */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_ADC12);	
	  /**ADC1 GPIO Configuration
  PA0   ------> ADC1_IN1
  */
	GPIO_InitStructure.Pin = LL_GPIO_PIN_0;
	GPIO_InitStructure.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStructure.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	ADC_CommonInitStruct.CommonClock = LL_ADC_CLOCK_SYNC_PCLK_DIV4;
	ADC_CommonInitStruct.Multimode = LL_ADC_MULTI_INDEPENDENT;
	ADC_CommonInitStruct.MultiTwoSamplingDelay = LL_ADC_MULTI_TWOSMP_DELAY_1CYCLE;
	LL_ADC_CommonInit(ADC12_COMMON,&ADC_CommonInitStruct);
	
	ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
	ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
	ADC_InitStruct.LowPowerMode = LL_ADC_LP_MODE_NONE;
	LL_ADC_Init(ADC1,&ADC_InitStruct);
	
	ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
	ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
	ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
	ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
	ADC_REG_InitStruct.Overrun = LL_ADC_REG_OVR_DATA_OVERWRITTEN;
	LL_ADC_REG_Init(ADC1,&ADC_REG_InitStruct);
	LL_ADC_SetGainCompensation(ADC1, 0);
  LL_ADC_SetOverSamplingScope(ADC1, LL_ADC_OVS_DISABLE);
	  /* Disable ADC deep power down (enabled by default after reset state) */
  LL_ADC_DisableDeepPowerDown(ADC1);
  /* Enable ADC internal voltage regulator */
  LL_ADC_EnableInternalRegulator(ADC1);
	LL_mDelay(100);
	/** Configure Regular Channel **/
  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_1);
  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_1, LL_ADC_SAMPLINGTIME_247CYCLES_5);
	LL_ADC_SetChannelSingleDiff(ADC1, LL_ADC_CHANNEL_1, LL_ADC_SINGLE_ENDED);
	  /* Configuration of ADC interruptions */
  /* Enable interruption ADC group regular overrun */
  LL_ADC_EnableIT_OVR(ADC1);
	  if (LL_ADC_IsEnabled(ADC1) == 0)
  {
    /* Disable ADC deep power down (enabled by default after reset state) */
    LL_ADC_DisableDeepPowerDown(ADC1);
    
    /* Enable ADC internal voltage regulator */
    LL_ADC_EnableInternalRegulator(ADC1);
                           
	LL_mDelay(100);
    /* Run ADC self calibration */
    LL_ADC_StartCalibration(ADC1, LL_ADC_SINGLE_ENDED);
    
    while (LL_ADC_IsCalibrationOnGoing(ADC1) != 0)
    {
    }
	LL_mDelay(100);
    
    /* Enable ADC */
    LL_ADC_Enable(ADC1);
    while (LL_ADC_IsActiveFlag_ADRDY(ADC1) == 0)
    {
    }
  }
}

uint16_t Get_ADC(uint32_t ch)
{
	  if ((LL_ADC_IsEnabled(ADC1) == 1)               &&
      (LL_ADC_IsDisableOngoing(ADC1) == 0)        &&
      (LL_ADC_REG_IsConversionOngoing(ADC1) == 0)   )
  {
    LL_ADC_REG_StartConversion(ADC1);
  }
	while (LL_ADC_IsActiveFlag_EOC(ADC1) == 0);
	return LL_ADC_REG_ReadConversionData12(ADC1);
}


