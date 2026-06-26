#include "image.h"
#include "LCD_Test.h"
#include "LCD_1in14.h"
#include "DEV_Config.h"

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






