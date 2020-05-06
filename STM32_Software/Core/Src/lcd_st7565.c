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

#include "lcd_st7565.h"

uint8_t buffer [1024];

uint8_t pagemap[] = {7,6,5,4,3,2,1,0};

#define LCDWIDTH 128
#define LCDHEIGHT 64

// Send command
void CMD(uint8_t command) {
		HAL_GPIO_WritePin(ST7565_PORT, ST7565_A0_PIN, GPIO_PIN_RESET);
		st7565_sendbyte(command);
}

// Send data
void DATA(uint8_t data) {
	HAL_GPIO_WritePin(ST7565_PORT, ST7565_A0_PIN, GPIO_PIN_SET);
	st7565_sendbyte(data);
}

// Delay in ms
void DELAY(uint32_t delay)
{
	HAL_Delay(delay);
}

//Renders the buffer contents
void st7565_write_buffer(uint8_t *buffer) {
	uint8_t c, p;
	for (p = 0; p < 8; p++) {
		CMD(ST7565_CMD_SET_PAGE | pagemap[p]);
		CMD(ST7565_CMD_SET_COLUMN_LOWER | (0x0 & 0xf));
		CMD(ST7565_CMD_SET_COLUMN_UPPER | ((0x0 >> 4) & 0xf));
		CMD(ST7565_CMD_RMW);
		//DATA(0xff);
		for (c = 0; c < 128; c++) {
			DATA(buffer[(128 * p) + c]);
		}
	}
}

// Simulates an SPI write using GPIO
// with byte, The byte to send
void st7565_sendbyte(uint8_t byte) {
	int8_t i;
	// Make sure clock pin starts high
	HAL_GPIO_WritePin(ST7565_PORT, ST7565_SCLK_PIN, GPIO_PIN_SET);
	// Write from MSB to LSB
	for (i = 7; i >= 0; i--) {
		// Set clock pin low
		HAL_GPIO_WritePin(ST7565_PORT, ST7565_SCLK_PIN, GPIO_PIN_RESET);
		// Set data pin high or low depending on the value of the current bit
		HAL_GPIO_WritePin(ST7565_PORT, ST7565_SDAT_PIN,	byte & (1 << i) ? 1 : 0);
		// Set clock pin high
		HAL_GPIO_WritePin(ST7565_PORT, ST7565_SCLK_PIN, GPIO_PIN_SET);
	}
}

//Initialises the ST7565 LCD display
void st7565_init(void) {
	// Set clock pin to high
	HAL_GPIO_WritePin(ST7565_PORT, ST7565_SCLK_PIN, GPIO_PIN_SET);
	// Set data pin to output and high
	HAL_GPIO_WritePin(ST7565_PORT, ST7565_SDAT_PIN, GPIO_PIN_SET);
	// Configure backlight A+ pin to output and set high (off)
	HAL_GPIO_WritePin(ST7565_PORT, ST7565_BL_PIN, GPIO_PIN_SET);

	// Configure A0 pin to output and set high
	HAL_GPIO_WritePin(ST7565_PORT, ST7565_A0_PIN, GPIO_PIN_SET);

	// Configure Reset pin and set high
	HAL_GPIO_WritePin(ST7565_PORT, ST7565_RST_PIN, GPIO_PIN_SET);

	// Configure select pin and set high
	HAL_GPIO_WritePin(ST7565_PORT, ST7565_CS_PIN, GPIO_PIN_SET);

	// Reset
	HAL_GPIO_WritePin(ST7565_PORT, ST7565_CS_PIN, GPIO_PIN_RESET);    // Set CS low
	HAL_GPIO_WritePin(ST7565_PORT, ST7565_RST_PIN, GPIO_PIN_RESET);   // Set reset low
	DELAY(500);                // Wait 500mS
	HAL_GPIO_WritePin(ST7565_PORT, ST7565_RST_PIN, GPIO_PIN_SET);   // Set reset high

	// Configure Display
	CMD(ST7565_CMD_SET_BIAS_7);                         // LCD Bias Select
	CMD(ST7565_CMD_SET_ADC_NORMAL);                     // ADC Select
	CMD(ST7565_CMD_SET_COM_NORMAL);                     // SHL Select
	CMD(ST7565_CMD_SET_DISP_START_LINE);                // Initial Display Line
	CMD(ST7565_CMD_SET_POWER_CONTROL | 0x04); // Turn on voltage converter (VC=1, VR=0, VF=0)
	DELAY(50);                // Wait 50mS
	CMD(ST7565_CMD_SET_POWER_CONTROL | 0x06); // Turn on voltage regulator (VC=1, VR=1, VF=0)
	DELAY(50);                // Wait 50mS
	CMD(ST7565_CMD_SET_POWER_CONTROL | 0x07);        // Turn on voltage follower
	DELAY(10);                // Wait 10mS
	CMD(ST7565_CMD_SET_RESISTOR_RATIO | 0x6);       // Set LCD operating voltage

	// Turn display on
	CMD(ST7565_CMD_DISPLAY_ON);
	CMD(ST7565_CMD_SET_ALLPTS_NORMAL);
	st7565_set_brightness(0x18);
	st7565_clear_screen();

	//Write the Adafruit-Logo, clear the buffer, wait and fade out
	//st7565_write_buffer(logosenso_glcd_bmp);
	//st7565_clear_buffer(logosenso_glcd_bmp);
	//DELAY(800);
	//st7565_fade_out(24);
}

