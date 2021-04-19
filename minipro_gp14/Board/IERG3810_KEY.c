#include "stm32f10x.h"
#include "IERG3810_KEY.h"

// put your procedure and code here
void IERG3810_KEY_Init(){

//GPIOE && GPIOEA ENABLE
RCC ->APB2ENR |= 1 << 6;
RCC ->APB2ENR |= 1 << 2;

//Key2
GPIOE->CRL &= 0xFFFFF0FF;
GPIOE->CRL |= 0x00000800;
GPIOE->BSRR |= 0x00000004;
	
//Key1
GPIOE->CRL &= 0xFFFF0FFF;
GPIOE->CRL |= 0x00008000;
GPIOE->BSRR |= 0x00000008;

//Key-up
GPIOA->CRL &= 0xFFFFFFF0;
GPIOA->CRL |= 0x00000008;
}