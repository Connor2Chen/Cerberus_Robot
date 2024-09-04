/********************************************************** 
 * Last_Author  : Connor.C
 * since        : 2024-08-21 10:18:28
 * message      : The function of this file is 
 * �ļ��������Ŀ��·��   : /Sub_Controller_v01/connor/pre/lis/lis.h
 **********************************************************/

#ifndef __LIS_H_
#define __LIS_H_
 
/* #ifdef   LIS2MDL_MOUDLE
#define   
#else
#define     extern
#endif */
#include "stdbool.h"
#include "main.h"

/* LIS2MDLTR I2C�豸��ַ */ 
#define LIS2MDL_ADDR                                0x3C      //������HAL�⣬�Զ�+��дλ������ȥ�ֶ����
/*#define LIS2MDL_ADDR_WRITE                        0x3C        
  #define LIS2MDL_ADDR_READ                         0x3D */
 
/* �豸�Ĵ�����ַ */
#define LIS2MDL_ADDR_CFGA                         0x60
#define LIS2MDL_ADDR_CFGB                         0x61
#define LIS2MDL_ADDR_CFGC                         0x62
#define LIS2MDL_ADDR_INTCRTL                      0x63
#define LIS2MDL_ADDR_INTSOURCE                    0x64
#define LIS2MDL_ADDR_INTTHSL                      0x65
#define LIS2MDL_ADDR_INTTHSH                      0x66
#define LIS2MDL_ADDR_STATUS                       0x67
 
#define LIS2MDL_ADDR_XOUTL                        0x68
#define LIS2MDL_ADDR_XOUTH                        0x69
#define LIS2MDL_ADDR_YOUTHL                       0x6A
#define LIS2MDL_ADDR_YOUTH                        0x6B
#define LIS2MDL_ADDR_ZOUTL                        0x6C
#define LIS2MDL_ADDR_ZOUTH                        0x6D
 
#define LIS2MDL_ADDR_TEMPL                        0x6E
#define LIS2MDL_ADDR_TEMPH                        0x6F
 
#define LIS2MDL_ADDR_OFFSETX_L                    0x45
#define LIS2MDL_ADDR_OFFSETX_H                    0x46
#define LIS2MDL_ADDR_OFFSETY_L                    0x47
#define LIS2MDL_ADDR_OFFSETY_H                    0x48
#define LIS2MDL_ADDR_OFFSETZ_L                    0x49
#define LIS2MDL_ADDR_OFFSETZ_H                    0x4A
 
#define LIS2MDL_ADDR_CHIPID                       0x4F
 

 
/* �豸�Ĵ�������ֵ */
#define LIS2MDL_CFGA_TEMP_EN                    (1 << 7)    
#define LIS2MDL_CFGA_REBOOT                     (1 << 6)    //����ڴ�
#define LIS2MDL_CFGA_SOFT_RST                   (1 << 5)
#define LIS2MDL_CFGA_LP                         (1 << 4)    //�����͹���

#define LIS2MDL_CFGA_ODR_10HZ                   (0 << 3) | (0 << 2) // ODR[1:0]�� 0/1/2/3 �ֱ��Ӧ 10/20/50/100Hz
#define LIS2MDL_CFGA_ODR_20HZ                   (0 << 3) | (1 << 2)
#define LIS2MDL_CFGA_ODR_50HZ                   (1 << 3) | (0 << 2)
#define LIS2MDL_CFGA_ODR_100HZ                  (1 << 3) | (1 << 2)

#define LIS2MDL_CFGA_MODE_CONTINUE              (0 << 1) | (0 << 0) // ������ģʽѡ����� ���� �� ���� ��������
#define LIS2MDL_CFGA_MODE_SINGLE                (0 << 1) | (1 << 0)
#define LIS2MDL_CFGA_MODE_IDLE                  (1 << 1) | (1 << 0) //����ģʽ Ҳ����(1<<1)|(1<<1)
 
#define LIS2MDL_CFGB_OFF_CANC_ONE_SHOT_EN       (1 << 4)
#define LIS2MDL_CFGB_INT_EN                     (1 << 3)
#define LIS2MDL_CFGB_SET_FREQ                   (1 << 2)    //Ƶ��Ϊ 63*ORD
#define LIS2MDL_CFGB_OFF_CANC_EN                (1 << 1)
#define LIS2MDL_CFGB_LPF_EN                     (1 << 0)    //��ͨ�˲��������ƴ�����ORD/4 ����
 
#define LIS2MDL_CFGC_INT_ON_PIN                 (1 << 6)    //���������ж�
#define LIS2MDL_CFGC_I2C_DIS                    (1 << 5)    //I2Cʧ��   
#define LIS2MDL_CFGC_BDU                        (1 << 4)
#define LIS2MDL_CFGC_BLE                        (1 << 3)    //1���ߵ�λ��ת
#define LIS2MDL_CFGC_SPI                        (1 << 2)
#define LIS2MDL_CFGC_SELF_TEST                  (1 << 1)
#define LIS2MDL_CFGC_DRDY_ON_PIN                (1 << 0)
 

#define LIS2MDL_CHIPID_VALUE                      0x40                          /* ������ʶ */
 
#define LIS2MDL_CFGA_VALUE_CONTINUE             ( LIS2MDL_CFGA_TEMP_EN         \
                                                | LIS2MDL_CFGA_ODR_100HZ       \
                                                | LIS2MDL_CFGA_MODE_CONTINUE )  /* �¶Ȳ���,100HZ,����ģʽ */
 
#define LIS2MDL_CFGA_VALUE_IDLE                 ( LIS2MDL_CFGA_TEMP_EN         \
                                                | LIS2MDL_CFGA_ODR_100HZ       \
                                                | LIS2MDL_CFGA_MoDE_IDLE )      /* �¶Ȳ���,100HZ,����ģʽ */
 
