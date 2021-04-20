#include "IERG_Game_Logic.h"

#define Max_Lof_snake 50 // win after this long

u8 key;
u8 start=0;
u8 speed = 100; //easy:300 normal:100 hard:50 

struct Snake_data
{
	s16 X_coordinate[Max_Lof_snake];
	s16 Y_coordinate[Max_Lof_snake];
	u8 Long;
	u8 Life;
	u8 Direction; 

}snake;

struct Food_data
{
	u8 food_X;
	u8 food_Y;
	u8 Yes;
}food;


struct Game_data
{
	u16 Score;
	u8 Life;
}game;




void start_page(void)	
{	
	int i=0;
	char title[] = "Start Page";
	char start[] = "New game start at:";
	char CUID1[] = "1155095162";
	char CUID2[] = "1155126633";

	GPIOB->BRR = 1 << 8;
	delay_ms(300);
	TFT_ClearScreen(WHITE);
	
	for(i=0;i<10;i++)
		{IERG3810_TFTLCD_ShowChar(i*9+75, 180, title[i], 0, WHITE);}
		
	for(i=0;i<18;i++)
		{IERG3810_TFTLCD_ShowChar(i*9+30, 140, start[i], 0, WHITE);}
	
	for(i=0;i<10;i++)
		{IERG3810_TFTLCD_ShowChar(i*9+10, 10, CUID1[i], 0, WHITE);}
		
	for(i=0;i<10;i++)
		{IERG3810_TFTLCD_ShowChar(i*9+10, 30, CUID2[i], 0, WHITE);}
	
	for(i=0;i<3;i++)
	{	
			IERG3810_TFTLCD_ShowChar(200, 140, 3-i+'0', 0, WHITE);
			delay_ms(1000);
	}
		
	start_game();
}


void gameover(u8 score_tran[])
{
	int i=0;
	char over[] = "Game over:(";
	char score[] = "Your score:";
	
	TFT_ClearScreen(WHITE);

	for(i=0;i<11;i++)
		{IERG3810_TFTLCD_ShowChar(i*9+70, 180, score[i], 0, WHITE);}
		
	for(i=0;i<3;i++)
		{IERG3810_TFTLCD_ShowChar(i*10+170, 180, score_tran[i], 0, WHITE);}
		
	for(i=0;i<11;i++)
		{IERG3810_TFTLCD_ShowChar(i*9+80, 140, over[i], 0, WHITE);}
	
	for(i=0;i<15;i++)
	{
		delay_ms(16960);
	}
	start_page();
}


void direction_controller(void)
{	
	static u8 start=0;
	key=keyscan(0);	
	start=1;
	if(start==1)
	{				
		
		if(key==K_UP_PRESS&&snake.Direction!=3)
		{
			snake.Direction=4;
		} 
		if(key==K_DOWN_PRESS&&snake.Direction!=4)
		{
			snake.Direction=3;
		} 
		if(key==K_LEFT_PRESS&&snake.Direction!=1)
		{
			snake.Direction=2;
		} 
		if(key==K_RIGHT_PRESS&&snake.Direction!=2)
		{
			snake.Direction=1;
		}

	}
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!= RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		direction_controller();
	}
}  


