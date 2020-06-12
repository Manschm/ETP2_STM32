/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "shtc3.h"
#include "st7565.h"
#include <string.h>
#include "event_handler.h"
#include "state_machine.h"
#include "action_handler.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SMOOTH_LEN      64U  // Must have 2 as a base
#define SMOOTH_SHIFT    6U  // Must be the exponent of SMOOTH_LEN

// UART defines
#define UART_DATA_LEN   5U

// LED enums and structs
typedef enum {
    cRed = 0,
    cGreen = 1,
    cBlue = 2,
    cBrightness = 3 // I know, this is not a color
} colorInput;

typedef struct {
    uint8_t colors[4][SMOOTH_LEN];
    uint8_t time[4];
} Smoother_TypeDef;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// UART variables
uint8_t uartRxData[UART_DATA_LEN];      // Most recent data
uint8_t workingData[4];
uint8_t setData[4];                     // Data currently displayed
uint8_t tempData[4];

// LED variables
uint16_t rgbwValues[4];
uint8_t lightSwitch = 0;
Smoother_TypeDef smoother;

// I2C buffer
//uint8_t shtc3RxBuf[6];
//uint8_t shtc3TxBuf[2];

// RTC ISR
static uint8_t counter = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint8_t ColorSmoother(Smoother_TypeDef *holder, uint8_t input, colorInput color);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_RTC_Init();
  MX_TIM1_Init();
  MX_TIM15_Init();
  MX_USART1_UART_Init();
  MX_ADC_Init();
  MX_I2C2_Init();
  MX_TIM3_Init();
  MX_TIM6_Init();
  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */

    HAL_RTC_DeactivateAlarm(&hrtc, RTC_ALARM_A);

    __HAL_TIM_SET_COMPARE(&htim3, LED_CH_UP, 900);
    HAL_TIM_PWM_Start(&htim3, LED_CH_UP);
    __HAL_TIM_SET_COMPARE(&htim3, LED_CH_DN, 900);
    HAL_TIM_PWM_Start(&htim3, LED_CH_DN);
    __HAL_TIM_SET_COMPARE(&htim3, LED_CH_LT, 900);
    HAL_TIM_PWM_Start(&htim3, LED_CH_LT);
    __HAL_TIM_SET_COMPARE(&htim3, LED_CH_RT, 900);
    HAL_TIM_PWM_Start(&htim3, LED_CH_RT);

    //HAL_TIM_Base_Start_IT(&htim6);	// Color change timer

    //HAL_I2C_Master_Transmit(&hi2c2, SHTC3_ADDR,

    st7565_init();
    st7565_backlight_enable();
    st7565_set_brightness(0);

    HAL_Delay(10);

    // Show startup screen
    st7565_clear_buffer();
    st7565_drawbitmap(43, 5, atom_symbol, 43, 51, 10);
    st7565_drawstring(22, 7, "Moodlight 2020");
    st7565_drawstring(0, 0, "Manuel");
    st7565_drawstring(0, 1, "Schmid");
    st7565_drawstring(85, 0, "Lukas");
    st7565_drawstring(85, 1, "Eugster");
    st7565_write_buffer();

    HAL_Delay(3000);
    st7565_clear_buffer();

    event_t event;
    fsm_init();

    // RTC init
    RTC_AlarmTypeDef sAlarm;
    HAL_RTC_GetAlarm(&hrtc, &sAlarm, RTC_ALARM_A, RTC_FORMAT_BCD);
    HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD);

    // UART init
    HAL_UART_Receive_DMA(&huart1, uartRxData, UART_DATA_LEN);
    HAL_UART_DMAStop(&huart1);
    setData[0] = 0;
    setData[1] = 0;
    setData[2] = 0;
    setData[3] = 0;
    workingData[0] = 0;
    workingData[1] = 0;
    workingData[2] = 0;
    workingData[3] = 0;
    HAL_UART_Receive_DMA(&huart1, uartRxData, UART_DATA_LEN);
    HAL_TIM_Base_Start_IT(&htim6);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (1) {

        event = eh_get_event();
        if (event != EV_NO_EVENT) {
            fsm_handle_event(event);
        }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    }
