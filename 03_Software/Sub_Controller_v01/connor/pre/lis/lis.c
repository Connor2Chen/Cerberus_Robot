/*
 * @Author: Connor2Chen 397080067@qq.com
 * @Date: 2024-09-05 08:41:23
 * @LastEditors: Connor2Chen 397080067@qq.com
 * @LastEditTime: 2024-09-05 10:55:35
 * @FilePath: \03_Software\Sub_Controller_v01\connor\pre\lis\lis.c
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */



#include "lis.h"
#include "stdio.h"
#include "main.h"
#include "i2c.h"


/**
 * @description: LIS2MDL д�Ĵ���
 * @Date: 2024-09-05 10:52:25
 * @param {uint8_t} reg_addr
 * @param {uint8_t} data
 * @return {*}
 */
void LIS2MDL_Register_Write(uint8_t reg_addr, uint8_t data)
{
    HAL_StatusTypeDef status;
    status = HAL_I2C_Mem_Write(&hi2c1, LIS2MDL_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, &data, 1, 1000);
    if(status != HAL_OK)
    {
        char error[] = "LIS2MDL I2C Write Register error!!!";
        printf("%s\n",error);
    }
}


/**
 * @description: LIS2MDL ���Ĵ���
 * @Date: 2024-09-05 10:52:48
 * @param {uint8_t} reg_add
 * @param {unsigned char*} read
 * @param {uint8_t} num
 * @return {*}
 */
void LIS2MDL_Register_Read(uint8_t reg_add, unsigned char* read, uint8_t num)
{
    if(read == NULL)
    {
        printf("LIS2MDL I2C Read is Null!!!");
        return;
    }
    HAL_StatusTypeDef status;
    status = HAL_I2C_Mem_Read(&hi2c1, LIS2MDL_ADDR, reg_add, I2C_MEMADD_SIZE_8BIT, read, num, 1000);
    if(status != HAL_OK)
    {
        char error[] = "LIS2MDL I2C Read Register error!!!";
        printf("%s\n",error);
    }
}


/**
 * @description:  LIS2MDL ��ʼ��
 * @Date: 2024-09-05 10:53:12
 * @return {*}
 */
void LIS2MDL_Init(void)
{
    uint8_t chipid = 0;
    LIS2MDL_Register_Read(LIS2MDL_ADDR_CHIPID, &chipid, 1);
    if(chipid != LIS2MDL_CHIPID_VALUE)
    {
        char error = "LIS2MDL CHIPID VALUE ERROR !!!";
        printf("%s\n",error);
    }

    LIS2MDL_Register_Write(LIS2MDL_ADDR_CFGA,LIS2MDL_CFGA_VALUE_IDLE);
    LIS2MDL_Register_Write(LIS2MDL_ADDR_CFGB,LIS2MDL_CFGB_VALUE);
    LIS2MDL_Register_Write(LIS2MDL_ADDR_CFGC,LIS2MDL_CFGC_VALUE);
}


/**
 * @description: LIS2MDL �����λ
 * @Date: 2024-09-05 10:53:50
 * @return {*}
 */
void LIS2MDL_Soft_Reset(void)
{
    LIS2MDL_Register_Write(LIS2MDL_ADDR_CFGA, LIS2MDL_CFGA_SOFT_RST);
    HAL_Delay(2);
    LIS2MDL_Register_Write(LIS2MDL_ADDR_CFGA, LIS2MDL_CFGA_REBOOT);
    HAL_Delay(20);
}



// void LIS2MDL_Hard_Reset(void)



/**
 * @description: LIS2MDL ��ȡ�������
 * @Date: 2024-09-05 10:54:10
 * @param {int16_t} *magData_x
 * @param {int16_t} *magData_y
 * @param {int16_t} *magData_z
 * @return {*}
 */
void LIS2MDL_Read_MagDensity(int16_t *magData_x, int16_t *magData_y, int16_t *magData_z)
{
    uint8_t rawData_x[2] = 0;
    uint8_t rawData_y[2] = 0;
    uint8_t rawData_z[2] = 0;

    LIS2MDL_Register_Read(LIS2MDL_ADDR_XOUTL, rawData_x[2], 2);
    LIS2MDL_Register_Read(LIS2MDL_ADDR_YOUTL, rawData_y[2], 2);
    LIS2MDL_Register_Read(LIS2MDL_ADDR_ZOUTL, rawData_z[2], 2);

    *magData_x = (int16_t)((rawData_x[1]<<8) | rawData_x[0]);
    *magData_y = (int16_t)((rawData_y[1]<<8) | rawData_y[0]);
    *magData_z = (int16_t)((rawData_z[1]<<8) | rawData_z[0]);
}



