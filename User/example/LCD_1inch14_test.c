#include "image.h"
#include "LCD_Test.h"
#include "LCD_1in14.h"
#include "DEV_Config.h"

//void LCD_1in14_test()
//{
//	printf("LCD_1IN14_test Demo\r\n");
//	DEV_Module_Init();
//
//  printf("LCD_1IN14_ Init and Clear...\r\n");
//	LCD_1IN14_SetBackLight(2000);
//	LCD_1IN14_Init(HORIZONTAL);
//	LCD_1IN14_Clear(WHITE);
//
//  printf("Paint_NewImage\r\n");
//	Paint_NewImage(LCD_1IN14.WIDTH,LCD_1IN14.HEIGHT,ROTATE_0, WHITE);
//
//  printf("Set Clear and Display Funtion\r\n");
//	Paint_SetClearFuntion(LCD_1IN14_Clear);
//	Paint_SetDisplayFuntion(LCD_1IN14_DrawPaint);
//
//  printf("Paint_Clear\r\n");
//  Paint_Clear(WHITE);
//  DEV_Delay_ms(100);
//
//  printf("drawing...\r\n");
//
//
//  Paint_DrawPoint(2,1, BLACK, DOT_PIXEL_1X1,  DOT_FILL_RIGHTUP);//240 240
//  Paint_DrawPoint(2,6, BLACK, DOT_PIXEL_2X2,  DOT_FILL_RIGHTUP);
//  Paint_DrawPoint(2,11, BLACK, DOT_PIXEL_3X3, DOT_FILL_RIGHTUP);
//  Paint_DrawPoint(2,16, BLACK, DOT_PIXEL_4X4, DOT_FILL_RIGHTUP);
//  Paint_DrawPoint(2,21, BLACK, DOT_PIXEL_5X5, DOT_FILL_RIGHTUP);
//  Paint_DrawLine( 10,  5, 40, 35, MAGENTA, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
//	Paint_DrawLine( 10, 35, 40,  5, MAGENTA, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
//
//  Paint_DrawLine( 80,  20, 110, 20, CYAN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
//	Paint_DrawLine( 95,   5,  95, 35, CYAN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
//
//  Paint_DrawRectangle(10, 5, 40, 35, RED, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
//  Paint_DrawRectangle(45, 5, 75, 35, BLUE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
//
//  Paint_DrawCircle(95, 20, 15, GREEN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
//  Paint_DrawCircle(130, 20, 15, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//
//
//  Paint_DrawFloatNum (50, 40 ,9.87654321,3, &Font20,  WHITE,  BLACK);
//	Paint_DrawString_EN(1, 40, "ABC", &Font20, 0x000f, 0xfff0);
//	Paint_DrawString_CN(1,60, "΢ѩ����",  &Font24CN, WHITE, BLUE);
//  Paint_DrawString_EN(1, 100, "WaveShare", &Font16, RED, WHITE);
//  Paint_DrawImage(gImage_1,160,70,60,60);
//  Paint_DrawImage(dino_jump,160,10,28,26);
//  /*
//  Paint_Clear(WHITE);
//
//  Paint_DrawImage(gImage_1,80,10,60,60);
//	*/
//
//
//	printf("quit...\r\n");
//	//DEV_Module_Exit();
//
//}

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




