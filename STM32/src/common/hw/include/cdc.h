/*
 * cdc.h
 *
 *  Created on: May 22, 2024
 *      Author: mzeu
 */

#ifndef SRC_COMMON_HW_INCLUDE_CDC_H_
#define SRC_COMMON_HW_INCLUDE_CDC_H_

#include "hw_def.h"


#ifdef  _USE_HW_CDC


bool cdcInit(void);
uint32_t cdcAvailable(void);
uint8_t cdcRead(void);
void cdcDatain(uint8_t rx_data);
uint32_t cdcWrite(uint8_t *p_data, uint32_t length);
uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);
uint32_t cdcGetBaud(void);

#endif


#endif /* SRC_COMMON_HW_INCLUDE_CDC_H_ */
