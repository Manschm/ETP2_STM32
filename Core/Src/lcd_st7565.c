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

uint8_t buffer[1024];

uint8_t pagemap[] = {7, 6, 5, 4, 3, 2, 1, 0};

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
void DELAY(uint32_t delay) {
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
        HAL_GPIO_WritePin(ST7565_PORT, ST7565_SDAT_PIN, byte & (1 << i) ? 1 : 0);
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
    HAL_GPIO_WritePin(ST7565_PORT, ST7565_BL_PIN, GPIO_PIN_SET);
}

///Disables the backlight
void st7565_backlight_disable(void) {
    HAL_GPIO_WritePin(ST7565_PORT, ST7565_BL_PIN, GPIO_PIN_RESET);
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


//=============================================================================================
// New functions added by Lukas Eugster
//=============================================================================================

//==========================================================
// Placing Digit Bitmaps
//===========================================================
// display first hour digit (fhd)
void st7565_drawfhd(uint8_t fhd, uint8_t *LCD_Buffer) {
    switch (fhd) {
        case 0:
            st7565_drawbitmap(LCD_Buffer, 12, 1, clock_zero, 128, 64, 10);
            break;
        case 1:
            st7565_drawbitmap(LCD_Buffer, 17, 1, clock_one, 128, 64, 10);
            break;
        case 2:
            st7565_drawbitmap(LCD_Buffer, 12, 1, clock_two, 128, 64, 10);
            break;
    }
}

// display second hour digit (shd)
void st7565_drawshd(uint8_t shd, uint8_t *LCD_Buffer) {
    switch (shd) {
        case 0:
            st7565_drawbitmap(LCD_Buffer, 37, 1, clock_zero, 128, 64, 10);
            break;
        case 1:
            st7565_drawbitmap(LCD_Buffer, 37, 1, clock_one, 128, 64, 10);
            break;
        case 2:
            st7565_drawbitmap(LCD_Buffer, 37, 1, clock_two, 128, 64, 10);
            break;
        case 3:
            st7565_drawbitmap(LCD_Buffer, 37, 1, clock_three, 128, 64, 10);
            break;
        case 4:
            st7565_drawbitmap(LCD_Buffer, 37, 1, clock_four, 128, 64, 10);
            break;
        case 5:
            st7565_drawbitmap(LCD_Buffer, 37, 2, clock_five, 128, 64, 10);
            break;
        case 6:
            st7565_drawbitmap(LCD_Buffer, 37, 1, clock_six, 128, 64, 10);
            break;
        case 7:
            st7565_drawbitmap(LCD_Buffer, 37, 1, clock_seven, 128, 64, 10);
            break;
        case 8:
            st7565_drawbitmap(LCD_Buffer, 37, 0, clock_eight, 128, 64, 10);
            break;
        case 9:
            st7565_drawbitmap(LCD_Buffer, 37, 0, clock_nine, 128, 64, 10);
            break;

    }
}

// display clock dots (dts)
void st7565_drawdts(uint8_t *LCD_Buffer) {
    st7565_drawbitmap(LCD_Buffer, 59, 5, clock_dots, 128, 64, 10);
}

// display first minute digit (fmd)
void st7565_drawfmd(uint8_t fmd, uint8_t *LCD_Buffer) {
    switch (fmd) {
        case 0:
            st7565_drawbitmap(LCD_Buffer, 72, 1, clock_zero, 128, 64, 10);
            break;
        case 1:
            st7565_drawbitmap(LCD_Buffer, 77, 1, clock_one, 128, 64, 10);
            break;
        case 2:
            st7565_drawbitmap(LCD_Buffer, 72, 1, clock_two, 128, 64, 10);
            break;
        case 3:
            st7565_drawbitmap(LCD_Buffer, 72, 1, clock_three, 128, 64, 10);
            break;
        case 4:
            st7565_drawbitmap(LCD_Buffer, 72, 1, clock_four, 128, 64, 10);
            break;
        case 5:
            st7565_drawbitmap(LCD_Buffer, 72, 2, clock_five, 128, 64, 10);
            break;
    }
}

// display second minute digit (smd)
void st7565_drawsmd(uint8_t smd, uint8_t *LCD_Buffer) {
    switch (smd) {
        case 0:
            st7565_drawbitmap(LCD_Buffer, 92, 1, clock_zero, 128, 64, 10);
            break;
        case 1:
            st7565_drawbitmap(LCD_Buffer, 92, 1, clock_one, 128, 64, 10);
            break;
        case 2:
            st7565_drawbitmap(LCD_Buffer, 92, 1, clock_two, 128, 64, 10);
            break;
        case 3:
            st7565_drawbitmap(LCD_Buffer, 92, 1, clock_three, 128, 64, 10);
            break;
        case 4:
            st7565_drawbitmap(LCD_Buffer, 92, 1, clock_four, 128, 64, 10);
            break;
        case 5:
            st7565_drawbitmap(LCD_Buffer, 92, 2, clock_five, 128, 64, 10);
            break;
        case 6:
            st7565_drawbitmap(LCD_Buffer, 92, 1, clock_six, 128, 64, 10);
            break;
        case 7:
            st7565_drawbitmap(LCD_Buffer, 92, 1, clock_seven, 128, 64, 10);
            break;
        case 8:
            st7565_drawbitmap(LCD_Buffer, 92, 0, clock_eight, 128, 64, 10);
            break;
        case 9:
            st7565_drawbitmap(LCD_Buffer, 92, 0, clock_nine, 128, 64, 10);
            break;

    }
}

//==========================================================
// Temperature functions
//==========================================================
// Draw temperature symbol
void st7565_drawtempsymbol(uint8_t *LCD_Buffer) {
    st7565_drawbitmap(LCD_Buffer, 15, 47, symbol_temp, 128, 64, 10);
}

//Draw temperature 
void st7565_drawtemp(uint8_t temp[], uint8_t *LCD_Buffer) {
    st7565_drawstring(LCD_Buffer, 30, 7, temp);
    st7565_drawbitmap(LCD_Buffer, 42, 53, symbol_deg, 128, 64, 10);
}

//==========================================================
// Humidity functions
//==========================================================
// Draw humidity symbol
void st7565_drawhumidsymbol(uint8_t *LCD_Buffer) {
    st7565_drawbitmap(LCD_Buffer, 65, 47, symbol_humid, 128, 64, 10);
}

// Draw humidity level
void st7565_drawhumid(uint8_t hum[], uint8_t *LCD_Buffer) {
    st7565_drawstring(LCD_Buffer, 82, 7, hum);
    st7565_drawstring(LCD_Buffer, 95, 7, "%");
}


//==========================================================
// Alarmclock symbols
//==========================================================
// Draw alarm symbol
void st7565_drawalarmsymbol(uint8_t *LCD_Buffer) {
    st7565_drawbitmap(LCD_Buffer, 110, 20, symbol_alarm, 128, 64, 10);
}

// Draw snooze symbol 
void st7565_drawsnsymbol(uint8_t *LCD_Buffer) {
    st7565_drawbitmap(LCD_Buffer, 113, 5, symbol_snooze, 128, 64, 10);

}

//==========================================================
// Draw date 
//========================================================== 
void st7565_drawdate(uint8_t *LCD_Buffer, uint8_t day, uint8_t month, uint8_t year) {
    uint8_t day_s[2];
    uint8_t month_s[2];
    uint8_t year_s[2];

    day_s[1] = (day & 0xF) + 0x30;
    day_s[0] = (day >> 4U) + 0x30;

    month_s[1] = (month & 0xF) + 0x30;
    month_s[0] = (month >> 4U) + 0x30;

    year_s[1] = (year & 0xF) + 0x30;
    year_s[0] = (year >> 4U) + 0x30;

    st7565_drawstring(LCD_Buffer, 40, 5, day_s);
    st7565_drawstring(LCD_Buffer, 52, 5, "/");
    st7565_drawstring(LCD_Buffer, 60, 5, month_s);
    st7565_drawstring(LCD_Buffer, 72, 5, "/");
    st7565_drawstring(LCD_Buffer, 80, 5, "20");
    st7565_drawstring(LCD_Buffer, 92, 5, year_s);
}

//==========================================================
// Draw cursor
//========================================================== 
void st7565_drawcursor(uint8_t *LCD_Buffer, uint8_t position) {
    switch (position) {
        case 1:
            st7565_drawbitmap(LCD_Buffer, 2, 7, cursor, 128, 64, 10);
            break;
        case 2:
            st7565_drawbitmap(LCD_Buffer, 2, 15, cursor, 128, 64, 10);
            break;
        case 3:
            st7565_drawbitmap(LCD_Buffer, 2, 23, cursor, 128, 64, 10);
            break;
        case 4:
            st7565_drawbitmap(LCD_Buffer, 2, 31, cursor, 128, 64, 10);
            break;
        case 5:
            st7565_drawbitmap(LCD_Buffer, 2, 39, cursor, 128, 64, 10);
            break;
        case 6:
            st7565_drawbitmap(LCD_Buffer, 2, 47, cursor, 128, 64, 10);
            break;
        case 7:
            st7565_drawbitmap(LCD_Buffer, 2, 55, cursor, 128, 64, 10);
            break;
    }
}

//==========================================================
// Draw menu
//========================================================== 
void st7565_drawmenu(uint8_t *LCD_Buffer, menu_t type) {
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
            st7565_drawstring(LCD_Buffer, 8, 3, " Lights OFF");
            st7565_drawstring(LCD_Buffer, 8, 4, " Return");
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

        case colors:
            st7565_drawstring(LCD_Buffer, 40, 0, " COLORS");
            st7565_drawstring(LCD_Buffer, 8, 1, " White");
            st7565_drawstring(LCD_Buffer, 8, 2, " Red");
            st7565_drawstring(LCD_Buffer, 8, 3, " Green");
            st7565_drawstring(LCD_Buffer, 8, 4, " Blue");
            st7565_drawstring(LCD_Buffer, 8, 5, " Yellow");
            st7565_drawstring(LCD_Buffer, 8, 6, " Purple");
            st7565_drawstring(LCD_Buffer, 8, 7, " Return");
            break;
    }
}