//Enables the backlight
void st7565_backlight_enable(void) {
	HAL_GPIO_WritePin( ST7565_PORT, ST7565_BL_PIN, GPIO_PIN_SET);
}

///Disables the backlight
void st7565_backlight_disable(void) {
	HAL_GPIO_WritePin( ST7565_PORT, ST7565_BL_PIN, GPIO_PIN_RESET);
}

//Sets the display brightness
void st7565_set_brightness(uint8_t val) {
	CMD(ST7565_CMD_SET_VOLUME_FIRST);
	CMD(ST7565_CMD_SET_VOLUME_SECOND | (val & 0x3f));
}

// Fade out from max 64 to 0
void st7565_fade_out(uint8_t level) {
	uint8_t i = 0;
	for (i = level; i > 0; i--) {
		st7565_set_brightness(i);
		DELAY(100);
	}
}

// Fade in from 0 to max 64
void st7565_fade_in(uint8_t level) {
	uint8_t i = 0;
	for (i = 0; i < level; i++) {
		st7565_set_brightness(i);
		DELAY(100);
	}
}

//Clears the screen
void st7565_clear_screen(void) {
	uint8_t p, c;
	for (p = 0; p < 8; p++) {
		CMD(ST7565_CMD_SET_PAGE | p);
		for (c = 0; c < 129; c++) {
			CMD(ST7565_CMD_SET_COLUMN_LOWER | (c & 0xf));
			CMD(ST7565_CMD_SET_COLUMN_UPPER | ((c >> 4) & 0xf));
			DATA(0x0);
		}
	}
}

// clear everything
void st7565_clear_buffer(uint8_t *buff) {
	memset(buff, 0, 1024);
}

#define ANZAHL 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
void st7565_drawfallingbitmap(uint8_t *buff, const uint8_t *bitmap, uint8_t w, uint8_t h) {
	uint8_t icons[ANZAHL][3];
	srand(buff[666]);
// initialize
	uint8_t f = 0;
	for (f = 0; f < ANZAHL; f++) {
		icons[f][XPOS] = rand() % 128;
		icons[f][YPOS] = 0;
		icons[f][DELTAY] = rand() % 5 + 1;
	}
	while (1) {
// draw each icon
		for (f = 0; f < ANZAHL; f++) {
			st7565_drawbitmap(buffer, icons[f][XPOS], icons[f][YPOS], bitmap, w,
					h, 1);
		}
		DELAY(200);
		st7565_write_buffer(buffer);
// then erase it + move it
		for (f = 0; f < ANZAHL; f++) {
			st7565_drawbitmap(buffer, icons[f][XPOS], icons[f][YPOS], bitmap, w,
					h, 0);
// move it
			icons[f][YPOS] += icons[f][DELTAY];
// if its gone, reinit
			if (icons[f][YPOS] > 64) {
				icons[f][XPOS] = rand() % 128;
				icons[f][YPOS] = 0;
				icons[f][DELTAY] = rand() % 5 + 1;
			}
		}
	}
}

