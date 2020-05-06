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
                case EV_BUTTON_SL:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MAIN_CLOCK;
                    break;
                
                default:
                    state = HOME_SCREEN;
                    break;
            }
        break;

        case MENU_MAIN_CLOCK:
            switch (event) {
                case EV_BUTTON_SL:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(clock);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CLOCK_TIME;
                    break;
               
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(main_m);
                    ah_draw_cursor(5);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MAIN_RETURN;
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(main_m);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MAIN_MOODLIGHT;
                    break;                
                          
                default:
                    state = MENU_MAIN_CLOCK;   
                    break;
            }
            break;
            
        case MENU_MAIN_MOODLIGHT:
            switch (event) {
                case EV_BUTTON_SL:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(moodlight);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MOODL_PRESETS;
                    break;
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MAIN_CLOCK;
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(main_m);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MAIN_BLUETOOTH;
                    break;                   
                
                default:
                    state = MENU_MAIN_MOODLIGHT;
                    break;
            }
            break;
        
        case MENU_MAIN_BLUETOOTH:
            switch (event) {
                case EV_BUTTON_SL:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(bluetooth);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_BT_PAIR;
                    break;
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(main_m);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MAIN_MOODLIGHT;
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(main_m);
                    ah_draw_cursor(4);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MAIN_MUSIC;
                    break;
                
                default:
                    state = MENU_MAIN_BLUETOOTH;
            }
            break;

        case MENU_MAIN_MUSIC:    
            switch (event) {
                case EV_BUTTON_SL:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(music);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MUSIC_PLAYER;
                    break;    
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(main_m);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MAIN_BLUETOOTH;
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(main_m);
                    ah_draw_cursor(5);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MAIN_RETURN;
                    break;
                
                default:
                    state = MENU_MAIN_MUSIC;
            }
            break;
                    
        case MENU_MAIN_RETURN:
            switch (event) {
                case EV_BUTTON_SL:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_draw_time();
                    ah_draw_date();
                    ah_draw_sensor();
                    // later to be moved to seperate states
                    ah_draw_snooze();
                    ah_draw_alarm();
                    st7565_write_buffer(LCD_Buffer);
                    state = HOME_SCREEN;
                    break;
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(main_m);
                    ah_draw_cursor(4);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MAIN_MUSIC;
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MAIN_CLOCK;
                    break;
                
                default:    
                    state = MENU_MAIN_RETURN;
            }
            break;
        
        case MENU_CLOCK_TIME:
            switch (event) {
                case EV_BUTTON_SL:          
                    state = MENU_CLOCK_TIME;            // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(clock);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CLOCK_RETURN;
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(clock);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CLOCK_ALARM;
                    break;
                
                default:
                    state = MENU_CLOCK_TIME;
            }
            break;
        
        case MENU_CLOCK_ALARM:  
            switch (event) {
                case EV_BUTTON_SL:              
          
                    state = MENU_CLOCK_ALARM;           // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(clock);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CLOCK_TIME;
                    break;
                 
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(clock);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CLOCK_RETURN;
                    break;                    
                
                default: 
                    state = MENU_CLOCK_ALARM;
            }
            break;
        
        case MENU_CLOCK_RETURN: 
            switch (event) {
                case EV_BUTTON_SL:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MAIN_CLOCK;
                    break;    
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(clock);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CLOCK_ALARM;
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(clock);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CLOCK_TIME;
                    break;
                
                default:  
                    state = MENU_CLOCK_RETURN;
            }
            break;
        
        case MENU_MOODL_PRESETS:
            switch (event) {
                case EV_BUTTON_SL:          
                    state = MENU_MOODL_PRESETS;         // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(moodlight);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MOODL_RETURN;  
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(moodlight);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MOODL_CUSTOM;  
                    break;
                
                default:  
                    state = MENU_MOODL_PRESETS;
            }
            break;
                
        case MENU_MOODL_CUSTOM:
            switch (event) {
                case EV_BUTTON_SL:
                    state = MENU_MOODL_CUSTOM;          // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(moodlight);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MOODL_PRESETS;  
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(moodlight);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MOODL_RETURN;  
                    break;
                        
                default:
                    state = MENU_MOODL_CUSTOM;
            }
            break;
        
        case MENU_MOODL_RETURN:
            switch (event) {
                case EV_BUTTON_SL:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MAIN_CLOCK;
                    break;
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(moodlight);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MOODL_CUSTOM;  
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(moodlight);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MOODL_PRESETS;  
                    break;
                        
                default:
                    state = MENU_MOODL_RETURN;
            }
            break;
            
        
        case MENU_BT_PAIR:
            switch (event) {
                case EV_BUTTON_SL:        
                    state = MENU_BT_PAIR;               // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(bluetooth);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_BT_RETURN;  
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(bluetooth);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_BT_SETTINGS;  
                    break;
                
                default:  
                    state = MENU_BT_PAIR;
            }
            break;
            
        case MENU_BT_SETTINGS:
            switch (event) {
                case EV_BUTTON_SL:          
                    state = MENU_BT_SETTINGS;           // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(bluetooth);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_BT_PAIR;  
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(bluetooth);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_BT_RETURN;  
                    break;
                
                default:  
                    state = MENU_BT_SETTINGS;
            }
            break;
       
        case MENU_BT_RETURN:
            switch (event) {
                case EV_BUTTON_SL:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MAIN_CLOCK;
                    break;
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(bluetooth);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_BT_SETTINGS;  
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(bluetooth);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_BT_PAIR;  
                    break;
                
                default:  
                    state = MENU_BT_RETURN;
            }
            break;
        
        case MENU_MUSIC_PLAYER:
            switch (event) {
                case EV_BUTTON_SL:         
                    state = MENU_MUSIC_PLAYER;          // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(music);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MUSIC_RETURN;  
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(music);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MUSIC_VOLUME;  
                    break;
                
                default:  
                    state = MENU_MUSIC_PLAYER;
            }
            break;
       
        case MENU_MUSIC_VOLUME:
            switch (event) {
                case EV_BUTTON_SL:         
                    state = MENU_MUSIC_VOLUME;          // To be continued ********************************************************
                    break;
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(music);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MUSIC_PLAYER;  
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(music);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MUSIC_RETURN;  
                    break;
                
                default:  
                    state = MENU_MUSIC_PLAYER;
            }
            break;
        
        case MENU_MUSIC_RETURN:
            switch (event) {
                case EV_BUTTON_SL:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(main_m);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MAIN_CLOCK;
                    break;
                
                case EV_BUTTON_UP:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(music);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MUSIC_VOLUME;  
                    break;
                
                case EV_BUTTON_DN:
                	st7565_clear_buffer(LCD_Buffer);
                    ah_menu(music);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MUSIC_PLAYER;  
                    break;
                
                default:  
                    state = MENU_MUSIC_PLAYER;
            }
            break;
        }            
}



