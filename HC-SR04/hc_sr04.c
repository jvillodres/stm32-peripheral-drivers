#include "hc_sr04.h"

void HCSR04_Init(HCSR04_HandleTypeDef* hsensor) {
	// GPIO Timers
	if (hsensor->Echo_Port == GPIOA || hsensor->Trigger_Port == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
	if (hsensor->Echo_Port == GPIOB || hsensor->Trigger_Port == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
	if (hsensor->Echo_Port == GPIOC || hsensor->Trigger_Port == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();

	// GPIO Configurations
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// Trigger Configuration
	GPIO_InitStruct.Pin = hsensor->Trigger_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(hsensor->Trigger_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(hsensor->Trigger_Port, hsensor->Trigger_Pin, GPIO_PIN_RESET);

	// Echo Configuration
	GPIO_InitStruct.Pin = hsensor->Echo_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(hsensor->Echo_Port, &GPIO_InitStruct);

	hsensor->Distance = 0.0f;
}

void HCSR04_Trigger(HCSR04_HandleTypeDef* hsensor) {
	HAL_GPIO_WritePin(hsensor->Trigger_Port, hsensor->Trigger_Pin, GPIO_PIN_SET);

	// Hold Trigger pin on for 10us
	uint32_t start_time = HCSR04_Get_Us_Timestamp();
	while((HCSR04_Get_Us_Timestamp() - start_time) < 10) {}

	HAL_GPIO_WritePin(hsensor->Trigger_Port, hsensor->Trigger_Pin, GPIO_PIN_RESET);
}

void HCSR04_EXTI_Callback(HCSR04_HandleTypeDef* hsensor, uint16_t GPIO_Pin) {
	if (GPIO_Pin == hsensor->Echo_Pin) {
		if (HAL_GPIO_ReadPin(hsensor->Echo_Port, hsensor->Echo_Pin) == GPIO_PIN_SET) {
			hsensor->T1 = HCSR04_Get_Us_Timestamp(); // Time when first rising edge
			hsensor->First_Edge = 1;

		} else {
			if (hsensor->First_Edge == 1) {
				hsensor->T2 = HCSR04_Get_Us_Timestamp(); // Time when falling edge

				if (hsensor->T2 >= hsensor->T1) {
					hsensor->Distance = (hsensor->T2 - hsensor->T1)/58; // Normal distance estimation
				} else {
					hsensor->Distance = (0xFFFFFFFF - hsensor->T1 + hsensor->T2)/58; // Overflowed distance estimation
				}

				hsensor->First_Edge = 0;
			}
		}
	}
}

__weak uint32_t HCSR04_Get_Us_Timestamp(void) {
	return 0;
}
