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
	{190,310,310,430,0,0},
	{190,310,430,550,550,670}
};
int16_t pos_y[][6]={
	{52,4,85,0,0,0},
	{33,4,101,52,0,0},
	{85,33,85,33,85,52}
};
static void set_level(uint8_t l){
	for(int i=0;i<6;i++){
		if(levels[l][i]){
			Karts[i]->x=pos_x[l][i];
			Karts[i]->y=pos_y[l][i];
			Karts[i]->active=1;
		}else
			Karts[i]->active=0;
	}
}
void kart_init(){
	RKart=(obstacle){.image=RedKart,.w=50,.h=29,.x=10,.y=52,.vis=1,.active=1};
	BKart1=(obstacle){.image=BlueKart,.w=50,.h=29,.active=1};
	YKart1=(obstacle){.image=YellowKart,.w=50,.h=29,.active=1};
	BKart2=(obstacle){.image=BlueKart,.w=50,.h=29,.active=1};
	YKart2=(obstacle){.image=YellowKart,.w=50,.h=29,.active=1};
	BKart3=(obstacle){.image=BlueKart,.w=50,.h=29,.x=10,.active=1};
	YKart3=(obstacle){.image=YellowKart,.w=50,.h=29,.active=1};
	Paint_DrawString_EN(100,1,"Score:",&Font20,0xFFFF,0x0000);
	Paint_DrawImage_new(RKart.image,RKart.w*RKart.h*2, RKart.x,RKart.y,RKart.w,RKart.h);
	set_level(2);
}



void kart_map(){
	int8_t speed=10;
	uint32_t size=sizeof(Karts)/sizeof(Karts[0]);
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
		Karts[i]->x-=speed;
	}
}

int16_t prev_y=0;
void kart_move(){
	float pitch=0;
	LIS3DSH_DataScaled myData;
	if(data_ready){
		prev_y=RKart.y;
		data_ready=0;
		myData = LIS3DSH_GetDataScaled();
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
