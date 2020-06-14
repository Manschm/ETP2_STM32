/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern uint8_t LCD_Buffer[1024];
extern uint8_t userOverride;
extern uint16_t userRed;
extern uint16_t userGreen;
extern uint16_t userBlue;
extern uint16_t userWhite;

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LEDTEMP_Pin GPIO_PIN_0
#define LEDTEMP_GPIO_Port GPIOA
#define LCDBL_Pin GPIO_PIN_2
#define LCDBL_GPIO_Port GPIOA
#define LCDCS_Pin GPIO_PIN_3
#define LCDCS_GPIO_Port GPIOA
#define LCDRST_Pin GPIO_PIN_4
#define LCDRST_GPIO_Port GPIOA
#define LCDA0_Pin GPIO_PIN_5
#define LCDA0_GPIO_Port GPIOA
#define LCDSI_Pin GPIO_PIN_6
#define LCDSI_GPIO_Port GPIOA
#define LCDSCL_Pin GPIO_PIN_7
#define LCDSCL_GPIO_Port GPIOA
#define LEDRT_Pin GPIO_PIN_0
#define LEDRT_GPIO_Port GPIOB
#define LEDDN_Pin GPIO_PIN_1
#define LEDDN_GPIO_Port GPIOB
#define SWRT_Pin GPIO_PIN_2
#define SWRT_GPIO_Port GPIOB
#define SWDN_Pin GPIO_PIN_12
#define SWDN_GPIO_Port GPIOB
#define SWLT_Pin GPIO_PIN_13
#define SWLT_GPIO_Port GPIOB
#define SWSL_Pin GPIO_PIN_14
#define SWSL_GPIO_Port GPIOB
#define SWUP_Pin GPIO_PIN_15
#define SWUP_GPIO_Port GPIOB
#define LEDR_Pin GPIO_PIN_8
#define LEDR_GPIO_Port GPIOA
#define LEDG_Pin GPIO_PIN_9
#define LEDG_GPIO_Port GPIOA
#define LEDB_Pin GPIO_PIN_10
#define LEDB_GPIO_Port GPIOA
#define LEDW_Pin GPIO_PIN_11
#define LEDW_GPIO_Port GPIOA
#define PROX_Pin GPIO_PIN_3
#define PROX_GPIO_Port GPIOB
#define LEDUP_Pin GPIO_PIN_4
#define LEDUP_GPIO_Port GPIOB
#define LEDLT_Pin GPIO_PIN_5
#define LEDLT_GPIO_Port GPIOB
#define ESPIR_Pin GPIO_PIN_8
#define ESPIR_GPIO_Port GPIOB
#define MCUIR_Pin GPIO_PIN_9
#define MCUIR_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
