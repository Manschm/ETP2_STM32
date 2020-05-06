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
#include "i2c.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "shtc3.h"
#include "lcd_st7565.h"
#include <string.h>

#include "event_handler.h"
#include "state_machine.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PWM_CH_R	TIM_CHANNEL_1
#define PWM_CH_G	TIM_CHANNEL_2
#define PWM_CH_B	TIM_CHANNEL_3
#define PWM_CH_W	TIM_CHANNEL_4
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// Interrupt variables
static uint8_t updateUI = 0;
static uint8_t updateSensor = 0;

// Data buffer
uint8_t shtc3RxBuf[6];
uint8_t shtc3TxBuf[2];

// Flags
uint8_t readSHTC3 = 0;

// LCD buffer
uint8_t LCD_Buffer[1024];


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
	HAL_GPIO_WritePin(LEDUP_GPIO_Port, LEDUP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LEDDN_GPIO_Port, LEDDN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LEDLT_GPIO_Port, LEDLT_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LEDRT_GPIO_Port, LEDRT_Pin, GPIO_PIN_SET);
	
	
	__HAL_TIM_SET_COMPARE(&htim1, PWM_CH_R, 200);
	HAL_TIM_PWM_Start(&htim1, PWM_CH_R);
	
	
	//HAL_TIM_Base_Start_IT(&htim3);	// UI timer
	//HAL_TIM_Base_Start_IT(&htim6);	// Sensor timer
	
	//HAL_I2C_Master_Transmit(&hi2c2, SHTC3_ADDR, 
    
    st7565_init();
//=======================================================================
//Begin program
//=======================================================================

// Turn on / initialize RTC

//


//=======================================================================
// Show Startup Screen
//=======================================================================
    st7565_backlight_enable(); 
    st7565_set_brightness(0); 
    HAL_Delay(100);
   
// Show startup screen
    st7565_clear_buffer(LCD_Buffer);
    st7565_drawbitmap(LCD_Buffer, 0, 0, atom_symbol, 128, 64, 10);
    st7565_drawstring(LCD_Buffer, 22, 7, "Moodlight 2020");
    st7565_drawstring(LCD_Buffer, 0, 0, "Manuel");
    st7565_drawstring(LCD_Buffer, 0, 1, "Schmid");
    st7565_drawstring(LCD_Buffer, 85, 0, "Lukas");
    st7565_drawstring(LCD_Buffer, 85, 1, "Eugster");
	st7565_write_buffer(LCD_Buffer);
    
    HAL_Delay(3000);
    st7565_clear_buffer(LCD_Buffer);
//=======================================================================
  
    event_t event;
    fsm_init();
    
    while(1) {
        event = eh_get_event();
        if(event != EV_NO_EVENT) {
            fsm_handle_event(event);
        }
    }

    /* USER CODE BEGIN 3 */
		st7565_clear_buffer(LCD_Buffer);
 
// Draw the clock
      //Time 1
    st7565_drawfhd(0, LCD_Buffer);
    st7565_drawshd(6, LCD_Buffer);
    st7565_drawdts(LCD_Buffer);
    st7565_drawfmd(5, LCD_Buffer);
    st7565_drawsmd(7, LCD_Buffer);
           
      
      
      
      
// Draw the temperature
    uint8_t temp[]= "18";
    st7565_drawtempsymbol(LCD_Buffer);
    st7565_drawtemp(temp , LCD_Buffer);

    
// Draw the humidity
    uint8_t hum[] = "57";
    st7565_drawhumidsymbol(LCD_Buffer);
    st7565_drawhumid(hum, LCD_Buffer);

// Draw alarm symbol
   st7565_drawalarmsymbol(LCD_Buffer);
    
// Draw snooze symbol
   st7565_drawsnsymbol(LCD_Buffer);

st7565_write_buffer(LCD_Buffer);

		
		/**** UI LED test
		HAL_GPIO_TogglePin(LEDUP_GPIO_Port, LEDUP_Pin);
		HAL_Delay(200);
		HAL_GPIO_TogglePin(LEDUP_GPIO_Port, LEDUP_Pin);
		HAL_GPIO_TogglePin(LEDLT_GPIO_Port, LEDLT_Pin);
		HAL_Delay(200);
		HAL_GPIO_TogglePin(LEDLT_GPIO_Port, LEDLT_Pin);
		HAL_GPIO_TogglePin(LEDDN_GPIO_Port, LEDDN_Pin);
		HAL_Delay(200);
		HAL_GPIO_TogglePin(LEDDN_GPIO_Port, LEDDN_Pin);
		HAL_GPIO_TogglePin(LEDRT_GPIO_Port, LEDRT_Pin);
		HAL_Delay(200);
		HAL_GPIO_TogglePin(LEDRT_GPIO_Port, LEDRT_Pin);
		*/
  }
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
	if (htim->Instance == TIM3)	{
		updateUI = 1;
	} else if (htim->Instance == TIM6) {
		updateSensor = 1;
	}
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
