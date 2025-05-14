/*
 * led.c
 *
 *  Created on: May 7, 2024
 *      Author: mzeu
 */




#include "led.h"


typedef struct
{
  GPIO_TypeDef *port;
  uint16_t      pin;
  GPIO_PinState on_stat;
  GPIO_PinState off_stat;
} led_tbl_t;

  led_tbl_t led_tbl[LED_MAX_CH] = // 채널이 추가되면 여기에 복사넣기해서 n개로 만들면 됨$
      {
          {GPIOC,GPIO_PIN_13,GPIO_PIN_RESET,GPIO_PIN_SET},
          {GPIOA,GPIO_PIN_8,GPIO_PIN_RESET,GPIO_PIN_SET}
      };

bool ledInit(void)
{
  bool ret = true;

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();



  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  for(int a=0;a<LED_MAX_CH;a++)
  {
    GPIO_InitStruct.Pin = led_tbl[a].pin;
    HAL_GPIO_Init(led_tbl[a].port, &GPIO_InitStruct);

    ledOff(a);

  }

  return ret;
}

void ledOn(uint8_t ch)
{
  /*Configure GPIO pin  Output Level */
  if (ch >= LED_MAX_CH) return;

  HAL_GPIO_WritePin(led_tbl[ch].port, led_tbl[ch].pin, led_tbl[ch].on_stat);
}

void ledOff(uint8_t ch)
{
  if (ch >= LED_MAX_CH) return;

  HAL_GPIO_WritePin(led_tbl[ch].port, led_tbl[ch].pin, led_tbl[ch].off_stat);

}

void ledToggle(uint8_t ch)
{
  if (ch >= LED_MAX_CH) return;

  HAL_GPIO_TogglePin(led_tbl[ch].port, led_tbl[ch].pin);

}
