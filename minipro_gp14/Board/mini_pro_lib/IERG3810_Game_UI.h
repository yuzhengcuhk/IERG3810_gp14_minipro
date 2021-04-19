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

#define GUI_FLASH_ASCII_ADDR     6112846 
#define GUI_FLASH_12CHAR_ADDR    6114304
#define GUI_FLASH_16CHAR_ADDR    6880386


#define GUI_UPDATE_ASCII         0x01     
#define GUI_UPDATE_12CHAR        0x02
#define GUI_UPDATE_16CHAR        0x04
#define GUI_UPDATE_ALL           0x07


void GUI_Dot(uint16_t x, uint16_t y, uint16_t color);
void GUI_Line(u16 xStart, u16 yStart, u16 xEnd, u16 yEnd, u16 color);
void GUI_BigPoint(uint16_t x, uint16_t y, uint16_t color);
void GUI_Box(uint16_t xState, uint16_t yState, uint16_t xEnd, uint16_t yEnd, uint16_t color);
void GUI_DrowSign(uint16_t x, uint16_t y, uint16_t color);

void GUI_FontUpdate(uint8_t updateState);
void GUI_Show12ASCII(uint16_t x, uint16_t y, uint8_t *p, 
                     uint16_t wordColor, uint16_t backColor);
void GUI_Show12Char(uint16_t x, uint16_t y, uint8_t *ch, 
                    uint16_t wordColor, uint16_t backColor);
void GUI_Show16Chinese(uint16_t x, uint16_t y, uint8_t *cn, 
                       uint16_t  wordColor, uint16_t backColor);
void LCD_Draw_Point(u16 x,u16 y,u16 color);
void Test_Show_CH_Font16(u16 x,u16 y,u8 index,u16 color);
void Test_Show_CH_Font24(u16 x,u16 y,u8 index,u16 color);
void TEST_FONT(void);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void GUI_ShowPicture(uint x, uint y, uint wide, uint high);
#endif
