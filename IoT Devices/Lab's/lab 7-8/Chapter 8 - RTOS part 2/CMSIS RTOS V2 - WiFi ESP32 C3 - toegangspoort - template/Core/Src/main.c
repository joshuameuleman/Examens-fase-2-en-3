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
#include "cmsis_os.h"

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
#define PWM_OFFSET 1000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

IWDG_HandleTypeDef hiwdg;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* Definitions for watchdogTask */
osThreadId_t watchdogTaskHandle;
const osThreadAttr_t watchdogTask_attributes = {
  .name = "watchdogTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for esp32Task */
osThreadId_t esp32TaskHandle;
const osThreadAttr_t esp32Task_attributes = {
  .name = "esp32Task",
  .stack_size = 1280 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for adConvTask */
osThreadId_t adConvTaskHandle;
const osThreadAttr_t adConvTask_attributes = {
  .name = "adConvTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for stateMachineTas */
osThreadId_t stateMachineTasHandle;
const osThreadAttr_t stateMachineTas_attributes = {
  .name = "stateMachineTas",
  .stack_size = 1280 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for switchesTask */
osThreadId_t switchesTaskHandle;
const osThreadAttr_t switchesTask_attributes = {
  .name = "switchesTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for adQueue */
osMessageQueueId_t adQueueHandle;
const osMessageQueueAttr_t adQueue_attributes = {
  .name = "adQueue"
};
/* Definitions for switchQueue */
osMessageQueueId_t switchQueueHandle;
const osMessageQueueAttr_t switchQueue_attributes = {
  .name = "switchQueue"
};
/* Definitions for mqttQueue */
osMessageQueueId_t mqttQueueHandle;
const osMessageQueueAttr_t mqttQueue_attributes = {
  .name = "mqttQueue"
};
/* Definitions for ledTimer */
osTimerId_t ledTimerHandle;
const osTimerAttr_t ledTimer_attributes = {
  .name = "ledTimer"
};
/* Definitions for gateMovingTimer */
osTimerId_t gateMovingTimerHandle;
const osTimerAttr_t gateMovingTimer_attributes = {
  .name = "gateMovingTimer"
};
/* Definitions for usart2TxMutex */
osMutexId_t usart2TxMutexHandle;
const osMutexAttr_t usart2TxMutex_attributes = {
  .name = "usart2TxMutex"
};
/* Definitions for statemachineEvents */
osEventFlagsId_t statemachineEventsHandle;
const osEventFlagsAttr_t statemachineEvents_attributes = {
  .name = "statemachineEvents"
};
/* USER CODE BEGIN PV */
static uint8_t index = 0;
static volatile uint32_t ticks = 0;
volatile bool timerTicked = false;
static char text[CHAR_ARRAY_BUFFER_LENGTH];
static char receivedText[CHAR_ARRAY_BUFFER_LENGTH];
static volatile enum UsartState usart1State =	idle;

// Verwijzing maken naar een circulair buffer dat alle binnenkomende data van de ESP-module opslaat.
extern volatile CircularBuffer circularBuffer;
extern enum CircularBufferActionResult circularBufferActionResult;
static volatile uint8_t receivedUsart1Data = 0;
enum States {error, closed, firstOk, secondOk, thirdOk, openingLedOn, openingLedOff, 
								open, closingLedOn, closingLedOff};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_IWDG_Init(void);
static void MX_TIM2_Init(void);
void Watchdog(void *argument);
void Esp32(void *argument);
void AdConversion(void *argument);
void StateMachine(void *argument);
void Switches(void *argument);
void LedTimeOut(void *argument);
void GateMovingTimeOut(void *argument);

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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	// OPM: gebruikte WiFi-module = ESP01-C3 (https://www.lilygo.cc/products/t-01c3 
	// of https://www.tinytronics.nl/shop/nl/communicatie-en-signalen/draadloos/wi-fi/modules/lilygo-t-01c3-esp32-wi-fi-en-bluetooth-le-module).
	
	// Laten weten dat we opgestart zijn, via de USART2 (USB).
	printf("Reboot\r\n");	
	
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
  /* Create the mutex(es) */
  /* creation of usart2TxMutex */
  usart2TxMutexHandle = osMutexNew(&usart2TxMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of ledTimer */
  ledTimerHandle = osTimerNew(LedTimeOut, osTimerPeriodic, NULL, &ledTimer_attributes);

  /* creation of gateMovingTimer */
  gateMovingTimerHandle = osTimerNew(GateMovingTimeOut, osTimerOnce, NULL, &gateMovingTimer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of adQueue */
  adQueueHandle = osMessageQueueNew (1, sizeof(uint8_t), &adQueue_attributes);

  /* creation of switchQueue */
  switchQueueHandle = osMessageQueueNew (5, sizeof(int8_t), &switchQueue_attributes);

  /* creation of mqttQueue */
  mqttQueueHandle = osMessageQueueNew (3, sizeof(uint8_t), &mqttQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of watchdogTask */
  watchdogTaskHandle = osThreadNew(Watchdog, NULL, &watchdogTask_attributes);

  /* creation of esp32Task */
  esp32TaskHandle = osThreadNew(Esp32, NULL, &esp32Task_attributes);

  /* creation of adConvTask */
  adConvTaskHandle = osThreadNew(AdConversion, NULL, &adConvTask_attributes);

  /* creation of stateMachineTas */
  stateMachineTasHandle = osThreadNew(StateMachine, NULL, &stateMachineTas_attributes);

  /* creation of switchesTask */
  switchesTaskHandle = osThreadNew(Switches, NULL, &switchesTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* creation of statemachineEvents */
  statemachineEventsHandle = osEventFlagsNew(&statemachineEvents_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

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
  hiwdg.Init.Reload = 999;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 79;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 19999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

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
		osMutexAcquire(usart2TxMutexHandle, osWaitForever);
		HAL_UART_Transmit(&huart2, (uint8_t *)&receivedUsart1Data, 1, 0);
		osMutexRelease(usart2TxMutexHandle);
//		// Indien timing problemen, zou onderstaande kunnen helpen...
//		huart2.Instance->TDR = (uint8_t)receivedUsart1Data;
		
		// Ontvangen data opslaan in een circulair buffer. 
		// Het circulair buffer zorgt ervoor dat er geen bytes misgelopen raken. 
		// Je kan daarna in de hoofdlus 'rustig aan' alle ontvangen data gaan verwerken...
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

/* USER CODE BEGIN Header_Watchdog */
/**
  * @brief  Function implementing the watchdogTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Watchdog */
void Watchdog(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
		// Watchdog timer resetten. Dit zorgt voor een herstart als ��n van de threads met hogere 
		// prioriteit iets meer dan 8 seconden geblokkeerd is.
		HAL_IWDG_Refresh(&hiwdg);
		
		// LED laten knipperen als visueel teken van het doorlopen van deze thread.
		ToggleLed(1);
		
		// Even wachten.
    osDelay(1000);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_Esp32 */
/**
* @brief Function implementing the esp32Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Esp32 */
void Esp32(void *argument)
{
  /* USER CODE BEGIN Esp32 */
	
	osStatus_t osStatus;
	enum States state;
	
	// Let op: deze tread heeft een vrij grote 'Stack Size' nodig om correct te kunnen werken. Bijvoorbeeld 1280...
	//				 Stel dat in via STM32CubeMX.
	
	// Circulaire buffer initialiseren.
	if(InitCircularBuffer(&circularBuffer) != initSucceeded)
		printf("Initialization of CircularBuffer failed!\r\n");
	
	// WiFi-module tijd geven om op te starten.
	osDelay(1000);
	
	// Ontvangst van ��n byte via interrupts starten (voor de ESP32-module).
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&receivedUsart1Data, 1);
	
	// WiFi-module in AT-mode zetten.
	StringToUsart1("AT\r\n");
	while(!LookForString1(&circularBuffer, "OK\r\n"));
	
	// Tussendoor de Watchdog timer resetten.
	HAL_IWDG_Refresh(&hiwdg);
	
	// WiFi-module resetten.
	StringToUsart1("AT+RST\r\n");
	while(!LookForString1(&circularBuffer, "ready\r\n"));
	
	// Tussendoor de Watchdog timer resetten.
	HAL_IWDG_Refresh(&hiwdg);
	
	// Huidige AT-firmware versie opvragen (optioneel).
	StringToUsart1("AT+GMR\r\n");
	while(!LookForString1(&circularBuffer, "OK\r\n"));
	
	// Tussendoor de Watchdog timer resetten.
	HAL_IWDG_Refresh(&hiwdg);
	
	// MAC-adres opvragen (optioneel).
	StringToUsart1("AT+CIPSTAMAC?\r\n");
	while(!LookForString1(&circularBuffer, "OK\r\n"));
	
	// Tussendoor de Watchdog timer resetten.
	HAL_IWDG_Refresh(&hiwdg);
	
	// Verbinding maken met het WiFi-netwerk (zie wifi.h).
	ConnectToWiFiNetwork(WIFI_SSID, WIFI_PWD);
	
	// Tussendoor de Watchdog timer resetten.
	HAL_IWDG_Refresh(&hiwdg);
	
	// Verbinding maken met de MQTT-broker (enkel indien MQTT van toepassing is).
	ConnectToMqttBroker(MQTT_BROKER_ADDRESS, MQTT_PORT, MQTT_USER, MQTT_PWD, MQTT_CLIENT_ID);
	
	// Tussendoor de Watchdog timer resetten.
	HAL_IWDG_Refresh(&hiwdg);
	
	// Abonneren op een MQTT-topic.
	SubscribeToMqttTopic(MQTT_SUB_TOPIC);
	
	// Tussendoor de Watchdog timer resetten.
	HAL_IWDG_Refresh(&hiwdg);
	
  /* Infinite loop */
  for(;;)
  {    
		// Is er een nieuwe state opgehaald?
		osStatus = osMessageQueueGet(mqttQueueHandle, &state, NULL, 1);		
		if(osStatus == osOK)
		{
			if(state == open)
			{
				// MQTT-bericht publish'n.
				MqttPublish(MQTT_PUB_TOPIC, "{\"state\":\"open\"}");
			}
			
			if(state == closed)
			{
				// MQTT-bericht publish'n.
				MqttPublish(MQTT_PUB_TOPIC, "{\"state\":\"closed\"}");
			}
		}
		
		// Mogelijks ontvangen TCP-, HTTP-, HTTPS-, of MQTT-berichten zoeken in het circulair buffer.
		// De berichten zijn van de vorm: +IPD, of +MQTTSUBRECV:0,"rubu/esp8266",3,254.
		while(circularBuffer.numberOfStringsInBuffer > 0)
		{		
			// E�n string ophalen.
			circularBufferActionResult = PopStringFromCircularBuffer(&circularBuffer, receivedText);
			if(circularBufferActionResult == readStringSucceeded)
			{				
				// MQTT-ontvangst onderzoeken. Zoek achter "+MQTTSUBRECV:0,"het huidige topic",". Dat geeft het begin aan van de ontvangen MQTT-data.
				sprintf(text, "+MQTTSUBRECV:0,\"%s\",", MQTT_SUB_TOPIC);
				index = strlen(text);																	// Opzoeken hoe lang dat gedeelte van de string is.
				
				// Begin van de lijn vergelijken met de verwachte tekst en topic.
				if(strncmp(text, receivedText, index) == 0)
				{
//					// Melden aan de gebruiker (optioneel).
//					osMutexAcquire(usart2TxMutexHandle, osWaitForever);
//					printf("New MQTT-data received: ");
//					printf("%s\r\n\r\n", receivedText);
//					osMutexRelease(usart2TxMutexHandle);
					
//					// Het aantal ontvangen bytes opzoeken.
//					numberOfReceivedBytes = (uint8_t)atoi(&receivedText[index]);
//					printf("numberOfReceivedBytes: %d.\r\n", numberOfReceivedBytes);
					
					//...
					
					// OPM: indien je UART2 wil gebruiken, vraag eerst de Mutex aan.
					//		osMutexAcquire(usart2TxMutexHandle, osWaitForever);
					//		printf("...");
					//		osMutexRelease(usart2TxMutexHandle);
				}
			}
		}
		
		// LED laten knipperen als visueel teken van het doorlopen van deze thread.
		ToggleLed(2);
		
		// Even wachten.
		osDelay(20);
  }
  /* USER CODE END Esp32 */
}

/* USER CODE BEGIN Header_AdConversion */
/**
* @brief Function implementing the adConvTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AdConversion */
void AdConversion(void *argument)
{
  /* USER CODE BEGIN AdConversion */
	uint16_t adValue = 0;
	
  /* Infinite loop */
  for(;;)
  {
		// AD-waarde inlezen.
		adValue = (uint8_t)(GetAdValue(&hadc1) >> 4);
		
		// Gemeten AD-waarde in een queue zetten. Als dat niet lukt (omdat die vol zit bijvoorbeeld), wacht dan maximum 10ms.
		osMessageQueuePut(adQueueHandle, &adValue, NULL, 10);
		
		// LED laten knipperen als visueel teken van het doorlopen van deze thread.
		ToggleLed(3);
		
		// Even wachten.
    osDelay(100);
  }
  /* USER CODE END AdConversion */
}

/* USER CODE BEGIN Header_StateMachine */
/**
* @brief Function implementing the stateMachineTas thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StateMachine */
void StateMachine(void *argument)
{
  /* USER CODE BEGIN StateMachine */
	uint8_t sw;
	uint8_t adValue;
	uint16_t movingTime;
	osStatus_t osStatus;
	enum States currentState, nextState;
	
	currentState = nextState = closed;
	
	// Timer starten voor de LED die de beweging van de poort toont.
	osTimerStart(ledTimerHandle, 250);
	
	// PWM-waarde klaarzetten in het CCR2-register.
	// Via een macro... (met daarin verschillende geneste 'conditional operators').
	// Macro = 'to access peripheral registers hardware'.
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, PWM_OFFSET + 500);
	
	// PWM starten.
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	
  /* Infinite loop */
  for(;;)
  {
		// Let op: voorzie een grote stack size voor deze thread.
		
		// Is er een nieuwe AD-omzetting binnengekomen? Gebruik die om de tijd waarin
		// de poort opent/sluit, aan te passen.
		osStatus = osMessageQueueGet(adQueueHandle, &adValue, NULL, 1);
		if(osStatus == osOK)
		{
			// Tijd waarin de poort beweegt, deels instelbaar maken.
			movingTime = 1000 + adValue * 20;
		}
		// Minstens ��n seconde openen/sluiten.
		if(movingTime < 1000)
			movingTime = 1000;
		
		
		// Is er nieuwe keypad/switch data binnengekomen?
		sw = 0;
		osStatus = osMessageQueueGet(switchQueueHandle, &sw, NULL, 1);
		
		// Is er data opgehaald?
		if(osStatus == osOK)
		{
			osMutexAcquire(usart2TxMutexHandle, osWaitForever);
			printf("Key pressed: %d.\r\n", sw);
			osMutexRelease(usart2TxMutexHandle);
		}
		
		// Om de poort te openen, druk achtereenvolgens op SW1, SW2, SW3 en SW4. Dit zou
		// uiteraard nog aangepast kunnen worden zodat je met een echt keypad werkt en een instelbare
		// PIN-code.
		
		// State machine verwerken.
		switch(currentState)
		{
			case closed:
				// LED8 doven.
				HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);
				
				// Servo (op PA15) stoppen.
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, PWM_OFFSET + 500);
			
				if(sw == 1)
					nextState = firstOk;
				else
					if((sw == 2) || (sw == 3) || (sw == 4))
						nextState = closed;
				break;
			
			case firstOk:
				if(sw == 2)
					nextState = secondOk;
				else
					if((sw == 1) || (sw == 3) || (sw == 4))
						nextState = closed;
				break;
					
			case secondOk:
				if(sw == 3)
					nextState = thirdOk;
				else
					if((sw == 1) || (sw == 2) || (sw == 4))
						nextState = closed;
				break;
					
			case thirdOk:
				if(sw == 4)
				{
					nextState = openingLedOn;
					osTimerStart(gateMovingTimerHandle, movingTime);
				}
				else
					if((sw == 1) || (sw == 2) || (sw == 3))
						nextState = closed;
				break;
					
			case openingLedOn:
				// LED8 laten oplichten om aan te geven dat de poort in beweging is.
				HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
			
				// Servo (op PA15) naar links laten draaien.
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, PWM_OFFSET + 1000);
			
				// Is de beweginstijd nog niet voorbij?
				if((osEventFlagsGet(statemachineEventsHandle) & GATE_MOVING_TIMER_TICKED_FLAG) == GATE_MOVING_TIMER_TICKED_FLAG)
				{
					osEventFlagsClear(statemachineEventsHandle, GATE_MOVING_TIMER_TICKED_FLAG);
					nextState = open;
				}
				else
					// Moet LED8 toggle'n?
					if((osEventFlagsGet(statemachineEventsHandle) & LED_TIMER_TICKED_FLAG) == LED_TIMER_TICKED_FLAG)
					{
						osEventFlagsClear(statemachineEventsHandle, LED_TIMER_TICKED_FLAG);
						nextState = openingLedOff;
					}
				break;
			
			case openingLedOff:
				// LED8 doven.
				HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);
			
				// Is de beweginstijd nog niet voorbij?
				if((osEventFlagsGet(statemachineEventsHandle) & GATE_MOVING_TIMER_TICKED_FLAG) == GATE_MOVING_TIMER_TICKED_FLAG)
				{
					osEventFlagsClear(statemachineEventsHandle, GATE_MOVING_TIMER_TICKED_FLAG);
					nextState = open;
				}
				else
					// Moet LED8 toggle'n?
					if((osEventFlagsGet(statemachineEventsHandle) & LED_TIMER_TICKED_FLAG) == LED_TIMER_TICKED_FLAG)
					{
						osEventFlagsClear(statemachineEventsHandle, LED_TIMER_TICKED_FLAG);
						nextState = openingLedOn;
					}
				break;
						
			case open:
				// LED8 doven.
				HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);

				// Servo (op PA15) stoppen.
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, PWM_OFFSET + 500);
			
				if(UserButtonActive())
				{
					nextState = closingLedOn;
					osTimerStart(gateMovingTimerHandle, movingTime);
				}
				break;
									
			case closingLedOn:
				// LED8 laten oplichten om aan te geven dat de poort in beweging is.
				HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
			
				// Servo (op PA15) naar rechts laten draaien.
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, PWM_OFFSET + 0);

				// Is de beweginstijd nog niet voorbij?
				if((osEventFlagsGet(statemachineEventsHandle) & GATE_MOVING_TIMER_TICKED_FLAG) == GATE_MOVING_TIMER_TICKED_FLAG)
				{
					osEventFlagsClear(statemachineEventsHandle, GATE_MOVING_TIMER_TICKED_FLAG);
					nextState = closed;
				}
				else
					// Moet LED8 toggle'n?
					if((osEventFlagsGet(statemachineEventsHandle) & LED_TIMER_TICKED_FLAG) == LED_TIMER_TICKED_FLAG)
					{
						osEventFlagsClear(statemachineEventsHandle, LED_TIMER_TICKED_FLAG);
						nextState = closingLedOff;
					}
				break;
			
			case closingLedOff:
				// LED8 doven.
				HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);
			
				// Is de beweginstijd nog niet voorbij?
				if((osEventFlagsGet(statemachineEventsHandle) & GATE_MOVING_TIMER_TICKED_FLAG) == GATE_MOVING_TIMER_TICKED_FLAG)
				{
					osEventFlagsClear(statemachineEventsHandle, GATE_MOVING_TIMER_TICKED_FLAG);
					nextState = closed;
				}
				else
					// Moet LED8 toggle'n?
					if((osEventFlagsGet(statemachineEventsHandle) & LED_TIMER_TICKED_FLAG) == LED_TIMER_TICKED_FLAG)
					{
						osEventFlagsClear(statemachineEventsHandle, LED_TIMER_TICKED_FLAG);
						nextState = closingLedOn;
					}
				break;
					
			default:
				nextState = error;
				break;			
		}
		
		// Nieuwe state opslaan en melden.
		if(currentState != nextState)
		{
			currentState = nextState;
			
			osMutexAcquire(usart2TxMutexHandle, osWaitForever);
			printf("New state: %d.\r\n", currentState);
			osMutexRelease(usart2TxMutexHandle);
			
			// Het open en gesloten zijn, melden via MQTT.
			if((currentState == open) || (currentState == closed))
				osMessageQueuePut(mqttQueueHandle, &currentState, NULL, 10);
		}		

		// LED laten knipperen als visueel teken van het doorlopen van deze thread.
		ToggleLed(4);
		
		// Even wachten.
    osDelay(50);
  }
  /* USER CODE END StateMachine */
}

/* USER CODE BEGIN Header_Switches */
/**
* @brief Function implementing the switchesTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Switches */
void Switches(void *argument)
{
  /* USER CODE BEGIN Switches */
	bool sw1Help = false, sw2Help = false, sw3Help = false, sw4Help = false;
	uint8_t sw;
	
  /* Infinite loop */
  for(;;)
  {
    // Flankdetectie SW1.
		if(SW1Active() && sw1Help == false)
		{
			sw1Help = true;
			
			// Indrukken van de knop melden via een queue.
			sw = 1;
			osMessageQueuePut(switchQueueHandle, &sw, NULL, 100);
		}		
		if(!SW1Active())
			sw1Help = false;

		// Flankdetectie SW2.
		if(SW2Active() && sw2Help == false)
		{
			sw2Help = true;

			// Indrukken van de knop melden via een queue.
			sw = 2;
			osMessageQueuePut(switchQueueHandle, &sw, NULL, 100);
		}		
		if(!SW2Active())
			sw2Help = false;
		
		// Flankdetectie SW3.
		if(SW3Active() && sw3Help == false)
		{
			sw3Help = true;

			// Indrukken van de knop melden via een queue.
			sw = 3;
			osMessageQueuePut(switchQueueHandle, &sw, NULL, 100);
		}		
		if(!SW3Active())
			sw3Help = false;
		
		// Flankdetectie SW4.
		if(SW4Active() && sw4Help == false)
		{
			sw4Help = true;

			// Indrukken van de knop melden via een queue.
			sw = 4;
			osMessageQueuePut(switchQueueHandle, &sw, NULL, 100);
		}		
		if(!SW4Active())
			sw4Help = false;
		
		// LED laten knipperen als visueel teken van het doorlopen van deze thread.
		ToggleLed(5);
		
		// Anti-dender wachttijd.
    osDelay(20);
  }
  /* USER CODE END Switches */
}

/* LedTimeOut function */
void LedTimeOut(void *argument)
{
  /* USER CODE BEGIN LedTimeOut */
	// Vlag zetten die aangeeft dat de LED mag toggle'n.
	osEventFlagsSet(statemachineEventsHandle, LED_TIMER_TICKED_FLAG);
	
	// LED laten knipperen als visueel teken van het ticken van de timer.
	ToggleLed(6);
  /* USER CODE END LedTimeOut */
}

/* GateMovingTimeOut function */
void GateMovingTimeOut(void *argument)
{
  /* USER CODE BEGIN GateMovingTimeOut */
	// Vlag zetten die aangeeft dat de poort moet stoppen met bewegen.
	osEventFlagsSet(statemachineEventsHandle, GATE_MOVING_TIMER_TICKED_FLAG);
	
	// LED laten knipperen als visueel teken van het ticken van de timer.
	ToggleLed(7);
  /* USER CODE END GateMovingTimeOut */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
