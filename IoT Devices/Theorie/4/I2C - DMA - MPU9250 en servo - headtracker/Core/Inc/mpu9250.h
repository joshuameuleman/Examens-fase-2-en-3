#include "stm32l4xx_hal.h"

#ifndef MPU9250_DEFINED
	#define MPU9250_DEFINED
	
	#define SLAVE_ADDRESS_GYRO_ACC 			0x68			// Slave address van de MPU9250 (7-bit gedeelte).
	#define	SLAVE_ADDRESS_MAGNETOMETER 	0x0C			// Slave address van de magnetometer.
	
	typedef struct{
		int16_t gyroX;
		int16_t gyroY;
		int16_t gyroZ;
		int16_t accX;
		int16_t accY;
		int16_t accZ;
		int16_t temp;
	} Mpu9250;
	
	void InitMpu9250(I2C_HandleTypeDef* hi2c);							// Clock selecteren, scale kiezen voor gyroscoop en accelerometer.
	void WhoAmIMpu9250(I2C_HandleTypeDef* hi2c);						// Adres opvragen.
	void ReadMpu9250(I2C_HandleTypeDef* hi2c);						// Gyroscope en accelerometer uitlezen.
#endif
