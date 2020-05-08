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
#include <stdint.h>
#include <stdbool.h>
#include "action_handler.h"
#include "event_handler.h"
#include "lcd_st7565.h"
#include "main.h"
#include "rtc.h"


//=================================================
//Public function definitions
//=================================================

// Home screen actions
//------------------------------------
void ah_draw_time()
{  
    uint8_t fhd = 1;
    uint8_t shd = 1;
    uint8_t fmd = 2;
    uint8_t smd = 3;
    
    // GET TIME FROM RTC, safe time in given variables or change
    
    st7565_drawfhd(fhd, LCD_Buffer);
    st7565_drawshd(shd, LCD_Buffer);
    st7565_drawdts(LCD_Buffer);
    st7565_drawfmd(fmd, LCD_Buffer);
    st7565_drawsmd(smd, LCD_Buffer);
	st7565_write_buffer(LCD_Buffer);

}    

void ah_draw_date()
{
    //void st7565_drawdate(LCD_Buffer);
}

void ah_set_time(uint8_t set_hour,uint8_t set_min)
{
	RTC_TimeTypeDef sTime = {0};

	sTime.Hours = set_hour;
	sTime.Minutes  = set_min;
	sTime.Seconds = 0;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;

	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
}

void ah_set_date(uint8_t set_day, uint8_t set_mon, uint8_t set_year)
{

	RTC_DateTypeDef sDate = {0};
	sDate.WeekDay = RTC_WEEKDAY_MONDAY;

	switch(set_mon) {
		case 1: sDate.Month = RTC_MONTH_JANUARY; break;
		case 2: sDate.Month = RTC_MONTH_FEBRUARY; break;
		case 3: sDate.Month = RTC_MONTH_MARCH; break;
		case 4: sDate.Month = RTC_MONTH_APRIL; break;
		case 5: sDate.Month = RTC_MONTH_MAY; break;
		case 6: sDate.Month = RTC_MONTH_JUNE; break;
		case 7: sDate.Month = RTC_MONTH_JULY; break;
		case 8: sDate.Month = RTC_MONTH_AUGUST; break;
		case 9: sDate.Month = RTC_MONTH_SEPTEMBER; break;
		case 10: sDate.Month = RTC_MONTH_OCTOBER; break;
		case 11: sDate.Month = RTC_MONTH_NOVEMBER; break;
		case 12: sDate.Month = RTC_MONTH_DECEMBER; break;
	}

	sDate.Date = set_day;
	sDate.Year = set_year;

	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD);
}



void ah_draw_sensor()
{
// Draw the temperature
    uint8_t temp[]= "18";   // Should be changed to read from sensor here
    st7565_drawtempsymbol(LCD_Buffer);
    st7565_drawtemp(temp , LCD_Buffer);
	st7565_write_buffer(LCD_Buffer);


// Draw the humidity
    uint8_t hum[] = "57";   // Should be changed to read from sensor here
    st7565_drawhumidsymbol(LCD_Buffer);
    st7565_drawhumid(hum, LCD_Buffer);
	st7565_write_buffer(LCD_Buffer);

}

void ah_draw_snooze()
{
// Draw snooze symbol
   st7565_drawsnsymbol(LCD_Buffer);
	st7565_write_buffer(LCD_Buffer);

}

void ah_draw_alarm()
{
// Draw alarm symbol
   st7565_drawalarmsymbol(LCD_Buffer);
   st7565_write_buffer(LCD_Buffer);

}



// Menu screen actions
//=======================================
void ah_draw_cursor(uint8_t position)
{
	st7565_drawcursor(LCD_Buffer, position);

}

void ah_menu(menu_t type)
{
	st7565_drawmenu(LCD_Buffer, type);
}

// LED Actions
//=======================================
void ah_setcolor(color_preset_t color_preset)
{
	// TO BE CODED****** Set led color and PWM. Color presets. Feel free.
}


