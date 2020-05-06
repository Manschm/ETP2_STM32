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
#include <stdio.h>
#include "event_handler.h"
#include "main.h"


#define BUTTON_UP_MASK      0x10
#define BUTTON_DN_MASK      0x08
#define BUTTON_LT_MASK      0x04
#define BUTTON_RT_MASK      0x02
#define BUTTON_SL_MASK      0x01

static uint8_t  button_value_old =  0xffu;

//==============================================================================
  
event_t eh_get_event(void) {  
    
    //detect timer event on timer 14
    // HAL_TIM_Base_Start_IT(&htim14)  -- Start timer
   
    
    //detect button events 
    
    uint8_t button_value = HAL_GPIO_ReadPin (SWUP_GPIO_Port, SWUP_Pin);
    button_value <<= 1;
    button_value |= HAL_GPIO_ReadPin (SWDN_GPIO_Port, SWDN_Pin);
    button_value <<= 1;
    button_value |= HAL_GPIO_ReadPin (SWLT_GPIO_Port, SWLT_Pin);
    button_value <<= 1;
    button_value |= HAL_GPIO_ReadPin (SWRT_GPIO_Port, SWRT_Pin);
    button_value <<= 1;
    button_value |= HAL_GPIO_ReadPin (SWSL_GPIO_Port, SWSL_Pin);
 
    uint8_t button_edge_pos = ~button_value_old & button_value;
    button_value_old = button_value;
    
    if (button_edge_pos & BUTTON_UP_MASK) {
        return EV_BUTTON_UP;
    }
    else if (button_edge_pos & BUTTON_DN_MASK) {
        return EV_BUTTON_DN;
    }
    else if (button_edge_pos & BUTTON_LT_MASK) {
        return EV_BUTTON_LT;
    }    
    else if (button_edge_pos & BUTTON_RT_MASK) {
        return EV_BUTTON_RT;
    }    
    else if (button_edge_pos & BUTTON_SL_MASK) {
        return EV_BUTTON_SL;
    } 
    
    return EV_NO_EVENT;
}


