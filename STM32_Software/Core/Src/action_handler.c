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
#include "tim.h"

#define PWM_CH_R	TIM_CHANNEL_1
#define PWM_CH_G	TIM_CHANNEL_2
#define PWM_CH_B	TIM_CHANNEL_3
#define PWM_CH_W	TIM_CHANNEL_4

//=================================================
//Public function definitions
//=================================================

// Home screen actions
//------------------------------------

//=================================================
//RTC Draw Time on LCD
//=================================================
void ah_draw_time()
{  
	RTC_TimeTypeDef sTime = {0};
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD);

	uint8_t fhd = sTime.Hours >> 4;
    uint8_t shd = sTime.Hours & 0xF;
    uint8_t fmd = sTime.Minutes >> 4;
    uint8_t smd = sTime.Minutes & 0xF;

    // GET TIME FROM RTC, safe time in given variables or change
    
    st7565_drawfhd(fhd, LCD_Buffer);
    st7565_drawshd(shd, LCD_Buffer);
    st7565_drawdts(LCD_Buffer);
    st7565_drawfmd(fmd, LCD_Buffer);
    st7565_drawsmd(smd, LCD_Buffer);
	st7565_write_buffer(LCD_Buffer);

}    

//=================================================
// Draw RTC Date on LCD
//=================================================
void ah_draw_date()
{
	RTC_DateTypeDef sDate = {0};
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BCD);
    uint8_t year = (sDate.Year)-12;
    uint8_t month = sDate.Month;
    uint8_t day = sDate.Date;

	st7565_drawdate(LCD_Buffer, day, month, year);
}

//=================================================
// SET RTC Time
//=================================================
void ah_set_time(uint8_t set_hour,uint8_t set_min)
{
	RTC_TimeTypeDef sTime;
	RTC_AlarmTypeDef sAlarm;

	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetAlarm(&hrtc, &sAlarm, RTC_ALARM_A, RTC_FORMAT_BCD);
	HAL_RTC_DeactivateAlarm(&hrtc,  RTC_ALARM_A);

	sAlarm.AlarmTime.Hours = set_hour;
	sAlarm.AlarmTime.Minutes = set_min;
	sAlarm.AlarmTime.Seconds = 0;

	sTime.Hours = set_hour;
	sTime.Minutes  = set_min;
	sTime.Seconds = 0;
	//sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	//sTime.StoreOperation = RTC_STOREOPERATION_RESET;

	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD);
}

//=================================================
// Set RTC Date
//=================================================
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

	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
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

//=================================================================================================
// LED Actions
//=================================================================================================
// Set Color Preset
//================================
void ah_setPWM(TIM_HandleTypeDef *htim, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
	if (r == 0) {
		HAL_TIM_PWM_Stop(htim, PWM_CH_R);
		__HAL_TIM_SET_COMPARE(&htim1, PWM_CH_R, 0);
	} else {
		__HAL_TIM_SET_COMPARE(&htim1, PWM_CH_R, r);
		HAL_TIM_PWM_Start(htim, PWM_CH_R);
	}

	if (g == 0) {
		HAL_TIM_PWM_Stop(htim, PWM_CH_G);
		__HAL_TIM_SET_COMPARE(&htim1, PWM_CH_G, 0);
	} else {
		__HAL_TIM_SET_COMPARE(&htim1, PWM_CH_G, g);
		HAL_TIM_PWM_Start(htim, PWM_CH_G);
	}

	if (b == 0) {
		HAL_TIM_PWM_Stop(htim, PWM_CH_B);
		__HAL_TIM_SET_COMPARE(&htim1, PWM_CH_B, 0);
	} else {
		__HAL_TIM_SET_COMPARE(&htim1, PWM_CH_B, b);
		HAL_TIM_PWM_Start(htim, PWM_CH_B);
	}

	if (w == 0) {
		HAL_TIM_PWM_Stop(htim, PWM_CH_W);
		__HAL_TIM_SET_COMPARE(&htim1, PWM_CH_W, 0);
	} else {
		__HAL_TIM_SET_COMPARE(&htim1, PWM_CH_W, w);
		HAL_TIM_PWM_Start(htim, PWM_CH_W);
	}
}

void ah_setcolor(color_preset_t color_preset)
{
	switch(color_preset) {
		case white:
			ah_setPWM(&htim1, 0, 0, 0, 20);
			break;

		case red:
			ah_setPWM(&htim1, 20, 0, 0, 0);
			break;

		case green:
			ah_setPWM(&htim1, 0, 20, 0, 0);
			break;

		case blue:
			ah_setPWM(&htim1, 0, 0, 20, 0);
			break;

		case yellow:
			ah_setPWM(&htim1, 10, 10, 0, 0);
			break;

		case purple:
			ah_setPWM(&htim1, 10, 0, 10, 0);
			break;

		default:
			ah_setPWM(&htim1, 0, 0, 0, 0);
			break;
	}
}

//=================================================
// Set Color Custom
//=================================================
void ah_set_custom(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {

	ah_setPWM(&htim1, red, green, blue, white);
}
//=================================================
// Stop LEDs
//=================================================
void ah_stop_led(TIM_HandleTypeDef *htim) {
	HAL_TIM_PWM_Stop(htim, PWM_CH_R);
	HAL_TIM_PWM_Stop(htim, PWM_CH_G);
	HAL_TIM_PWM_Stop(htim, PWM_CH_B);
	HAL_TIM_PWM_Stop(htim, PWM_CH_W);
}




