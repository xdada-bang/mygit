/*
 * qbuffer.h
 *
 *  Created on: May 22, 2024
 *      Author: mzeu
 */

#ifndef SRC_COMMON_HW_INCLUDE_QBUFFER_H_
#define SRC_COMMON_HW_INCLUDE_QBUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "def.h"


typedef struct
{
  uint32_t in;
  uint32_t out;
  uint32_t len;

  uint8_t *p_buf;
}q_buffer_t;

void qbufferInit(void);
bool     qbufferCreate(q_buffer_t *p_node,uint8_t *p_buf ,uint32_t length);
bool     qbufferWrite(q_buffer_t *p_node, uint8_t *p_data, uint32_t length);
bool     qbufferRead(q_buffer_t *p_node, uint8_t *p_data, uint32_t length);
uint32_t qbufferAvailable(q_buffer_t *p_node);
void     qbufferFlush(q_buffer_t *p_node);


#ifdef __cplusplus
}
#endif

#endif /* SRC_COMMON_HW_INCLUDE_QBUFFER_H_ */

