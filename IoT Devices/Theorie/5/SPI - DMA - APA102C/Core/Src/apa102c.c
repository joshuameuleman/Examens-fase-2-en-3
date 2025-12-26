#include "stm32l4xx_hal.h"
#include "apa102c.h"

// Verstuur de data over SPI1. Let op: zorg dat SPI1 reeds geïnitialiseerd is.
void UpdateAPA102CLeds(SPI_HandleTypeDef* hspi, APA102C led[])
{
	uint8_t index = 0;
	extern uint8_t source[4 + NUMBER_OF_APA102C_LEDS * 4 + 4];
	
	source[0] = 0;		// Start frame.
	source[1] = 0;
	source[2] = 0;
	source[3] = 0;	

	for(index = 0; index < NUMBER_OF_APA102C_LEDS; index++)
	{	
		source[4 + index * 4] = led[index].brightness | 0xE0;					// 5-bit intensiteit.
		source[5 + index * 4] = led[index].blue;											// Blauw.
		source[6 + index * 4] = led[index].green;											// Groen.
		source[7 + index * 4] = led[index].red;												// Rood.
	}
	
	source[4 + NUMBER_OF_APA102C_LEDS * 4] = 255;										// End frame.
	source[5 + NUMBER_OF_APA102C_LEDS * 4] = 255;
	source[6 + NUMBER_OF_APA102C_LEDS * 4] = 255;
	source[7 + NUMBER_OF_APA102C_LEDS * 4] = 255;
	
	// Alle data verzenden via DMA.
	HAL_SPI_Transmit_DMA(hspi, source, (4 + NUMBER_OF_APA102C_LEDS * 4 + 4));
}