void start_game()
{
	u16 i,n;
	u16 counter = 0;
	
	char life_text[] = "life:";
	char score_text[] = "score:";
	
	u8 life[2];
	u8 score[4];
	
	//snake_init_para
	snake.Long = 10;
	snake.Life = 1;
	snake.Direction = 4;
	
	//game_init_para
	game.Score = 0;
	game.Life = 5;
	
	//food_init_para
	food.Yes = 1;
	
	//snake_init_position
	snake.X_coordinate[0]=120;snake.Y_coordinate[0]=168;
	snake.X_coordinate[1]=120;snake.Y_coordinate[1]=168;
	
	
	IERG3810_TFTLCD_FillRectangle(WHITE,1,240,1,320);
	while(1)	
	{	

			/*-----------------Food Logic------------------*/
		
			//random position for the food
			if(food.Yes==1) 
			{
				while(1)
				{
					srand(calendar.sec);
					food.food_X=60 + (rand()%(10))*12;
					food.food_Y=84 + (rand()%(14))*12;
					
					for(n=0;n<snake.Long;n++)
					{
						if(food.food_X==snake.X_coordinate[n]&&food.food_Y==snake.Y_coordinate[n])
						break;
					}
					if(n==snake.Long) {food.Yes=0;}
					break;
				}
			}
			
			//Make the food appear
			if(food.Yes==0)
			{	GUI_Box(food.food_X,food.food_Y,food.food_X+10,food.food_Y+10,CYAN);}

			//snake eats a food 
			if(snake.X_coordinate[0]==food.food_X&&snake.Y_coordinate[0]==food.food_Y)
			{
				GUI_Box(food.food_X,food.food_Y,food.food_X+10,food.food_Y+10,WHITE);
				if(!(snake.Long==Max_Lof_snake))
				snake.Long++;
				game.Score+=1;
				score[0]=game.Score%100/10+0x30;
				score[1]=game.Score%100%10+0x30;
				score[2]='\0';
				food.Yes=1; //for remaking a food 
			}

			for(i=0;i<6;i++)
			{IERG3810_TFTLCD_ShowChar(i*9+5, 300, score_text[i], 0, WHITE);}
			
			for(i=0;i<2;i++)
			{
				if(score[i] == '0' && (i == 0)) {;}
				else{IERG3810_TFTLCD_ShowChar(i*10+50, 300, score[i], 0, WHITE);}
			}
			//End of food
			
			
			
			
			/*-----------------Snake Logic------------------*/
			
			//struct the snake with the long
			for(i=snake.Long-1;i>0;i--)
			{
				snake.X_coordinate[i]=snake.X_coordinate[i-1];
				snake.Y_coordinate[i]=snake.Y_coordinate[i-1];
			}
			
			//locate the snake with direction
			switch(snake.Direction)
			{
				case 1:snake.X_coordinate[0]+=12;break;
				case 2:snake.X_coordinate[0]-=12;break;
				case 3:snake.Y_coordinate[0]-=12;break;
				case 4:snake.Y_coordinate[0]+=12;break;
			}
				
			//make the snake appear
			for(i=0;i<snake.Long;i++) { GUI_Box(snake.X_coordinate[i],snake.Y_coordinate[i],snake.X_coordinate[i]+10,snake.Y_coordinate[i]+10,YELLOW);}
			
			//make the tail of the snake disappear
			GUI_Box(snake.X_coordinate[snake.Long-1],snake.Y_coordinate[snake.Long-1],snake.X_coordinate[snake.Long-1]+10,snake.Y_coordinate[snake.Long-1]+10,WHITE);
			//End of snake
			
				
				
				
				
				
			/*-----------------Life Logic------------------*/
			//the snake out of the boundary, user will lose the game
			if(snake.X_coordinate[0]<0||snake.X_coordinate[0]>220||snake.Y_coordinate[0]<0||snake.Y_coordinate[0]>300) {snake.Life=0;}
			
		  	//the snake hit its' body, life -1
			for(i=3;i<snake.Long;i++)
			{
				if(snake.X_coordinate[i]==snake.X_coordinate[0]&&snake.Y_coordinate[i]==snake.Y_coordinate[0]) 
					{
						game.Life-=1;
						GPIOB->BSRR = 1 << 8;
					}
			}
			
			//life = 0, gameover
			if(snake.Life==0||game.Life==0)
			{
				delay_ms(100);
				GPIOB->BRR = 1 << 8;
				gameover(score);
				break;
			}	

			//life display
			life[0]=game.Life%10+0x30;
			life[1]='\0';
			
			for(i=0;i<5;i++)
			{IERG3810_TFTLCD_ShowChar(i*9+166, 300, life_text[i], 0, WHITE);}
			
			IERG3810_TFTLCD_ShowChar(220, 300, life[0], 0, WHITE);
			//End of life
			
			
			
			
			
			//control the speed of the snake 
			delay_ms(speed); //easy:300 normal:100 hard:50 
			GPIOB->BRR = 1 << 8;
		}	
}
