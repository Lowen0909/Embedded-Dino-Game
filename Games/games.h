#ifndef _GAMES_H_
#define _GAMES_H_

#include "image.h"
#include "LCD_Test.h"
#include "LCD_1in14.h"
#include "DEV_Config.h"


typedef struct obs{
	unsigned char*image;
	uint16_t w;
	uint16_t h;
	int16_t x;
	int16_t y;
	uint8_t vis;
	uint8_t active;
}obstacle;

extern volatile int8_t jump;
extern volatile int8_t squat;
void dino_map();
void dino_move();
void Dino_Init();
void Dino_Game();
//char collision(int8_t);
//void score();
//void set_level(uint8_t);

void Kart_Init();
void kart_map();
void kart_move();
void Kart_Game();

//void menu();
void Clear_Screen();
#endif
