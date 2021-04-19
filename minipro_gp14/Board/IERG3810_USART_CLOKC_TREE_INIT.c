#include "stm32f10x.h"
#include "IERG3810_USART_CLOKC_TREE_INIT.h"

// put procedure header here

void IERG3810_clock_tree_init(void){
	u8 PLL=7;
	unsigned char temp=0;
	RCC->CFGR&=0xF8FF0000;
	RCC->CR&=0xFEF6FFFF;
	RCC->CR|=0x00010000; //HSEON=1, (HSE bypass mode)
	while(!(RCC->CR>>17)); //Check HSERDY
	RCC->CFGR=0X00000400; //PPRE1=100
	RCC->CFGR|=PLL<<18; //PLLMUL=111
	RCC->CFGR|=1<<16; //PLLSRC=1
	FLASH->ACR|=0x32; //set FLASH with 2 wait states
	RCC->CR|=0x01000000; //PLLON=1
	while(!(RCC->CR>>25)); //check PLLRDY
	RCC->CFGR|=0x00000002; //SW=10
	while(temp!=0x02) //check SWS
	{
		temp=RCC->CFGR>>2; //SWS
		temp&=0x03; //set SWS = 11
	}
}
