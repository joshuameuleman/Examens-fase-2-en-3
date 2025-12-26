#include "usart2.h"
#include "stdio.h"

//struct __FILE
//{
//  int handle;
//	// Whatever you require here. If the only file you are using is
//	// standard output using printf() for debugging, no file handling
//	// is required.
//	//
//	// https://community.arm.com/developer/tools-software/tools/f/keil-forum/34791/how-printf-to-specific-usart
//};
// FILE is typedef’d in stdio.h.
FILE __stdout;
FILE __stdin;

// Redirect printf() to USART2.
int fputc(int ch, FILE *f)
{
	extern UART_HandleTypeDef huart2;
	
	HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
	return ch;
}

// Redirect scanf() to USART2.
int fgetc(FILE *f)
{
	extern UART_HandleTypeDef huart2;
	int ch = 0;
	
	HAL_UART_Receive(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
	return ch;
}
