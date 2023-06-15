/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Led_Pin GPIO_PIN_13
#define Led_GPIO_Port GPIOC
#define RS_Pin GPIO_PIN_1
#define RS_GPIO_Port GPIOA
#define RW_Pin GPIO_PIN_2
#define RW_GPIO_Port GPIOA
#define EN_Pin GPIO_PIN_3
#define EN_GPIO_Port GPIOA
#define DATA0_Pin GPIO_PIN_4
#define DATA0_GPIO_Port GPIOA
#define DATA1_Pin GPIO_PIN_5
#define DATA1_GPIO_Port GPIOA
#define DATA2_Pin GPIO_PIN_6
#define DATA2_GPIO_Port GPIOA
#define DATA3_Pin GPIO_PIN_7
#define DATA3_GPIO_Port GPIOA
#define ADC_VOUT_Pin GPIO_PIN_1
#define ADC_VOUT_GPIO_Port GPIOB
#define SAN_Pin GPIO_PIN_13
#define SAN_GPIO_Port GPIOB
#define SBN_Pin GPIO_PIN_14
#define SBN_GPIO_Port GPIOB
#define SCN_Pin GPIO_PIN_15
#define SCN_GPIO_Port GPIOB
#define SAP_Pin GPIO_PIN_8
#define SAP_GPIO_Port GPIOA
#define SBP_Pin GPIO_PIN_9
#define SBP_GPIO_Port GPIOA
#define SCP_Pin GPIO_PIN_10
#define SCP_GPIO_Port GPIOA
#define BT1_Pin GPIO_PIN_4
#define BT1_GPIO_Port GPIOB
#define BT2_Pin GPIO_PIN_5
#define BT2_GPIO_Port GPIOB
#define BT3_Pin GPIO_PIN_6
#define BT3_GPIO_Port GPIOB
#define BT4_Pin GPIO_PIN_7
#define BT4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
