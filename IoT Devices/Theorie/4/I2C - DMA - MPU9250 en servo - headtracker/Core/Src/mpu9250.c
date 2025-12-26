// Uitlezen van een MPU9250 via I²C (Sparkfun breakout board) (7-bit adres = 0x68).
//
// Dit breakout board bevat reeds 10kOhm pull-up weerstanden naar de 3V3.
//
// OPM: Alle registers van de MPU9250 staan na reset op 0x00, behalve Who Am I en het Power management register 
// (adres 0x6B = 107 staat op 0x01 = Auto selects the best available clock source – PLL if ready, else use the Internal oscillator).

#include "mpu9250.h"
#include "main.h"

void InitMpu9250(I2C_HandleTypeDef* hi2c)
{
	uint32_t waitSteps = 0;
	uint8_t data[2];
	
	// MPU Resetten.
	data[0] = 0x6B; // MPU register
	data[1] = 0x80; // bit 7 (H_RESET)
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), data, 2, 100);	
	
	// Wachten tot heropstart...
	for(waitSteps = 0; waitSteps < 500000 ; waitSteps++)
		__NOP();	
	
	// Range Gyro instellen. 2000°/sec (= 2000dps) = 16.4 LSB/°/s ...
	// = laagste bit van de digitale representatie van de hoeksnelheid 1/16.4 van een graad per seconde
	data[0] = 0x1B;
	data[1] = 0x18;
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), data, 2, 100);	
	
	// Magnetometer instellen.
	data[0] = 0x6A;
	data[1] = 0x00;
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), data, 2, 100);

	// I²C Bypass enable modus (p. 29 MPU registers).
	data[0] = 0x37;
	data[1] = 0x02;
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), data, 2, 100);	
	
	// Continuous measurement mode 2 (dat is meten op 100Hz), in 16-bit mode (magnetometer). 
	// (p. 48 & 51 MPU registers. De magnetometer zit in een apart hoofdstuk!)
	data[0] = 0x0A;
	data[1] = 0x16;
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_MAGNETOMETER << 1), data, 2, 100);
}

void WhoAmIMpu9250(I2C_HandleTypeDef* hi2c)
{
	extern uint8_t i2cData[NUMBER_OF_BYTES_TO_RECEIVE];
	
	// Who am I register.
	i2cData[0] = 0x75;
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), i2cData, 1, 100);
	
	// Who am I lezen.
	HAL_I2C_Master_Receive_DMA(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), i2cData, 1);
}

void ReadMpu9250(I2C_HandleTypeDef* hi2c)
{
	extern uint8_t i2cData[NUMBER_OF_BYTES_TO_RECEIVE];
	
	// Register 0x3B: Acc X High byte.
	i2cData[0] = 0x3B;
	HAL_I2C_Master_Transmit(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), i2cData, 1, 100);
	
	// 14 bytes aan IMU-data lezen.
	HAL_I2C_Master_Receive_DMA(hi2c, (SLAVE_ADDRESS_GYRO_ACC << 1), i2cData, 14);
}
