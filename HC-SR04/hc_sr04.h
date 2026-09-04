/**
  ******************************************************************************
  * @file           : hc_sr04.h
  * @brief          : Header for hc_sr04.c file.
  *                   This file contains the common defines of the HC-SR04 driver.
  ******************************************************************************
*/

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __HC_SR04_H
#define __HC_SR04_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "stm32l4xx_hal.h"

/* Exported types ------------------------------------------------------------*/

/**
 * @brief	Sensor handle structure definition
 * @note	Be aware when modifying T1, T2 and First_Edge since they work as flags
 */
typedef struct {
	GPIO_TypeDef*				Trigger_Port;
	uint16_t					Trigger_Pin;
	GPIO_TypeDef*				Echo_Port;
	uint16_t					Echo_Pin;

	uint32_t					T1, T2;
	uint8_t						First_Edge;
	uint16_t					Distance;
} HCSR04_HandleTypeDef;


/* Exported functions prototypes -------------------------------------------- */
void HCSR04_Init(HCSR04_HandleTypeDef* hsensor);
void HCSR04_Trigger(HCSR04_HandleTypeDef* hsensor);
void HCSR04_EXTI_Callback(HCSR04_HandleTypeDef* hsensor, uint16_t GPIO_Pin);

uint32_t HCSR04_Get_Us_Timestamp(void);

#ifdef __cplusplus
}
#endif

#endif
