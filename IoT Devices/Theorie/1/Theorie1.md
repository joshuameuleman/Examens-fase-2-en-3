# Belangrijk

Download het codevoorbeeld Pointers en los onderstaande vragen daarmee op.



Let op: de invulvragen zijn hoofdlettergevoelig!


## Vraag 1

Hoe heet het derde register dat aangemaakt werd in de definitie van USART_TypeDef?

answer: CR3

## Vraag 2
In welk bestand kan je de definitie terugvinden van SW2_Pin?
answer: main.h
## Vraag 3
De functie HAL_ADC_Init() verwacht een parameter van het type ADC_HandleTypeDef*. Daarin zit een verwijzing naar een Instance. Van welk type is Instance precies?
answer: ADC_TypeDef*
## Vraag 4
In welk bestand kan je de definitie van de functie HAL_ADC_Start() terugvinden?
answer: stm32l4xx_hal_adc.c
## Vraag 5
Noteer de lijn code uit leds.c waarop LED3 ingeschakeld wordt in de functie ByteToLeds().
answer: HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
## Vraag 6
Het sjabloon bevat ook een bestand met code om gemakkelijker met de AD-converter te werken (ad.c). De functie GetAdValue() neemt één parameter mee. Van welk type is die parameter exact?
answer: ADC_HandleTypeDef*
## Vraag 7
De C-taal heeft verschillende versies. Welke versie werd gebruikt om dit project te compileren?

Zoek dat op bij de Options for Target….
possible answers pick 1

C21
C90
C11
C99 dit is juist
## Vraag 8
Welke numerieke waarde geeft de functie HAL_UART_Init() terug, als de parameter die je meegeeft naar die functie, NULL zou zijn?
answer: 1
## Vraag 9
Noteer het statement uit de main.c dat ervoor zorgt dat de klok voor GPIOC ingeschakeld wordt.
answer: __HAL_RCC_GPIOC_CLK_ENABLE();
## Vraag 10
In de functie HAL_UART_Init() wordt gebruik gemaakt van een parameter met als naam huart. Die variabele is van een bepaald struct type. In welk bestand kan je de definitie vinden van dat struct type?
answer: stm32l4xx_hal_uart.h