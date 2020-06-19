#include "LIS3DSH.h"
#include "main.h"

static I2C_HandleTypeDef hi2c1;

//2. Sensitivity value
static float lis3dsh_Sensitivity = LIS3DSH_SENSITIVITY_0_06G;
//3. bias variables
static float __X_Bias = 0.0f;
static float __Y_Bias = 0.0f;
static float __Z_Bias = 0.0f;
//4. scaling variables
static float __X_Scale = 1.0f;
static float __Y_Scale = 1.0f;
static float __Z_Scale = 1.0f;


/**
	* @brief Write into the specified register
	* @param reg register to be written
	* @param dataW Pointer to data buffer
	* @param size Amount of data to be sent
  */
void LIS3DSH_WriteReg(uint8_t reg, uint8_t *dataW, uint8_t size){
	HAL_I2C_Mem_Write(&hi2c1, LIS3DSH_I2C_ADDR, reg, 1, (uint8_t*)dataW, size, 10);
}

/**
	* @brief Read from the specified register
	* @param reg register to be read
	* @param dataR Pointer to data buffer
	* @param size Amount of data to be sent
  */
void LIS3DSH_ReadReg(uint8_t reg, uint8_t *dataR, uint8_t size){
	HAL_I2C_Mem_Read(&hi2c1, LIS3DSH_I2C_ADDR, reg, 1, (uint8_t*)dataR, size, 10);
}

/**
	* @brief Initialization function for Accelerometer
	* @param hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
	* @param accInitDef Pointer to a LIS3DSH_InitTypeDef sturcture that contains
									 the configuration information for the Accelerometer.
	*/
void LIS3DSH_Init(I2C_HandleTypeDef *hi2c, LIS3DSH_InitTypeDef *accInitDef){
	uint8_t I2CData = 0;
	
	memcpy(&hi2c1, hi2c, sizeof(*hi2c));
	//** 1. Enable Axes and Output Data Rate **//
	//Set CTRL REG4 settings value
	I2CData |= (accInitDef->enableAxes & 0x07);		//Enable Axes
	I2CData |= (accInitDef->dataRate & 0xF0);			//Output Data Rate
	//Write to accelerometer
	LIS3DSH_WriteReg(LIS3DSH_CTRL_REG4_ADDR, &I2CData, 1);
	
	//** 2. Full-Scale selection, Anti-aliasing BW, self test and 4-wire SPI **//
	I2CData = 0;
	I2CData |= (accInitDef->antiAliasingBW & 0xC0);		//Anti-aliasing BW
	I2CData |= (accInitDef->fullScale & 0x38);				//Full-Scale
	//Write to accelerometer
	LIS3DSH_WriteReg(LIS3DSH_CTRL_REG5_ADDR, &I2CData, 1);
	
	//** 3. Interrupt Configuration **//
	if(accInitDef->interruptEnable){
		I2CData = 0x88;
		//Write to accelerometer
		LIS3DSH_WriteReg(LIS3DSH_CTRL_REG3_ADDR, &I2CData, 1);
	}
	
	//Assign sensor sensitivity (based on Full-Scale)
	switch(accInitDef->fullScale){
		case LIS3DSH_FULLSCALE_2:
			lis3dsh_Sensitivity = LIS3DSH_SENSITIVITY_0_06G;
			break;
		
		case LIS3DSH_FULLSCALE_4:
			lis3dsh_Sensitivity = LIS3DSH_SENSITIVITY_0_12G;
			break;
		
		case LIS3DSH_FULLSCALE_6:
			lis3dsh_Sensitivity = LIS3DSH_SENSITIVITY_0_18G;
			break;
		
		case LIS3DSH_FULLSCALE_8:
			lis3dsh_Sensitivity = LIS3DSH_SENSITIVITY_0_24G;
			break;
		
		case LIS3DSH_FULLSCALE_16:
			lis3dsh_Sensitivity = LIS3DSH_SENSITIVITY_0_73G;
			break;
	}
}

/**
	* @brief Poll for Data Ready
	* @param msTimeout is time in millisecond
	*/
bool LIS3DSH_PollDRDY(uint32_t msTimeout){
	uint8_t Acc_status;
	uint32_t startTick = HAL_GetTick();
	do{
		//Read status register with a timeout
		LIS3DSH_ReadReg(0x27, &Acc_status, 1);
		if(Acc_status & 0x07)break;
		
	}while((Acc_status & 0x07)==0 && (HAL_GetTick() - startTick) < msTimeout);
	if(Acc_status & 0x07){
		return true;
	}
	return false;
	
}

/** 
	*	@brief Get Accelerometer raw data
	*/
LIS3DSH_DataRaw LIS3DSH_GetDataRaw(void){
	uint8_t I2CBuf[2];
	LIS3DSH_DataRaw tempDataRaw;
	//Read X data
	LIS3DSH_ReadReg(LIS3DSH_OUT_X_L_ADDR, I2CBuf, 2);
	tempDataRaw.x = ((I2CBuf[1] << 8) + I2CBuf[0]);
	
	//Read Y data
	LIS3DSH_ReadReg(LIS3DSH_OUT_Y_L_ADDR, I2CBuf, 2);
	tempDataRaw.y = ((I2CBuf[1] << 8) + I2CBuf[0]);
	
	//Read Z data
	LIS3DSH_ReadReg(LIS3DSH_OUT_Z_L_ADDR, I2CBuf, 2);
	tempDataRaw.z = ((I2CBuf[1] << 8) + I2CBuf[0]);
	
	return tempDataRaw;
}

