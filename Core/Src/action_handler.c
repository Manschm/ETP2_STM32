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
#include "st7565.h"
#include "main.h"
#include "rtc.h"
#include "tim.h"

//=================================================
//Public function definitions
//=================================================

// Home screen actions
//------------------------------------

//=================================================
//RTC Draw Time on LCD
//=================================================
void ah_draw_time() {
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;

    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BCD);

    uint8_t fhd = sTime.Hours >> 4U;
    uint8_t shd = sTime.Hours & 0xFU;
    uint8_t fmd = sTime.Minutes >> 4U;
    uint8_t smd = sTime.Minutes & 0xFU;

    // GET TIME FROM RTC, safe time in given variables or change

    st7565_drawfhd(fhd);
    st7565_drawshd(shd);
    st7565_drawdts();
    st7565_drawfmd(fmd);
    st7565_drawsmd(smd);
    st7565_write_buffer();
}

//=================================================
// Draw RTC Date on LCD
//=================================================
void ah_draw_date() {
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;

    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BCD);

    uint8_t year = (sDate.Year);
    uint8_t month = sDate.Month;
    uint8_t day = sDate.Date;

    st7565_drawdate(day, month, year);
}

//=================================================
// Set RTC time and date
//=================================================
void ah_set_TimeDate(uint8_t hour, uint8_t minute, uint8_t second, uint8_t day, uint8_t month, uint8_t year) {
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;
    RTC_AlarmTypeDef sAlarm;

    HAL_RTC_DeactivateAlarm(&hrtc, RTC_ALARM_A);
    HAL_RTC_GetAlarm(&hrtc, &sAlarm, RTC_ALARM_A, RTC_FORMAT_BCD);

    sTime.Hours = hour;
    sTime.Minutes = minute;
    sTime.Seconds = second;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;

    sDate.Date = day;
    sDate.Month = month;
    sDate.Year = year;
    sDate.WeekDay = RTC_WEEKDAY_MONDAY;

    HAL_RTC_WaitForSynchro(&hrtc);

    HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
    HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD);
}

void ah_draw_sensor() {
    // Draw the temperature
    uint8_t temp[] = "18";   // Should be changed to read from sensor here
    st7565_drawtempsymbol();
    st7565_drawtemp(temp);
    st7565_write_buffer();

    // Draw the humidity
    uint8_t hum[] = "57";   // Should be changed to read from sensor here
    st7565_drawhumidsymbol();
    st7565_drawhumid(hum);
    st7565_write_buffer();

}

void ah_draw_snooze() {
    // Draw snooze symbol
    st7565_drawsnsymbol();
    st7565_write_buffer();

}

void ah_draw_alarm() {
    // Draw alarm symbol
    st7565_drawalarmsymbol();
    st7565_write_buffer();
}

// Menu screen actions
//=======================================
void ah_draw_cursor(uint8_t position) {
    st7565_drawcursor(position);
}

void ah_menu(menu_t type) {
    st7565_drawmenu(type);
}

//=================================================================================================
// LED Actions
//=================================================================================================
// Set Color Preset
//================================
void ah_setPWM(TIM_HandleTypeDef *htim, uint16_t red, uint16_t green, uint16_t blue, uint16_t white) {
    if (red == 0) {
        HAL_TIM_PWM_Stop(htim, PWM_CH_R);
        __HAL_TIM_SET_COMPARE(&htim1, PWM_CH_R, 0);
    } else {
        __HAL_TIM_SET_COMPARE(&htim1, PWM_CH_R, red);
        HAL_TIM_PWM_Start(htim, PWM_CH_R);
    }

    if (green == 0) {
        HAL_TIM_PWM_Stop(htim, PWM_CH_G);
        __HAL_TIM_SET_COMPARE(&htim1, PWM_CH_G, 0);
    } else {
        __HAL_TIM_SET_COMPARE(&htim1, PWM_CH_G, green);
        HAL_TIM_PWM_Start(htim, PWM_CH_G);
    }

    if (blue == 0) {
        HAL_TIM_PWM_Stop(htim, PWM_CH_B);
        __HAL_TIM_SET_COMPARE(&htim1, PWM_CH_B, 0);
    } else {
        __HAL_TIM_SET_COMPARE(&htim1, PWM_CH_B, blue);
        HAL_TIM_PWM_Start(htim, PWM_CH_B);
    }

    if (white == 0) {
        HAL_TIM_PWM_Stop(htim, PWM_CH_W);
        __HAL_TIM_SET_COMPARE(&htim1, PWM_CH_W, 0);
    } else {
        __HAL_TIM_SET_COMPARE(&htim1, PWM_CH_W, white);
        HAL_TIM_PWM_Start(htim, PWM_CH_W);
    }
}

void ah_setValues(uint16_t red, uint16_t green, uint16_t blue, uint16_t white) {
    userOverride = 1;
    userRed = red;
    userGreen = green;
    userBlue = blue;
    userWhite = white;
}

void ah_setcolor(color_preset_t color) {
    switch (color) {
        case white:
            ah_setValues(0, 0, 0, 100);
            break;

        case red:
            ah_setValues(100, 0, 0, 0);
            break;

        case green:
            ah_setValues(0, 100, 0, 0);
            break;

        case blue:
            ah_setValues(0, 0, 100, 0);
            break;

        case yellow:
            ah_setValues(100U>>2U, 100U>>2U, 0, 0);
            break;

        case purple:
            ah_setValues(100U>>2U, 0, 100U>>2U, 0);
            break;

        default:
            ah_setValues(0, 0, 0, 0);
            break;
    }
}
