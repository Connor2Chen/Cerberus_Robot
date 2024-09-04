/********************************************************** 
 * Last_Author  : Connor.C
 * since        : 2024-08-21 10:18:28
 * message      : The function of this file is 
 * 文件相对于项目的路径   : /Sub_Controller_v01/connor/pre/lis/lis.h
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

/* LIS2MDLTR I2C设备地址 */ 
#define LIS2MDL_ADDR                                0x3C      //这里用HAL库，自动+读写位，不用去手动添加
/*#define LIS2MDL_ADDR_WRITE                        0x3C        
  #define LIS2MDL_ADDR_READ                         0x3D */
 
/* 设备寄存器地址 */
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
 

 
/* 设备寄存器参数值 */
#define LIS2MDL_CFGA_TEMP_EN                    (1 << 7)    
#define LIS2MDL_CFGA_REBOOT                     (1 << 6)    //清除内存
#define LIS2MDL_CFGA_SOFT_RST                   (1 << 5)
#define LIS2MDL_CFGA_LP                         (1 << 4)    //开启低功耗

#define LIS2MDL_CFGA_ODR_10HZ                   (0 << 3) | (0 << 2) // ODR[1:0]的 0/1/2/3 分别对应 10/20/50/100Hz
#define LIS2MDL_CFGA_ODR_20HZ                   (0 << 3) | (1 << 2)
#define LIS2MDL_CFGA_ODR_50HZ                   (1 << 3) | (0 << 2)
#define LIS2MDL_CFGA_ODR_100HZ                  (1 << 3) | (1 << 2)

#define LIS2MDL_CFGA_MODE_CONTINUE              (0 << 1) | (0 << 0) // 工作的模式选择仅有 连续 和 单次 采样两种
#define LIS2MDL_CFGA_MODE_SINGLE                (0 << 1) | (1 << 0)
#define LIS2MDL_CFGA_MODE_IDLE                  (1 << 1) | (1 << 0) //空闲模式 也可以(1<<1)|(1<<1)
 
#define LIS2MDL_CFGB_OFF_CANC_ONE_SHOT_EN       (1 << 4)
#define LIS2MDL_CFGB_INT_EN                     (1 << 3)
#define LIS2MDL_CFGB_SET_FREQ                   (1 << 2)    //频率为 63*ORD
#define LIS2MDL_CFGB_OFF_CANC_EN                (1 << 1)
#define LIS2MDL_CFGB_LPF_EN                     (1 << 0)    //低通滤波器，限制带宽在ORD/4 以下
 
#define LIS2MDL_CFGC_INT_ON_PIN                 (1 << 6)    //启用引脚中断
#define LIS2MDL_CFGC_I2C_DIS                    (1 << 5)    //I2C失能   
#define LIS2MDL_CFGC_BDU                        (1 << 4)
#define LIS2MDL_CFGC_BLE                        (1 << 3)    //1：高低位翻转
#define LIS2MDL_CFGC_SPI                        (1 << 2)
#define LIS2MDL_CFGC_SELF_TEST                  (1 << 1)
#define LIS2MDL_CFGC_DRDY_ON_PIN                (1 << 0)
 

#define LIS2MDL_CHIPID_VALUE                      0x40                          /* 器件标识 */
 
#define LIS2MDL_CFGA_VALUE_CONTINUE             ( LIS2MDL_CFGA_TEMP_EN         \
                                                | LIS2MDL_CFGA_ODR_100HZ       \
                                                | LIS2MDL_CFGA_MODE_CONTINUE )  /* 温度补偿,100HZ,连续模式 */
 
#define LIS2MDL_CFGA_VALUE_IDLE                 ( LIS2MDL_CFGA_TEMP_EN         \
                                                | LIS2MDL_CFGA_ODR_100HZ       \
                                                | LIS2MDL_CFGA_MoDE_IDLE )      /* 温度补偿,100HZ,空闲模式 */
 