#pragma clang diagnostic pop
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure LSE Drive Capability 
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_HIGH);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI14|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_RTC;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM6) {
        if (lightSwitch) {
            tempData[0] = workingData[0];
            tempData[1] = workingData[1];
            tempData[2] = workingData[2];
            tempData[3] = workingData[3];
            uint8_t red     = ColorSmoother(&smoother, tempData[0], cRed);
            uint8_t green   = ColorSmoother(&smoother, tempData[1], cGreen);
            uint8_t blue    = ColorSmoother(&smoother, tempData[2], cBlue);
            uint8_t bright  = ColorSmoother(&smoother, tempData[3], cBrightness);


            // Convert RGB to RGBW
            if ((setData[0] != red) || (setData[1] != green) || (setData[2] != blue) || (setData[3] != bright)) {
                uint8_t white;  // Also min value
                uint8_t max;

                // Find min and max values
                if (red <= green) {
                    if (red <= blue) {          // red <= (green && blue)
                        white = red;
                        if (blue >= green) {    // red <= green <= blue
                            max = blue;
                        } else {
                            max = green;        // red <= blue < green
                        }
                    } else {                    // blue < red <= green
                        white = blue;
                        max = green;
                    }
                } else if (green <= blue) {     // green <= (red && blue)
                    white = green;
                    if (blue >= red) {          // green <= red <= blue
                        max = blue;
                    } else {                    // green <= blue < red
                        max = red;
                    }
                } else {                        // blue < green < red
                    white = blue;
                    max = red;
                }

                float multiplier = (float)white / 255.0f / (float)max + 1.0f;

                rgbwValues[0] = multiplier * (float)red - (float)white;
                rgbwValues[1] = multiplier * (float)green - (float)white;
                rgbwValues[2] = multiplier * (float)blue - (float)white;
                rgbwValues[3] = white;

                float brightness = (float)bright / 100.0f;
                for (uint8_t i = 0; i < 4; i++) {
                    rgbwValues[i] = rgbwValues[i] << 1U;    // Adjust scale (max. value 255 becomes 510)
                    rgbwValues[i] *= brightness;            // Scale with brightness
                }

                // Apply new RGBW values
                ah_setPWM(&htim1, rgbwValues[0], rgbwValues[1], rgbwValues[2], rgbwValues[3]);

                setData[0] = tempData[0];
                setData[1] = tempData[1];
                setData[2] = tempData[2];
                setData[3] = tempData[3];
            }
        } else {
            ColorSmoother(&smoother, 0, cRed);
            ColorSmoother(&smoother, 0, cGreen);
            ColorSmoother(&smoother, 0, cBlue);
            ColorSmoother(&smoother, 0, cBrightness);
            ah_setPWM(&htim1, 0, 0, 0, 0);
        }
	}
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) {
    if (state == HOME_SCREEN) {
        if (counter < 4) {
            counter += 1;
        } else {
            st7565_clear_buffer();
            ah_draw_time();
            ah_draw_date();
            ah_draw_sensor();
            ah_draw_snooze();
            ah_draw_alarm();
            counter = 0;
        }
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    lightSwitch = uartRxData[1];
    workingData[0] = uartRxData[2]; // Red
    workingData[1] = uartRxData[3]; // Green
    workingData[2] = uartRxData[4]; // Blue
    workingData[3] = uartRxData[0]; // Brightness
}

uint8_t ColorSmoother(Smoother_TypeDef *holder, uint8_t input, colorInput color) {
    if (holder->time[color] >= SMOOTH_LEN) {
        holder->time[color] = 0;
    }

    holder->colors[color][holder->time[color]] = input;

    uint16_t sum = 0;
    for(uint8_t i = 0; i < SMOOTH_LEN; i++) {
        sum += holder->colors[color][i];
    }

    holder->time[color]++;
    return (uint8_t)(sum >> SMOOTH_SHIFT);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
