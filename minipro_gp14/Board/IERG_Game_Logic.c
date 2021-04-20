#include "IERG_Game_Logic.h"

#define Max_Lof_snake 50 // win after this long

u8 key;
u8 start=0;
u16 speed = 100; //easy:300 normal:100 hard:50 
extern int ps2key, ps2count, timeout;

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

struct Item
{
	u8 type;
	u8 X;
	u8 Y;
	u8 Yes;
}item;

struct Life_Item
{
	u8 type;
	u8 LX;
	u8 LY;
	u8 Yes;
}life_item;

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

char item_msg[] = "Slow Item:";
char item_press[] = "press 0!";
int period = 0;

void start_game()
{
	
	int count = 0,speed_temp;
	int item_count = 48;//means ascii table char "0"
	u16 i,n;
	u16 bgc = WHITE;
	
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
	
	//item_init
	item.Yes = 1;
	life_item.Yes = 1;
	
	IERG3810_TFTLCD_FillRectangle(WHITE,1,240,1,320);
	while(1)	
	{	
			//Key 
			if (ps2count >= 11)
			{
				//EXTI->IMR &= ~(1<<11);
				if (ps2key == 0x70 && item_count > 48 && period == 0){
					IERG3810_TFTLCD_FillRectangle(DARKBLUE,0,240,0,320);
					speed_temp = speed;
					speed = 100;
					period++;
					item_count--;
					bgc = DARKBLUE;
				}

				EXTI->PR = 1<<11;
				//EXTI->IMR = 1<<11;
				
			}
		
			//Slow mode & return normal mode
			if (period > 0 && period++ >= 30)
				{
					period = 0; 
					speed = speed_temp;
					IERG3810_TFTLCD_FillRectangle(WHITE,0,240,0,320);
					bgc = WHITE;
				}
			
			//Show the remaining number of slow items
			for(i=0;i<10;i++)
			{IERG3810_TFTLCD_ShowChar(i*9+10, 10, item_msg[i], 0, bgc);}
			IERG3810_TFTLCD_ShowChar(i*9+20, 10, item_count, 0, bgc);
			for(i=0;i<8;i++)
			{IERG3810_TFTLCD_ShowChar(i*9+160, 10, item_press[i], 0, bgc);}
			//?
			ps2key = 0;
			ps2count = 0;

		
			//{	GUI_Box(food.X,food.Y,food.X+15,food.Y+15, 5555);}

			/*-----------------Food Logic------------------*/
		
				//random position for the food
				if(food.Yes==1) 
				{
					while(1)
					{
						srand(calendar.sec);
//<<<<<<< HEAD
						food.food_X=60 + (rand()%(10))*12;
						food.food_Y=84 + (rand()%(14))*12;
						
//=======
					//food.X=60 + (rand()%(10))*12;
					//food.Y=84 + (rand()%(14))*12;	
//>>>>>>> 38d496b (Testing)
					
						for(n=0;n<snake.Long;n++)
						{
							if(food.food_X==snake.X_coordinate[n]&&food.food_Y==snake.Y_coordinate[n])
							break;
						}
						if(n==snake.Long) {
						food.Yes=0;
						}
						break;
					}
				}
				
				//Slow item
				if (item.Yes == 1 && count > 30){
					while(1)
					{
						srand(calendar.sec/10);
						item.X=60 + (rand()%(10))*12;
						item.Y=84 + (rand()%(14))*12;
						for(n=0;n<snake.Long;n++)
						{
							if((item.X==snake.X_coordinate[n]&&item.Y==snake.Y_coordinate[n]) || (item.X==food.food_X && item.Y == food.food_Y))
							break;
						}
						if(n==snake.Long) {
						item.Yes=0;
						}
						break;
						
					}
				}
				
				//Life item
				if (life_item.Yes == 1 && count > 20){
				while(1)
				{
					srand(calendar.sec/15);
					life_item.LX=60 + (rand()%(10))*12;
					life_item.LY=84 + (rand()%(14))*12;
					for(n=0;n<snake.Long;n++)
					{
						if((life_item.LX==snake.X_coordinate[n]&&life_item.LY==snake.Y_coordinate[n]) || (life_item.LX==food.food_X && life_item.LY == food.food_Y))
						break;
					}
					if(n==snake.Long) {
					life_item.Yes=0;
					}
					break;
					
				}
			}
			
			//Make the food appear
			if(food.Yes==0)
			{	GUI_Box(food.food_X,food.food_Y,food.food_X+10,food.food_Y+10,GREEN);}

			//make the items appear
			if(item.Yes==0)
			{	GUI_Box(item.X,item.Y,item.X+10,item.Y+10, CYAN);}

			if(life_item.Yes==0)
			{	GUI_Box(life_item.LX,life_item.LY,life_item.LX+10,life_item.LY+10, RED);}
			
			
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
//<<<<<<< HEAD

			for(i=0;i<6;i++)
			{IERG3810_TFTLCD_ShowChar(i*9+5, 300, score_text[i], 0, bgc);}
			
//=======
			
			//snake eats a slow item
			if(snake.X_coordinate[0]==item.X&&snake.Y_coordinate[0]==item.Y)
			{
				GUI_Box(item.X,item.Y,item.X+10,item.Y+10,WHITE);
				if(item_count <57) {item_count++;}//
				item.Yes=1; //for remaking a item 
				
			}
			
			//snake eats a life item
			if(snake.X_coordinate[0]==life_item.LX&&snake.Y_coordinate[0]==life_item.LY)
			{
				GUI_Box(life_item.LX,life_item.LY,life_item.LX+10,life_item.LY+10,WHITE);
				if(game.Life<5) {game.Life++;}
				life_item.Yes=1; //for remaking a item 
				
			}
//>>>>>>> 38d496b (Testing)
			for(i=0;i<2;i++)
			{
				if(score[i] == 0x30 && (i == 0)) {;}
				else{IERG3810_TFTLCD_ShowChar(i*10+60, 300, score[i], 0, bgc);}
			}
			//End of food
			
			
			//life display
			life[0]=game.Life%10+0x30;
			life[1]='\0';
			
			for(i=0;i<game.Life;i++)
			{IERG3810_TFTLCD_FillRectangle(RED,i*7+200,6,300,14);}
			for(i=5;i>game.Life;i--)
			{IERG3810_TFTLCD_FillRectangle(WHITE,-(i-game.Life)*7+235,6,300,14);}
			for(i=0;i<5;i++)
			{IERG3810_TFTLCD_ShowChar(i*9+153, 300, life_text[i], 0, bgc);}
			
			//IERG3810_TFTLCD_ShowChar(220, 300, life[0], 0, WHITE);
			//End of life
			
			
			
			
			/*-----------------Snake Logic------------------*/
			
			
			
			//the snake out of the boundary, user will lose the game
			if(snake.X_coordinate[0]<0) {
				snake.X_coordinate[0]=240;
			}
			if(snake.X_coordinate[0]>240) {
				snake.X_coordinate[0]=0;
			}
			if(snake.Y_coordinate[0]<0) {
				snake.Y_coordinate[0]=312;
			}
			if(snake.Y_coordinate[0]>312) {
				snake.Y_coordinate[0]=0;
			}
			
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
			for(i=0;i<snake.Long;i++) { 
			if(period!=0){GUI_Box(snake.X_coordinate[i],snake.Y_coordinate[i],snake.X_coordinate[i]+10,snake.Y_coordinate[i]+10,CYAN);}
			else{GUI_Box(snake.X_coordinate[i],snake.Y_coordinate[i],snake.X_coordinate[i]+10,snake.Y_coordinate[i]+10,YELLOW);}
			}
			
			//make the tail of the snake disappear
			if(period!=0){GUI_Box(snake.X_coordinate[snake.Long-1],snake.Y_coordinate[snake.Long-1],snake.X_coordinate[snake.Long-1]+10,snake.Y_coordinate[snake.Long-1]+10,DARKBLUE);}
			else{GUI_Box(snake.X_coordinate[snake.Long-1],snake.Y_coordinate[snake.Long-1],snake.X_coordinate[snake.Long-1]+10,snake.Y_coordinate[snake.Long-1]+10,WHITE);}

			//End of snake
			
				
				
				
				
				
			/*-----------------Life Logic------------------*/
			
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


			
			
			
			//control the speed of the snake 
			delay_ms(speed); //easy:300 normal:100 hard:50
			if(speed > 10) { if(count == 45) { speed=speed-10; count = 0;}}
			count++;
			
			GPIOB->BRR = 1 << 8;
			//if(snake.Long == 30){break;}
		}	
}
