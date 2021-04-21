#include "IERG3810_Game_UI.h"
#include "IERG3810_LED.h"

void GUI_Dot(uint16_t x, uint16_t y, uint16_t color)
{  
	IERG3810_TFTLCD_SetWindow(x, y, x, y);
	IERG3810_TFTLCD_WrData(color);
}

void GUI_Line(u16 xStart, u16 yStart, u16 xEnd, u16 yEnd, u16 color)
{
	u16 t;  
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;  
	int incx, incy;  
	u16 row, col;  
	delta_x = xEnd - xStart;
	delta_y = yEnd - yStart;  
	col = xStart;  
	row = yStart;  
	if (delta_x > 0)
	{
		incx=1;
	} 	  
	else    
	{  
	    if (delta_x == 0)
		{
			incx = 0;
		} 		 
	    else 
			{
				incx = -1;
				delta_x = -delta_x;
			}  
	}  
	if (delta_y > 0)
	{
		incy = 1;
	}	  
	else  
	{  
	    if (delta_y == 0)
		{
			incy = 0; 
		} 
	    else 
		{
			incy = -1;
			delta_y = -delta_y;
		}  
	}  
	if (delta_x > delta_y)
	{ 
		distance = delta_x;
	}
	else
	{
		distance = delta_y; 
	} 	
	for (t=0; t<=distance+1; t++)  
	{
	    GUI_Dot(col, row, color);
	    xerr += delta_x;  
	    yerr += delta_y;  
	  	if(xerr > distance)  
	    {  
	        xerr -= distance;  
	        col += incx;  
	    }  
	    if(yerr > distance)  
	    {  
	        yerr -= distance;  
	        row += incy;  
	    }  
	}  
}


void GUI_Box(uint16_t xState, uint16_t yState, uint16_t xEnd, uint16_t yEnd, uint16_t color)
{ 
	uint16_t temp;

  if((xState > xEnd) || (yState > yEnd))
  {
        return;
  }   
	IERG3810_TFTLCD_SetWindow(xState, yState, xEnd, yEnd); 
  xState = xEnd - xState + 1;
	yState = yEnd - yState + 1;

	while(xState--)
	{
	 	temp = yState;
		while (temp--)
	 	{	
			IERG3810_TFTLCD_WrData(color);
		}
	}
}






