/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_dma.h"

/* USER CODE BEGIN Includes */
#define RTC_CLOCK_SOURCE_LSE
/* #define RTC_CLOCK_SOURCE_LSI */

#ifdef RTC_CLOCK_SOURCE_LSI
#define RTC_ASYNCH_PREDIV    0x7F
#define RTC_SYNCH_PREDIV     0x0130
#endif

#ifdef RTC_CLOCK_SOURCE_LSE
#define RTC_ASYNCH_PREDIV  0x7F
#define RTC_SYNCH_PREDIV   0x00FF
#endif
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define LED1_Pin LL_GPIO_PIN_4
#define LED1_GPIO_Port GPIOA
#define C1_KEY_Pin LL_GPIO_PIN_5
#define C1_KEY_GPIO_Port GPIOA
#define C1_KEY_EXTI_IRQn EXTI4_15_IRQn
#define WMMG2_A_Pin LL_GPIO_PIN_6
#define WMMG2_A_GPIO_Port GPIOA
#define WMMG2_A_EXTI_IRQn EXTI4_15_IRQn
#define WMMG2_B_Pin LL_GPIO_PIN_7
#define WMMG2_B_GPIO_Port GPIOA
#define WMMG2_B_EXTI_IRQn EXTI4_15_IRQn
#define WMMG1_A_Pin LL_GPIO_PIN_0
#define WMMG1_A_GPIO_Port GPIOB
#define WMMG1_A_EXTI_IRQn EXTI0_1_IRQn
#define WMMG1_B_Pin LL_GPIO_PIN_1
#define WMMG1_B_GPIO_Port GPIOB
#define WMMG1_B_EXTI_IRQn EXTI0_1_IRQn
#define LED2_Pin LL_GPIO_PIN_12
#define LED2_GPIO_Port GPIOB
#define UP_KEY_Pin LL_GPIO_PIN_13
#define UP_KEY_GPIO_Port GPIOB
#define UP_KEY_EXTI_IRQn EXTI4_15_IRQn
#define DOWN_KEY_Pin LL_GPIO_PIN_14
#define DOWN_KEY_GPIO_Port GPIOB
#define DOWN_KEY_EXTI_IRQn EXTI4_15_IRQn
#define RIGHT_KEY_Pin LL_GPIO_PIN_15
#define RIGHT_KEY_GPIO_Port GPIOB
#define RIGHT_KEY_EXTI_IRQn EXTI4_15_IRQn
#define ON_OFF_KEY_Pin LL_GPIO_PIN_8
#define ON_OFF_KEY_GPIO_Port GPIOA
#define ON_OFF_KEY_EXTI_IRQn EXTI4_15_IRQn
#define C2_KEY_Pin LL_GPIO_PIN_11
#define C2_KEY_GPIO_Port GPIOA
#define C2_KEY_EXTI_IRQn EXTI4_15_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
