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
#include "tim.h"


//========================================
// Module-wide variables & constants
//========================================
uint8_t led_intens_w = 50;
uint8_t led_intens_r = 50;
uint8_t led_intens_g = 50;
uint8_t led_intens_b = 50;
uint8_t set_hour;
uint8_t set_min;
uint8_t set_day;
uint8_t set_mon;
uint8_t set_year;
uint8_t set_al_hr;
uint8_t set_al_min;

color_preset_t color_preset = white;

// current FSM state
state_t state = HOME_SCREEN;


void fsm_init(void) {
    state = HOME_SCREEN;
    st7565_clear_buffer(LCD_Buffer);
    ah_draw_time();
    ah_draw_date();
    ah_draw_sensor();
    // later to be moved to seperate states
    ah_draw_snooze();
    ah_draw_alarm();

}

// State Machine

void fsm_handle_event(event_t event) {
    switch (state) {
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
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_HOUR;
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
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_setalarm(LCD_Buffer, set_al_hr, set_al_min);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_ALARM_HOUR;
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
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_WHITE;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(moodlight);
                    ah_draw_cursor(4);
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
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CUSTOM_WHITE;
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
                    state = MENU_MOODL_OFF;
                    break;

                default:
                    state = MENU_MOODL_CUSTOM;
            }
            break;

        case MENU_MOODL_OFF:
            switch (event) {
                case EV_BUTTON_SL:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(moodlight);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    ah_stop_led(&htim1);
                    state = MENU_MOODL_OFF;
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
                    ah_draw_cursor(4);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MOODL_RETURN;
                    break;

                default:
                    state = MENU_MOODL_OFF;
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
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_MOODL_OFF;
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

//=======================================================================================================================
// Menu - Moodlight - Custom Colors (Set individual values for RGBW)
//=======================================================================================================================

        case MENU_CUSTOM_WHITE:
            switch (event) {
                case EV_BUTTON_LT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (led_intens_w > 0) {
                        led_intens_w -= 5;
                    }
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    ah_set_custom(led_intens_r, led_intens_g, led_intens_b, led_intens_w);
                    state = MENU_CUSTOM_WHITE;
                    break;

                case EV_BUTTON_RT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (led_intens_w < 100) {
                        led_intens_w += 5;
                    }
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    ah_set_custom(led_intens_r, led_intens_g, led_intens_b, led_intens_w);
                    state = MENU_CUSTOM_WHITE;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(5);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CUSTOM_RETURN;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CUSTOM_RED;
                    break;

                default:
                    state = MENU_CUSTOM_WHITE;
            }
            break;

        case MENU_CUSTOM_RED:
            switch (event) {
                case EV_BUTTON_LT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (led_intens_r > 0) {
                        led_intens_r -= 5;
                    }
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    ah_set_custom(led_intens_r, led_intens_g, led_intens_b, led_intens_w);
                    state = MENU_CUSTOM_RED;
                    break;

                case EV_BUTTON_RT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (led_intens_r < 100) {
                        led_intens_r += 5;
                    }
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    ah_set_custom(led_intens_r, led_intens_g, led_intens_b, led_intens_w);
                    state = MENU_CUSTOM_RED;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CUSTOM_WHITE;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CUSTOM_GREEN;
                    break;

                default:
                    state = MENU_CUSTOM_RED;
            }
            break;

        case MENU_CUSTOM_GREEN:
            switch (event) {
                case EV_BUTTON_LT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (led_intens_g > 0) {
                        led_intens_g -= 5;
                    }
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    ah_set_custom(led_intens_r, led_intens_g, led_intens_b, led_intens_w);
                    state = MENU_CUSTOM_GREEN;
                    break;

                case EV_BUTTON_RT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (led_intens_g < 100) {
                        led_intens_g += 5;
                    }
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    ah_set_custom(led_intens_r, led_intens_g, led_intens_b, led_intens_w);
                    state = MENU_CUSTOM_GREEN;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CUSTOM_RED;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(4);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CUSTOM_BLUE;
                    break;

                default:
                    state = MENU_CUSTOM_GREEN;
            }
            break;

        case MENU_CUSTOM_BLUE:
            switch (event) {
                case EV_BUTTON_LT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (led_intens_b > 0) {
                        led_intens_b -= 5;
                    }
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(4);
                    st7565_write_buffer(LCD_Buffer);
                    ah_set_custom(led_intens_r, led_intens_g, led_intens_b, led_intens_w);
                    state = MENU_CUSTOM_BLUE;
                    break;

                case EV_BUTTON_RT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (led_intens_b < 100) {
                        led_intens_b += 5;
                    }
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(4);
                    st7565_write_buffer(LCD_Buffer);
                    ah_set_custom(led_intens_r, led_intens_g, led_intens_b, led_intens_w);
                    state = MENU_CUSTOM_BLUE;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CUSTOM_GREEN;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(5);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CUSTOM_RETURN;
                    break;

                default:
                    state = MENU_CUSTOM_BLUE;
            }
            break;

        case MENU_CUSTOM_RETURN:
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
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(4);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CUSTOM_BLUE;
                    break;
                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_custom(LCD_Buffer, led_intens_w, led_intens_r, led_intens_g, led_intens_b);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CUSTOM_WHITE;
                    break;
                default:
                    state = MENU_CUSTOM_RETURN;
            }
            break;

//=======================================================================================================================
// Menu - Clock - Set Time & Date (Set Date and Time values/ variables for RTC)
//=======================================================================================================================

        case MENU_SETTIME_HOUR:
            switch (event) {
                case EV_BUTTON_LT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (set_hour > 0) {
                        set_hour -= 1;
                    } else if (set_hour == 0) {
                        set_hour = 23;
                    }
                    ah_draw_cursor(1);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_HOUR;
                    break;

                case EV_BUTTON_RT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (set_hour < 23) {
                        set_hour += 1;
                    } else if (set_hour == 23) {
                        set_hour = 0;
                    }
                    ah_draw_cursor(1);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_HOUR;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    ah_draw_cursor(6);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_RETURN;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_MINUTE;
                    break;

                default:
                    state = MENU_SETTIME_HOUR;
            }
            break;

        case MENU_SETTIME_MINUTE:
            switch (event) {
                case EV_BUTTON_LT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (set_min > 0) {
                        set_min -= 1;
                    } else if (set_min == 0) {
                        set_min = 59;
                    }
                    ah_draw_cursor(2);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_MINUTE;
                    break;

                case EV_BUTTON_RT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (set_min < 59) {
                        set_min += 1;
                    } else if (set_min == 59) {
                        set_min = 0;
                    }
                    ah_draw_cursor(2);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_MINUTE;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_HOUR;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_DAY;
                    break;

                default:
                    state = MENU_SETTIME_MINUTE;
            }
            break;

        case MENU_SETTIME_DAY:
            switch (event) {
                case EV_BUTTON_LT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (set_day > 1) {
                        set_day -= 1;
                    } else if (set_day == 1) {
                        set_day = 31;
                    }
                    ah_draw_cursor(3);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_DAY;
                    break;

                case EV_BUTTON_RT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (set_day < 31) {
                        set_day += 1;
                    } else if (set_day == 31) {
                        set_day = 1;
                    }
                    ah_draw_cursor(3);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_DAY;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_MINUTE;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    ah_draw_cursor(4);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_MONTH;
                    break;

                default:
                    state = MENU_SETTIME_DAY;
            }
            break;

        case MENU_SETTIME_MONTH:
            switch (event) {
                case EV_BUTTON_LT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (set_mon > 1) {
                        set_mon -= 1;
                    } else if (set_mon == 1) {
                        set_mon = 12;
                    }
                    ah_draw_cursor(4);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_MONTH;
                    break;

                case EV_BUTTON_RT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (set_mon < 12) {
                        set_mon += 1;
                    } else if (set_mon == 12) {
                        set_mon = 1;
                    }
                    ah_draw_cursor(4);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_MONTH;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_DAY;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    ah_draw_cursor(5);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_YEAR;
                    break;

                default:
                    state = MENU_SETTIME_MONTH;
            }
            break;


        case MENU_SETTIME_YEAR:
            switch (event) {
                case EV_BUTTON_LT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (set_year > 0) {
                        set_year -= 1;
                    } else if (set_year <= 0) {
                        set_year = 99;
                    }
                    ah_draw_cursor(5);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_YEAR;
                    break;

                case EV_BUTTON_RT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (set_year < 99) {
                        set_year += 1;
                    } else if (set_year >= 99) {
                        set_year = 0;
                    }
                    ah_draw_cursor(5);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_YEAR;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    ah_draw_cursor(4);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_MONTH;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    ah_draw_cursor(6);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_RETURN;
                    break;

                default:
                    state = MENU_SETTIME_YEAR;
            }
            break;


        case MENU_SETTIME_RETURN:
            switch (event) {
                case EV_BUTTON_SL:
                    ah_set_TimeDate(set_hour, set_min, 0, set_day, set_mon, set_year);
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(clock);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_CLOCK_TIME;
                    break;
                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    ah_draw_cursor(5);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_YEAR;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_settime(LCD_Buffer, set_hour, set_min, set_day, set_mon, set_year);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_SETTIME_HOUR;
                    break;

                default:
                    state = MENU_SETTIME_RETURN;
            }
            break;

//=======================================================================================================================
// Menu - Clock - Alarm   (Set Alarm Time)
//=======================================================================================================================

        case MENU_ALARM_HOUR:
            switch (event) {
                case EV_BUTTON_LT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (set_al_hr > 0) {
                        set_al_hr -= 1;
                    } else if (set_al_hr == 0) {
                        set_al_hr = 23;
                    }
                    ah_draw_cursor(1);
                    st7565_drawmenu_setalarm(LCD_Buffer, set_al_hr, set_al_min);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_ALARM_HOUR;
                    break;

                case EV_BUTTON_RT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (set_al_hr < 23) {
                        set_al_hr += 1;
                    } else if (set_al_hr == 23) {
                        set_al_hr = 0;
                    }
                    ah_draw_cursor(1);
                    st7565_drawmenu_setalarm(LCD_Buffer, set_al_hr, set_al_min);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_ALARM_HOUR;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_setalarm(LCD_Buffer, set_al_hr, set_al_min);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_ALARM_RETURN;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_setalarm(LCD_Buffer, set_al_hr, set_al_min);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_ALARM_MINUTE;
                    break;

                default:
                    state = MENU_ALARM_HOUR;
            }
            break;

        case MENU_ALARM_MINUTE:
            switch (event) {
                case EV_BUTTON_LT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (set_al_min > 0) {
                        set_al_min -= 1;
                    } else if (set_al_min == 0) {
                        set_al_min = 59;
                    }
                    ah_draw_cursor(2);
                    st7565_drawmenu_setalarm(LCD_Buffer, set_al_hr, set_al_min);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_ALARM_MINUTE;
                    break;

                case EV_BUTTON_RT:
                    st7565_clear_buffer(LCD_Buffer);
                    if (set_al_min < 59) {
                        set_al_min += 1;
                    } else if (set_al_min == 59) {
                        set_al_min = 0;
                    }
                    ah_draw_cursor(2);
                    st7565_drawmenu_setalarm(LCD_Buffer, set_al_hr, set_al_min);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_ALARM_MINUTE;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_setalarm(LCD_Buffer, set_al_hr, set_al_min);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_ALARM_HOUR;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_setalarm(LCD_Buffer, set_al_hr, set_al_min);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_ALARM_RETURN;
                    break;

                default:
                    state = MENU_ALARM_MINUTE;
            }
            break;

        case MENU_ALARM_RETURN:
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
                    st7565_drawmenu_setalarm(LCD_Buffer, set_al_hr, set_al_min);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_ALARM_MINUTE;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    st7565_drawmenu_setalarm(LCD_Buffer, set_al_hr, set_al_min);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_ALARM_HOUR;
                    break;

                default:
                    state = MENU_ALARM_RETURN;
            }
            break;