/**
 * @description: LIS2MDL ��ȡ�¶�
 * @Date: 2024-09-05 10:54:31
 * @return {*}
 */
int16_t LIS2MDL_Read_TEMP(void)
{
    uint8_t rawData[2];
    LIS2MDL_Register_Read(LIS2MDL_ADDR_TEMPL, rawData, 2);
    return (int16_t)((rawData[1]<<8) | rawData[0]);
}



/**
 * @description: LIS2MDL ��ȡƫ��
 * @Date: 2024-09-05 10:54:47
 * @param {int16_t} *offset_x
 * @param {int16_t} *offset_y
 * @param {int16_t} *offset_z
 * @return {*}
 */
void LIS2MDL_Read_Offset(int16_t *offset_x, int16_t *offset_y, int16_t *offset_z)
{
    uint8_t rawData_x[2] = 0;
    uint8_t rawData_y[2] = 0;
    uint8_t rawData_z[2] = 0;

    LIS2MDL_Register_Read(LIS2MDL_ADDR_OFFSETX_L, rawData_x, 2);
    LIS2MDL_Register_Read(LIS2MDL_ADDR_OFFSETY_L, rawData_y, 2);
    LIS2MDL_Register_Read(LIS2MDL_ADDR_OFFSETZ_L, rawData_z, 2);

    *offset_x = (int16_t)((rawData_x[1]<<8) | rawData_x[0]);
    *offset_y = (int16_t)((rawData_y[1]<<8) | rawData_y[0]);
    *offset_z = (int16_t)((rawData_z[1]<<8) | rawData_z[0]);
}



/**
 * @description: LIS2MDL �޸�ƫ��
 * @Date: 2024-09-05 10:55:07
 * @param {int16_t} *offset_x
 * @param {int16_t} *offset_y
 * @param {int16_t} *offset_z
 * @return {*}
 */
void LIS2MDL_Write_Offset(int16_t *offset_x, int16_t *offset_y, int16_t *offset_z)
{
    uint8_t rawData_x[2];
    uint8_t rawData_y[2];
    uint8_t rawData_z[2];



    rawData_x[0] = (uint8_t)(*offset_x & 0xFF);
    rawData_x[1] = (uint8_t)((*offset_x >> 8) & 0xFF);

    rawData_y[0] = (uint8_t)(*offset_y & 0xFF);
    rawData_y[1] = (uint8_t)((*offset_y >> 8) & 0xFF);

    rawData_z[0] = (uint8_t)(*offset_z & 0xFF);
    rawData_z[1] = (uint8_t)((*offset_z >> 8) & 0xFF);



    LIS2MDL_Register_Write(LIS2MDL_ADDR_OFFSETX_L, rawData_x[0]);
    LIS2MDL_Register_Write(LIS2MDL_ADDR_OFFSETX_H, rawData_x[1]);

    LIS2MDL_Register_Write(LIS2MDL_ADDR_OFFSETY_L, rawData_y[0]);
    LIS2MDL_Register_Write(LIS2MDL_ADDR_OFFSETY_H, rawData_y[1]);

    LIS2MDL_Register_Write(LIS2MDL_ADDR_OFFSETZ_L, rawData_z[0]);
    LIS2MDL_Register_Write(LIS2MDL_ADDR_OFFSETZ_H, rawData_z[1]);

}



/**
 * @description: LIS2MDL ���ƫ����
 * @Date: 2024-09-05 10:55:21
 * @return {*}
 */
void LIS2MDL_Clean_Offset(void)
{
    int16_t offset_x = 0;
    int16_t offset_y = 0;
    int16_t offset_z = 0;

    LIS2MDL_Write_Offset(&offset_x, &offset_y, &offset_z);
}



/**
 * @description: LIS2MDL �ȴ����ݸ���
 * @Date: 2024-09-05 10:55:40
 * @param {uint8_t} max_cnt
 * @return {*}
 */
bool LIS2MDL_Wait_Data_Update(uint8_t max_cnt)
{
    for(; max_cnt>=0 ; max_cnt--)
    {
        uint8_t addrStatus = 0;
        LIS2MDL_Register_Read(LIS2MDL_ADDR_STATUS, &addrStatus, 1);
        if(addrStatus & 0x08)
        {
            return true;
        }
        HAL_Delay(1);
    }

    return false;
}


//�Ȳ�д
// bool LIS2MDL_Read_Average


//�Ȳ�д
//bool LIS2MDL_Adjust_Magnetic(void)










