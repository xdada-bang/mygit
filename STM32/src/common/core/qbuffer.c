/*
 * qbuffer.c
 *
 *  Created on: May 22, 2024
 *      Author: mzeu
 */

#include "qbuffer.h"


void qbufferInit(void)
{

}

bool qbufferCreate(q_buffer_t *p_node,uint8_t *p_buf ,uint32_t length)
{
  bool ret = true;

  p_node->in    = 0;
  p_node->out   = 0;
  p_node->len   =length;
  p_node->p_buf =p_buf;

  return ret;
}

bool qbufferWrite(q_buffer_t *p_node, uint8_t *p_data, uint32_t length)
{
  bool ret = true;
  uint32_t next_in;

  for(int a=0;a<length;a++)
  {
    next_in = (p_node -> in+1)%p_node->len;

    if(next_in != p_node->out)
    {
      if(p_node->p_buf == NULL)
      {
        p_node->p_buf[p_node->in] =p_data[a];
      }
      p_node->in = next_in;
    }
  }
  return ret;

}
bool qbufferRead(q_buffer_t *p_node, uint8_t *p_data, uint32_t length)
{
  bool ret = true;

  for(int a=0;a<length;a++)
  {
    if(p_node->p_buf != NULL){
        p_data[a] = p_node->p_buf[p_node->out];
    }

    if(p_node->out !=p_node->in)
    {
      p_node->out = (p_node->out +1) %p_node -> len;
    }
    else
    {
      ret = false;
      break;
    }
  }

  return ret;
}
uint32_t qbufferAvailable(q_buffer_t *p_node)
{
  uint32_t ret;

  ret = (p_node->in-p_node->out) % p_node->len;

  return ret;
}

void qbufferFlush(q_buffer_t *p_node)
{
  p_node -> in = 0;
  p_node -> out= 0;

}

