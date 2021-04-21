#include"stm32f10x.h"


#define DS0_ON GPIOB->BRR = 1 << 5;
#define DS0_OFF GPIOB->BSRR = 1 << 5;
#define DS1_ON GPIOE->BRR = 1 << 5;
#define DS1_OFF GPIOE->BSRR = 1 << 5;


#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 	 0x001F  
#define BRED             0XF81F
#define GRED 			 			 0XFFE0
#define GBLUE			 		 	 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40
#define BRRED 			     0XFC07
#define GRAY  			     0X8430 


#define DARKBLUE      	 0X01CF
#define LIGHTBLUE      	 0X7D7C 
#define GRAYBLUE       	 0X5458

 
void TFT_ClearScreen(uint16_t color);