//set *pixel on *x/*y with *color
void st7565_setpixel(uint8_t *buff, uint8_t x, uint8_t y, uint8_t color) {
	if ((x >= LCDWIDTH) || (y >= LCDHEIGHT))
		return;
// x is which column

	if (color)
		buff[x + (y / 8) * 128] |= (1 << (7 - (y % 8)));
	else
		buff[x + (y / 8) * 128] &= ~(1 << (7 - (y % 8)));
}

//draw pixel at *x/*y from *bitmap
void st7565_drawbitmap(uint8_t *buff, uint8_t x, uint8_t y,
		const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color) {
	uint8_t j, i;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			if (*(bitmap + i + (j / 8) * w) & (1 << (j % 8))) {
				st7565_setpixel(buff, x + i, y + j, color);
			}
		}
	}
}

//draw a sting at *x/*y
void st7565_drawstring(uint8_t *buff, uint8_t x, uint8_t line, uint8_t *c) {
	while (c[0] != 0) {
		st7565_drawchar(buff, x, line, c[0]);
		c++;
		x += 6; // 6 pixels wide
		if (x + 6 >= LCDWIDTH) {
			x = 0; // ran out of this line
			line++;
		}
		if (line >= (LCDHEIGHT / 8))
			return; // ran out of space :(
	}
}

//draw a single character at *x/*y
void st7565_drawchar(uint8_t *buff, uint8_t x, uint8_t line, uint8_t c) {
	uint8_t i;
	for (i = 0; i < 5; i++) {
		buff[x + (line * 128)] = *(lcdfont5x7 + (c * 5) + i);
		x++;
	}
}

// the most basic function, clear a single pixel
void st7565_clearpixel(uint8_t *buff, uint8_t x, uint8_t y) {
// x is which column
	buff[x + (y / 8) * 128] &= ~(1 << (7 - (y % 8)));
}

// Draw a line, based on bresenham's algorithm
void st7565_drawline(uint8_t *buff, uint8_t x0, uint8_t y0, uint8_t x1,
		uint8_t y1, uint8_t color) {
	uint8_t tmp, swap = 0;
	uint8_t x, y;
	uint8_t dx, dy;
	int8_t ystep, err;

	if (x0 > x1)
		dx = x0 - x1;
	else
		dx = x1 - x0;
	if (y0 > y1)
		dy = y0 - y1;
	else
		dy = y1 - y0;

	if (dy > dx) {
		swap = 1;
		tmp = dx;
		dx = dy;
		dy = tmp;
		tmp = x0;
		x0 = y0;
		y0 = tmp;
		tmp = x1;
		x1 = y1;
		y1 = tmp;
	}
	if (x0 > x1) {
		tmp = x0;
		x0 = x1;
		x1 = tmp;
		tmp = y0;
		y0 = y1;
		y1 = tmp;
	}

	err = dx >> 1;
	if (y1 > y0)
		ystep = 1;
	else
		ystep = -1;
	y = y0;
	for (x = x0; x <= x1; x++) {
		if (swap == 0)
			st7565_setpixel(buff, x, y, color);
		else
			st7565_setpixel(buff, y, x, color);
		err -= (uint8_t) dy;
		if (err < 0) {
			y += (uint8_t) ystep;
			err += (uint8_t) dx;
		}
	}
}

// draw a filled rectangle
void st7565_fillrect(uint8_t *buff, uint8_t x, uint8_t y, uint8_t w, uint8_t h,
		uint8_t color) {
// stupidest version - just pixels - but fast with internal buffer!
	uint8_t i, j;
	for (i = x; i < x + w; i++) {
		for (j = y; j < y + h; j++) {
			st7565_setpixel(buff, i, j, color);
		}
	}
}

