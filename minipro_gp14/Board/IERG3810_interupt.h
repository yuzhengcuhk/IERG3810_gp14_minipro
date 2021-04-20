#include "stm32f10x.h"
#include "IERG3810_System_Init.h"
#include "IERG3810_key_Controller.h"
#include "IERG3810_LCD_Controller.h"
#include "IERG3810_Game_UI.h"
#include "IERG3810_LED.h"
#include "IERG3810_KEY.h"
#include "IERG3810_Delay.h"
#include "usart.h"
#include "tim.h"
#include "rtc.h"
#include "stdlib.h"

void IERG3810_NVIC_SetPriorityGroup(u8 prigroup);
void EXTI15_10_IRQHandler(void);
void IERG3810_PS2key_ExtiInit(void);