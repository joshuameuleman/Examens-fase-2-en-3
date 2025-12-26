/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
	// Versie: 20252026
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdlib.h"
#include "string.h"
#include "leds.h"
#include "buttons.h"
#include "usart1.h"
#include "usart2.h"
#include "ad.h"
#include "stdio.h"
#include "circularBuffer.h"
#include "esp32c3.h"
#include "wifi.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

IWDG_HandleTypeDef hiwdg;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
static uint8_t buttonsValue = 0, index = 0;
static uint16_t adValue = 0;
static volatile uint32_t ticks = 0;

static bool userButtonHelp = false, sw1Help = false, sw2Help = false, sw3Help = false, sw4Help = false;	
volatile bool timerTicked = false;
static bool timeBasedPublishing = false;
static char text[CHAR_ARRAY_BUFFER_LENGTH];
static char receivedText[CHAR_ARRAY_BUFFER_LENGTH];
static char httpParameters[CHAR_ARRAY_BUFFER_LENGTH];					// Steeds in de vorm:  "key1=value1&key2=value2&...".
static volatile enum UsartState usart1State =	idle;

// Verwijzing maken naar een circulair buffer dat alle binnenkomende data van de ESP-module opslaat.
extern volatile CircularBuffer circularBuffer;
extern enum CircularBufferActionResult circularBufferActionResult;
static uint8_t leds = 0, numberOfReceivedBytes = 0;

