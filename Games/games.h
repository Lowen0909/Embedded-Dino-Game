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

extern int8_t jump;
extern int8_t squat;
void map();
void dino();
void map_init();
char collision(int8_t);
//void score();
//void set_level(uint8_t);

void kart_init();
void kart_map();
void kart_move();
//void MEMS_Write(uint8_t address,uint8_t data);
//void MEMS_Read(uint8_t address,uint8_t *data);
#endif
