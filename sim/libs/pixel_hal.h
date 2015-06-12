#ifndef __PIXEL_HAL_H
#define __PIXEL_HAL_H

#include <stdint.h>

#define LCD_PIXEL_WIDTH          24
#define LCD_PIXEL_HEIGHT         24

#define LCD_WIDTH  LCD_PIXEL_WIDTH          
#define LCD_HEIGHT LCD_PIXEL_HEIGHT     

void setLedXY(uint8_t x,uint8_t y, uint8_t r,uint8_t g,uint8_t b);
void getLedXY(uint8_t x, uint8_t y, uint8_t* r,uint8_t* g, uint8_t* b);
void invLedXY(uint8_t x, uint8_t y);
void sync_frame(void);
void clearDisplay(void);
#endif
