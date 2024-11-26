#include "pca9685.h"
#include "math.h"
#include "i2c.h"

/*
功能：读取一个字节的数据
参数：起始寄存器地址
返回：寄存器数据
解释：创建tx和buffer两个长度1的数组，先用I2C的Transmit给PCA从机地址发送寄存器地址
      再返回该寄存器中1字节的数据.
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
功能：写入1字节的数据
参数：寄存器地址，数据
返回：无
解释：首先HAL_I2C_Master_Transmit这个函数会自动把最后一位改成写位（0），故不需要手动更改；
      这里创建一个长度为2的数组，把寄存器地址和数据分别放在tx[0]和tx[1]，再利用函数一起发过去.
*/
void pca_write(uint8_t startAddress, uint8_t buffer) {
    //Send address to start reading from.
    uint8_t tx[2];
    tx[0]=startAddress;
    tx[1]=buffer;
    HAL_I2C_Master_Transmit(&hi2c1,pca_adrr, tx,2,10000);

}


/*
功能：用于设置PWM频率
参数：float 频率
返回：无
解释：1.prescale用来存分频值，oldmode和newmode表示当前和新模式，prescaleval是后面来存分频值；
      2.因为PCA9685内部晶振是25Mhz，把它拿去计算完，再用floor四舍五入一下；
      3.然后读取MODE1寄存器当前值，再生成一个新的MODE1值，让它休眠，写进去；
      4.休眠状态下改变分频值后，再唤醒开启自动增量；
	  5.4096为计数器分辨率（12位），pwm period == clk/(pre * res) == 25Mhz / (pre * 4096);
*/
void pca_setfreq(float freq)//设置PWM频率
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
功能：设置PWM占空比；
参数：num为PCA9685的第几个通道，0~15；
返回：无
解释：1.num:舵机PWM输出引脚0~15，on:PWM上升计数值0~4096,off:PWM下降计数值0~4096
		一个PWM周期分成4096份，由0开始+1计数，计到on时跳变为高电平，继续计数到off时
		跳变为低电平，直到计满4096重新开始。
	2.LED0 与 LED1 相差4位，LED1 与 LED2 相差4位，以此类推;
	
*/
void pca_setpwm(uint8_t num, uint32_t on, uint32_t off)
{
		pca_write(LED0_ON_L+4*num,on);
		pca_write(LED0_ON_H+4*num,on>>8);
		pca_write(LED0_OFF_L+4*num,off);
		pca_write(LED0_OFF_H+4*num,off>>8);
}







