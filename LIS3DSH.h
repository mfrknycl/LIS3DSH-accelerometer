#ifndef __LIS3DSH_H__
#define __LIS3DSH_H__


/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include <stdbool.h>
#include <string.h>


extern I2C_HandleTypeDef hi2c1;
/* Variables ------------------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/

//Device Registers
#define LIS3DSH_I2C_ADDR                    (0x1E<<1)  //3C
#define LIS3DSH_I2C_PORT		 								 hi2c1

//LIS3DHS registers addresses
#define LIS3DSH_WHO_AM_I_ADDR                0x0F
#define LIS3DSH_OFF_X_ADDR                   0x10
#define LIS3DSH_OFF_Y_ADDR                   0x11
#define LIS3DSH_OFF_Z_ADDR                   0x12

#define LIS3DSH_CTRL_REG4_ADDR               0x20
#define LIS3DSH_CTRL_REG1_ADDR               0x21
#define LIS3DSH_CTRL_REG2_ADDR               0x22
#define LIS3DSH_CTRL_REG3_ADDR               0x23              
#define LIS3DSH_CTRL_REG5_ADDR               0x24
#define LIS3DSH_CTRL_REG6_ADDR               0x25

#define LIS3DSH_FIFO_CTRL_REG								 0x2E

#define LIS3DSH_STATUS_ADDR                  0x27

#define LIS3DSH_OUT_TEMP    							   0x0C

#define LIS3DSH_OUT_X_L_ADDR                 0x28
#define LIS3DSH_OUT_X_H_ADDR                 0x29
#define LIS3DSH_OUT_Y_L_ADDR                 0x2A
#define LIS3DSH_OUT_Y_H_ADDR                 0x2B
#define LIS3DSH_OUT_Z_L_ADDR                 0x2C
#define LIS3DSH_OUT_Z_H_ADDR                 0x2D


//Data rate
#define LIS3DSH_DATARATE_POWERDOWN           ((uint8_t)0x00)  /* Power Down Mode*/
#define LIS3DSH_DATARATE_3_125               ((uint8_t)0x10)  /* 3.125 Hz Normal Mode */
#define LIS3DSH_DATARATE_6_25                ((uint8_t)0x20)  /* 6.25  Hz Normal Mode */
#define LIS3DSH_DATARATE_12_5                ((uint8_t)0x30)  /* 12.5  Hz Normal Mode */
#define LIS3DSH_DATARATE_25                  ((uint8_t)0x40)  /* 25    Hz Normal Mode */
#define LIS3DSH_DATARATE_50                  ((uint8_t)0x50)  /* 50    Hz Normal Mode */
#define LIS3DSH_DATARATE_100                 ((uint8_t)0x60)  /* 100   Hz Normal Mode */
#define LIS3DSH_DATARATE_400                 ((uint8_t)0x70)  /* 400   Hz Normal Mode */
#define LIS3DSH_DATARATE_800                 ((uint8_t)0x80)  /* 800   Hz Normal Mode */
#define LIS3DSH_DATARATE_1600                ((uint8_t)0x90)  /* 1600  Hz Normal Mode */

//Full scale
#define LIS3DSH_FULLSCALE_2                  ((uint8_t)0x00)  /* 2  g  */
#define LIS3DSH_FULLSCALE_4                  ((uint8_t)0x08)  /* 4  g  */
#define LIS3DSH_FULLSCALE_6                  ((uint8_t)0x10)  /* 6  g  */
#define LIS3DSH_FULLSCALE_8                  ((uint8_t)0x18)  /* 8  g  */
#define LIS3DSH_FULLSCALE_16                 ((uint8_t)0x20)  /* 16 g */

//Anti-Aliasing Bandwidth
#define LIS3DSH_FILTER_BW_800                ((uint8_t)0x00)  /* 800 Hz */
#define LIS3DSH_FILTER_BW_400                ((uint8_t)0x80)  /* 400 Hz  */
#define LIS3DSH_FILTER_BW_200                ((uint8_t)0x40)  /* 200 Hz */
#define LIS3DSH_FILTER_BW_50                 ((uint8_t)0xC0)  /* 50 Hz  */

//Enabled axis 
#define LIS3DSH_X_ENABLE                     ((uint8_t)0x01)
#define LIS3DSH_Y_ENABLE                     ((uint8_t)0x02)
#define LIS3DSH_Z_ENABLE                     ((uint8_t)0x04)
#define LIS3DSH_XYZ_ENABLE                   ((uint8_t)0x07)

//Sensitivity values (Based on Full-Scale)
#define LIS3DSH_SENSITIVITY_0_06G            0.06  /* 0.06 mg/digit*/
#define LIS3DSH_SENSITIVITY_0_12G            0.12  /* 0.12 mg/digit*/
#define LIS3DSH_SENSITIVITY_0_18G            0.18  /* 0.18 mg/digit*/
#define LIS3DSH_SENSITIVITY_0_24G            0.24  /* 0.24 mg/digit*/
#define LIS3DSH_SENSITIVITY_0_73G            0.73  /* 0.73 mg/digit*/

