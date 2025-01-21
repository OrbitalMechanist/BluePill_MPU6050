#include "mpu6050.h"

MPU6050_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef* hi2c, MPU6050_AddrTypeDef targetAddr){
	HAL_StatusTypeDef i2cStatus;

	  uint8_t unsleepBurst[] = {0x6b, 0};

	  i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, unsleepBurst, 2, 150);
	  if(i2cStatus != HAL_OK){
		  return MPU6050_STATUS_I2C_FAIL;
	  } else {
		  return MPU6050_STATUS_OK;
	  }
}

MPU6050_StatusTypeDef MPU6050_SetAccelRange(I2C_HandleTypeDef* hi2c, MPU6050_AddrTypeDef targetAddr,
		MPU6050_AccelRangeTypeDef range){
	HAL_StatusTypeDef i2cStatus;

	uint8_t accelRangeBurst[] = {0x1c, range << 3};

	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, accelRangeBurst, 2, 150);

	if(i2cStatus != HAL_OK){
	  return MPU6050_STATUS_I2C_FAIL;
	} else {
	  return MPU6050_STATUS_OK;
	}
}

MPU6050_StatusTypeDef MPU6050_SetGyroRange(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr, MPU6050_GyroRangeTypeDef range){
	HAL_StatusTypeDef i2cStatus;

	uint8_t gyroRangeBurst[] = {27, range << 3};

	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, gyroRangeBurst, 2, 150);

	if(i2cStatus != HAL_OK){
		return MPU6050_STATUS_I2C_FAIL;
	} else {
		return MPU6050_STATUS_OK;
	}
}


int16_t MPU6050_GetAccelXRegister(I2C_HandleTypeDef* hi2c, MPU6050_AddrTypeDef targetAddr,
		MPU6050_StatusTypeDef* hStatus){
	HAL_StatusTypeDef i2cStatus;

	/*STM32 is little-endian, so the less-significant registers need to go
	* into lower memory addresses when being made into a 16-bit integer.
	* Here, we will be getting the less significant register first,
	* but sometimes MPU explicitly requires that the most significant
	* register be read fist. In that case, the order is reversed from
	* what is seen in these data registers.*/
	uint8_t registersAccelX[] = {60, 59};
	int16_t accelXResult = 0;

	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, registersAccelX, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Receive(hi2c, targetAddr, (uint8_t*)&accelXResult, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, registersAccelX + 1, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Receive(hi2c, targetAddr, ((uint8_t*)&accelXResult) + 1, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	if(hStatus != NULL){
		*hStatus = MPU6050_STATUS_OK;
	}
	return accelXResult;
}

int16_t MPU6050_GetAccelYRegister(I2C_HandleTypeDef* hi2c, MPU6050_AddrTypeDef targetAddr,
		MPU6050_StatusTypeDef* hStatus){
	HAL_StatusTypeDef i2cStatus;

	uint8_t registersAccelY[] = {62, 61};
	int16_t accelYResult = 0;

	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, registersAccelY, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Receive(hi2c, targetAddr, (uint8_t*)&accelYResult, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, registersAccelY + 1, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Receive(hi2c, targetAddr, ((uint8_t*)&accelYResult) + 1, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	if(hStatus != NULL){
		*hStatus = MPU6050_STATUS_OK;
	}
	return accelYResult;
}

int16_t MPU6050_GetAccelZRegister(I2C_HandleTypeDef* hi2c, MPU6050_AddrTypeDef targetAddr,
		MPU6050_StatusTypeDef* hStatus)
{
	HAL_StatusTypeDef i2cStatus;

	uint8_t registersAccelZ[] = {64, 63};
	int16_t accelZResult = 0;

	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, registersAccelZ, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Receive(hi2c, targetAddr, (uint8_t*)&accelZResult, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, registersAccelZ + 1, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Receive(hi2c, targetAddr, ((uint8_t*)&accelZResult) + 1, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	if(hStatus != NULL){
		*hStatus = MPU6050_STATUS_OK;
	}
	return accelZResult;
}

int16_t MPU6050_GetGyroXRegister(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr, MPU6050_StatusTypeDef* hStatus){
	HAL_StatusTypeDef i2cStatus;

	uint8_t registersGyroX[] = {68, 67};
	int16_t gyroXResult = 0;

	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, registersGyroX, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Receive(hi2c, targetAddr, (uint8_t*)&gyroXResult, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, registersGyroX + 1, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Receive(hi2c, targetAddr, ((uint8_t*)&gyroXResult) + 1, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	if(hStatus != NULL){
		*hStatus = MPU6050_STATUS_OK;
	}
	return gyroXResult;

}

int16_t MPU6050_GetGyroYRegister(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr, MPU6050_StatusTypeDef* hStatus){
	HAL_StatusTypeDef i2cStatus;

	uint8_t registersGyroY[] = {70, 69};
	int16_t gyroYResult = 0;

	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, registersGyroY, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Receive(hi2c, targetAddr, (uint8_t*)&gyroYResult, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, registersGyroY + 1, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Receive(hi2c, targetAddr, ((uint8_t*)&gyroYResult) + 1, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	if(hStatus != NULL){
		*hStatus = MPU6050_STATUS_OK;
	}
	return gyroYResult;

}

int16_t MPU6050_GetGyroZRegister(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr, MPU6050_StatusTypeDef* hStatus){
	HAL_StatusTypeDef i2cStatus;

	uint8_t registersGyroZ[] = {72, 71};
	int16_t gyroZResult = 0;

	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, registersGyroZ, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Receive(hi2c, targetAddr, (uint8_t*)&gyroZResult, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, registersGyroZ + 1, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Receive(hi2c, targetAddr, ((uint8_t*)&gyroZResult) + 1, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	if(hStatus != NULL){
		*hStatus = MPU6050_STATUS_OK;
	}
	return gyroZResult;
}



uint16_t MPU6050_GetFIFOCountRegister(I2C_HandleTypeDef* hi2c, MPU6050_AddrTypeDef targetAddr,
		MPU6050_StatusTypeDef* hStatus){

	HAL_StatusTypeDef i2cStatus;

	uint8_t fifoCountRegisters[] = {114, 115};
	uint16_t fifoCountResult = 0;

	//Most significant byte requested from register (lower address in MPU6050)
	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, fifoCountRegisters, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	//Most significant byte read into higher address of little-endian STM32 memory.
	i2cStatus = HAL_I2C_Master_Receive(hi2c, targetAddr, (uint8_t*)&fifoCountResult + 1, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	i2cStatus = HAL_I2C_Master_Transmit(hi2c, targetAddr, fifoCountRegisters + 1, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	//Less significant byte goes into lower address
	i2cStatus = HAL_I2C_Master_Receive(hi2c, targetAddr, (uint8_t*)&fifoCountResult, 1, 150);
	if(i2cStatus != HAL_OK){
		if(hStatus != NULL){
			*hStatus = MPU6050_STATUS_I2C_FAIL;
		}
		return 0;
	}

	if(hStatus != NULL){
		*hStatus = MPU6050_STATUS_OK;
	}
	return fifoCountResult;

}
