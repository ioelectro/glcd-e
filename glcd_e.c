#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "glcd_e.h"

uint8_t glcd_e_buf[GLCD_E_BUF_SIZE];

static glcd_e_config_s config;

void glcd_e_init(uint8_t *buf,void (*update)(void))
{
    config.buf=buf;
    config.update=update;
}

void glcd_e_move(uint8_t *des,uint8_t *src,uint8_t dir,uint8_t n)
{
  int x,y,ix;

  for(x=0;x<128;x++)
    for(y=0;y<8;y++)
    {
      ix=x+(((dir)?-1:+1)*n);
      if(ix<0)ix=0;
      if(ix>127)ix=127;
      des[(y*128)+x]=src[(y*128)+ix];
    }
}

void glcd_e_copy(uint8_t * des,uint8_t *src)
{
  memcpy(des,src,GLCD_E_BUF_SIZE);
}

void glcd_e_mem()
{
  glcd_e_copy(glcd_e_buf,config.buf);
}

void glcd_e_update(uint8_t dir)
{
  int i;
  uint8_t glcd_e_temp[GLCD_E_BUF_SIZE];

  glcd_e_copy(glcd_e_temp,config.buf);
  for(i=0;i<128;i++,i*=i)
  {
    glcd_e_move(config.buf,glcd_e_buf,(dir)?1:0,i);
    config.update();
    HAL_Delay(GLCD_E_DELAY_MS);
  }
  for(i=127;i>=0;i=sqrtf(i),i--)
  {
    glcd_e_move(config.buf,glcd_e_temp,(dir)?0:1,i);
    config.update();
    HAL_Delay(GLCD_E_DELAY_MS);
  }
}
