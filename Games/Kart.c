#include "games.h"

static obstacle RKart;
static obstacle BKart;
static obstacle YKart;

void kart_init(){
	RKart=(obstacle){.image=YellowKart,.w=50,.h=29,.x=10,.y=52,.vis=1,.active=1};
	Paint_DrawString_EN(100,1,"Score:",&Font20,0xFFFF,0x0000);
}

void kart_map(){
	Paint_DrawImage_new(RKart.image,RKart.w*RKart.h*2, RKart.x,RKart.y,RKart.w,RKart.h);
}
int move[5]={-1,0,1,0,-1};
int i=0;
void kart_move(){
	LCD_partial_Clear(RKart.x,RKart.y,RKart.w,RKart.h);
	switch(move[i]){
		case -1:
			RKart.y=4;
			break;
		case 1:
			RKart.y=101;
			break;
		default:
			RKart.y=52;
			break;
	}
	DEV_Delay_ms(10);
	Paint_DrawImage_new(RKart.image,RKart.w*RKart.h*2, RKart.x,RKart.y,RKart.w,RKart.h);
	DEV_Delay_ms(10);
	i++;
	i%=5;
}
