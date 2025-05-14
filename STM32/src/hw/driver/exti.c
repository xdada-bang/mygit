/*
 * exti.c
 *
 *  Created on: Nov 28, 2024
 *      Author: mzeu
 */


#include "exti.h"

void extiInit(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // EXTI 핀 초기화 (예: PA0)
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  // 상승 엣지에서 인터럽트 발생
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // NVIC 설정
  HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

// HAL의 EXTI 핸들러 호출
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  extiCallback(GPIO_Pin);  // 사용자 정의 콜백 함수 호출
}

// 사용자 정의 콜백 함수v
void extiCallback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_0)
  {
    // EXTI 핀 처리 로직 (예: LED 토글)
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
  }
}
