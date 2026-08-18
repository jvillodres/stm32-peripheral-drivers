#ifndef __HC_SR04_H
#define __HC_SR04_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx_hal.h"

typedef struct {
	GPIO_TypeDef*				Trigger_Port;	// GPIOX
	uint16_t					Trigger_Pin;	// GPIO_PIN_X
	GPIO_TypeDef*				Echo_Port;		// GPIOX
	uint16_t					Echo_Pin;		// GPIO_PIN_X

	uint32_t					T1, T2;			// Flank interruption moments
	uint8_t						First_Edge;		// Flag for first rising edge
	uint16_t					Distance;		// x cm
} HCSR04_HandleTypeDef;


void HCSR04_Init(HCSR04_HandleTypeDef* hsensor); // Initialize sensor
void HCSR04_Trigger(HCSR04_HandleTypeDef* hsensor); // Trigger sensor by software for measuring
void HCSR04_EXTI_Callback(HCSR04_HandleTypeDef* hsensor, uint16_t GPIO_Pin); // Callback for echo pin interruptions

uint32_t HCSR04_Get_Us_Timestamp(void);

#ifdef __cplusplus
}
#endif

#endif
