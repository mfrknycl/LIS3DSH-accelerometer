#include "LIS3DSH.h"
#include "main.h"

uint8_t buff8[8];
int res1 = 0;
int res2 = 0;

//3. bias variables
static float __X_Bias = 0.0f;
static float __Y_Bias = 0.0f;
static float __Z_Bias = 0.0f;
//4. scaling variables
static float __X_Scale = 1.0f;
static float __Y_Scale = 1.0f;
static float __Z_Scale = 1.0f;

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

/**
 *    @brief  Startup sequence for LIS3DSH
 */
void startup(void){
	// X, Y, Z enabled, ODR = 100 Hz
	//writeReg(LIS3DSH_CTRL_REG4_ADDR, 0x67);
	// DRY active high on INT1 pin
	//writeReg(LIS3DSH_CTRL_REG3_ADDR, 0xC8);
	//***************************************
	// Normal power mode, all axes enabled, 50 Hz ODR
	writeReg(LIS3DSH_CTRL_REG4_ADDR, 0x5F);
	// 200 Hz antialias filter, +/- 2g FS range
	writeReg(LIS3DSH_CTRL_REG5_ADDR, 0x80);
	// configure FIFO for bypass mode
	writeReg(LIS3DSH_FIFO_CTRL_REG, 0);
	// disable FIFO, enable register address auto-increment
	writeReg(LIS3DSH_CTRL_REG6_ADDR, 0x10);
}

// Reads the 3 accelerometer channels
void readAccel(int16_t *pX, int16_t *pY, int16_t *pZ)
{
		uint8_t xla;
		uint8_t xha;
		uint8_t yla;
		uint8_t yha;
		uint8_t zla;
		uint8_t zha;

		xla = readReg(LIS3DSH_OUT_X_L_ADDR);
		xha = readReg(LIS3DSH_OUT_X_H_ADDR);
		yla = readReg(LIS3DSH_OUT_Y_L_ADDR);
		yha = readReg(LIS3DSH_OUT_Y_H_ADDR);
		zla = readReg(LIS3DSH_OUT_Z_L_ADDR);
		zha = readReg(LIS3DSH_OUT_Z_H_ADDR);

		*pX = (int16_t)(xha << 8 | xla);
		*pY = (int16_t)(yha << 8 | yla);
		*pZ = (int16_t)(zha << 8 | zla);

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

//** Calibration functions **//
//1. Set X-Axis calibrate
void LIS3DSH_X_calibrate(float x_min, float x_max)
{
	__X_Bias = (x_max+x_min)/2.0f;
	__X_Scale = (2*10000)/(x_max - x_min);
}
//2. Set Y-Axis calibrate
void LIS3DSH_Y_calibrate(float y_min, float y_max)
{
	__Y_Bias = (y_max+y_min)/2.0f;
	__Y_Scale = (2*10000)/(y_max - y_min);
}
//3. Set Z-Axis calibrate
void LIS3DSH_Z_calibrate(float z_min, float z_max)
{
	__Z_Bias = (z_max+z_min)/2.0f;
	__Z_Scale = (2*10000)/(z_max - z_min);
}

//************************************

//1. Write IO
void LIS3DSH_WriteIO(uint8_t reg, uint8_t *dataW, uint8_t size){
	res1 = HAL_I2C_Mem_Write(&hi2c1, LIS3DSH_I2C_ADDR, reg, 8, (uint8_t*)dataW, size, 10);
}

//2. Read IO
void LIS3DSH_ReadIO(uint8_t reg, uint8_t *dataR, uint8_t size){
	res2 = HAL_I2C_Mem_Read(&hi2c1, LIS3DSH_I2C_ADDR, reg, 8, (uint8_t*)dataR, size, 10);
}