//=======================================================================================================================
// Menu - Moodlight - Colors (Choose Color presets)
//=======================================================================================================================

        case MENU_COLORS_WHITE:
            switch (event) {
                case EV_BUTTON_SL:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(1);
                    ah_setcolor(white);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_WHITE;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(7);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_RETURN;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_RED;
                    break;

                default:
                    state = MENU_COLORS_WHITE;
            }
            break;


        case MENU_COLORS_RED:
            switch (event) {
                case EV_BUTTON_SL:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(2);
                    ah_setcolor(red);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_RED;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_WHITE;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_GREEN;
                    break;

                default:
                    state = MENU_COLORS_RED;
            }
            break;


        case MENU_COLORS_GREEN:
            switch (event) {
                case EV_BUTTON_SL:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(3);
                    ah_setcolor(green);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_GREEN;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(2);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_RED;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(4);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_BLUE;
                    break;

                default:
                    state = MENU_COLORS_GREEN;
            }
            break;


        case MENU_COLORS_BLUE:
            switch (event) {
                case EV_BUTTON_SL:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(4);
                    ah_setcolor(blue);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_BLUE;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(3);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_GREEN;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(5);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_YELLOW;
                    break;

                default:
                    state = MENU_COLORS_BLUE;
            }
            break;


        case MENU_COLORS_YELLOW:
            switch (event) {
                case EV_BUTTON_SL:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(5);
                    ah_setcolor(yellow);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_YELLOW;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(4);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_BLUE;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(6);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_PURPLE;
                    break;

                default:
                    state = MENU_COLORS_YELLOW;
            }
            break;


        case MENU_COLORS_PURPLE:
            switch (event) {
                case EV_BUTTON_SL:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(6);
                    ah_setcolor(purple);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_PURPLE;
                    break;

                case EV_BUTTON_UP:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(5);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_YELLOW;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(7);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_RETURN;
                    break;

                default:
                    state = MENU_COLORS_PURPLE;
            }
            break;

        case MENU_COLORS_RETURN:
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
                    ah_menu(colors);
                    ah_draw_cursor(6);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_PURPLE;
                    break;

                case EV_BUTTON_DN:
                    st7565_clear_buffer(LCD_Buffer);
                    ah_menu(colors);
                    ah_draw_cursor(1);
                    st7565_write_buffer(LCD_Buffer);
                    state = MENU_COLORS_WHITE;
                    break;

                default:
                    state = MENU_COLORS_RETURN;
            }
            break;

    }
}
