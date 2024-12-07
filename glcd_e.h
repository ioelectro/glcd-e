/**
 * GLCD_E
 * Monochrome Graphics LCD Effect
 * by: ioelectro.ir 
 * date: 1403/09/17
 * 
 * Usage:
 *  after init():
 *  1: use glcd_e_mem() for memorise the old screen.
 *  2: paint new screen on buffer, widout update screen.
 *  3: use glcd_e_update(0 or 1) for print buffer on LCD and update by effect.
 * 
 * Warning:
 *  - The memory modules not optimized!
 *    the library use huge buffer size (2x1024 byte) for buffering and not recommended for low space or slow MCUs.
 *  - Default screen size is 64x128 pixel.
 *  - The LCD driver must use full buffer mode.
 *    the lib need lcd-buffer and update() function by init().
 *  - Hardware HI-Speed SPI recommended for LCD driver.
 *  - The library written for STM32 
 * 
 */

#ifndef _glcd_e_h_
#define _glcd_e_h_

#include <stdint.h>
#include "main.h"

#define GLCD_E_DELAY_MS 20
#define GLCD_E_BUF_SIZE 1024

typedef struct {
    uint8_t *buf;
    void (*update)(void);
} glcd_e_config_s;

#ifdef __cplusplus
extern "C" {
#endif

void glcd_e_init(uint8_t *buf,void (*update)(void));
void glcd_e_mem();
void glcd_e_update(uint8_t dir);

#ifdef __cplusplus
}
#endif
#endif
