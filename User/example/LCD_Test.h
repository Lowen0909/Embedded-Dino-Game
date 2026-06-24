/*****************************************************************************
* | File      	:	LCD_Test.h
* | Author      :   Waveshare team
* | Function    :   LCD test Demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-06-09
* | Info        :   
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _EPD_TEST_H_
#define _EPD_TEST_H_

#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "Debug.h"
#include <stdlib.h> // malloc() free()

//typedef struct obs{
//	unsigned char*image;
//	uint16_t w;
//	uint16_t h;
//	int16_t x;
//	int16_t y;
//	uint8_t vis;
//	uint8_t active;
//}obstacle;
//
//extern int8_t jump;
//extern int8_t squat;
//void LCD_1in14_test(void);
//void map();
void lcd_init();
//void dino();
//void map_init();
//char collision(int8_t);
//void score();
//void set_level(uint8_t);
#endif