#define LIS2MDL_CFGB_VALUE                      ( LIS2MDL_CFGB_OFF_CANC_EN     \
                                                | LIS2MDL_CFGB_LPF_EN )         /* 偏移抵消,启用低通滤波 */
 
#define LIS2MDL_CFGC_VALUE                      ( LIS2MDL_CFGC_BDU )            /* 开启数据完整性保护 */
 
#define LIS2MDL_XYZBUF_LEN                        0x06
#define LIS2MDL_TEMBUF_LEN                        0x02
#define LIS2MDL_OFFSETBUF_LEN                     0x06
 
#define LIS2MDL_SENSITIVITY                     ( 1.5 )                         /* 磁力计灵敏度 */
 
#define LIS2MDL_CUM_REBOOT_MAXCNT               ( 100 )                         /* 磁力计累计重启最大次数 */
#define LIS2MDL_CON_REBOOT_MAXCNT               LIS2MDL_CUM_REBOOT_MAXCNT       /* 磁力计连续重启最大次数 */
 
/* LIS2MDL 供电控制 */ 
/* #define LIS2MDL_POWER_ON()                      BSP_SNR_PWR_H()
#define LIS2MDL_POWER_OFF()                     BSP_SNR_PWR_L() */
 
/* LIS2MDL 管脚 */ 
#define LIS2MDL_PIN_SCL                    GPIO_PIN_9     /* BSP_IIC1_PIN_SCL */
#define LIS2MDL_PIN_SDA                    GPIO_PIN_8     /* BSP_IIC1_PIN_SDA */
#define LIS2MDL_PORT_SDA_SCL               GPIOB     /* BSP_IIC1_PORT_SDA_SCL */
 
//#define LIS2MDL_READ_TEMP                                                       /* 使用LIS2MDL内部温度 */
 
typedef struct 
{
    int16_t  X_Data;                                                         /* 磁力计X轴数据 */
    int16_t  Y_Data;                                                         /* 磁力计Y轴数据 */
    int16_t  Z_Data;                                                         /* 磁力计Z轴数据 */
    int16_t  T_Data;                                                         /* 磁力计内部温度 */
    uint16_t  MagDensity;                                                     /* 磁力计总磁扰强度 */
    float    XY_Angle;                                                       /* 磁力计X轴Y轴夹角 */
    float    XZ_Angle;                                                       /* 磁力计X轴Z轴夹角 */
    float    YZ_Angle;                                                       /* 磁力计Y轴Z轴夹角 */
 
    int16_t  X_Offset;                                                       /* 磁力计X轴OFFSET */
    int16_t  Y_Offset;                                                       /* 磁力计Y轴OFFSET */
    int16_t  Z_Offset;                                                       /* 磁力计Z轴OFFSET */
 
    bool HardFault;                                                      /* 传感器硬件损坏 */
    bool DetectInvalid;                                                  /* 传感器检测失效 */
}LIS2MDL_SAMPLE_DEF;
 
typedef struct 
{
    int16_t X_Offset;                                                        /* 磁力计X轴OFFSET */
    int16_t Y_Offset;                                                        /* 磁力计Y轴OFFSET */
    int16_t Z_Offset;                                                        /* 磁力计Z轴OFFSET */
}LIS2MDL_Save_DEF;
 
typedef enum{
    LIS2MDL_DATA_SUCCESS,                                                       /* 获取数据成功 */
    LIS2MDL_DATA_ERROR_ADDR,                                                    /* 传感器通信地址错误 */
    LIS2MDL_DATA_ERROR_TIMEOUT,                                                 /* 传感器读取超时 */
    LIS2MDL_DATA_ERROR_VALUE,                                                   /* 传感器数值错误 */
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
//  原作者 .c文件中包含 内部函数  ---> 为了方便，我全拿到头文件里了
//-------------------------------------------------------------------------------------------
 void         LIS2MDL_IOInit(void);             //这个没必要吧，在I2C初始化里设置好了
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


