#include "IERG3810_LCD_Controller.h"
#include "IERG3810_LED.h"



	  
void TFT_ClearScreen(uint16_t color)
{
 	uint16_t i, j ;

	IERG3810_TFTLCD_SetWindow(0, 0, 240, 320);
  	for(i=0; i<240+1; i++)
	{
		for (j=0; j<320+1; j++)
		{
			IERG3810_TFTLCD_WrData(color);
		}
	}
}


