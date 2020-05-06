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
    MENU_MUSIC_VOLUME,
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
    ah_draw_date();
    ah_draw_sensor();
    // later to be moved to seperate states
    ah_draw_snooze();
    ah_draw_alarm();

}

// State Machine

void fsm_handle_event(event_t event)
{
    switch(state) {
        case HOME_SCREEN:  
            switch (event) {
                case EV_NO_EVENT:
                    ah_draw_time();
                    ah_draw_date();
                    ah_draw_sensor();
                    // later to be moved to seperate states
                    ah_draw_snooze();
                    ah_draw_alarm();
                    break;
                
                case EV_BUTTON_SL:
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    state = MENU_MAIN_CLOCK;
                    break;
                
                default:
                    state = HOME_SCREEN;
                    break;
            }

        case MENU_MAIN_CLOCK:
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    state = MENU_MAIN_CLOCK;
                    break;
                
                case EV_BUTTON_SL:
                    ah_menu(clock);
                    ah_draw_cursor(1);
                    state = MENU_CLOCK_TIME;
                    break;
               
                case EV_BUTTON_UP:
                    ah_menu(main_m);
                    ah_draw_cursor(5);
                    state = MENU_MAIN_RETURN;
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(main_m);
                    ah_draw_cursor(2);
                    state = MENU_MAIN_MOODLIGHT;
                    break;                
                          
                default:
                    state = MENU_MAIN_CLOCK;   
                    break;
            }
            
        case MENU_MAIN_MOODLIGHT:
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(main_m);
                    ah_draw_cursor(2);
                    state = MENU_MAIN_MOODLIGHT;
                    break;    
                
                case EV_BUTTON_SL:
                    ah_menu(moodlight);
                    ah_draw_cursor(1);
                    state = MENU_MOODL_PRESETS;
                    break;
                
                case EV_BUTTON_UP:
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    state = MENU_MAIN_CLOCK;
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(main_m);
                    ah_draw_cursor(3);
                    state = MENU_MAIN_BLUETOOTH;
                    break;                   
                
                default:
                    state = MENU_MAIN_MOODLIGHT;
                    break;
            }
        
        case MENU_MAIN_BLUETOOTH:
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(main_m);
                    ah_draw_cursor(3);
                    state = MENU_MAIN_BLUETOOTH;
                    break;                    
                
                case EV_BUTTON_SL:
                    ah_menu(bluetooth);
                    ah_draw_cursor(1);
                    state = MENU_BT_PAIR;
                    break;
                
                case EV_BUTTON_UP:
                    ah_menu(main_m);
                    ah_draw_cursor(2);
                    state = MENU_MAIN_MOODLIGHT;
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(main_m);
                    ah_draw_cursor(4);
                    state = MENU_MAIN_MUSIC;
                    break;
                
                default:
                    state = MENU_MAIN_BLUETOOTH;
            }

        case MENU_MAIN_MUSIC:    
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(main_m);
                    ah_draw_cursor(4);
                    state = MENU_MAIN_MUSIC;
                    break;                  
              
                case EV_BUTTON_SL: 
                    ah_menu(music);
                    ah_draw_cursor(1);
                    state = MENU_MUSIC_PLAYER;
                    break;    
                
                case EV_BUTTON_UP:
                    ah_menu(main_m);
                    ah_draw_cursor(3);
                    state = MENU_MAIN_BLUETOOTH;
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(main_m);
                    ah_draw_cursor(5);
                    state = MENU_MAIN_RETURN;
                    break;
                
                default:
                    state = MENU_MAIN_MUSIC;
            }
                    
        case MENU_MAIN_RETURN:
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(main_m);
                    ah_draw_cursor(5);
                    state = MENU_MAIN_RETURN;              
                
                case EV_BUTTON_SL:
                    ah_draw_time();
                    ah_draw_date();
                    ah_draw_sensor();
                    // later to be moved to seperate states
                    ah_draw_snooze();
                    ah_draw_alarm();
                    state = HOME_SCREEN;
                    break;
                
                case EV_BUTTON_UP:
                    ah_menu(main_m);
                    ah_draw_cursor(4);
                    state = MENU_MAIN_MUSIC;
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    state = MENU_MAIN_CLOCK;
                    break;
                
                default:    
                    state = MENU_MAIN_RETURN;
            }
        
        case MENU_CLOCK_TIME:
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    state = MENU_MAIN_CLOCK;                    
                
                case EV_BUTTON_SL:          
                    state = MENU_CLOCK_TIME;            // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                    ah_menu(clock);
                    ah_draw_cursor(3);
                    state = MENU_CLOCK_RETURN;
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(clock);
                    ah_draw_cursor(2);
                    state = MENU_CLOCK_ALARM;
                    break;
                
                default:
                    state = MENU_CLOCK_TIME;
            }
        
        case MENU_CLOCK_ALARM:  
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(clock);
                    ah_draw_cursor(2);
                    state = MENU_CLOCK_ALARM;
                    break;
                
                case EV_BUTTON_SL:              
          
                    state = MENU_CLOCK_ALARM;           // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                    ah_menu(clock);
                    ah_draw_cursor(1);
                    state = MENU_CLOCK_TIME;
                    break;
                 
                case EV_BUTTON_DN:
                    ah_menu(clock);
                    ah_draw_cursor(3);
                    state = MENU_CLOCK_RETURN;
                    break;                    
                
                default: 
                    state = MENU_CLOCK_ALARM;
            }
        
        case MENU_CLOCK_RETURN: 
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(clock);
                    ah_draw_cursor(3);
                    state = MENU_CLOCK_RETURN;
                    break;                    
                
                case EV_BUTTON_SL:
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    state = MENU_MAIN_CLOCK;
                    break;    
                
                case EV_BUTTON_UP:
                    ah_menu(clock);
                    ah_draw_cursor(2);
                    state = MENU_CLOCK_ALARM;
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(clock);
                    ah_draw_cursor(1);
                    state = MENU_CLOCK_TIME;
                    break;
                
                default:  
                    state = MENU_CLOCK_RETURN;
            }
        
        case MENU_MOODL_PRESETS:
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(clock);
                    ah_draw_cursor(1);
                    state = MENU_CLOCK_TIME;
                    break;                    
                
                case EV_BUTTON_SL:          
                    state = MENU_MOODL_PRESETS;         // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                    ah_menu(moodlight);
                    ah_draw_cursor(3);
                    state = MENU_MOODL_RETURN;  
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(moodlight);
                    ah_draw_cursor(2);
                    state = MENU_MOODL_CUSTOM;  
                    break;
                
                default:  
                    state = MENU_MOODL_PRESETS;
            }
                
        case MENU_MOODL_CUSTOM:
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(moodlight);
                    ah_draw_cursor(2);
                    state = MENU_MOODL_CUSTOM;  
                    break;                    
                
                case EV_BUTTON_SL:
          
                    state = MENU_MOODL_CUSTOM;          // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                    ah_menu(moodlight);
                    ah_draw_cursor(1);
                    state = MENU_MOODL_PRESETS;  
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(moodlight);
                    ah_draw_cursor(3);
                    state = MENU_MOODL_RETURN;  
                    break;
                        
                default:
                    state = MENU_MOODL_CUSTOM;
            }
        
        case MENU_MOODL_RETURN:
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(moodlight);
                    ah_draw_cursor(3);
                    state = MENU_MOODL_RETURN;  
                    break;                    
                
                case EV_BUTTON_SL:
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    state = MENU_MAIN_CLOCK;
                    break;
                
                case EV_BUTTON_UP:
                    ah_menu(moodlight);
                    ah_draw_cursor(2);
                    state = MENU_MOODL_CUSTOM;  
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(moodlight);
                    ah_draw_cursor(1);
                    state = MENU_MOODL_PRESETS;  
                    break;
                        
                default:
                    state = MENU_MOODL_RETURN;
            }
            
        
        case MENU_BT_PAIR:
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(moodlight);
                    ah_draw_cursor(1);
                    state = MENU_MOODL_PRESETS;  
                    break;                    
                
                case EV_BUTTON_SL:        
                    state = MENU_BT_PAIR;               // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                    ah_menu(bluetooth);
                    ah_draw_cursor(3);
                    state = MENU_BT_RETURN;  
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(bluetooth);
                    ah_draw_cursor(2);
                    state = MENU_BT_SETTINGS;  
                    break;
                
                default:  
                    state = MENU_BT_PAIR;
            }
            
        case MENU_BT_SETTINGS:
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(bluetooth);
                    ah_draw_cursor(2);
                    state = MENU_BT_SETTINGS;  
                    break;                   
                
                case EV_BUTTON_SL:          
                    state = MENU_BT_SETTINGS;           // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                    ah_menu(bluetooth);
                    ah_draw_cursor(1);
                    state = MENU_BT_PAIR;  
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(bluetooth);
                    ah_draw_cursor(3);
                    state = MENU_BT_RETURN;  
                    break;
                
                default:  
                    state = MENU_BT_SETTINGS;
            }      
       
        case MENU_BT_RETURN:
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(bluetooth);
                    ah_draw_cursor(3);
                    state = MENU_BT_RETURN;  
                    break;                    
                
                case EV_BUTTON_SL:
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    state = MENU_MAIN_CLOCK;
                    break;
                
                case EV_BUTTON_UP:
                    ah_menu(bluetooth);
                    ah_draw_cursor(2);
                    state = MENU_BT_SETTINGS;  
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(bluetooth);
                    ah_draw_cursor(1);
                    state = MENU_BT_PAIR;  
                    break;
                
                default:  
                    state = MENU_BT_RETURN;
            }            
        
        case MENU_MUSIC_PLAYER:
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(bluetooth);
                    ah_draw_cursor(1);
                    state = MENU_BT_PAIR;  
                    break;                  
                
                case EV_BUTTON_SL:         
                    state = MENU_MUSIC_PLAYER;          // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                    ah_menu(music);
                    ah_draw_cursor(3);
                    state = MENU_MUSIC_RETURN;  
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(music);
                    ah_draw_cursor(2);
                    state = MENU_MUSIC_VOLUME;  
                    break;
                
                default:  
                    state = MENU_MUSIC_PLAYER;
            }             
       
        case MENU_MUSIC_VOLUME:
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(music);
                    ah_draw_cursor(2);
                    state = MENU_MUSIC_VOLUME;  
                    break;                  
                
                case EV_BUTTON_SL:         
                    state = MENU_MUSIC_VOLUME;          // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                    ah_menu(music);
                    ah_draw_cursor(1);
                    state = MENU_MUSIC_PLAYER;  
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(music);
                    ah_draw_cursor(3);
                    state = MENU_MUSIC_RETURN;  
                    break;
                
                default:  
                    state = MENU_MUSIC_PLAYER;
            }          
        
        case MENU_MUSIC_RETURN:
            switch (event) {
                case EV_NO_EVENT:
                    ah_menu(music);
                    ah_draw_cursor(3);
                    state = MENU_MUSIC_RETURN;  
                    break;                    
                
                case EV_BUTTON_SL:
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    state = MENU_MAIN_CLOCK;
                    break;
                
                case EV_BUTTON_UP:
                    ah_menu(music);
                    ah_draw_cursor(2);
                    state = MENU_MUSIC_VOLUME;  
                    break;
                
                case EV_BUTTON_DN:
                    ah_menu(music);
                    ah_draw_cursor(1);
                    state = MENU_MUSIC_PLAYER;  
                    break;
                
                default:  
                    state = MENU_MUSIC_PLAYER;
            }
        }            
}



