#include "stm32f10x.h"
#include "IERG3810_USART2_INIT.h"

void IERG3810_USART2_init(u32 pclkl, u32 bound)
{
	//USART2
	float temp;
	u16 mantissa;
	u16 fraction;
	temp=(float)(pclkl*1000000)/(bound*16);
	mantissa=temp;
	fraction=(temp-mantissa)*16;
		mantissa<<=4;
	mantissa+=fraction;
	RCC->APB2ENR|=1<<2;
	RCC->APB1ENR|=1<<17;
	GPIOA->CRL&=0XFFFF00FF;
	GPIOA->CRL|=0X00008B00;
	RCC->APB1RSTR|=1<<17;
	RCC->APB1RSTR&=~(1<<17);
	USART2->BRR=mantissa;
	USART2->CR1|=0X2008;
}