#define LIS2MDL_CFGB_VALUE                      ( LIS2MDL_CFGB_OFF_CANC_EN     \
                                                | LIS2MDL_CFGB_LPF_EN )         /* ƫ�Ƶ���,���õ�ͨ�˲� */
 
#define LIS2MDL_CFGC_VALUE                      ( LIS2MDL_CFGC_BDU )            /* �������������Ա��� */
 
#define LIS2MDL_XYZBUF_LEN                        0x06
#define LIS2MDL_TEMBUF_LEN                        0x02
#define LIS2MDL_OFFSETBUF_LEN                     0x06
 
#define LIS2MDL_SENSITIVITY                     ( 1.5 )                         /* ������������ */
 
#define LIS2MDL_CUM_REBOOT_MAXCNT               ( 100 )                         /* �������ۼ����������� */
#define LIS2MDL_CON_REBOOT_MAXCNT               LIS2MDL_CUM_REBOOT_MAXCNT       /* �������������������� */
 
/* LIS2MDL ������� */ 
/* #define LIS2MDL_POWER_ON()                      BSP_SNR_PWR_H()
#define LIS2MDL_POWER_OFF()                     BSP_SNR_PWR_L() */
 
/* LIS2MDL �ܽ� */ 
#define LIS2MDL_PIN_SCL                    GPIO_PIN_9     /* BSP_IIC1_PIN_SCL */
#define LIS2MDL_PIN_SDA                    GPIO_PIN_8     /* BSP_IIC1_PIN_SDA */
#define LIS2MDL_PORT_SDA_SCL               GPIOB     /* BSP_IIC1_PORT_SDA_SCL */
 
//#define LIS2MDL_READ_TEMP                                                       /* ʹ��LIS2MDL�ڲ��¶� */
 
typedef struct 
{
    int16_t  X_Data;                                                         /* ������X������ */
    int16_t  Y_Data;                                                         /* ������Y������ */
    int16_t  Z_Data;                                                         /* ������Z������ */
    int16_t  T_Data;                                                         /* �������ڲ��¶� */
    uint16_t  MagDensity;                                                     /* �������ܴ���ǿ�� */
    float    XY_Angle;                                                       /* ������X��Y��н� */
    float    XZ_Angle;                                                       /* ������X��Z��н� */
    float    YZ_Angle;                                                       /* ������Y��Z��н� */
 
    int16_t  X_Offset;                                                       /* ������X��OFFSET */
    int16_t  Y_Offset;                                                       /* ������Y��OFFSET */
    int16_t  Z_Offset;                                                       /* ������Z��OFFSET */
 
    bool HardFault;                                                      /* ������Ӳ���� */
    bool DetectInvalid;                                                  /* ���������ʧЧ */
}LIS2MDL_SAMPLE_DEF;
 
typedef struct 
{
    int16_t X_Offset;                                                        /* ������X��OFFSET */
    int16_t Y_Offset;                                                        /* ������Y��OFFSET */
    int16_t Z_Offset;                                                        /* ������Z��OFFSET */
}LIS2MDL_Save_DEF;
 
typedef enum{
    LIS2MDL_DATA_SUCCESS,                                                       /* ��ȡ���ݳɹ� */
    LIS2MDL_DATA_ERROR_ADDR,                                                    /* ������ͨ�ŵ�ַ���� */
    LIS2MDL_DATA_ERROR_TIMEOUT,                                                 /* ��������ȡ��ʱ */
    LIS2MDL_DATA_ERROR_VALUE,                                                   /* ��������ֵ���� */
}LIS2MDL_RESULT_SAMPLE;
/*
***********************************************************************************************
*                                            EXTERNS
***********************************************************************************************
*/
  LIS2MDL_Save_DEF LIS2MDLSave;
/*
***********************************************************************************************
*                                  GLOBAL FUNCTION PROTOTYPES
***********************************************************************************************
*/
  void LIS2MDL_Soft_Reset(void);
  void LIS2MDL_Hard_Reset(void);
  bool LIS2MDL_Init(void);
  bool LIS2MDL_HardState(void);
  bool LIS2MDL_DetectState(void);
  bool LIS2MDL_Adjust_Magnetic(void);
  LIS2MDL_RESULT_SAMPLE LIS2MDL_Read_MagDensity(void);
  void LIS2MDL_ManualAdjustMag(int16_t x_offset,int16_t y_offset,int16_t z_offset);

//-------------------------------------------------------------------------------------------
//  ԭ���� .c�ļ��а��� �ڲ�����  ---> Ϊ�˷��㣬��ȫ�õ�ͷ�ļ�����
//-------------------------------------------------------------------------------------------
 void         LIS2MDL_IOInit(void);             //���û��Ҫ�ɣ���I2C��ʼ�������ú���
 uint8_t      LIS2MDL_Register_Read(uint8_t addr, uint8_t num);
 void         LIS2MDL_Register_Write(uint8_t addr,uint8_t val);
 void         LIS2MDL_Read_XYZ(int16_t *x,int16_t *y,int16_t *z);
 void         LIS2MDL_Read_Offset(int16_t *x_offset,int16_t *y_offset,int16_t *z_offset);
 void         LIS2MDL_Write_Offset(int16_t x_offset,int16_t y_offset,int16_t z_offset);
 void         LIS2MDL_Clean_Offset(void);
 bool         LIS2MDL_Wait_Data_Update(uint8_t max_cnt);
 bool         LIS2MDL_Read_Average(int16_t *x,int16_t *y,int16_t *z,uint8_t times);
 void         LIS2MDL_Read_TEMP(int16_t *temp);


#endif


