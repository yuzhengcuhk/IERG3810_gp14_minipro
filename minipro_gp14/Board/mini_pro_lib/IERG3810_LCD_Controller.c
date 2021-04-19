#include "IERG3810_LCD_Controller.h"
#include "IERG3810_LED.h"
u16 tft_id;



void TFT_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE  
	                      | RCC_APB2Periph_GPIOG, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_Init(GPIOG, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 
	                              | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_8 
								  | GPIO_Pin_9 | GPIO_Pin_10 |GPIO_Pin_11
								  | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14
								  | GPIO_Pin_15 );

	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9
	                               | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12
								   | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

	GPIO_Init(GPIOE, &GPIO_InitStructure);
}



void TFT_FSMC_Config(void)
{

	FSMC_NORSRAMInitTypeDef        FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  FSMC_NORSRAMTiming;


	FSMC_NORSRAMTiming.FSMC_AddressSetupTime = 0x02;


	FSMC_NORSRAMTiming.FSMC_AddressHoldTime = 0x00;


	FSMC_NORSRAMTiming.FSMC_DataSetupTime = 0x05;


	FSMC_NORSRAMTiming.FSMC_DataLatency = 0x00;

	FSMC_NORSRAMTiming.FSMC_BusTurnAroundDuration = 0x00;
	
	FSMC_NORSRAMTiming.FSMC_CLKDivision = 0x01;

	FSMC_NORSRAMTiming.FSMC_AccessMode = FSMC_AccessMode_B;

	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;

	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;

	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;

	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;

	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;
	
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTiming;
	
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTiming;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
	 
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);	
}


void TFT_WriteCmd(uint16_t cmd)
{
	TFT->TFT_CMD = cmd;
}


void TFT_WriteData(u16 dat)
{
	TFT->TFT_DATA = dat;
}


void TFT_Init(void)
{
	uint16_t i;

	TFT_GPIO_Config();
	TFT_FSMC_Config();

	TFT_WriteCmd(0xE9); 
	TFT_WriteData(0x20); 
	
	TFT_WriteCmd(0x11);
	for(i=500; i>0; i--);
	
	TFT_WriteCmd(0x3A);
	TFT_WriteData(0x55);  
	
	TFT_WriteCmd(0xD1); 
	TFT_WriteData(0x00); 
	TFT_WriteData(0x65); 
	TFT_WriteData(0x1F); 
	
	TFT_WriteCmd(0xD0); 
	TFT_WriteData(0x07); 
	TFT_WriteData(0x07); 
	TFT_WriteData(0x80); 
	
	TFT_WriteCmd(0x36); 
	TFT_WriteData(0x48);
	
	TFT_WriteCmd(0xC1); 
	TFT_WriteData(0x10); 
	TFT_WriteData(0x10); 
	TFT_WriteData(0x02); 
	TFT_WriteData(0x02); 
	
	TFT_WriteCmd(0xC0);
	TFT_WriteData(0x00);  
	TFT_WriteData(0x35); 
	TFT_WriteData(0x00); 
	TFT_WriteData(0x00); 
	TFT_WriteData(0x01); 
	TFT_WriteData(0x02); 

	TFT_WriteCmd(0xC4);			
	TFT_WriteData(0x03);

	TFT_WriteCmd(0xC5);
	TFT_WriteData(0x01); 
	
	TFT_WriteCmd(0xD2);
	TFT_WriteData(0x01); 
	TFT_WriteData(0x22); 

	TFT_WriteCmd(0xE7);			
	TFT_WriteData(0x38);
	
	TFT_WriteCmd(0xF3);			
    TFT_WriteData(0x08); 
	TFT_WriteData(0x12);
	TFT_WriteData(0x12);
	TFT_WriteData(0x08);

	TFT_WriteCmd(0xC8);
	TFT_WriteData(0x01); 
	TFT_WriteData(0x52); 
	TFT_WriteData(0x37); 
	TFT_WriteData(0x10); 
	TFT_WriteData(0x0d); 
	TFT_WriteData(0x01); 
	TFT_WriteData(0x04); 
	TFT_WriteData(0x51); 
	TFT_WriteData(0x77); 
	TFT_WriteData(0x01); 
	TFT_WriteData(0x01); 
	TFT_WriteData(0x0d); 
	TFT_WriteData(0x08); 
	TFT_WriteData(0x80); 
	TFT_WriteData(0x00);  

	TFT_WriteCmd(0x29);



}



void TFT_SetWindow(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd)
{
 	TFT_WriteCmd(0x2A);

    TFT_WriteData(xStart>>8);
    TFT_WriteData(xStart&0XFF);
    TFT_WriteData(xEnd>>8);
    TFT_WriteData(xEnd&0XFF);

    TFT_WriteCmd(0x2b);
    TFT_WriteData(yStart>>8);
    TFT_WriteData(yStart&0XFF);
    TFT_WriteData(yEnd>>8);
    TFT_WriteData(yEnd&0XFF);
    TFT_WriteCmd(0x2c);
}


	  
void TFT_ClearScreen(uint16_t color)
{
 	uint16_t i, j ;

	IERG3810_TFTLCD_SetWindow(0, 0, TFT_XMAX, TFT_YMAX);
  	for(i=0; i<TFT_XMAX+1; i++)
	{
		for (j=0; j<TFT_YMAX+1; j++)
		{
			IERG3810_TFTLCD_WrData(color);
		}
	}
}


