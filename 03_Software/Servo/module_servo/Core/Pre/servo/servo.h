#ifndef __SERVO_H
#define __SERVO_H	

#include "stm32h7xx_hal.h"
#include "pca9685.h"



void PCA_Servo_Init(float hz,uint8_t angle);
void PCA_Servo_20_Init(void);
void PCA_Servo_20(uint8_t num,uint8_t end_angle);


#endif