// draw a rectangle
void st7565_drawrect(uint8_t *buff, uint8_t x, uint8_t y, uint8_t w, uint8_t h,
		uint8_t color) {
// stupidest version - just pixels - but fast with internal buffer!
	uint8_t i;
	for (i = x; i < x + w; i++) {
		st7565_setpixel(buff, i, y, color);
		st7565_setpixel(buff, i, y + h - 1, color);
	}
	for (i = y; i < y + h; i++) {
		st7565_setpixel(buff, x, i, color);
		st7565_setpixel(buff, x + w - 1, i, color);
	}
}

// draw a circle
void st7565_drawcircle(uint8_t *buff, uint8_t x0, uint8_t y0, uint8_t r,
		uint8_t color) {
	int8_t f = 1 - r;
	int8_t ddF_x = 1;
	int8_t ddF_y = -2 * r;
	int8_t x = 0;
	int8_t y = r;
	st7565_setpixel(buff, x0, y0 + r, color);
	st7565_setpixel(buff, x0, y0 - r, color);
	st7565_setpixel(buff, x0 + r, y0, color);
	st7565_setpixel(buff, x0 - r, y0, color);
	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		st7565_setpixel(buff, x0 + x, y0 + y, color);
		st7565_setpixel(buff, x0 - x, y0 + y, color);
		st7565_setpixel(buff, x0 + x, y0 - y, color);
		st7565_setpixel(buff, x0 - x, y0 - y, color);
		st7565_setpixel(buff, x0 + y, y0 + x, color);
		st7565_setpixel(buff, x0 - y, y0 + x, color);
		st7565_setpixel(buff, x0 + y, y0 - x, color);
		st7565_setpixel(buff, x0 - y, y0 - x, color);
	}
}

// draw a filled circle
void st7565_fillcircle(uint8_t *buff, uint8_t x0, uint8_t y0, uint8_t r,
		uint8_t color) {
	int8_t f = 1 - r;
	int8_t ddF_x = 1;
	int8_t ddF_y = -2 * r;
	int8_t x = 0;
	int8_t y = r;
	uint8_t i;
	for (i = y0 - r; i <= y0 + r; i++) {
		st7565_setpixel(buff, x0, i, color);
	}
	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		for (i = y0 - y; i <= y0 + y; i++) {
			st7565_setpixel(buff, x0 + x, i, color);
			st7565_setpixel(buff, x0 - x, i, color);
		}
		for (i = y0 - x; i <= y0 + x; i++) {
			st7565_setpixel(buff, x0 + y, i, color);
			st7565_setpixel(buff, x0 - y, i, color);
		}
	}
}



//=============================================================================================
// New functions added by Lukas Eugster
//=============================================================================================

//==========================================================
// Placing Digit Bitmaps
//===========================================================
// display first hour digit (fhd)
void st7565_drawfhd(uint8_t fhd, uint8_t* LCD_Buffer)
    {
        switch(fhd) {
            case 0: st7565_drawbitmap(LCD_Buffer, 12, 1, clock_zero, 128, 64, 10); break;
            case 1: st7565_drawbitmap(LCD_Buffer, 17, 1, clock_one, 128, 64, 10); break;
            case 2: st7565_drawbitmap(LCD_Buffer, 12, 1, clock_two, 128, 64, 10); break;
        }
    }   
    
// display second hour digit (shd)
void st7565_drawshd(uint8_t shd, uint8_t* LCD_Buffer)
    {
        switch(shd) {
            case 0: st7565_drawbitmap(LCD_Buffer, 37, 1, clock_zero, 128, 64, 10); break;
            case 1: st7565_drawbitmap(LCD_Buffer, 37, 1, clock_one, 128, 64, 10); break;
            case 2: st7565_drawbitmap(LCD_Buffer, 37, 1, clock_two, 128, 64, 10); break;
            case 3: st7565_drawbitmap(LCD_Buffer, 37, 1, clock_three, 128, 64, 10); break;
            case 4: st7565_drawbitmap(LCD_Buffer, 37, 1, clock_four, 128, 64, 10); break;
            case 5: st7565_drawbitmap(LCD_Buffer, 37, 2, clock_five, 128, 64, 10); break;
            case 6: st7565_drawbitmap(LCD_Buffer, 37, 1, clock_six, 128, 64, 10); break;
            case 7: st7565_drawbitmap(LCD_Buffer, 37, 1, clock_seven, 128, 64, 10); break;
            case 8: st7565_drawbitmap(LCD_Buffer, 37, 0, clock_eight, 128, 64, 10); break;
            case 9: st7565_drawbitmap(LCD_Buffer, 37, 0, clock_nine, 128, 64, 10); break;
            
        }
    }
    
