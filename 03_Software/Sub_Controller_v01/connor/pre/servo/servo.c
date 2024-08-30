#include "servo.h"
#include "pca9685.h"


/*
���ܣ���ʼ�����������
������PWMƵ�� ��ʼ������Ƕ�
���أ���
���ͣ�������ʼ������ĽǶȣ�Ĭ��onΪ0��
*/
void PCA_Servo_Init(float hz,uint8_t angle)
{
	uint32_t off=0;
	pca_write(pca_mode1,0x0);
	pca_setfreq(hz);//����PWMƵ��
	//off=(uint32_t)(145+angle*2.4);
    off=(uint32_t)((((angle+45)*4096)/1800)-1);
	pca_setpwm(0,0,off);pca_setpwm(1,0,off);pca_setpwm(2,0,off);pca_setpwm(3,0,off);
	pca_setpwm(4,0,off);pca_setpwm(5,0,off);pca_setpwm(6,0,off);pca_setpwm(7,0,off);
	pca_setpwm(8,0,off);pca_setpwm(9,0,off);pca_setpwm(10,0,off);pca_setpwm(11,0,off);
	pca_setpwm(12,0,off);pca_setpwm(13,0,off);pca_setpwm(14,0,off);pca_setpwm(15,0,off);
	HAL_Delay(500);
}

/*
���ܣ���ʼ��20KG���
��������
���أ���
���ͣ�1.���ڳ�ʼ���Ǹ�20KG�������ͬ��PCAͨ�������ͬ�ĽǶȣ�
      2.���PWM��Ƶ��20ms(50hz);
      3.������� 0~270�㣬��Ӧ0.5~2.5ms;
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
���ܣ����ƶ��ת����
����������˿ڣ���ѡ0~15   �����Ƕȣ���ѡ0~180��SG90����
���أ���
���ͣ�Ĭ��onΪ0��
*/
void PCA_Servo_20(uint8_t num,uint8_t end_angle)
{
	uint32_t off=0;
	off=(uint32_t)(((0.025+end_angle)/270)*4096);
	pca_setpwm(num,0,off);
}

