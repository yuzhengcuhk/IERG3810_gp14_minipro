#include "stm32f10x.h"
#include "IERG3810_Buzzer.h"

// put your procedure and code here
void IERG_3810_Buzzer_Init(){

//GPIOB ENABLE
RCC ->APB2ENR |= 1 << 3;

//buzzer
GPIOB->CRH &= 0xFFFFFFF0;
GPIOB->CRH |= 0x00000003;
GPIOB->BRR |= 0x00000100;
GPIOB->BSRR |= 0x00000100;
}