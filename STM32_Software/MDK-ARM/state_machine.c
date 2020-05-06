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
#include "state_machine.h"
#include "action_handler.h"


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
    MENU_MOODL_RETURN,
    MENU_BT_PAIR,
    MENU_BT_SETTINGS,
    MENU_BT_RETURN,
    MENU_MUSIC_Volume,
    MENU_MUSIC_PLAYER,
    MENU_MUSIC_RETURN
} state_t;

/* Module-wide variables & constants
 * ------------------------------------------------------------------------- */

// current FSM state 
static state_t state = HOME_SCREEN;


void fsm_init(void)
{
    state = HOME_SCREEN;
    ah_draw_time();

    
    
    
}

// State Machine

void fsm_handle_event(event_t event)
{
    switch(state) {
        case HOME_SCREEN:
            switch (event) {
                case EV_BUTTON_SL:
                    st7565_backlight_enable(); 
                    ah_menu_main();
                    ah_cursor(1);
                    state = ;
                    break;
                case EV_BUTTON_F1:
                    ah_door(DOOR_LOCK);
                    ah_motor(MOTOR_UP);
                    ah_show_state("MOVING_UP");
                    state = MOVING_UP;
                    break;
                default:
                    state = F0_CLOSED; 
                    break;
            }
            break;
        
    default:
        state = HOME_SCREEN;
}