// display clock dots (dts)
void st7565_drawdts(uint8_t* LCD_Buffer)
    {
    st7565_drawbitmap(LCD_Buffer, 59, 5, clock_dots, 128, 64, 10);
    }

// display first minute digit (fmd)
void st7565_drawfmd(uint8_t fmd, uint8_t* LCD_Buffer)
    {
        switch(fmd) {
            case 0: st7565_drawbitmap(LCD_Buffer, 72, 1, clock_zero, 128, 64, 10); break;
            case 1: st7565_drawbitmap(LCD_Buffer, 77, 1, clock_one, 128, 64, 10); break;
            case 2: st7565_drawbitmap(LCD_Buffer, 72, 1, clock_two, 128, 64, 10); break;
            case 3: st7565_drawbitmap(LCD_Buffer, 72, 1, clock_three, 128, 64, 10); break;
            case 4: st7565_drawbitmap(LCD_Buffer, 72, 1, clock_four, 128, 64, 10); break;
            case 5: st7565_drawbitmap(LCD_Buffer, 72, 2, clock_five, 128, 64, 10); break;
        }
    }
    
// display second minute digit (smd)
void st7565_drawsmd(uint8_t smd, uint8_t* LCD_Buffer)
    {
        switch(smd) {
            case 0: st7565_drawbitmap(LCD_Buffer, 92, 1, clock_zero, 128, 64, 10); break;
            case 1: st7565_drawbitmap(LCD_Buffer, 92, 1, clock_one, 128, 64, 10); break;
            case 2: st7565_drawbitmap(LCD_Buffer, 92, 1, clock_two, 128, 64, 10); break;
            case 3: st7565_drawbitmap(LCD_Buffer, 92, 1, clock_three, 128, 64, 10); break;
            case 4: st7565_drawbitmap(LCD_Buffer, 92, 1, clock_four, 128, 64, 10); break;
            case 5: st7565_drawbitmap(LCD_Buffer, 92, 2, clock_five, 128, 64, 10); break;
            case 6: st7565_drawbitmap(LCD_Buffer, 92, 1, clock_six, 128, 64, 10); break;
            case 7: st7565_drawbitmap(LCD_Buffer, 92, 1, clock_seven, 128, 64, 10); break;
            case 8: st7565_drawbitmap(LCD_Buffer, 92, 0, clock_eight, 128, 64, 10); break;
            case 9: st7565_drawbitmap(LCD_Buffer, 92, 0, clock_nine, 128, 64, 10); break;
            
        }
    }
    
//==========================================================
// Temperature functions
//==========================================================
// Draw temperature symbol
void st7565_drawtempsymbol(uint8_t* LCD_Buffer)
    {
    st7565_drawbitmap(LCD_Buffer, 15, 42, symbol_temp, 128, 64, 10);
    }
    
//Draw temperature 
void st7565_drawtemp(uint8_t temp[] , uint8_t* LCD_Buffer)
    {
    st7565_drawstring(LCD_Buffer, 30, 6, temp);
    st7565_drawbitmap(LCD_Buffer, 42, 47, symbol_deg, 128, 64, 10);
    }
    
//==========================================================
// Humidity functions
//==========================================================
// Draw humidity symbol
void st7565_drawhumidsymbol(uint8_t* LCD_Buffer)
    {
    st7565_drawbitmap(LCD_Buffer, 65, 42, symbol_humid, 128, 64, 10);
    }

// Draw humidity level
void st7565_drawhumid(uint8_t hum[], uint8_t* LCD_Buffer)
    {
    st7565_drawstring(LCD_Buffer, 82, 6, hum);
    st7565_drawstring(LCD_Buffer, 95, 6, "%");
    }

  
