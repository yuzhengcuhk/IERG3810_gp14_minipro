#include "stm32f10x.h"
#include "IERG3810_USART1_INIT.h"

void IERG3810_USART1_init(u32 pclkl, u32 bound)
{
	//USART1 to add APB2 with 72MHz
	float temp;
	u16 mantissa;
	u16 fraction;
	temp=(float)(pclkl*1000000)/(bound*16);
	mantissa=temp;
	fraction=(temp-mantissa)*16;
		mantissa<<=4;
	mantissa+=fraction;
	RCC->APB2ENR|=1<<2;
	RCC->APB2ENR|=1<<14;
	GPIOA->CRH&=0XFFFFF00F;
	GPIOA->CRH|=0X000008B0;
	RCC->APB2RSTR|=1<<14;
	RCC->APB2RSTR&=~(1<<14);
	USART1->BRR=mantissa;
	USART1->CR1|=0X2008;
}