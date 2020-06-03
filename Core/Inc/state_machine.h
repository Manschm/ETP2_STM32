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
// Re-definition guard
#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H

// Standard includes
#include <stdint.h>
#include "event_handler.h"
#include "lcd_st7565.h"

// Definition of FSM states

typedef enum {
    HOME_SCREEN,
    MENU_MAIN_CLOCK,
    MENU_MAIN_MOODLIGHT,
    MENU_MAIN_BLUETOOTH,
    MENU_MAIN_MUSIC,
    MENU_MAIN_RETURN,
    MENU_CLOCK_TIME,
    MENU_CLOCK_ALARM,
    MENU_CLOCK_RETURN,
    MENU_MOODL_CUSTOM,
    MENU_MOODL_PRESETS,
	MENU_MOODL_OFF,
    MENU_MOODL_RETURN,
    MENU_BT_PAIR,
    MENU_BT_SETTINGS,
    MENU_BT_RETURN,
    MENU_MUSIC_VOLUME,
    MENU_MUSIC_PLAYER,
    MENU_MUSIC_RETURN,
	MENU_CUSTOM_WHITE,
	MENU_CUSTOM_RED,
	MENU_CUSTOM_GREEN,
	MENU_CUSTOM_BLUE,
	MENU_CUSTOM_RETURN,
	MENU_SETTIME_HOUR,
	MENU_SETTIME_MINUTE,
	MENU_SETTIME_DAY,
	MENU_SETTIME_MONTH,
	MENU_SETTIME_YEAR,
	MENU_SETTIME_RETURN,
	MENU_ALARM_HOUR,
	MENU_ALARM_MINUTE,
	MENU_ALARM_RETURN,
	MENU_COLORS_WHITE,
	MENU_COLORS_RED,
	MENU_COLORS_GREEN,
	MENU_COLORS_BLUE,
	MENU_COLORS_YELLOW,
	MENU_COLORS_PURPLE,
	MENU_COLORS_RETURN
} state_t;

// current FSM state
extern state_t state;

// Initialize state machine
void fsm_init(void);



// Process the given event, based on actual state.

void fsm_handle_event(event_t event);

#endif
