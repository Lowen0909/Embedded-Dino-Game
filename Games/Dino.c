#include "games.h"
//variable declaration
static obstacle Boat;
static obstacle Runner;
static obstacle Cactus;
static obstacle Rock;
static obstacle Pyrimid;
static obstacle Dino_j;
static obstacle Dino_s;
static obstacle Meteor;


//function def
static void set_level(uint8_t);
static char collision(int8_t);
static void score();

obstacle *obstacles[] = {
    &Boat,
    &Runner,
    &Cactus,
    &Rock,
	&Meteor,
	&Pyrimid

};
static uint16_t levels[][6]={
	{0,0,1,0,1,0},
	{0,1,1,1,1,0},
	{1,1,1,1,1,1}
};
uint16_t* map_num;
static int8_t tail,head;
int8_t jump=0,squat=0;
int8_t buzz=0;
int16_t counter=5;
static int32_t distance=0;
static int8_t stage=0;
//function definition
static void set_level(uint8_t level){
	map_num=levels[level];
	int16_t prev=200;
	for(int i=0;i<6;i++){
		if(map_num[i]){
			if(prev==200)
				head=i;
			printf("active");
			obstacles[i]->active=1;
			obstacles[i]->x=prev;
			prev=obstacles[i]->x+obstacles[i]->w+60;
			tail=i;
		}
	}
}

void Dino_Init(){
	Boat=(obstacle){.image=boat,.w=30,.h=15,.x=200,.y=135-15,.vis=0,.active=0};
	Runner=(obstacle){.image=runner,.w=16,.h=20,.x=200,.y=135-20,.vis=0,.active=0};
	Cactus=(obstacle){.image=cactus,.w=24,.h=28,.x=200,.y=135-28,.vis=0,.active=0};
	Rock=(obstacle){.image=rock,.w=16,.h=7,.x=200,.y=135-7,.vis=0,.active=0};
	Pyrimid=(obstacle){.image=pyrimid,.w=24,.h=13,.x=200,.y=135-13,.vis=0,.active=0};
	Meteor=(obstacle){.image=meteor,.w=12,.h=10,.x=200,.y=135-15-10,.vis=0,.active=0};
	set_level(0);
	//dino moves
	Dino_j.image=dino_jump;Dino_j.w=26;Dino_j.h=27;Dino_j.y=135-Dino_j.h;
	Dino_s.image=dino_squat;Dino_s.w=40;Dino_s.h=12;Dino_s.y=135-Dino_s.h;
	Paint_DrawString_EN(100,1,"Score:",&Font20,0xFFFF,0x0000);
	Paint_DrawString_EN(50,65,"Game Start!",&Font20,0xFFFF,0xF800);
	DEV_Delay_ms(800);
	Paint_DrawString_EN(50,65,"Game Start!",&Font20,0xFFFF,0xFFFF);
}



static char collision(int8_t squat){
	printf("squat %d\r\n",squat);
	obstacle*Dino;
	if(squat)
		Dino=&Dino_s;
	else
		Dino=&Dino_j;
	uint16_t x,y,w,h;
	uint32_t size=sizeof(obstacles)/sizeof(obstacles[0]);
	for(int i=0;i<size;i++){
		if(!obstacles[i]->active)
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
		if(HAL_GPIO_ReadPin(buzzer_GPIO_Port, buzzer_Pin) == GPIO_PIN_SET){
			HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin,GPIO_PIN_RESET);
		}
		Paint_DrawString_EN(55,65,"Game Over",&Font20,0xFFFF,0xF800);
		return 1;//overlap
	}
	return 0;
}


void dino_map(){
//	static int16_t pos=200;

	int8_t speed;
	switch(stage){
		case 0:
			speed=10;
			break;
		case 1:
			speed=15;
			break;
		case 2:
			speed=20;
			break;
		default:
			Paint_DrawString_EN(50,35,"Congrats!",&Font20,0xFFFF,0x0000);
			Paint_DrawString_EN(25,65,"You beat the game!",&Font16,0xFFFF,0x0000);
			break;
	}
	if(stage>2)
		return;


	uint32_t size=sizeof(obstacles)/sizeof(obstacles[0]);
	for(int i=0;i<size;i++){
		if(!obstacles[i]->active)
			continue;
		if(obstacles[i]->x<=200||obstacles[i]->vis)
			Paint_DrawImage_new(obstacles[i]->image,obstacles[i]->w*obstacles[i]->h*2,obstacles[i]->x,obstacles[i]->y,obstacles[i]->w,obstacles[i]->h);

	}
	DEV_Delay_ms(100);

	for(int i=0;i<size;i++){
		if(!obstacles[i]->active)
			continue;
		if(obstacles[i]->x<=200)
			LCD_partial_Clear(obstacles[i]->x,obstacles[i]->y,obstacles[i]->w,obstacles[i]->h);
		obstacles[i]->x-=speed;

		if(obstacles[i]->x<0){
			obstacles[i]->x=(obstacles[tail]->x-speed>=200)?obstacles[tail]->x+obstacles[tail]->w+60-speed:260;
			tail=i;
		}
	}

	score();
	DEV_Delay_ms(10);
}

void dino_move(){
	int16_t pos1=10;
	Dino_j.x=pos1;
	if(!jump&&!squat){
		Paint_DrawImage_new(Dino_j.image,Dino_j.w*Dino_j.h*2, pos1,Dino_j.y,Dino_j.w,Dino_j.h);
		Dino_j.y=135-Dino_j.h;
	}
//	Paint_DrawImage(cactus,pos,107,24,28);
//	printf("Dino Position is %d\r\n",pos1);


	if(jump&&(counter==5)){
//		DEV_Delay_ms(5);
		LCD_partial_Clear(pos1,Dino_j.y,Dino_j.w,Dino_j.h);
		Dino_j.y=135-30-Dino_j.h;
		Paint_DrawImage_new(Dino_j.image,Dino_j.w*Dino_j.h*2, pos1,Dino_j.y,Dino_j.w,Dino_j.h);
		buzz=1;
		counter--;
	}else if(jump&&counter){
		counter--;
//		printf("\rJump counter %d\n",counter);
	}else if(jump){
		jump=0;
		counter=5;
//		printf("\rafter jump clear\n");
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
//		printf("\rSquat counter %d\n",counter);
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
static char col=0;
void Dino_Game(){
	if(!col){
		dino_map();
		dino_move();
		col=collision(squat);
	}
}
