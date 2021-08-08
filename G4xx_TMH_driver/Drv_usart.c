/******************** (C) COPYRIGHT 2017 ANO Tech ********************************
 * 作者    ：匿名科创
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
 * 描述    ：串口驱动
**********************************************************************************/
#include "Drv_usart.h"

//====uart2
void Usart2_Init ( uint32_t br_num )
{
	LL_USART_InitTypeDef USART_InitStructure;
	LL_USART_ClockInitTypeDef	USART_ClockInitStruct;
	LL_GPIO_InitTypeDef	GPIO_InitStructure;
	
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
		  /* GPIO Ports Clock Enable */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

	//配置PB3作为USART2　Tx
	GPIO_InitStructure.Pin = LL_GPIO_PIN_3;
	GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;
//	GPIO_InitStructure.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOB,&GPIO_InitStructure);	
	LL_GPIO_SetAFPin_0_7(GPIOB,LL_GPIO_PIN_3,LL_GPIO_AF_7);	
	
	//配置PB4作为USART2　Rx
	GPIO_InitStructure.Pin = LL_GPIO_PIN_4;
	GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;
//	GPIO_InitStructure.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOB,&GPIO_InitStructure);	
	LL_GPIO_SetAFPin_0_7(GPIOB,LL_GPIO_PIN_4,LL_GPIO_AF_7);	
	
  /* USART2 interrupt Init */
	NVIC_SetPriority(USART2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2, 0));
  NVIC_EnableIRQ(USART2_IRQn);	
	
	USART_InitStructure.PrescalerValue  = LL_USART_PRESCALER_DIV1;
	USART_InitStructure.BaudRate = br_num;
	USART_InitStructure.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitStructure.StopBits = LL_USART_STOPBITS_1;
	USART_InitStructure.Parity = LL_USART_PARITY_NONE;
	USART_InitStructure.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStructure.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStructure.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART2,&USART_InitStructure);
	
	USART_ClockInitStruct.ClockOutput = LL_USART_CLOCK_DISABLE;
	USART_ClockInitStruct.ClockPolarity  = LL_USART_POLARITY_LOW;
	USART_ClockInitStruct.ClockPhase = LL_USART_PHASE_2EDGE;
	USART_ClockInitStruct.LastBitClockPulse = LL_USART_LASTCLKPULSE_NO_OUTPUT;
	LL_USART_ClockInit(USART2,&USART_ClockInitStruct);

		//使能USART2接收中断
	LL_USART_EnableIT_RXNE_RXFNE(USART2);
	//使能USART2
	LL_USART_Enable(USART2);
}
uint8_t dtu_rxlen = 0;
uint8_t DT_RxBuffer[28]={'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
uint8_t TxBuffer[256];
uint8_t CTxBuffer[17];
uint8_t TxCounter = 0;
uint8_t count = 0;
void Usart2_IRQ()
{
	uint8_t com_data;
	  if (LL_USART_IsActiveFlag_RXNE(USART2) && LL_USART_IsEnabledIT_RXNE(USART2))
  {
	  /* Read Received character. RXNE flag is cleared by reading of RDR register */
		com_data = LL_USART_ReceiveData8(USART2);
//		DT_RxBuffer[dtu_rxlen++] = com_data;
//		if(dtu_rxlen==28)
//		{
//			dtu_rxlen=0;
//		}
		ANO_DT_Data_Receive_Prepare(com_data);
  }
		if (LL_USART_IsActiveFlag_TXE(USART2) && LL_USART_IsEnabledIT_TXE(USART2))
  {
		USART2->TDR = TxBuffer[TxCounter++];
				if(TxCounter==count)
			{
				LL_USART_DisableIT_TXE(USART2);//关闭TXE（发送中断）中断
			}
  }

}

void Usart2_Send ( unsigned char *DataToSend , uint8_t data_num )
{
    uint8_t i;
    for ( i = 0; i < data_num; i++ )
    {
        TxBuffer[count++] = * ( DataToSend + i );
    }

    if ( LL_USART_IsActiveFlag_TXE(USART2) )
    {
        LL_USART_EnableIT_TXE(USART2); //打开发送中断
    }

}

void ANO_DT_Data_Receive_Prepare(uint8_t data)
{
	static uint8_t _data_len = 0;
	static uint8_t state = 0;
	if(state==0&&data=='A')//帧头‘A’
	{
		state=1;
		DT_RxBuffer[0]=data;
	}
	else if(state==1&&data=='T')//帧头‘T’
	{
		state=2;
		DT_RxBuffer[1]=data;
	}
		else if(state==2&&data=='+')//帧头‘+’
	{
		state=3;
		DT_RxBuffer[2]=data;
	}
		else if(state==3&&data=='C')//帧头‘C’
	{
		state=4;
		DT_RxBuffer[3]=data;
	}
		else if(state==4&&data=='S')//帧头‘S’
	{
		state=5;
		DT_RxBuffer[4]=data;
	}
		else if(state==5&&data=='Q')//帧头‘Q’
	{
		state=6;
		DT_RxBuffer[5]=data;
	}
		else if(state==6&&data==0x0D)//帧头空格
	{
		state=7;
		DT_RxBuffer[6]=data;
	}
			else if(state==7&&data==0x0A)//帧头换行
	{
		state=8;
		DT_RxBuffer[7]=data;
	}
			else if(state==8&&data==0x0D)//帧头空格
	{
		state=9;
		DT_RxBuffer[8]=data;
	}
			else if(state==9&&data==0x0A)//帧头换行
	{
		state=10;
		DT_RxBuffer[9]=data;
	}
			else if(state==10&&data=='+')//帧头指令+
	{
		state=11;
		DT_RxBuffer[10]=data;
	}
			else if(state==11&&data=='C')//帧头指令C
	{
		state=12;
		DT_RxBuffer[11]=data;
	}
			else if(state==12&&data=='S')//帧头指令S
	{
		state=13;
		DT_RxBuffer[12]=data;
	}
			else if(state==13&&data=='Q')//帧头指令Q
	{
		state=14;
		DT_RxBuffer[13]=data;
	}
		else if(state==14&&data==':')//帧头指令冒号
	{
		state=15;
		DT_RxBuffer[14]=data;
	}
			else if(state==15&&data==0x20)//帧头指令空
	{
		state=16;
		DT_RxBuffer[15]=data;
	}
		else if(state==16)//数据0,0
	{
		DT_RxBuffer[16]=data;
		if(data=='0')
		{
			state=17;
		}
		else
		{
		  state=20;
		}
	}
		else if(state==17&&data==',')//数据
	{
		state=18;
		DT_RxBuffer[17]=data;
	}
			else if(state==18)//数据
	{
		state=19;
		DT_RxBuffer[18]=data;
	}
			else if(state==19)//数据
	{
		state=30;
		DT_RxBuffer[19]=data;
	}
			else if(state==20)//数据
	{
		state=21;
		DT_RxBuffer[20]=data;
	}
			else if(state==21&&data==',')//数据
	{
		state=22;
		DT_RxBuffer[21]=data;
	}
			else if(state==22)//数据
	{
		state=23;
		DT_RxBuffer[22]=data;
	}
			else if(state==23)//数据
	{
		state=24;
		DT_RxBuffer[23]=data;
	}
	else
	{
		state=0;
	}
	
}
