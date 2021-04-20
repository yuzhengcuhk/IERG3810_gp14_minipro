#ifndef __IERG3810_LED_H
#define __IERG3810_LED_H
#include "stm32f10x.h"
#define LCD_BASE	((u32)(0x6c000000 | 0x000007FE))
#define LCD				((LCD_TypeDef *) LCD_BASE)
#define LCD_LIGHT_ON GPIO_SetBits(GPIOB,GPIO_Pin_0);
#define SNAKE_Max_Long 50
// put procedure header here

void IERG3810_LED_Init();

void IERG3810_TFTLCD_WrReg(u16 regval);
void IERG3810_TFTLCD_WrData(u16 data);

void IERG3810_TFTLCD_SetParameter();
void IERG3810_TFTLCD_Init();
void IERG3810_TFTLCD_FillRectangle(u16 color, u16 start_x, u16 length_x, u16 start_y, u16 length_y);

void IERG3810_TFTLCD_SetWindow(u16 start_x, u16 start_y, u16 length_x, u16 length_y);

void IERG3810_TFTLCD_ShowChar(u16 x, u16 y, u8 ascii, u16 color, u16 bgcolor);
void IERG3810_TFTLCD_ShowTChar(u16 x, u16 y, u8 Tfont, u16 color, u16 bgcolor);
#endif
