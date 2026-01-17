#include "stm32l4xx_hal.h"

#ifndef MPU9250_DEFINED
	#define MPU9250_DEFINED
	
	#define SLAVE_ADDRESS_GYRO_ACC 			0x68			// Slave address van de MPU9250 (7-bit gedeelte).
	
	// TODO: slave address van de magnetometer invullen.
	#define	SLAVE_ADDRESS_MAGNETOMETER 	0X0C			// Slave address van de magnetometer.
	
	typedef struct{
		int16_t gyroX;
		int16_t gyroY;
		int16_t gyroZ;
		int16_t accX;
		int16_t accY;
		int16_t accZ;
		int16_t temp;
		// TODO: extra velden voorzien voor de data van de magnetometer.
		int16_t magnX;
		int16_t magnY;
		int16_t magnZ;
	} Mpu9250;
	
	void InitMpu9250(I2C_HandleTypeDef* hi2c);							// Clock selecteren, scale kiezen voor gyroscoop en accelerometer.
	uint8_t WhoAmIMpu9250(I2C_HandleTypeDef* hi2c);					// Adres opvragen.
	// TODO: functieprototypes toevoegen/aanpassen.
	uint8_t ReadIdAK8963(I2C_HandleTypeDef* hi2c);					// Device ID van de magnetometer opvragen.
	Mpu9250 ReadMpu9250(I2C_HandleTypeDef* hi2c);						// Sensordata uitlezen.


#endif