static volatile uint8_t receivedUsart1Data = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_IWDG_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_IWDG_Init();
  /* USER CODE BEGIN 2 */
	// OPM: gebruikte WiFi-module = ESP01-C3 (https://www.lilygo.cc/products/t-01c3 
	// of https://www.tinytronics.nl/shop/nl/communicatie-en-signalen/draadloos/wi-fi/modules/lilygo-t-01c3-esp32-wi-fi-en-bluetooth-le-module).
	
	// Laten weten dat we opgestart zijn, via de USART2 (USB).
	printf("Reboot\r\n");	
	printf("User button = start/stop pushing to Firebase.\r\n");
	
	// Circulaire buffer initialiseren.
	if(InitCircularBuffer(&circularBuffer) != INIT_SUCCEEDED)
		printf("Initialization of CircularBuffer failed!\r\n");
	
	// WiFi-module tijd geven om op te starten.
	HAL_Delay(1000);
	
	// Ontvangst van ��n byte via interrupts starten (voor de ESP32-module).
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&receivedUsart1Data, 1);
	
	// WiFi-module in AT-mode zetten.
	StringToUsart1("AT\r\n");
	while(!LookForString1(&circularBuffer, "OK\r\n"));
	
	// WiFi-module resetten.
	StringToUsart1("AT+RST\r\n");
	while(!LookForString1(&circularBuffer, "ready\r\n"));
	
	// Huidige AT-firmware versie opvragen (optioneel).
	StringToUsart1("AT+GMR\r\n");
	while(!LookForString1(&circularBuffer, "OK\r\n"));
	
	// MAC-adres opvragen (optioneel).
	StringToUsart1("AT+CIPSTAMAC?\r\n");
	while(!LookForString1(&circularBuffer, "OK\r\n"));
	
	// Verbinding maken met het WiFi-netwerk (zie wifi.h).
	ConnectToWiFiNetwork(WIFI_SSID, WIFI_PWD);
	
	// Verbinding maken met de MQTT-broker (enkel indien MQTT van toepassing is).
	ConnectToMqttBroker(MQTT_BROKER_ADDRESS, MQTT_PORT, MQTT_USER, MQTT_PWD, MQTT_CLIENT_ID);
	
	// Abonneren op een MQTT-topic.
	SubscribeToMqttTopic(MQTT_SUB_TOPIC);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		// Watchdog timer resetten. Dit zorgt voor een herstart als de hoofdlus iets 
		// meer dan x-seconden (zie instellingen in Cube) geblokkeerd is.
		HAL_IWDG_Refresh(&hiwdg);
		
		// AD-waarde inlezen.
		adValue = (uint8_t)(GetAdValue(&hadc1) >> 4);
			
		// Alle knoppen inlezen.
		buttonsValue = 0;
		if(SW1Active())
			buttonsValue |= 0x01;
		if(SW2Active())
			buttonsValue |= 0x02;
		if(SW3Active())
			buttonsValue |= 0x04;
		if(SW4Active())
			buttonsValue |= 0x08;
		if(UserButtonActive())
			buttonsValue |= 0x10;
		
		// LED's updaten.
		ByteToLeds(leds);

		
		
		// HTTP GET voorbeeld (via rubu.be).
		// Flankdetectie SW1.
		if(SW1Active() && sw1Help == false)
		{
			sw1Help = true;
			
			// GET parameters voorbereiden.
			sprintf(httpParameters, "apikey=%s", HTTP_APIKEY);
			
			// GET request versturen
			HttpRequest(HTTP_HOST, HTTP_URL_GET, 80, GET, httpParameters);
		}		
		if(!SW1Active())
			sw1Help = false;
		
		// HTTP POST voorbeeld (via rubu.be).
		// Flankdetectie SW2.
		if(SW2Active() && sw2Help == false)
		{
			sw2Help = true;
			
			// POST body voorbereiden.
			sprintf(httpParameters, "apikey=%s&ad=%d", HTTP_APIKEY, adValue);
			
			// POST request versturen.
			HttpRequest(HTTP_HOST, HTTP_URL_POST, 80, POST, httpParameters);
		}		
		if(!SW2Active())
			sw2Help = false;
		
		
		
		// HTTPS GET voorbeeld (via Firebase).
		// Flankdetectie SW3.
		if(SW3Active() && sw3Help == false)
		{
			sw3Help = true;
			
			// GET parameters voorbereiden.
			sprintf(httpParameters, "auth=%s", HTTPS_DATABASE_SECRET);
			
			// GET request versturen
			HttpsRequest(HTTPS_HOST, HTTPS_URL_GET, 443, GET, httpParameters);
		}		
		if(!SW3Active())
			sw3Help = false;
		
		// HTTPS PATCH voorbeeld (via Firebase).
		// Flankdetectie SW4.
		if(SW4Active() && sw4Help == false)
		{
			sw4Help = true;
			
			// Eerst PATCH data voorbereiden.	
			sprintf(httpParameters, "{\"advalue\":%d}", adValue);
			
			// PATCH request versturen
			sprintf(text, "%s?auth=%s", HTTPS_URL_PATCH, HTTPS_DATABASE_SECRET);
			HttpsRequest(HTTPS_HOST, text, 443, PATCH, httpParameters);
		}		
		if(!SW4Active())
			sw4Help = false;
		
		
		
		// MQTT voorbeeld (via test.mosquitto.org).
		// Flankdetectie User Button.
		if(UserButtonActive() && userButtonHelp == false)
		{
			userButtonHelp = true;
			
			// Automatisch publish'n of niet?
			timeBasedPublishing = !timeBasedPublishing;
		}		
		if(!UserButtonActive())
			userButtonHelp = false;		
		
		// Met behulp van de User Button het automatisch publish'n in- of uitschakelen.
		// timerTicked wordt ingesteld in de stm32l4xx_it.c.
		if(timeBasedPublishing && timerTicked)
		{
			// Timer verwerken.
			timerTicked = false;
			
			// MQTT-bericht publish'n.
			sprintf(text, "%d", adValue); 
			MqttPublish(MQTT_PUB_TOPIC, text);	
		}

		
		
		// Mogelijks ontvangen TCP-, HTTP-, HTTPS-, of MQTT-berichten zoeken in het circulair buffer.
		// De berichten zijn van de vorm: +IPD, of +MQTTSUBRECV:0,"rubu/esp8266",3,254.
		while(circularBuffer.numberOfStringsInBuffer > 0)
		{		
			// E�n string ophalen.
			circularBufferActionResult = PopStringFromCircularBuffer(&circularBuffer, receivedText);
			if(circularBufferActionResult == READ_STRING_SUCCEEDED)
			{				
				// HTTP(S)-ontvangst onderzoeken. Zoek achter "+IPD,". Dat geeft het begin aan van de ontvangen TCP-data.
				if(strncmp("+IPD,", receivedText, 5) == 0)
				{				
					// Zoek uit hoeveel bytes er ontvangen werden (optioneel).
					numberOfReceivedBytes = (uint16_t)atoi(&receivedText[5]);					
					//sprintf(text, "Number of received bytes: %d.\r\n", numberOfReceivedBytes);
					//StringToUsart2(text);
					
					// Op het einde van de HTTP-headers is een lege lijn. Zoek ze. Sla dus alle HTTP-headers over. 
					// Daarna staat de gevraagde info, afkomstig van de server.
					while(!LookForString1(&circularBuffer, "\r\n"));
					
					// Even wachten, zodat de volgende lijn data kan binnenkomen.
					while(circularBuffer.numberOfStringsInBuffer == 0);
					
					// Lees die volgende lijn uit. Dat is de lijn met de ontvangen data vanop het netwerk.
					circularBufferActionResult = PopStringFromCircularBuffer(&circularBuffer, receivedText);
					
//					// Melden aan de gebruiker (optioneel).
//					printf("New TCP- or HTTP(S)-data received: ");
//					printf("%s\r\n\r\n", receivedText);

					// De ontvangen tekst omzetten naar een getal en dat op de LED's zetten (optioneel).
					leds = (uint8_t)atoi(receivedText);
					printf("leds: %d.\r\n\r\n", leds);
					ByteToLeds(leds);
				}
				
				// MQTT-ontvangst onderzoeken. Zoek achter "+MQTTSUBRECV:0,"het huidige topic",". Dat geeft het begin aan van de ontvangen MQTT-data.
				sprintf(text, "+MQTTSUBRECV:0,\"%s\",", MQTT_SUB_TOPIC);
				index = strlen(text);																	// Opzoeken hoe lang dat gedeelte van de string is.
				
				// Begin van de lijn vergelijken met de verwachte tekst en topic.
				if(strncmp(text, receivedText, index) == 0)
				{
//					// Melden aan de gebruiker (optioneel).
//					printf("New MQTT-data received: ");
//					printf("%s\r\n\r\n", receivedText);
					
					// Het aantal ontvangen bytes opzoeken.
					numberOfReceivedBytes = (uint8_t)atoi(&receivedText[index]);
					printf("numberOfReceivedBytes: %d.\r\n", numberOfReceivedBytes);
					
					// TODO: actief op zoek gaan naar de laatste komma. Daarna de omzetting naar integer starten.
					// De ontvangen tekst omzetten naar een getal en dat op de LED's zetten (optioneel).
					leds = (uint8_t)atoi(&receivedText[index + 2]);
					printf("leds: %d.\r\n\r\n", leds);
					ByteToLeds(leds);
				}
			}
		}
		
		// Even wachten (voor onder andere anti dender).
		HAL_Delay(10);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_256;
  hiwdg.Init.Window = 4095;
  hiwdg.Init.Reload = 1249;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT;
  huart1.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT;
  huart2.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED1_Pin|LED7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, UserLED_Pin|LED6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED5_Pin|LED2_Pin|LED4_Pin|LED3_Pin
                          |LED8_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : UserButton_Pin SW4_Pin */
  GPIO_InitStruct.Pin = UserButton_Pin|SW4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_Pin LED7_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : SW1_Pin SW2_Pin */
  GPIO_InitStruct.Pin = SW1_Pin|SW2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : UserLED_Pin LED6_Pin */
  GPIO_InitStruct.Pin = UserLED_Pin|LED6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : SW3_Pin */
  GPIO_InitStruct.Pin = SW3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SW3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED5_Pin LED2_Pin LED4_Pin LED3_Pin
                           LED8_Pin */
  GPIO_InitStruct.Pin = LED5_Pin|LED2_Pin|LED4_Pin|LED3_Pin
                          |LED8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
