/*
 * hw.c
 *
 *  Created on: May 5, 2024
 *      Author: mzeu
 */


#include "hw.h"





void hwInit(void)
{
  bspInit();
  rtcInit();
  resetInit();
  ledInit();
  //usbInit();
  flashInit();
  MX_CAN_Init();
  CAN_Start();

}
