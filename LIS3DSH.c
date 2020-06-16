#include "LIS3DSH.h"
#include "main.h"

uint8_t buff8[8];

/**
 *    @brief  Low level 8 bit write procedure
 *    @param  reg
 *    @param  value
 */
void writeReg(uint8_t reg, uint8_t value){
	HAL_I2C_Mem_Write(&LIS3DSH_I2C_PORT, LIS3DSH_I2C_ADDR, reg, 1, &value, 1, 10);
}

/**
 *    @brief  Low level 8 bit read procedure
 *    @param  reg
 *    @return value
 */
uint8_t readReg(uint8_t reg){
	if(HAL_I2C_Mem_Read(&LIS3DSH_I2C_PORT, LIS3DSH_I2C_ADDR, reg, 1, buff8, 1, 10) == HAL_OK){
		return *buff8;
	}
	else{
		return 0;
	}
}

//*****************************************************
//1. Accelerometer initialise function




//******************************************************
/**
 *    @brief  Startup sequence for LIS3DSH
 */
void startup(void){
	// X, Y, Z enabled, ODR = 100 Hz
	writeReg(LIS3DSH_CTRL_REG4_ADDR, 0x67);
	// DRY active high on INT1 pin
	writeReg(LIS3DSH_CTRL_REG3_ADDR, 0xC8);
}

/**
	*		@brief  Reading acceleration data
	*/
uint8_t readAcc(){
	readReg(LIS3DSH_STATUS_ADDR);
	
	readReg(LIS3DSH_OUT_X_L_ADDR);
	readReg(LIS3DSH_OUT_X_H_ADDR);
	readReg(LIS3DSH_OUT_Y_L_ADDR);
	readReg(LIS3DSH_OUT_Y_H_ADDR);
	readReg(LIS3DSH_OUT_Z_L_ADDR);
	readReg(LIS3DSH_OUT_Z_H_ADDR);
}