/** 
	*	@brief Get Accelerometer mg data
	*/
LIS3DSH_DataScaled LIS3DSH_GetDataScaled(void){
	//Read raw data
	LIS3DSH_DataRaw tempRawData = LIS3DSH_GetDataRaw();;
	//Scale data and return 
	LIS3DSH_DataScaled tempScaledData;
	tempScaledData.x = (tempRawData.x * lis3dsh_Sensitivity * __X_Scale) + 0.0f - __X_Bias;
	tempScaledData.y = (tempRawData.y * lis3dsh_Sensitivity * __Y_Scale) + 0.0f - __Y_Bias;
	tempScaledData.z = (tempRawData.z * lis3dsh_Sensitivity * __Z_Scale) + 0.0f - __Z_Bias;
	
	return tempScaledData;
}

/**
	* @brief Calibration functions, Set X-Axis calibrate
	* @param x_min minimum value on x axis
	* @param x_max maximum value on x axis
	*/
void LIS3DSH_X_calibrate(float x_min, float x_max)
{
	__X_Bias = (x_max+x_min)/2.0f;
	__X_Scale = (2*10000)/(x_max - x_min);
}

/**
	* @brief Calibration functions, Set Y-Axis calibrate
	* @param y_min minimum value on y axis
	* @param y_max maximum value on y axis
	*/
void LIS3DSH_Y_calibrate(float y_min, float y_max)
{
	__Y_Bias = (y_max+y_min)/2.0f;
	__Y_Scale = (2*10000)/(y_max - y_min);
}

/**
	* @brief Calibration functions, Set Z-Axis calibrate
	* @param z_min minimum value on z axis
	* @param z_max maximum value on z axis
	*/
void LIS3DSH_Z_calibrate(float z_min, float z_max)
{
	__Z_Bias = (z_max+z_min)/2.0f;
	__Z_Scale = (2*10000)/(z_max - z_min);
}

/**
  * @brief  Set LIS3DSH for click detection
  * @param  None
  * @retval None
  */
void LIS3DSH_Click_IntConfig(void){
	uint8_t ctrl = 0x00;
  LIS3DSH_InterruptConfigTypeDef   LIS3DSH_InterruptStruct; 
	
	//ACCELERO_IO_ITConfig();
	
	/* Set LIS3DSH Interrupt configuration */
  LIS3DSH_InterruptStruct.Interrupt_Selection_Enable = LIS3DSH_INTERRUPT_2_ENABLE;
  LIS3DSH_InterruptStruct.Interrupt_Request = LIS3DSH_INTERRUPT_REQUEST_LATCHED;
  LIS3DSH_InterruptStruct.Interrupt_Signal = LIS3DSH_INTERRUPT_SIGNAL_HIGH;
  LIS3DSH_InterruptStruct.State_Machine1_Enable = LIS3DSH_SM_DISABLE;
  LIS3DSH_InterruptStruct.State_Machine2_Enable = LIS3DSH_SM_ENABLE;
  LIS3DSH_InterruptStruct.State_Machine2_Interrupt = LIS3DSH_SM_INT1;
	
	//LIS3DSH_InterruptConfig(&LIS3DSH_InterruptStruct);
	
	  /* Set LIS3DSH State Machines configuration */
  ctrl=0x03; 
  LIS3DSH_WriteReg(LIS3DSH_TIM2_1_L_ADDR, &ctrl, 1);
  ctrl=0xC8; 
  LIS3DSH_WriteReg(LIS3DSH_TIM1_1_L_ADDR, &ctrl, 1);
  ctrl=0x45; 
  LIS3DSH_WriteReg(LIS3DSH_THRS2_1_ADDR, &ctrl, 1);
  ctrl=0xFC; 
  LIS3DSH_WriteReg(LIS3DSH_MASK1_A_ADDR, &ctrl, 1);
  ctrl=0xA1; 
  LIS3DSH_WriteReg(LIS3DSH_SETT1_ADDR, &ctrl, 1);
  ctrl=0x01; 
  LIS3DSH_WriteReg(LIS3DSH_PR1_ADDR, &ctrl, 1);

  LIS3DSH_WriteReg(LIS3DSH_SETT2_ADDR, &ctrl, 1);
  
  /* Configure State Machine 2 to detect single click */
  LIS3DSH_WriteReg(LIS3DSH_ST2_1_ADDR, &ctrl, 1);
  ctrl=0x06; 
  LIS3DSH_WriteReg(LIS3DSH_ST2_2_ADDR, &ctrl, 1);
  ctrl=0x28; 
  LIS3DSH_WriteReg(LIS3DSH_ST2_3_ADDR, &ctrl, 1);
  ctrl=0x11; 
  LIS3DSH_WriteReg(LIS3DSH_ST2_4_ADDR, &ctrl, 1);
	
}
