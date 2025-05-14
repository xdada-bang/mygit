/*
 * usb.c
 *
 *  Created on: May 21, 2024
 *      Author: mzeu
 */


#include "usb.h"
#include "usb_device.h"


bool usbInit(void)
{
  bool ret = true;

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,GPIO_PIN_RESET);
  delay(200);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,GPIO_PIN_SET);

  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);




  MX_USB_DEVICE_Init();

  return ret;

}

