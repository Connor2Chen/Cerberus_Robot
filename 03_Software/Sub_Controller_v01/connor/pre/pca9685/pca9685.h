#ifndef __PCA9685_H
#define __PCA9685_H	

#include "stm32f4xx_hal.h"

#define pca_adrr 0x80

#define pca_mode1 0x0
#define pca_pre 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9


void pca_write(uint8_t adrr,uint8_t data);
uint8_t pca_read(uint8_t adrr);
void pca_setfreq(float freq);
void pca_setpwm(uint8_t num, uint32_t on, uint32_t off);


#endif

