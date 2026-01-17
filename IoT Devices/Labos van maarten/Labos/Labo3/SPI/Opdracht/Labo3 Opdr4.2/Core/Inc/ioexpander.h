#include "stm32l4xx_hal.h"

#if !defined(IOEXPANDER_DEFINED)
	#define IOEXPANDER_DEFINED

void InitIOExpander(SPI_HandleTypeDef* hspi);
	void SetIOExpanderLeds(SPI_HandleTypeDef* hspi, uint8_t data);
	uint8_t GetIOExpanderButtons(SPI_HandleTypeDef* hspi);
#endif
