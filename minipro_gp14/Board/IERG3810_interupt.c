#include "IERG3810_System_Init.h"
#include "IERG3810_key_Controller.h"
#include "IERG3810_LCD_Controller.h"
#include "IERG3810_Game_UI.h"
#include "IERG3810_LED.h"
#include "IERG3810_KEY.h"
#include "IERG3810_Delay.h"
#include "IERG3810_Buzzer.h"
#include "IERG_Game_Logic.h"

#include "usart.h"
#include "tim.h"
#include "rtc.h"
#include "stdlib.h"
void delay(u32 count)
{
	u32 i;
	for(i = 0; i< count; i++);
}

int ps2count, timeout, ps2key, release, i;
void IERG3810_NVIC_SetPriorityGroup(u8 prigroup)
{
	//Set PRIGROUP AIRCR[l0:8]
	u32 temp, temp1;
	temp1 = prigroup & 0x0000007; 
	temp1 <<= 8 ; 
	temp = SCB->AIRCR;	
	temp &= 0x0000F8FF;
	temp |= 0x05FA0000;
	temp |= temp1;
	SCB->AIRCR=temp;
}
void EXTI15_10_IRQHandler(void)
{
	u16 bit = (GPIOC->IDR & (1<<10)) >> 10;
	
	if (ps2count > 0 && ps2count < 9) {
		ps2key |= bit << (ps2count - 1); 
	}
	ps2count++;
	
	delay(10);	
	EXTI->PR = 1<<11;
}
void IERG3810_PS2key_ExtiInit(void)
{
	RCC->APB2ENR|=1<<4;
	GPIOC->CRH &= 0xFFFF00FF;
	GPIOC->CRH |= 0x00008800;
	GPIOC->ODR |= 1<<11;
	
	
	RCC->APB2ENR |= 0x01;
	AFIO->EXTICR[2] &= 0xFFFF0FFF;
	AFIO->EXTICR[2] |= 0x00002000;
	EXTI->IMR |= 1<<11;
	EXTI->FTSR |=1<<11;

	NVIC->IP[40] = 0x95;
	NVIC->ISER[1] |= (1<<8);
	
	RCC->APB2ENR|=1<<4;
	GPIOC->CRH &= 0xFFFFF0FF;
	GPIOC->CRH |= 0x00000800;
}