

/*
 * *@Last_Author  : Connor.C
 * *@since        : 2024-08-20 20:31:09
 * *@message      : The function of this file is drive the mpu6050;
 * *@文件相对于项目的路径   : /Sub_Controller_v01/connor/pre/mpu6050/mpu6050.c
 */

#include "mpu6050.h"
#include "usart.h"
#include "stdio.h"
#include "i2c.h"
/**
 * *@Function       : mpu6050 write register
 * *@since          : 2024-08-20 22:09:25
 * *@Param          : 
 * *@Return         : 
 * *@Statement      : 
 * *@Input           {uint8_t} reg_add
 * *@Input           {uint8_t} reg_dat
 */
void MPU6050_WriteReg(uint8_t reg_add,uint8_t reg_dat)
{
    HAL_StatusTypeDef status = HAL_OK;
    status = HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, reg_add, I2C_MEMADD_SIZE_8BIT, &reg_dat, 1 , 1000);
    if(status != HAL_OK)
    {
        char error[] = "mpu6050 write register error!";
        printf("%s\n",error);
    }
}


/**
 * *@Function       : mpu6050 read data
 * *@since          : 2024-08-20 22:40:42
 * *@Param          : 
 * *@Return         : 
 * *@Statement      : 
 * *@Input           {uint8_t} reg_add
 * *@Input           {unsigned char*} Read
 * *@Input           {uint8_t} num
 */
void MPU6050_ReadData(uint8_t reg_add, unsigned char* Read, uint8_t num)
{
    if(Read == NULL)
    {
        printf("MPU6050 have not read the data! ");
        return;
    }

    HAL_StatusTypeDef status = HAL_OK;
    status =HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS, reg_add, I2C_MEMADD_SIZE_8BIT, Read, num, 1000); 
    if(status != HAL_OK)
    {
        char error[] = "mpu6050 read data error!";
        printf("%s\n",error);
    }
}


/**
 * *@Function       : MPU6050 初始化
 * *@since          : 2024-08-21 00:14:05
 * *@Param          : 
 * *@Return         : 
 * *@Statement      : 
 */
void MPU6050_Init(void)
{
    // 初始前延时，否则重新上电会数据出错
    HAL_Delay(100);
    MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0X00); // 出休眠
    MPU6050_WriteReg(MPU6050_RA_SMPLRT_DIV, 0X07); // 陀螺仪8分频，200Hz
    MPU6050_WriteReg(MPU6050_RA_CONFIG, 0x06);     //陀螺仪频率1k
    MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG, 0X01);//加速度传感器4G模式
    MPU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0X18);//陀螺仪自检 ---> 0x18（不自检，2000°/s）
    //这种陀螺仪、加速度计配置，属于是精度拉满；
    HAL_Delay(200);
}


/**
 * *@Function       : MPU6050 读ID
 * *@since          : 2024-08-21 01:10:08
 * *@Param          : 
 * *@Return         : 0 --->ID地址有误；    1 --->ID地址正确；
 * *@Statement      : 
 */
uint8_t MPU6050ReadID(void)
{
    unsigned char Re = 0;
        MPU6050_ReadData(MPU6050_RA_WHO_AM_I,&Re,1);    //读器件地址，默认0x68
    if(Re != 0x68)
    {
        char error[] = "MPU6050 ID Address error!";
        printf("%s\n",error);
        return 0;
    }
    else
    {
        printf("MPU6050 ID = %d\n",Re);
        return 1;
    }
}


/**
 * *@Function       : 获取加速度传感器数据
 * *@since          : 2024-08-21 01:19:42
 * *@Param          : 
 * *@Return         : 
 * *@Statement      : 
 * *@Input           {short} *accData
 */
void MPU6050ReadAcc(short *accData)
{
    uint8_t buf[6];
    MPU6050_ReadData(MPU6050_ACC_OUT, buf, 6);
    accData[0] = (buf[0] << 8 ) | buf[1]; //x轴数据
    accData[1] = (buf[2] << 8 ) | buf[3]; //y轴数据
    accData[2] = (buf[4] << 8 ) | buf[5]; //z轴数据

}


/**
 * *@Function       : 获取温度数据
 * *@since          : 2024-08-21 01:25:37
 * *@Param          : 
 * *@Return         : 
 * *@Statement      : 
 * *@Input           {short} *tempData
 */
void MPU6050ReadTemp(short *tempData)
{
    uint8_t buf[2];
    MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H, buf, 2); 
    *tempData = (buf[0] <<8) | buf[1];
}


/**
 * *@Function       : 获取温度摄氏度
 * *@since          : 2024-08-21 01:28:40
 * *@Param          : 
 * *@Return         : 
 * *@Statement      : 
 * *@Input           {float} *Temperature
 */
void MPU6050_ReturnTemp(float *Temperature)
{
    short temp3;
    uint8_t buf[2];

    MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H, buf, 2);
    temp3 = (buf[0] << 8) | buf[1];
    *Temperature = ((double) temp3 / 340.0) + 36.53;
}






