#include "IERG3810_System_Init.h"
#include "IERG3810_key_Controller.h"
#include "IERG3810_LCD_Controller.h"
#include "IERG3810_Game_UI.h"
#include "IERG3810_LED.h"
#include "IERG3810_KEY.h"
#include "IERG3810_Delay.h"
#include "IERG3810_Buzzer.h"
#include "IERG_Game_Logic.h"

#include "tim.h"
#include "rtc.h"
#include "stdlib.h"



int main(void)
{	
	int i;
	button_init();
	delay_init();
	IERG_3810_Buzzer_Init();
	IERG3810_LED_Init();
	GPIOB->BRR = 1 << 8;
	DS0_OFF;
	DS1_OFF;
	IERG3810_TFTLCD_Init();
	IERG3810_TFTLCD_FillRectangle(WHITE,1,240,1,320);
	TIM3_Init(25,7199);
	rtc_init();	
	for(i=0;i<4;i++)
	uart_init(9600);
	IERG3810_NVIC_SetPriorityGroup(5);
	IERG3810_PS2key_ExtiInit();
	start_page();
	start_game();
}
