#include "pca9685.h"
#include "math.h"
#include "i2c.h"

/*
���ܣ���ȡһ���ֽڵ�����
��������ʼ�Ĵ�����ַ
���أ��Ĵ�������
���ͣ�����tx��buffer��������1�����飬����I2C��Transmit��PCA�ӻ���ַ���ͼĴ�����ַ
      �ٷ��ظüĴ�����1�ֽڵ�����.
*/
uint8_t pca_read(uint8_t startAddress) {
    //Send address to start reading from.
    uint8_t tx[1];
    uint8_t buffer[1];
    tx[0]=startAddress;

    HAL_I2C_Master_Transmit(&hi2c1,pca_adrr, tx,1,10000);
    HAL_I2C_Master_Receive(&hi2c1,pca_adrr,buffer,1,10000);
    return buffer[0];
}

/*
���ܣ�д��1�ֽڵ�����
�������Ĵ�����ַ������
���أ���
���ͣ�����HAL_I2C_Master_Transmit����������Զ������һλ�ĳ�дλ��0�����ʲ���Ҫ�ֶ����ģ�
      ���ﴴ��һ������Ϊ2�����飬�ѼĴ�����ַ�����ݷֱ����tx[0]��tx[1]�������ú���һ�𷢹�ȥ.
*/
void pca_write(uint8_t startAddress, uint8_t buffer) {
    //Send address to start reading from.
    uint8_t tx[2];
    tx[0]=startAddress;
    tx[1]=buffer;
    HAL_I2C_Master_Transmit(&hi2c1,pca_adrr, tx,2,10000);

}


/*
���ܣ���������PWMƵ��
������float Ƶ��
���أ���
���ͣ�1.prescale�������Ƶֵ��oldmode��newmode��ʾ��ǰ����ģʽ��prescaleval�Ǻ��������Ƶֵ��
      2.��ΪPCA9685�ڲ�������25Mhz��������ȥ�����꣬����floor��������һ�£�
      3.Ȼ���ȡMODE1�Ĵ�����ǰֵ��������һ���µ�MODE1ֵ���������ߣ�д��ȥ��
      4.����״̬�¸ı��Ƶֵ���ٻ��ѿ����Զ�������
	  5.4096Ϊ�������ֱ��ʣ�12λ����pwm period == clk/(pre * res) == 25Mhz / (pre * 4096);
*/
void pca_setfreq(float freq)//����PWMƵ��
{
		uint8_t prescale,oldmode,newmode;
		double prescaleval;
		//freq *= 0.92; 
		prescaleval = 25000000;
		prescaleval /= 4096;	
		prescaleval /= freq;
		prescaleval -= 1;
		prescale =floor(prescaleval + 0.5f);

		oldmode = pca_read(pca_mode1);
	
		newmode = (oldmode&0x7F) | 0x10; // sleep
	
		pca_write(pca_mode1, newmode); // go to sleep
	
		pca_write(pca_pre, prescale); // set the prescaler
	
		pca_write(pca_mode1, oldmode);
		HAL_Delay(2);
	
		pca_write(pca_mode1, oldmode | 0xa1); 
}

/*
���ܣ�����PWMռ�ձȣ�
������numΪPCA9685�ĵڼ���ͨ����0~15��
���أ���
���ͣ�1.num:���PWM�������0~15��on:PWM��������ֵ0~4096,off:PWM�½�����ֵ0~4096
		һ��PWM���ڷֳ�4096�ݣ���0��ʼ+1�������Ƶ�onʱ����Ϊ�ߵ�ƽ������������offʱ
		����Ϊ�͵�ƽ��ֱ������4096���¿�ʼ��
	2.LED0 �� LED1 ���4λ��LED1 �� LED2 ���4λ���Դ�����;
	
*/
void pca_setpwm(uint8_t num, uint32_t on, uint32_t off)
{
		pca_write(LED0_ON_L+4*num,on);
		pca_write(LED0_ON_H+4*num,on>>8);
		pca_write(LED0_OFF_L+4*num,off);
		pca_write(LED0_OFF_H+4*num,off>>8);
}







