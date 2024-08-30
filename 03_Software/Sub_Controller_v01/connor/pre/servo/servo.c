#include "servo.h"
#include "pca9685.h"


/*
功能：初始化舵机驱动板
参数：PWM频率 初始化舵机角度
返回：无
解释：用来初始化舵机的角度，默认on为0；
*/
void PCA_Servo_Init(float hz,uint8_t angle)
{
	uint32_t off=0;
	pca_write(pca_mode1,0x0);
	pca_setfreq(hz);//设置PWM频率
	//off=(uint32_t)(145+angle*2.4);
    off=(uint32_t)((((angle+45)*4096)/1800)-1);
	pca_setpwm(0,0,off);pca_setpwm(1,0,off);pca_setpwm(2,0,off);pca_setpwm(3,0,off);
	pca_setpwm(4,0,off);pca_setpwm(5,0,off);pca_setpwm(6,0,off);pca_setpwm(7,0,off);
	pca_setpwm(8,0,off);pca_setpwm(9,0,off);pca_setpwm(10,0,off);pca_setpwm(11,0,off);
	pca_setpwm(12,0,off);pca_setpwm(13,0,off);pca_setpwm(14,0,off);pca_setpwm(15,0,off);
	HAL_Delay(500);
}

/*
功能：初始化20KG舵机
参数：无
返回：无
解释：1.用于初始化那个20KG舵机，不同的PCA通道输出不同的角度；
      2.舵机PWM基频率20ms(50hz);
      3.舵机控制 0~270°，对应0.5~2.5ms;
*/

void PCA_Servo_20_Init(void)
{
    pca_write(pca_mode1,0x0);
    pca_setfreq(50);
    pca_setpwm(0,0,103);pca_setpwm(1,0,148);pca_setpwm(2,0,194);pca_setpwm(3,0,239);
    pca_setpwm(4,0,285);pca_setpwm(5,0,328);pca_setpwm(6,0,376);pca_setpwm(7,0,422);
    pca_setpwm(8,0,467);pca_setpwm(9,0,512);
    HAL_Delay(500);

}

/*
功能：控制舵机转动；
参数：输出端口，可选0~15   结束角度，可选0~180（SG90）；
返回：无
解释：默认on为0；
*/
void PCA_Servo_20(uint8_t num,uint8_t end_angle)
{
	uint32_t off=0;
	off=(uint32_t)(((0.025+end_angle)/270)*4096);
	pca_setpwm(num,0,off);
}

