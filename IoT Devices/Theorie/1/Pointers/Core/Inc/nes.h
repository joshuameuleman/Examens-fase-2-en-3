#include "stm32l4xx_hal.h"

#if !defined(NES_DEFINED)
	#define NES_DEFINED
	
	// Struct die de toestand van het Nucleo Extension Shield bijhoudt.
	typedef struct{
		uint8_t Leds;
		uint8_t Buttons;
		uint16_t AdValue;
	}NES;
#endif