//==========================================================
// Function to change variable numbers into chars
//==========================================================

//==========================================================
// Draw custom menu
//==========================================================
void st7565_drawmenu_custom(uint8_t *LCD_Buffer, uint8_t led_intens_w, uint8_t led_intens_r, uint8_t led_intens_g,
                            uint8_t led_intens_b) {

    uint8_t intens_w[1];
    uint8_t intens_r[1];
    uint8_t intens_g[1];
    uint8_t intens_b[1];

    itoa(led_intens_w, intens_w, 10);
    itoa(led_intens_r, intens_r, 10);
    itoa(led_intens_g, intens_g, 10);
    itoa(led_intens_b, intens_b, 10);

    st7565_drawstring(LCD_Buffer, 40, 0, "CUSTOM COLOR");
    st7565_drawstring(LCD_Buffer, 8, 1, " White:");
    st7565_drawstring(LCD_Buffer, 50, 1, intens_w);
    st7565_drawstring(LCD_Buffer, 70, 1, " %");
    st7565_drawstring(LCD_Buffer, 8, 2, " Red:");
    st7565_drawstring(LCD_Buffer, 50, 2, intens_r);
    st7565_drawstring(LCD_Buffer, 70, 2, " %");
    st7565_drawstring(LCD_Buffer, 8, 3, " Green:");
    st7565_drawstring(LCD_Buffer, 50, 3, intens_g);
    st7565_drawstring(LCD_Buffer, 70, 3, " %");
    st7565_drawstring(LCD_Buffer, 8, 4, " Blue:");
    st7565_drawstring(LCD_Buffer, 50, 4, intens_b);
    st7565_drawstring(LCD_Buffer, 70, 4, " %");
    st7565_drawstring(LCD_Buffer, 8, 5, " Return");
}

