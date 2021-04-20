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


#define DS0_ON GPIOB->BRR = 1 << 5;
#define DS0_OFF GPIOB->BSRR = 1 << 5;
#define DS1_ON GPIOE->BRR = 1 << 5;
#define DS1_OFF GPIOE->BSRR = 1 << 5;

int main(void)
{	
	button_init();
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	IERG_3810_Buzzer_Init();
	GPIOB->BRR = 1 << 8;
	IERG3810_TFTLCD_Init();
	IERG3810_TFTLCD_FillRectangle(WHITE,1,240,1,320);
	TIM3_Init(25,7199);
	rtc_init();	
	uart_init(9600);
	start_page();
	start_game();
}
