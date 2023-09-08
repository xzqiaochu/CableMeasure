/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED1_Pin GPIO_PIN_3
#define LED1_GPIO_Port GPIOE
#define TDC_SCK_Pin GPIO_PIN_2
#define TDC_SCK_GPIO_Port GPIOC
#define PULSE_Pin GPIO_PIN_1
#define PULSE_GPIO_Port GPIOA
#define TDC_SO_Pin GPIO_PIN_6
#define TDC_SO_GPIO_Port GPIOA
#define TDC_SI_Pin GPIO_PIN_7
#define TDC_SI_GPIO_Port GPIOA
#define TDC_SSN_Pin GPIO_PIN_4
#define TDC_SSN_GPIO_Port GPIOC
#define TDC_INT_Pin GPIO_PIN_5
#define TDC_INT_GPIO_Port GPIOC
#define TDC_RTN_Pin GPIO_PIN_0
#define TDC_RTN_GPIO_Port GPIOB
#define SWITCH_C_Pin GPIO_PIN_14
#define SWITCH_C_GPIO_Port GPIOB
#define SWITCH_L_Pin GPIO_PIN_6
#define SWITCH_L_GPIO_Port GPIOG
#define SWITCH_R_Pin GPIO_PIN_6
#define SWITCH_R_GPIO_Port GPIOC
#define FREQ_IN_Pin GPIO_PIN_8
#define FREQ_IN_GPIO_Port GPIOC
#define FREQ_IN_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
