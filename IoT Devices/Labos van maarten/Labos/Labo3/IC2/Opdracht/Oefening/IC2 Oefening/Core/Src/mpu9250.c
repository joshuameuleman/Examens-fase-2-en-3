// Uitlezen van een MPU9250 via I�C (Sparkfun breakout board) (7-bit adres = 0x68).
//
// Dit breakout board bevat reeds 10kOhm pull-up weerstanden naar de 3V3.
//
// OPM: Alle registers van de MPU9250 staan na reset op 0x00, behalve Who Am I en het Power management register 
// (adres 0x6B = 107 staat op 0x01 = Auto selects the best available clock source � PLL if ready, else use the Internal oscillator).

#include "mpu9250.h"
#include "main.h"

void InitMpu9250(I2C_HandleTypeDef* hi2c)
{
	uint32_t waitSteps = 0;
	uint8_t data[2];
	
	// MPU Resetten.
	data[0] = 0x6B;
	data[1] = 0x80;
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), data, 2, 100);	
	
	// Wachten tot heropstart...
	for(waitSteps = 0; waitSteps < 500000 ; waitSteps++)
		__NOP();	
	
	// Range Gyro instellen.
	data[0] = 0x1B;
	data[1] = 0x18;
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), data, 2, 100);	
	
	// Magnetometer instellen.
	data[0] = 0x6A;
	data[1] = 0x00;
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), data, 2, 100);

	// I�C Bypass enable modus.
	data[0] = 0x37;
	data[1] = 0x02;
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), data, 2, 100);	
	
	// Continuous measurement mode 2 (dat is meten op 100Hz), in 16-bit mode (magnetometer).
	data[0] = 0x0A;
	data[1] = 0x16;
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_MAGNETOMETER << 1), data, 2, 100);
}

uint8_t WhoAmIMpu9250(I2C_HandleTypeDef* hi2c)
{	
	// TODO: code aanvullen.
	uint8_t dt[1]; // data tijdelijk opslaan
	
	// Register 0x75: Who Am I register.
	dt[0] = 0x75;
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), dt, 1, 100);
	
	// 1 byte uitlezen 
	HAL_I2C_Master_Receive(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), dt, 1, 100);
	
	return dt[0];
}

uint8_t ReadIdAK8963(I2C_HandleTypeDef* hi2c)
{
	// TODO: code aanvullen.
	uint8_t dt[1];
	
	// Register 0x00: Device ID register (WIA - Who I Am).
	dt[0] = 0x00;
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_MAGNETOMETER << 1), dt, 1, 100);
	
	// 1 byte uitlezen .
	HAL_I2C_Master_Receive(hi2c, (SLAVE_ADDRESS_MAGNETOMETER << 1), dt, 1, 100);
	
	return dt[0];
}

// TODO: ReadMpu9250() functie maken (via polling functies).
Mpu9250 ReadMpu9250(I2C_HandleTypeDef* hi2c)
{
	Mpu9250 snrdata;
	uint8_t data[14];
	uint8_t magData[7];
	
	// Register 0x3B: Acc X High byte.
	data[0] = 0x3B;
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), data, 1, 100);
	
	// 14 bytes aan IMU-data lezen.
	HAL_I2C_Master_Receive(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), data, 14, 100);
	
	// Waardes uitrekenen.
	snrdata.accX = (int16_t)(data[0] * 256 + data[1]);
	snrdata.accY = (int16_t)(data[2] * 256 + data[3]);
	snrdata.accZ = (int16_t)(data[4] * 256 + data[5]);
	snrdata.temp = (int16_t)(data[6] * 256 + data[7]);
	snrdata.gyroX = (int16_t)(data[8] * 256 + data[9]);
	snrdata.gyroY = (int16_t)(data[10] * 256 + data[11]);
	snrdata.gyroZ = (int16_t)(data[12] * 256 + data[13]);
	
	// Magnetometer uitlezen (AK8963).
	// Register 0x03: HXL (Measurement data X Low byte).
	magData[0] = 0x03; // startadres voor uitlezen
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_MAGNETOMETER << 1), magData, 1, 100); 
	
	// 7 bytes lezen: HXL, HXH, HYL, HYH, HZL, HZH, ST2.
	// ST2 moet gelezen worden om aan te geven dat measurement data is uitgelezen.
	HAL_I2C_Master_Receive(hi2c, (SLAVE_ADDRESS_MAGNETOMETER << 1), magData, 7, 100);
	
	// Magnetometer waardes uitrekenen.
	snrdata.magnX = (int16_t)(magData[1] * 256 + magData[0]);
	snrdata.magnY = (int16_t)(magData[3] * 256 + magData[2]);
	snrdata.magnZ = (int16_t)(magData[5] * 256 + magData[4]);
	
	return snrdata;
}
