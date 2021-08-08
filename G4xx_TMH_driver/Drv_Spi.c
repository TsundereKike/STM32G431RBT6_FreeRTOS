#include "Drv_Spi.h"

void Drv_SPI2_Init(void)
{
	LL_SPI_InitTypeDef SPI2_Init_structure;
	LL_GPIO_InitTypeDef SPI2_GPIO_Init_structure;
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
	/*
	SPI2_SCK = GPIOB->LL_GPIO_PIN_13
	SPI2_MISO/SDI = GPIOB->LL_GPIO_PIN_14
	SPI2_MOSI/SDO = GPIOB->LL_GPIO_PIN_15
	*/
	SPI2_GPIO_Init_structure.Pin = LL_GPIO_PIN_13|LL_GPIO_PIN_15;
	SPI2_GPIO_Init_structure.Mode = LL_GPIO_MODE_ALTERNATE;
	SPI2_GPIO_Init_structure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	SPI2_GPIO_Init_structure.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	SPI2_GPIO_Init_structure.Pull = LL_GPIO_PULL_NO;
	SPI2_GPIO_Init_structure.Alternate = LL_GPIO_AF_5;
	LL_GPIO_Init(GPIOB,&SPI2_GPIO_Init_structure);
	
	SPI2_GPIO_Init_structure.Pin = LL_GPIO_PIN_14;
	SPI2_GPIO_Init_structure.Mode = LL_GPIO_MODE_ALTERNATE;
	SPI2_GPIO_Init_structure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	SPI2_GPIO_Init_structure.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	SPI2_GPIO_Init_structure.Pull = LL_GPIO_PULL_NO;
	SPI2_GPIO_Init_structure.Alternate = LL_GPIO_AF_5;
	LL_GPIO_Init(GPIOB,&SPI2_GPIO_Init_structure);
	
	SPI2_Init_structure.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI2_Init_structure.Mode = LL_SPI_MODE_MASTER;
	SPI2_Init_structure.DataWidth = LL_SPI_DATAWIDTH_8BIT;
	SPI2_Init_structure.ClockPolarity = LL_SPI_POLARITY_HIGH;
	SPI2_Init_structure.ClockPhase = LL_SPI_PHASE_2EDGE;
	SPI2_Init_structure.NSS = LL_SPI_NSS_SOFT;
	SPI2_Init_structure.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV4;
	SPI2_Init_structure.BitOrder = LL_SPI_MSB_FIRST;
	SPI2_Init_structure.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
	SPI2_Init_structure.CRCPoly = 7U;
	LL_SPI_Init(SPI2,&SPI2_Init_structure);
	
	LL_SPI_SetStandard(SPI2, LL_SPI_PROTOCOL_MOTOROLA);
  LL_SPI_DisableNSSPulseMgt(SPI2);
	LL_SPI_SetRxFIFOThreshold(SPI2, LL_SPI_RX_FIFO_TH_QUARTER);
	LL_SPI_Enable(SPI2);
}

uint8_t Drv_Spi2_RW(uint8_t dat)
{
	while(!LL_SPI_IsActiveFlag_TXE(SPI2));
	LL_SPI_TransmitData8(SPI2,dat);
	while(!LL_SPI_IsActiveFlag_RXNE(SPI2));
	return LL_SPI_ReceiveData8(SPI2);
}
void Drv_Spi2_receive_data(uint8_t *pData,uint16_t size)
{
	for(uint16_t i=0;i<size;i++)
	{
		pData[i] = Drv_Spi2_RW(0);
	}
	
}


