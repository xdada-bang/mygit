/*
 * ap.c
 *
 *  Created on: May 5, 2024
 *      Author: mzeu
 */


#include "ap.h"


void apInit(void)
{

}

void apMain(void)
{
  while(1)
  {
#if 0
      ledToggle(_DEF_LED2);
      delay(500);
      ledToggle(_DEF_LED1);
      delay(500);
#endif
      CAN_Send_Message();
      delay(1000);
  }
}

