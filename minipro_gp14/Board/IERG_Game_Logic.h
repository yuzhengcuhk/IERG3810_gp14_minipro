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

void direction_controller(void);
void start_page();
void start_game();
void gameover(u8 socre_buf[]);
void TIM3_IRQHandler(void);
