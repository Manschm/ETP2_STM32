 //============================================================================================================
 /*
 __  __                 _ _ _       _     _     ___   ___ ___   ___                             
 |  \/  |               | | (_)     | |   | |   |__ \ / _ \__ \ / _ \                            
 | \  / | ___   ___   __| | |_  __ _| |__ | |_     ) | | | | ) | | | |                           
 | |\/| |/ _ \ / _ \ / _` | | |/ _` | '_ \| __|   / /| | | |/ /| | | |                           
 | |  | | (_) | (_) | (_| | | | (_| | | | | |_   / /_| |_| / /_| |_| |                           
 |_|  |_|\___/ \___/ \__,_|_|_|\__, |_| |_|\__| |____|\___/____|\___/                            
                                __/ |                                                            
                       _   _   |___/          __           _               _             __ ___  
                      | | | |     | |        / /          | |             (_)           / /|__ \ 
   ___ _   _  __ _ ___| |_| |_   _| | __    / /   ___  ___| |__  _ __ ___  _ _ __ ___  / /_   ) |
  / _ \ | | |/ _` / __| __| | | | | |/ /   / /   / __|/ __| '_ \| '_ ` _ \| | '_ ` _ \| '_ \ / / 
 |  __/ |_| | (_| \__ \ |_| | |_| |   <   / /    \__ \ (__| | | | | | | | | | | | | | | (_) / /_ 
  \___|\__,_|\__, |___/\__|_|\__,_|_|\_\ /_/     |___/\___|_| |_|_| |_| |_|_|_| |_| |_|\___/____|
              __/ |                                                                              
             |___/                                                                               
*/
//============================================================================================================
/*******
 * Modified by schmim62
 * Date: 26.02.2020
 *******/

#ifndef __LCD_ST7565_H__
#define __LCD_ST7565_H__

#include "lcd_st7565_pinconf.h"

#include "font.h"
#include "string.h"
#include <stdlib.h>
#include "bitmaps.h"

// Commands from Datasheet
#define ST7565_CMD_DISPLAY_OFF            0xAE
#define ST7565_CMD_DISPLAY_ON             0xAF

#define ST7565_CMD_SET_DISP_START_LINE    0x40
#define ST7565_CMD_SET_PAGE               0xB0

#define ST7565_CMD_SET_COLUMN_UPPER       0x10
#define ST7565_CMD_SET_COLUMN_LOWER       0x00

#define ST7565_CMD_SET_ADC_NORMAL         0xA0
#define ST7565_CMD_SET_ADC_REVERSE        0xA1

#define ST7565_CMD_SET_DISP_NORMAL        0xA6
#define ST7565_CMD_SET_DISP_REVERSE       0xA7

#define ST7565_CMD_SET_ALLPTS_NORMAL      0xA4
#define ST7565_CMD_SET_ALLPTS_ON          0xA5
#define ST7565_CMD_SET_BIAS_9             0xA2
#define ST7565_CMD_SET_BIAS_7             0xA3

#define ST7565_CMD_RMW                    0xE0
#define ST7565_CMD_RMW_CLEAR              0xEE
#define ST7565_CMD_INTERNAL_RESET         0xE2
#define ST7565_CMD_SET_COM_NORMAL         0xC0
#define ST7565_CMD_SET_COM_REVERSE        0xC8
#define ST7565_CMD_SET_POWER_CONTROL      0x28
#define ST7565_CMD_SET_RESISTOR_RATIO     0x20
#define ST7565_CMD_SET_VOLUME_FIRST       0x81
#define ST7565_CMD_SET_VOLUME_SECOND      0
#define ST7565_CMD_SET_STATIC_OFF         0xAC
#define ST7565_CMD_SET_STATIC_ON          0xAD
#define ST7565_CMD_SET_STATIC_REG         0x0
#define ST7565_CMD_SET_BOOSTER_FIRST      0xF8
#define ST7565_CMD_SET_BOOSTER_234        0
#define ST7565_CMD_SET_BOOSTER_5          1
#define ST7565_CMD_SET_BOOSTER_6          3
#define ST7565_CMD_NOP                    0xE3
#define ST7565_CMD_TEST                   0xF0

// Initialisation/Config Prototypes
void st7565_init(void);
void st7565_set_brightness(uint8_t val);
void st7565_fade_out(uint8_t level);
void st7565_fade_in(uint8_t level);
void st7565_backlight_disable(void);
void st7565_backlight_enable(void);

//Work with LCD Prototypes
void st7565_sendbyte(uint8_t c);
void st7565_clear_screen(void);
void st7565_clear_buffer(uint8_t *buffer);
void st7565_write_buffer(uint8_t *buffer);;

//higher "draw"-prototypes
void st7565_drawstring(uint8_t *buff, uint8_t x, uint8_t line, uint8_t *c);
void st7565_drawchar(uint8_t *buff, uint8_t x, uint8_t line, uint8_t c);
void st7565_setpixel(uint8_t *buff, uint8_t x, uint8_t y, uint8_t color);
void st7565_clearpixel(uint8_t *buff, uint8_t x, uint8_t y);

void st7565_drawline(uint8_t *buff, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,uint8_t color);
void st7565_fillrect(uint8_t *buff, uint8_t x, uint8_t y, uint8_t w, uint8_t h,uint8_t color);
void st7565_drawrect(uint8_t *buff, uint8_t x, uint8_t y, uint8_t w, uint8_t h,uint8_t color);
void st7565_drawcircle(uint8_t *buff, uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);
void st7565_fillcircle(uint8_t *buff, uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);

//special "draw"-prototypes
void st7565_drawfallingbitmap(uint8_t *buff, const uint8_t *bitmap, uint8_t w, uint8_t h);
void st7565_drawbitmap(uint8_t *buff, uint8_t x, uint8_t y, const uint8_t *bitmap,uint8_t w, uint8_t h, uint8_t color);


// Added functions by Lukas Eugster
void st7565_drawfhd(uint8_t fhd, uint8_t *LCD_Buffer);
void st7565_drawshd(uint8_t shd, uint8_t* LCD_Buffer);
void st7565_drawdts(uint8_t* LCD_Buffer);
void st7565_drawfmd(uint8_t fmd, uint8_t* LCD_Buffer);
void st7565_drawsmd(uint8_t smd, uint8_t* LCD_Buffer);

void st7565_drawtempsymbol(uint8_t* LCD_Buffer);
void st7565_drawtemp(uint8_t temp[] , uint8_t* LCD_Buffer);

void st7565_drawhumidsymbol(uint8_t* LCD_Buffer);
void st7565_drawhumid(uint8_t hum[], uint8_t* LCD_Buffer);

void st7565_drawalarmsymbol(uint8_t* LCD_Buffer);
void st7565_drawsnsymbol(uint8_t* LCD_Buffer);




#endif
