/*
 * mpu6050.h
 * Author: OrbitalMechanist
 *
 * This library provides partial support for the MPU6050 Inertial Measurement
 * Unit (IMU) popular among hobbyists, often used via a GY-521 breakout board.
 *
 * Only the basic measurement functionality is implemented.
 * Burst reads, I2C slaving, and interrupts are not supported at this time.
 *
 * The IMU's own documentation can be found here:
 * https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf
 * https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
 */

#ifndef MPU6050_H
#define MPU6050_H

#include "stm32f1xx_hal.h"

//Error Codes
typedef enum {
	MPU6050_STATUS_OK = 0U,
	MPU6050_STATUS_ERROR = 1U,
	MPU6050_STATUS_I2C_FAIL = 2U,
} MPU6050_StatusTypeDef;

//An MPU6050 may have either 0x68 or 0x69 as its I2C slave address,
//controlled by the AD0 pin. This allows up to two to be used on the same bus.
//If both are used, each must be initialized, commanded and queried separately.
//Due to the way STM32 HAL I2C implementation works, all addresses must be
//shifted left by 1 (0x68 << 1), which is hardcoded here.
typedef enum {
	MPU6050_ADDR_0 = 0xD0U,
	MPU6050_ADDR_1 = 0xD2U
}MPU6050_AddrTypeDef;

/* The MPU6050 accelerometer return values may be converted to
 * g (approximately 9.81 m/s/s) using the following table:
Selection	Range	Conversion
0 			±2g 	16384 LSB/g
1 			±4g 	8192 LSB/g
2 			±8g 	4096 LSB/g
3 			±16g 	2048 LSB/g
*/
typedef enum {
	MPU6050_ACCELRANGE_2G = 0, //16384 units/1g (9.8 m/s/s)
	MPU6050_ACCELRANGE_4G = 1, //8192
	MPU6050_ACCELRANGE_8G = 2, //4096
	MPU6050_ACCELRANGE_16G = 3 //2048
}MPU6050_AccelRangeTypeDef;

/* The MPU6050 gyroscope return values may be converted to deg/s
 * using the following table (based the gyro range that was set):
Selection	Range		Conversion
0			±250°/s 	131 LSB/°/s
1 			±500°/s 	65.5 LSB/°/s
2 			±1000°/s 	32.8 LSB/°/s
3 			±2000°/s 	16.4 LSB/°/s
 */
typedef enum {
	MPU6050_GYRORANGE_250 = 0,
	MPU6050_GYRORANGE_500 = 1,
	MPU6050_GYRORANGE_1000 = 2,
	MPU6050_GYRORANGE_2000 = 3
}MPU6050_GyroRangeTypeDef;

/* The MPU6050 has an integrated Digital Low Pass Filter.
 * The numbers here are very approximate filter frequencies because
 * they differ slightly between the accelerometer and gyro components.
 * Additionally, different filters involve different delays (up to 20ms
 * for very low frequencies). The exact values can be found in the register
 * map.
 */
typedef enum {
	MPU6050_FILTER_260 = 0,
	MPU6050_FILTER_180 = 1,
	MPU6050_FILTER_90 = 2,
	MPU6050_FILTER_40 = 3,
	MPU6050_FILTER_20 = 4,
	MPU6050_FILTER_10 = 5,
	MPU6050_FILTER_5 = 6
}MPU6050_FilterCutoffTypeDef;

extern MPU6050_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr);
extern MPU6050_StatusTypeDef MPU6050_SetAccelRange(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr, MPU6050_AccelRangeTypeDef range);
extern MPU6050_StatusTypeDef MPU6050_SetGyroRange(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr, MPU6050_GyroRangeTypeDef range);
// WARNING: This function fully overwrites register 25 and sets EXT_SYNC_SET to 0.
extern MPU6050_StatusTypeDef MPU6050_SetFilter(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr, MPU6050_FilterCutoffTypeDef filter);

extern int16_t MPU6050_GetAccelXRegister(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr, MPU6050_StatusTypeDef* hStatus);
extern int16_t MPU6050_GetAccelYRegister(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr, MPU6050_StatusTypeDef* hStatus);
extern int16_t MPU6050_GetAccelZRegister(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr, MPU6050_StatusTypeDef* hStatus);

extern int16_t MPU6050_GetGyroXRegister(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr, MPU6050_StatusTypeDef* hStatus);
extern int16_t MPU6050_GetGyroYRegister(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr, MPU6050_StatusTypeDef* hStatus);
extern int16_t MPU6050_GetGyroZRegister(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr, MPU6050_StatusTypeDef* hStatus);

/* NOTE: this function returns the 2-byte signed integer stored
 * by MPU6050. It may be converted to degrees Celsius by the formula:
 *
 * TdegC = MPU6050_GetTemperatureRegister/340 + 36.53
 *
 * as per the Register Map document.
 */
extern int16_t MPU6050_GetTemperatureRegister(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr, MPU6050_StatusTypeDef* hStatus);

extern uint16_t MPU6050_GetFIFOCountRegister(I2C_HandleTypeDef* hi2c,
		MPU6050_AddrTypeDef targetAddr, MPU6050_StatusTypeDef* hStatus);

#endif /* MPU6050_H */
