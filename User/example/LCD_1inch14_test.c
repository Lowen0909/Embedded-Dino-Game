#include "image.h"
#include "LCD_Test.h"
#include "LCD_1in14.h"
#include "DEV_Config.h"

void LCD_1in14_test()
{
	printf("LCD_1IN14_test Demo\r\n");
	DEV_Module_Init();
  
  printf("LCD_1IN14_ Init and Clear...\r\n");
	LCD_1IN14_SetBackLight(2000);
	LCD_1IN14_Init(HORIZONTAL);
	LCD_1IN14_Clear(WHITE);
  
  printf("Paint_NewImage\r\n");
	Paint_NewImage(LCD_1IN14.WIDTH,LCD_1IN14.HEIGHT,ROTATE_0, WHITE);
  
  printf("Set Clear and Display Funtion\r\n");
	Paint_SetClearFuntion(LCD_1IN14_Clear);
	Paint_SetDisplayFuntion(LCD_1IN14_DrawPaint);
  
  printf("Paint_Clear\r\n");
  Paint_Clear(WHITE);
  DEV_Delay_ms(100);
  
  printf("drawing...\r\n");
  
  
  Paint_DrawPoint(2,1, BLACK, DOT_PIXEL_1X1,  DOT_FILL_RIGHTUP);//240 240
  Paint_DrawPoint(2,6, BLACK, DOT_PIXEL_2X2,  DOT_FILL_RIGHTUP);
  Paint_DrawPoint(2,11, BLACK, DOT_PIXEL_3X3, DOT_FILL_RIGHTUP);
  Paint_DrawPoint(2,16, BLACK, DOT_PIXEL_4X4, DOT_FILL_RIGHTUP);
  Paint_DrawPoint(2,21, BLACK, DOT_PIXEL_5X5, DOT_FILL_RIGHTUP);
  Paint_DrawLine( 10,  5, 40, 35, MAGENTA, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
	Paint_DrawLine( 10, 35, 40,  5, MAGENTA, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
  
  Paint_DrawLine( 80,  20, 110, 20, CYAN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawLine( 95,   5,  95, 35, CYAN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  
  Paint_DrawRectangle(10, 5, 40, 35, RED, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
  Paint_DrawRectangle(45, 5, 75, 35, BLUE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
  
  Paint_DrawCircle(95, 20, 15, GREEN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawCircle(130, 20, 15, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  
  
  Paint_DrawFloatNum (50, 40 ,9.87654321,3, &Font20,  WHITE,  BLACK);
	Paint_DrawString_EN(1, 40, "ABC", &Font20, 0x000f, 0xfff0);
	Paint_DrawString_CN(1,60, "΢ѩ����",  &Font24CN, WHITE, BLUE);
  Paint_DrawString_EN(1, 100, "WaveShare", &Font16, RED, WHITE);
  Paint_DrawImage(gImage_1,160,70,60,60);
  Paint_DrawImage(dino_jump,160,10,28,26);
  /*
  Paint_Clear(WHITE);
	
  Paint_DrawImage(gImage_1,80,10,60,60);
	*/
	
	
	printf("quit...\r\n");
	//DEV_Module_Exit();
  
}

void lcd_init(){
	DEV_Module_Init();
	LCD_1IN14_SetBackLight(3000);
	LCD_1IN14_Init(HORIZONTAL);
	LCD_1IN14_Clear(WHITE);
	Paint_NewImage(LCD_1IN14.WIDTH,LCD_1IN14.HEIGHT,ROTATE_0, WHITE);
	Paint_SetClearFuntion(LCD_1IN14_Clear);
//	Paint_SetDisplayFuntion(LCD_1IN14_DrawPaint);
	Paint_SetFlushFuntion(LCD_1IN14_DrawPaint_new);
}





static obstacle Boat;
static obstacle Runner;
static obstacle Cactus;
static obstacle Rock;
static obstacle Pyrimid;
static obstacle Dino_j;
static obstacle Dino_s;
static obstacle Meteor;

obstacle *obstacles[] = {
    &Boat,
    &Runner,
    &Cactus,
    &Rock,
	&Meteor,
	&Pyrimid

};

void map_init(){
	Boat.image=boat;Boat.w=30;Boat.h=15;Boat.y=135-Boat.h;Boat.vis=0;
	Runner.image=runner;Runner.w=16;Runner.h=20;Runner.y=135-Runner.h;Runner.vis=0;
	Cactus.image=cactus;Cactus.w=24;Cactus.h=28;Cactus.y=135-Cactus.h;Cactus.vis=0;
	Rock.image=rock;Rock.w=16;Rock.h=7;Rock.y=135-Rock.h;Rock.vis=0;
	Pyrimid.image=pyrimid;Pyrimid.w=24;Pyrimid.h=13;Pyrimid.y=135-Pyrimid.h;Pyrimid.vis=0;
	Meteor.image=meteor;Meteor.w=12;Meteor.h=10;Meteor.y=135-20-Meteor.h;Meteor.vis=0;
	//dino moves
	Dino_j.image=dino_jump;Dino_j.w=26;Dino_j.h=27;Dino_j.y=135-Dino_j.h;
	Dino_s.image=dino_squat;Dino_s.w=40;Dino_s.h=12;Dino_s.y=135-Dino_s.h;
}

int8_t jump=0,squat=0;
int8_t buzz=0;
int16_t counter=5;
char collision(int8_t squat){
	obstacle*Dino;
	if(squat)
		Dino=&Dino_s;
	else
		Dino=&Dino_j;
	uint16_t x,y,w,h;
	uint32_t size=sizeof(obstacles)/sizeof(obstacles[0]);
	for(int i=0;i<size;i++){
		if(!obstacles[i]->vis)
			continue;
		x=obstacles[i]->x;
		y=obstacles[i]->y;
		w=obstacles[i]->w;
		h=obstacles[i]->h;
		if(Dino->x+Dino->w<=x)//dino is on the left of obstacle
			continue;
		if(Dino->x>=x+w)//dino is on the right of obstacle
			continue;
		if(Dino->y+Dino->h<=y)//dino is on the top of obstacle
			continue;
		if(Dino->y>=y+h)//dino is on the bottm of obstacle
			continue;
		if(buzz)
			buzz=0;
		return 1;//overlap
	}
	return 0;
}


void map(){
	static int16_t pos=200;
	int8_t speed=8;

	if(pos>=200&&Rock.vis==0){
		Rock.x=200;Rock.vis=1;

	}

	if(pos<120&&Cactus.vis==0){
		Cactus.x=200;Cactus.vis=1;

	}

	if(pos<30&&Meteor.vis==0){
		Meteor.x=200;Meteor.vis=1;
	}
//	Paint_DrawImage_new(Boat.image,Boat.w*Boat.h*2, (pos+96)%212,Boat.y,Boat.w,Boat.h);
//	Paint_DrawImage_new(Runner.image,Runner.w*Runner.h*2, (pos+72)%212,Runner.y,Runner.w,Runner.h);
	if(Rock.vis)
		Paint_DrawImage_new(Rock.image,Rock.w*Rock.h*2,Rock.x,Rock.y,Rock.w,Rock.h);
	if(Meteor.vis)
		Paint_DrawImage_new(Meteor.image,Meteor.w*Meteor.h*2,Meteor.x,Meteor.y,Meteor.w,Meteor.h);
	if(Cactus.vis)
		Paint_DrawImage_new(Cactus.image,Cactus.w*Cactus.h*2,Cactus.x,Cactus.y,Cactus.w,Cactus.h);


	printf("Obstacle Position is %d\r\n",pos);
	DEV_Delay_ms(100);
//	LCD_partial_Clear((pos+96)%212,120,30,15);
	if(Meteor.vis)
		LCD_partial_Clear(Meteor.x,Meteor.y,Meteor.w,Meteor.h);
	if(Cactus.vis)
		LCD_partial_Clear(Cactus.x,Cactus.y,Cactus.w,Cactus.h);
    if(Rock.vis)
    	LCD_partial_Clear(Rock.x,Rock.y,Rock.w,Rock.h);
    uint32_t size=sizeof(obstacles)/sizeof(obstacles[0]);
	for(int i=0;i<size;i++){
		if(!obstacles[i]->vis)
			continue;
		obstacles[i]->x-=speed;
		if(obstacles[i]->x<0)
			obstacles[i]->x=200;
	}

	pos-=speed;
	if(pos<0)
		pos=200;

	DEV_Delay_ms(10);
}

void dino(){
	int16_t pos1=10;
	Dino_j.x=pos1;
	if(!jump&&!squat){
		Paint_DrawImage_new(Dino_j.image,Dino_j.w*Dino_j.h*2, pos1,Dino_j.y,Dino_j.w,Dino_j.h);
		Dino_j.y=135-Dino_j.h;
	}
//	Paint_DrawImage(cactus,pos,107,24,28);
	printf("Dino Position is %d\r\n",pos1);


	if(jump&&(counter==5)){
//		DEV_Delay_ms(5);
		LCD_partial_Clear(pos1,Dino_j.y,Dino_j.w,Dino_j.h);
		Dino_j.y=135-30-Dino_j.h;
		Paint_DrawImage_new(Dino_j.image,Dino_j.w*Dino_j.h*2, pos1,Dino_j.y,Dino_j.w,Dino_j.h);
		buzz=1;
		counter--;
	}else if(jump&&counter){
		counter--;
		printf("\rJump counter %d\n",counter);
	}else if(jump){
		jump=0;
		counter=5;
		printf("\rafter jump clear\n");
		LCD_partial_Clear(pos1,Dino_j.y,Dino_j.w,Dino_j.h);
		Dino_j.y=135-Dino_j.h;
	}

	if(squat&&(counter==5)){
		Dino_s.x=pos1;
		LCD_partial_Clear(pos1,135-Dino_j.h,Dino_j.w,Dino_j.h);
		Paint_DrawImage_new(Dino_s.image,Dino_s.w*Dino_s.h*2, pos1,Dino_s.y,Dino_s.w,Dino_s.h);
		buzz=1;
		counter--;
	}else if(squat&&counter){
		counter--;
		printf("\rSquat counter %d\n",counter);
	}else if(squat){
		squat=0;
		counter=5;
		LCD_partial_Clear(pos1,135-Dino_s.h,Dino_s.w,Dino_s.h);
	}

	if(buzz==1){
		HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin,GPIO_PIN_SET);
		buzz=0;
	}else
		HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin,GPIO_PIN_RESET);

//	printf("%d\n",counter);
	DEV_Delay_ms(10);
}