#define LIS3DSH_SETT1 0x5B
#define LIS3DSH_SETT2 0x7B 

#define LIS3DSH_PEAK1 0x19
#define LIS3DSH_PEAK2 0x1A

#define LIS3DSH_MASK1_A 0x5A
//*********
#define LIS3DSH_INTERRUPT_1_ENABLE           ((uint8_t)0x88)
#define LIS3DSH_INTERRUPT_2_ENABLE           ((uint8_t)0x00)
#define LIS3DSH_INTERRUPT_1_2_ENABLE         ((uint8_t)0x88)

#define LIS3DSH_INTERRUPT_REQUEST_LATCHED    ((uint8_t)0x00)
#define LIS3DSH_INTERRUPT_REQUEST_PULSED     ((uint8_t)0x20)

#define LIS3DSH_INTERRUPT_SIGNAL_LOW         ((uint8_t)0x00)
#define LIS3DSH_INTERRUPT_SIGNAL_HIGH        ((uint8_t)0x40)

#define LIS3DSH_SM_ENABLE                   ((uint8_t)0x01)
#define LIS3DSH_SM_DISABLE                  ((uint8_t)0x00)

#define LIS3DSH_SM_INT1                     ((uint8_t)0x00)
#define LIS3DSH_SM_INT2                     ((uint8_t)0x08)

#define LIS3DSH_TIM2_1_L_ADDR                0x52 
#define LIS3DSH_TIM1_1_L_ADDR                0x54
#define LIS3DSH_THRS2_1_ADDR                 0x56
#define LIS3DSH_MASK1_A_ADDR                 0x5A
#define LIS3DSH_SETT1_ADDR                   0x5B
#define LIS3DSH_PR1_ADDR                     0x5C
#define LIS3DSH_SETT2_ADDR                   0x7B
#define LIS3DSH_ST2_1_ADDR                   0x60
#define LIS3DSH_ST2_2_ADDR                   0x61
#define LIS3DSH_ST2_3_ADDR                   0x62
#define LIS3DSH_ST2_4_ADDR                   0x63

/* Tyoedefs Decleration ------------------------------------------------------------------*/
//Accelerometer Configuration struct
typedef struct 
{
	uint8_t dataRate;
	uint8_t fullScale;
	uint8_t antiAliasingBW;
	uint8_t enableAxes;
	bool interruptEnable;
}LIS3DSH_InitTypeDef;

//Accelerometer raw data
typedef struct 
{
	int16_t x;
	int16_t y;
	int16_t z;
}LIS3DSH_DataRaw;

//Accelerometer mg data (scaled data)
typedef struct
{
	float x;
	float y;
	float z;
}LIS3DSH_DataScaled;

/* LIS3DSH Interrupt struct */
typedef struct
{
  uint8_t Interrupt_Request;            /* Latch/Pulse Interrupt request into CTRL_REG3 register */
  uint8_t Interrupt_Selection_Enable;   /* Interrupt1/2 selection enable into CTRL_REG3 register */
  uint8_t Interrupt_Signal;             /* Interrupt signal active Low/High into CTRL_REG3 register */  
  uint8_t State_Machine1_Enable;        /* State Machine 1 enable/disable into CTRL_REG1 register */ 
  uint8_t State_Machine1_Interrupt;     /* State Machine 1 routed Interrupt into CTRL_REG1 register */
  uint8_t State_Machine2_Enable;        /* State Machine 2 enable/disable into CTRL_REG2 register */  
  uint8_t State_Machine2_Interrupt;     /* State Machine 2 routed Interrupt into CTRL_REG1 register */
}LIS3DSH_InterruptConfigTypeDef;

/* Function Decleration ------------------------------------------------------------------*/
void LIS3DSH_X_calibrate(float x_min, float x_max);
void LIS3DSH_Y_calibrate(float y_min, float y_max);
void LIS3DSH_Z_calibrate(float z_min, float z_max);

void LIS3DSH_WriteReg(uint8_t reg, uint8_t *dataW, uint8_t size);
void LIS3DSH_ReadReg(uint8_t reg, uint8_t *dataR, uint8_t size);
void LIS3DSH_Init(I2C_HandleTypeDef *accI2C, LIS3DSH_InitTypeDef *accInitDef);

bool LIS3DSH_PollDRDY(uint32_t msTimeout);

LIS3DSH_DataScaled LIS3DSH_GetDataScaled(void);

LIS3DSH_DataRaw LIS3DSH_GetDataRaw(void);

void LIS3DSH_Click_IntConfig(void);




#endif //__LIS3DSH_H__
