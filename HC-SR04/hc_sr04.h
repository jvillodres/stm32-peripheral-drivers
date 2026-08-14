#ifndef __HC_SR04_H
#define __HC_SR04_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef stm32f1xx
#include "stm32f1xx_hal.h"
#endif

#include "stm32l4xx_hal.h"

typedef struct {
	GPIO_TypeDef*		Trigger_Port;	// GPIOX
	uint16_t			Trigger_Pin;	// GPIO_PIN_X

	GPIO_TypeDef*		Echo_Port;		// GPIOX
	uint16_t			Echo_Pin;		// GPIO_PIN_X
	TIM_TypeDef			Echo_Timer;		// &htimx
} HCSR04_HandleTypeDef;


void HCSR04_Init(HCSR04_HandleTypeDef *hsensor); // Initialize sensor
void HCSR04_Trigger(HCSR04_HandleTypeDef *hsensor); // Trigger sensor by software for measuring
__weak void HCSR04_EXIT_Callback(HCSR04_HandleTypeDef *hsensor, uint16_t GPIO_Pin); // Callback for echo pin interruptions

#ifdef __cplusplus
}
#endif

#endif
