#ifndef __GUI_H
#define __GUI_H

#include "stm32f10x.h"
#include "IERG3810_LCD_Controller.h"





#define PICTURE_SHOW
#ifndef uchar
#define uchar uint8_t
#endif

#ifndef uint
#define uint  uint16_t
#endif



void GUI_Dot(uint16_t x, uint16_t y, uint16_t color);
void GUI_Line(u16 xStart, u16 yStart, u16 xEnd, u16 yEnd, u16 color);
void GUI_BigPoint(uint16_t x, uint16_t y, uint16_t color);
void GUI_Box(uint16_t xState, uint16_t yState, uint16_t xEnd, uint16_t yEnd, uint16_t color);
void GUI_DrowSign(uint16_t x, uint16_t y, uint16_t color);
#endif