//==========================================================
// Alarmclock symbols
//==========================================================
// Draw alarm symbol
void st7565_drawalarmsymbol(uint8_t* LCD_Buffer)
    {
    st7565_drawbitmap(LCD_Buffer, 110, 20, symbol_alarm, 128, 64, 10);
    }

// Draw snooze symbol 
void st7565_drawsnsymbol(uint8_t* LCD_Buffer)
    {
    st7565_drawbitmap(LCD_Buffer, 113, 5, symbol_snooze, 128, 64, 10);

    }
 
//==========================================================
// Draw date 
//========================================================== 
/*void st7565_drawdate(uint8_t *LCD_Buffer)
    {
    uint8_t day     = get from RTC;
    uint8_t month   = get from RTC;
    uint8_t year    = get from RTC;
    
    st7565_drawstring(LCD_Buffer, xy, line, day);
    st7565_drawstring(LCD_Buffer, xy, line, month);
    st7565_drawstring(LCD_Buffer, xy, line, year);
    }
 
*/
   
//==========================================================
// Draw cursor
//========================================================== 
void st7565_drawcursor(uint8_t* LCD_Buffer, uint8_t position)
    {
    switch (position) {
        case 1: st7565_drawbitmap(LCD_Buffer, 2, 7, cursor, 128, 64, 10); break;
        case 2: st7565_drawbitmap(LCD_Buffer, 2, 15, cursor, 128, 64, 10); break;
        case 3: st7565_drawbitmap(LCD_Buffer, 2, 23, cursor, 128, 64, 10); break;
        case 4: st7565_drawbitmap(LCD_Buffer, 2, 31, cursor, 128, 64, 10); break;
        case 5: st7565_drawbitmap(LCD_Buffer, 2, 39, cursor, 128, 64, 10); break;
        case 6: st7565_drawbitmap(LCD_Buffer, 2, 47, cursor, 128, 64, 10); break;
        case 7: st7565_drawbitmap(LCD_Buffer, 2, 55, cursor, 128, 64, 10); break;
        }
    }

//==========================================================
// Draw menu
//========================================================== 
void st7565_drawmenu(uint8_t* LCD_Buffer, menu_t type)
    {
    switch (type) {
        case main_m:
            st7565_drawstring(LCD_Buffer, 40, 0, "MAIN MENU");
            st7565_drawstring(LCD_Buffer, 8, 1, " Clock Settings");
            st7565_drawstring(LCD_Buffer, 8, 2, " Moodlight");
            st7565_drawstring(LCD_Buffer, 8, 3, " Bluetooth");
            st7565_drawstring(LCD_Buffer, 8, 4, " Music");
            st7565_drawstring(LCD_Buffer, 8, 5, " Return");
            break;

        case clock:
            st7565_drawstring(LCD_Buffer, 50, 0, "CLOCK");
            st7565_drawstring(LCD_Buffer, 8, 1, " Time & Date");
            st7565_drawstring(LCD_Buffer, 8, 2, " Alarm");
            st7565_drawstring(LCD_Buffer, 8, 3, " Return");
            break;

        case moodlight:
            st7565_drawstring(LCD_Buffer, 40, 0, "MOODLIGHT");
            st7565_drawstring(LCD_Buffer, 8, 1, " Colors");
            st7565_drawstring(LCD_Buffer, 8, 2, " Custom");
            st7565_drawstring(LCD_Buffer, 8, 3, " Return");
            break;
        
        case bluetooth:
            st7565_drawstring(LCD_Buffer, 50, 0, "BLUETOOTH");
            st7565_drawstring(LCD_Buffer, 8, 1, " Pair");
            st7565_drawstring(LCD_Buffer, 8, 2, " Settings");
            st7565_drawstring(LCD_Buffer, 8, 3, " Return");
            break;
        
        case music:
            st7565_drawstring(LCD_Buffer, 50, 0, "MUSIC");
            st7565_drawstring(LCD_Buffer, 8, 1, " Player");
            st7565_drawstring(LCD_Buffer, 8, 2, " Volume");
            st7565_drawstring(LCD_Buffer, 8, 3, " Return");
            break;
        }
    }

//==========================================================
// 
//==========================================================


