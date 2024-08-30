

/*
 * *@Last_Author  : Connor.C
 * *@since        : 2024-08-20 11:52:58
 * *@message      : The function of this file is 
 * *@文件相对于项目的路径   : /Sub_Controller_v01/Core/Src/i2c.c
 */

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2c.c
  * @brief   This file provides code for the configuration
  *          of the I2C instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "i2c.h"
#include "main.h"
/* USER CODE BEGIN 0 */
/************************************************************************************************************************************************************************************************ */


 /**
   * *@Function       : reinit i2c1 when it error
   * *@since          : 2024-08-20 21:37:35
   * *@Param          : 
   * *@Return         : 
   * *@Statement      : 
   * *@Input           {uint8_t} addr
   */
  static void I2C1_Error(uint8_t addr)
  {
    /*recover to default*/
    HAL_I2C_DeInit(&hi2c1);
    /*Reinit the i2c*/
    MX_I2C1_Init();
  }

  /**
   * *@Function       : 用于I2C1总线，写寄存器
   * *@since          : 2024-08-20 21:54:48
   * *@Param          : 
   * *@Return         : 
   * *@Statement      : 
   * *@Input           {unsigned char} slave_addr
   * *@Input           {unsigned char} reg_addr
   * *@Input           {unsigned char} len
   * *@Input           {unsigned char} *data_ptr
   */
  int Sensors_I2C1_WriteRegister(unsigned char slave_addr, unsigned char reg_addr, unsigned char len, unsigned char *data_ptr)
  {
    HAL_StatusTypeDef status = HAL_OK;
    status = HAL_I2C_Mem_Write(&hi2c1, slave_addr, reg_addr,I2C_MEMADD_SIZE_8BIT, data_ptr, len, 1000);

    /*Check the i2c state*/
    if(status != HAL_OK)
    {
      /*recover the bus when it error*/
      I2C1_Error(slave_addr);
    }

    while(HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
    {
      //char i2c_busy[] = "i2c is busy now...";
      // printf("%s\n",i2c_busy);
    }

    /*is sensor ready to next operation ?*/
    while(HAL_I2C_IsDeviceReady(&hi2c1, slave_addr, 1000, 1000) == HAL_TIMEOUT)
    /*wait for transmit over*/
    while(HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
    {
      //char i2c_transmit[] = "wait for sensor_i2c transmit over...";
      //printf("%s\n",i2c_transmit);
    }
    return status;

  }


  
  /*********************************************************************************************************************************************************************************************************** */
/* USER CODE END 0 */

I2C_HandleTypeDef hi2c1;

/* I2C1 init function */
void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  
  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9);

  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