//==========================================================
// Draw set time menu
//==========================================================
void st7565_drawmenu_settime(uint8_t *LCD_Buffer, uint8_t set_hour, uint8_t set_min, uint8_t set_day, uint8_t set_mon,
                             uint8_t set_year) {
    uint8_t hour[1];
    uint8_t min[1];
    uint8_t day[1];
    uint8_t mon[1];
    uint8_t year[1];

    itoa(set_hour, hour, 10);
    itoa(set_min, min, 10);
    itoa(set_day, day, 10);
    itoa(set_mon, mon, 10);
    itoa(set_year, year, 10);

    st7565_drawstring(LCD_Buffer, 40, 0, "SET TIME");
    st7565_drawstring(LCD_Buffer, 8, 1, " Set hour:");
    st7565_drawstring(LCD_Buffer, 80, 1, hour);
    st7565_drawstring(LCD_Buffer, 8, 2, " Set minute:");
    st7565_drawstring(LCD_Buffer, 80, 2, min);
    st7565_drawstring(LCD_Buffer, 8, 3, " Set Day:");
    st7565_drawstring(LCD_Buffer, 80, 3, day);
    st7565_drawstring(LCD_Buffer, 8, 4, " Set Month:");
    st7565_drawstring(LCD_Buffer, 80, 4, mon);
    st7565_drawstring(LCD_Buffer, 8, 5, " Set Year:");
    st7565_drawstring(LCD_Buffer, 80, 5, year);
    st7565_drawstring(LCD_Buffer, 8, 6, " Return");
}

//==========================================================
// Draw alarm menu
//==========================================================
void st7565_drawmenu_setalarm(uint8_t *LCD_Buffer, uint8_t set_al_hr, uint8_t set_al_min) {
    uint8_t al_hr[1];
    uint8_t al_min[1];

    itoa(set_al_hr, al_hr, 10);
    itoa(set_al_min, al_min, 10);

    st7565_drawstring(LCD_Buffer, 40, 0, "SET ALARM");
    st7565_drawstring(LCD_Buffer, 8, 1, " Set Hour:");
    st7565_drawstring(LCD_Buffer, 80, 1, al_hr);
    st7565_drawstring(LCD_Buffer, 8, 2, " Set Minute:");
    st7565_drawstring(LCD_Buffer, 80, 2, al_min);
    st7565_drawstring(LCD_Buffer, 8, 3, " Return");
}
