#include "games.h"

//motion sensor
#include "MY_LIS3DSH.h"
#include <math.h>


static obstacle RKart;
static obstacle BKart1;
static obstacle YKart1;
static obstacle BKart2;
static obstacle YKart2;
static obstacle BKart3;
static obstacle YKart3;

uint8_t data_ready=0;
static int32_t distance=0;
static int8_t stage=0;
static void score();
static void set_level(uint8_t);
static char collision();

obstacle* Karts[]={
		&BKart1,
		&YKart1,
		&BKart2,
		&YKart2,
		&BKart3,
		&YKart3
};

static uint8_t levels[][6]={
	{1,1,1,0,0,0},
	{1,1,1,1,0,0},
	{1,1,1,1,1,1},
};

int16_t pos_x[][6]={
	{190,310,430,0,0,0},
	{190,320,450,450,0,0},
	{190,320,450,580,580,710}
};

int16_t pos_y[][6]={
	{52,4,85,0,0,0},
	{33,4,101,52,0,0},
	{85,33,85,20,85,52}
};

static uint32_t size=sizeof(Karts)/sizeof(Karts[0]);
static int tail=0;
static char col=0;
int16_t prev_y=0;

static void set_level(uint8_t l){
	tail=190;
	for(int i=0;i<size;i++){
		if(levels[l][i]){
			Karts[i]->x=pos_x[l][i];
			Karts[i]->y=pos_y[l][i];
			Karts[i]->active=1;
			tail=i;
		}else
			Karts[i]->active=0;
	}
}
void Kart_Init(){
	stage=0;
	data_ready=0;
	distance=0;
	tail=0;
	col=0;
	prev_y=0;

	RKart=(obstacle){.image=RedKart,.w=50,.h=29,.x=10,.y=52,.vis=1,.active=1};
	BKart1=(obstacle){.image=BlueKart,.w=50,.h=29,.active=1};
	YKart1=(obstacle){.image=YellowKart,.w=50,.h=29,.active=1};
	BKart2=(obstacle){.image=BlueKart,.w=50,.h=29,.active=1};
	YKart2=(obstacle){.image=YellowKart,.w=50,.h=29,.active=1};
	BKart3=(obstacle){.image=BlueKart,.w=50,.h=29,.x=10,.active=1};
	YKart3=(obstacle){.image=YellowKart,.w=50,.h=29,.active=1};
	Paint_DrawString_EN(100,1,"Score:",&Font20,0xFFFF,0x0000);
	set_level(stage);
	Paint_DrawString_EN(50,65,"Game Start!",&Font20,0xFFFF,0xF800);
	DEV_Delay_ms(800);
	Paint_DrawString_EN(50,65,"Game Start!",&Font20,0xFFFF,0xFFFF);
	Paint_DrawImage_new(RKart.image,RKart.w*RKart.h*2, RKart.x,RKart.y,RKart.w,RKart.h);
}



void kart_map(){
	if(stage>2){
		Paint_DrawString_EN(50,35,"Congrats!",&Font20,0xFFFF,0x0000);
		Paint_DrawString_EN(25,65,"You beat the game!",&Font16,0xFFFF,0x0000);
		return;
	}
	int8_t speed=10;

	for(int i=0;i<size;i++){
		if(Karts[i]->active&&Karts[i]->x>=0&&Karts[i]->x<=190){
			Paint_DrawImage_new(Karts[i]->image,Karts[i]->w*Karts[i]->h*2,Karts[i]->x,Karts[i]->y,Karts[i]->w,Karts[i]->h);
		}
	}
	DEV_Delay_ms(100);
	for(int i=0;i<size;i++){
		if(Karts[i]->active&&Karts[i]->x>=0&&Karts[i]->x<=190){
			LCD_partial_Clear(Karts[i]->x,Karts[i]->y,Karts[i]->w,Karts[i]->h);
		}
		if(Karts[i]->active&&Karts[i]->x-speed<0){
			if(i!=tail&&pos_x[stage][i]==pos_x[stage][tail])
				Karts[i]->x=Karts[tail]->x;
			else
				Karts[i]->x=Karts[tail]->x-speed+130;
			tail=i;
		}else
			Karts[i]->x-=speed;
	}
	score();
}


void kart_move(){
	float pitch=0;
	LIS3DSH_DataScaled myData;
	if(data_ready){
		prev_y=RKart.y;
		data_ready=0;
		myData = LIS3DSH_GetDataScaled();
		printf("x:%f z:%f\r\n",myData.x,myData.z);
		pitch = atan2f(myData.x, myData.z) * (180.0f / M_PI);
		printf("angle is : %f\r\n",pitch);
		if(pitch<=160&&pitch>=135)
			RKart.y=85;
		else if(pitch<135&&pitch>=90)
			RKart.y=101;
		else if(pitch>=-160&&pitch<=-135)
			RKart.y=33;
		else if(pitch>-135&&pitch<=-90)
			RKart.y=4;
		else
			RKart.y=52;
		if(RKart.y!=prev_y){
			LCD_partial_Clear(RKart.x,prev_y,RKart.w,RKart.h);
			DEV_Delay_ms(10);
			Paint_DrawImage_new(RKart.image,RKart.w*RKart.h*2, RKart.x,RKart.y,RKart.w,RKart.h);
			DEV_Delay_ms(10);
		}
	}
}

static char collision(){
	uint16_t x,y,w,h;
	for(int i=0;i<size;i++){
		if(!Karts[i]->active)
			continue;
		x=Karts[i]->x;
		y=Karts[i]->y;
		w=Karts[i]->w;
		h=Karts[i]->h;
		if(RKart.x+RKart.w<=x)//dino is on the left of obstacle
			continue;
		if(RKart.x>=x+w)//dino is on the right of obstacle
			continue;
		if(RKart.y+RKart.h<=y)//dino is on the top of obstacle
			continue;
		if(RKart.y>=y+h)//dino is on the bottm of obstacle
			continue;
		Paint_DrawString_EN(45,65,"Game Over",&Font20,0xFFFF,0xF800);
		return 1;//overlap
	}
	return 0;
}
static void score(){
	if(++distance<50)
		Paint_DrawNum(191,1,distance,&Font20,0xFFFF,0x0000);
	else if(distance<100)
		Paint_DrawNum(191,1,distance,&Font20,0xFFFF,0xF800);
	else{
		Paint_DrawNum(191,1,--distance,&Font20,0xFFFF,0xFFFF);
		distance=0;
		stage++;
		set_level(stage);
		if(stage<3){
			Paint_DrawString_EN(40,35,"Entering next level ...",&Font20,0xFFFF,0x0000);
			DEV_Delay_ms(2000);
			Paint_DrawString_EN(40,35,"Entering next level ...",&Font20,0xFFFF,0xFFFF);
		}

	}
}


void Kart_Game(){
	if(!col){
		kart_map();
		kart_move();
		col=collision();
	}
}
void Clear_Screen(){
	LCD_1IN14_Clear(0xFFFF);
}