////variable declaration
//static obstacle Boat;
//static obstacle Runner;
//static obstacle Cactus;
//static obstacle Rock;
//static obstacle Pyrimid;
//static obstacle Dino_j;
//static obstacle Dino_s;
//static obstacle Meteor;
//
//obstacle *obstacles[] = {
//    &Boat,
//    &Runner,
//    &Cactus,
//    &Rock,
//	&Meteor,
//	&Pyrimid
//
//};
//uint16_t levels[][6]={
//	{0,0,1,0,1,0},
//	{0,1,1,1,1,0},
//	{1,1,1,1,1,1}
//};
//uint16_t* map_num;
//int8_t tail,head;
//int8_t jump=0,squat=0;
//int8_t buzz=0;
//int16_t counter=5;
//int32_t distance=0;
//int8_t stage=0;
////function definition
//void map_init(){
//	Boat=(obstacle){.image=boat,.w=30,.h=15,.x=200,.y=135-15,.vis=0,.active=0};
//	Runner=(obstacle){.image=runner,.w=16,.h=20,.x=200,.y=135-20,.vis=0,.active=0};
//	Cactus=(obstacle){.image=cactus,.w=24,.h=28,.x=200,.y=135-28,.vis=0,.active=0};
//	Rock=(obstacle){.image=rock,.w=16,.h=7,.x=200,.y=135-7,.vis=0,.active=0};
//	Pyrimid=(obstacle){.image=pyrimid,.w=24,.h=13,.x=200,.y=135-13,.vis=0,.active=0};
//	Meteor=(obstacle){.image=meteor,.w=12,.h=10,.x=200,.y=135-15-10,.vis=0,.active=0};
//	set_level(0);
//	//dino moves
//	Dino_j.image=dino_jump;Dino_j.w=26;Dino_j.h=27;Dino_j.y=135-Dino_j.h;
//	Dino_s.image=dino_squat;Dino_s.w=40;Dino_s.h=12;Dino_s.y=135-Dino_s.h;
//	Paint_DrawString_EN(100,1,"Score:",&Font20,0xFFFF,0x0000);
//}
//
//void set_level(uint8_t level){
//	map_num=levels[level];
//	int16_t prev=200;
//	for(int8_t i=0;i<6;i++){
//		if(map_num[i]){
//			if(prev==200)
//				head=i;
//			printf("active");
//			obstacles[i]->active=1;
//			obstacles[i]->x=prev;
//			prev=obstacles[i]->x+obstacles[i]->w+60;
//			tail=i;
//		}
//	}
//}
//
//char collision(int8_t squat){
//	obstacle*Dino;
//	if(squat)
//		Dino=&Dino_s;
//	else
//		Dino=&Dino_j;
//	uint16_t x,y,w,h;
//	uint32_t size=sizeof(obstacles)/sizeof(obstacles[0]);
//	for(int i=0;i<size;i++){
//		if(!obstacles[i]->active)
//			continue;
//		x=obstacles[i]->x;
//		y=obstacles[i]->y;
//		w=obstacles[i]->w;
//		h=obstacles[i]->h;
//		if(Dino->x+Dino->w<=x)//dino is on the left of obstacle
//			continue;
//		if(Dino->x>=x+w)//dino is on the right of obstacle
//			continue;
//		if(Dino->y+Dino->h<=y)//dino is on the top of obstacle
//			continue;
//		if(Dino->y>=y+h)//dino is on the bottm of obstacle
//			continue;
//		if(buzz)
//			buzz=0;
//		Paint_DrawString_EN(45,65,"Game Over",&Font20,0xFFFF,0xF800);
//		return 1;//overlap
//	}
//	return 0;
//}
//
//
//void map(){
////	static int16_t pos=200;
//
//	int8_t speed;
//	switch(stage){
//		case 0:
//			speed=10;
//			break;
//		case 1:
//			speed=15;
//			break;
//		case 2:
//			speed=20;
//			break;
//		default:
//			Paint_DrawString_EN(50,35,"Congrats!",&Font20,0xFFFF,0x0000);
//			Paint_DrawString_EN(25,65,"You beat the game!",&Font16,0xFFFF,0x0000);
//			break;
//	}
//	if(stage>2)
//		return;
//
////	if(pos<=220&&pos>0&&Rock.vis==0){
////		Rock.x=200;Rock.vis=1;
////
////	}else if(Rock.x>220){
////		Rock.vis=0;
////		Rock.x-=20;
////	}else
////		Rock.vis=1;
////
////	if(pos<120&&pos>0&&Cactus.vis==0){
////		Cactus.x=200;Cactus.vis=1;
////
////	}else if(Cactus.x>220){
////		Cactus.vis=0;
////		Cactus.x-=20;
////	}else
////		Cactus.vis=1;
////
////	if(pos<50&&pos>0&&Meteor.vis==0){
////		Meteor.x=200;Meteor.vis=1;
////	}else if(Meteor.x>220){
////		Meteor.vis=0;
////		Meteor.x-=20;
////	}else
////		Meteor.vis=1;
////	Paint_DrawImage_new(Boat.image,Boat.w*Boat.h*2, (pos+96)%212,Boat.y,Boat.w,Boat.h);
////	Paint_DrawImage_new(Runner.image,Runner.w*Runner.h*2, (pos+72)%212,Runner.y,Runner.w,Runner.h);
////	if(Rock.vis)
////		Paint_DrawImage_new(Rock.image,Rock.w*Rock.h*2,Rock.x,Rock.y,Rock.w,Rock.h);
////	if(Meteor.vis)
////		Paint_DrawImage_new(Meteor.image,Meteor.w*Meteor.h*2,Meteor.x,Meteor.y,Meteor.w,Meteor.h);
////	if(Cactus.vis)
////		Paint_DrawImage_new(Cactus.image,Cactus.w*Cactus.h*2,Cactus.x,Cactus.y,Cactus.w,Cactus.h);
//
//
////	printf("Obstacle Position is %d\r\n",pos);
//	uint32_t size=sizeof(obstacles)/sizeof(obstacles[0]);
//	for(int i=0;i<size;i++){
//		if(!obstacles[i]->active)
//			continue;
//		if(obstacles[i]->x<=200||obstacles[i]->vis)
//			Paint_DrawImage_new(obstacles[i]->image,obstacles[i]->w*obstacles[i]->h*2,obstacles[i]->x,obstacles[i]->y,obstacles[i]->w,obstacles[i]->h);
//
//	}
//	DEV_Delay_ms(100);
//
//	for(int i=0;i<size;i++){
//		if(!obstacles[i]->active)
//			continue;
//		if(obstacles[i]->x<=200)
//			LCD_partial_Clear(obstacles[i]->x,obstacles[i]->y,obstacles[i]->w,obstacles[i]->h);
//		obstacles[i]->x-=speed;
//
//		if(obstacles[i]->x<0){
//			obstacles[i]->x=(obstacles[tail]->x-speed>=200)?obstacles[tail]->x+obstacles[tail]->w+60-speed:260;
//			tail=i;
//		}
//	}
//
//
////	if(pos>0)
////		pos-=speed;
//	score();
//	DEV_Delay_ms(10);
//}
//
//void dino(){
//	int16_t pos1=10;
//	Dino_j.x=pos1;
//	if(!jump&&!squat){
//		Paint_DrawImage_new(Dino_j.image,Dino_j.w*Dino_j.h*2, pos1,Dino_j.y,Dino_j.w,Dino_j.h);
//		Dino_j.y=135-Dino_j.h;
//	}
////	Paint_DrawImage(cactus,pos,107,24,28);
////	printf("Dino Position is %d\r\n",pos1);
//
//
//	if(jump&&(counter==5)){
////		DEV_Delay_ms(5);
//		LCD_partial_Clear(pos1,Dino_j.y,Dino_j.w,Dino_j.h);
//		Dino_j.y=135-30-Dino_j.h;
//		Paint_DrawImage_new(Dino_j.image,Dino_j.w*Dino_j.h*2, pos1,Dino_j.y,Dino_j.w,Dino_j.h);
//		buzz=1;
//		counter--;
//	}else if(jump&&counter){
//		counter--;
////		printf("\rJump counter %d\n",counter);
//	}else if(jump){
//		jump=0;
//		counter=5;
////		printf("\rafter jump clear\n");
//		LCD_partial_Clear(pos1,Dino_j.y,Dino_j.w,Dino_j.h);
//		Dino_j.y=135-Dino_j.h;
//	}
//
//	if(squat&&(counter==5)){
//		Dino_s.x=pos1;
//		LCD_partial_Clear(pos1,135-Dino_j.h,Dino_j.w,Dino_j.h);
//		Paint_DrawImage_new(Dino_s.image,Dino_s.w*Dino_s.h*2, pos1,Dino_s.y,Dino_s.w,Dino_s.h);
//		buzz=1;
//		counter--;
//	}else if(squat&&counter){
//		counter--;
////		printf("\rSquat counter %d\n",counter);
//	}else if(squat){
//		squat=0;
//		counter=5;
//		LCD_partial_Clear(pos1,135-Dino_s.h,Dino_s.w,Dino_s.h);
//	}
//
//	if(buzz==1){
//		HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin,GPIO_PIN_SET);
//		buzz=0;
//	}else
//		HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin,GPIO_PIN_RESET);
//
////	printf("%d\n",counter);
//	DEV_Delay_ms(10);
//}
//void score(){
//	if(++distance<50)
//		Paint_DrawNum(191,1,distance,&Font20,0xFFFF,0x0000);
//	else if(distance<100)
//		Paint_DrawNum(191,1,distance,&Font20,0xFFFF,0xF800);
//	else{
//		Paint_DrawNum(191,1,--distance,&Font20,0xFFFF,0xFFFF);
//		distance=0;
//		stage++;
//		set_level(stage);
//		if(stage<3){
//			Paint_DrawString_EN(40,35,"Entering next level ...",&Font20,0xFFFF,0x0000);
//			DEV_Delay_ms(2000);
//			Paint_DrawString_EN(40,35,"Entering next level ...",&Font20,0xFFFF,0xFFFF);
//		}
//
//	}
//
//}

