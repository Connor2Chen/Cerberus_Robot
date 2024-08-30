

/*
 * *@Last_Author  : Connor.C
 * *@since        : 2024-08-21 10:18:12
 * *@message      : The function of this file is drive the Lis2mdl.
 * *@文件相对于项目的路径   : /Sub_Controller_v01/connor/pre/lis/lis.c
 */

#include "lis.h"
#include "stdio.h"
#include "main.h"
#include "i2c.h"


/**
 * *@@              : //-----------------------------------------------------------------------------------------------------------
 * *@Function       : LIS2MDL I2C写寄存器
 * *@since          : 2024-08-23 17:25:14
 * *@Param          : 
 * *@Return         : 
 * *@Statement      : 
 * *@@@             : //----------------------------------------------------------------------------------------------------------
 * *@Input           {uint8_t} reg_addr
 * *@Input           {uint8_t} data
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
 * *@@              : //-----------------------------------------------------------------------------------------------------------
 * *@Function       : LIS2MDL I2C 寄存器读函数
 * *@since          : 2024-08-23 17:33:05
 * *@Param          : 
 * *@Return         : 
 * *@Statement      : 
 * *@@@             : //----------------------------------------------------------------------------------------------------------
 * *@Input           {uint8_t} reg_add
 * *@Input           {unsigned char*} read
 * *@Input           {uint8_t} num
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
 * *@@              : //-----------------------------------------------------------------------------------------------------------
 * *@Function       : 
 * *@since          : 2024-08-23 17:42:03
 * *@Param          : 
 * *@Return         : 
 * *@Statement      : 
 * *@@@             : //----------------------------------------------------------------------------------------------------------
 */
void LIS2MDL_Init(void)
{
    HAL_Delay(100);
    LIS2MDL_Register_Write(LIS2MDL_ADDR_CFGA,LIS2MDL_CFGA_VALUE_CONTINUE);   
}