// Code hieronder wordt opgeroepen als alle data van HAL_UART_Receive_IT(() ontvangen is...
// Deze functie wordt opgeroepen vanuit HAL_UART_IRQHandler().
// De data is afkomstig van de ESP01-C3-module.
// Alle data wordt opgeslaan in de globale variabele 'circularBuffer', die gedefinieerd is in circularBuffer.c.
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	// Is het data van UART1?
	if(UartHandle->Instance == USART1)
	{		
		// Byte versturen op USART2 (USB) zodat je ook op de computer kan meevolgen. Dit is niet verplicht, maar vergemakkelijkt het debuggen.
		// Let op: zorg voor een timeout van 0, anders kan de code hier te traag verlopen en problemen bezorgen op UART1.
		HAL_UART_Transmit(&huart2, (uint8_t *)&receivedUsart1Data, 1, 0);
//		// Indien timing problemen, zou onderstaande kunnen helpen...
//		huart2.Instance->TDR = (uint8_t)receivedUsart1Data;
		
		// Ontvangen data opslaan in een circulair buffer. 
		// Het circulair buffer zorgt ervoor dat er geen bytes misgelopen raken. Je kan daarna in de hoofdlus 'rustig aan' alle
		// ontvangen data gaan verwerken...
		if(usart1State == busyReceiving)
		{
			// Is er nog plaats in het buffer?
			if(!IsCircularBufferFull(&circularBuffer))
			{
				// Karakter opslaan.
				PushCharToCircularBuffer(&circularBuffer, receivedUsart1Data);

				// Nieuwe lijn ontvangen. Geef aan dat je klaar bent voor een volgende lijn...
				if(receivedUsart1Data == '\n')
						usart1State = idle;
			}
		}
		else
		{
			// Start van de ontvangst/lijn.
			if(usart1State == idle)
			{
				// Is er nog plaats in het buffer?
				if(!IsCircularBufferFull(&circularBuffer))
				{
					// Buffer nog niet vol. Begin met opslaan in de circulaire buffer.
					usart1State = busyReceiving;
 
					// Karakter opslaan.
					PushCharToCircularBuffer(&circularBuffer, receivedUsart1Data);
					
					// Nieuwe lijn ontvangen. Geef aan dat je klaar bent voor een volgende lijn...
					if(receivedUsart1Data == '\n')
						usart1State = idle;
					else
					{					
						// Na het versturen van het 'AT+CIPSEND'- of een 'MQTTPUBRAW'-command, moet er gewacht worden op het '>'-karakter. Detecteer
						// de ontvangst van dat karakter hier. Voeg automatisch een "\r\n" toe om zo geforceerd een nieuwe lijn in het circulair buffer
						// aan te maken. Hierdoor kan de data uit dat buffer, gemakkelijker verwerkt worden.
						if(receivedUsart1Data == '>')
						{							
							// Geforceerd extra lijn opslaan met ">\r\n".
							PushCharToCircularBuffer(&circularBuffer, '\r');
							PushCharToCircularBuffer(&circularBuffer, '\n');
							
							usart1State = idle;
						}
					}
				}
			}				
		}		
		
		// Ontvangst via interrupts opnieuw starten. Want RXNEIE wordt automatisch uitgeschakeld.
		HAL_UART_Receive_IT(&huart1, (uint8_t*)&receivedUsart1Data, 1);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
// Versie: 20252026
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
