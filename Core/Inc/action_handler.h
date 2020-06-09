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

#ifndef _ACTION_HANDLER_H
#define _ACTION_HANDLER_H

#include <stdint.h>
#include "main.h"
#include "st7565.h"

//======================================================
// Typedef for functions
//======================================================
typedef enum {
    white,
    red,
    green,
    blue,
    yellow,
    purple,
} color_preset_t;

//======================================================
// Definition of functions
//======================================================
void ah_draw_time(void);

void ah_draw_date(void);

void ah_draw_sensor(void);

void ah_draw_snooze(void);

void ah_draw_alarm(void);

void ah_draw_cursor(uint8_t position);

void ah_menu(menu_t type);

void ah_setPWM(TIM_HandleTypeDef *htim, uint16_t red, uint16_t green, uint16_t blue, uint16_t white);

void ah_setcolor(color_preset_t color);

void ah_stop_led(TIM_HandleTypeDef *htim);

void ah_set_custom(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);

void ah_set_TimeDate(uint8_t hour, uint8_t minute, uint8_t second, uint8_t day, uint8_t month, uint8_t year);


#endif
