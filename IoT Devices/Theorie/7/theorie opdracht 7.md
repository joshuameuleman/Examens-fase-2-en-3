Download het codevoorbeeld CMSIS RTOS V2 - Blinky UART2 TX RX en los onderstaande vragen daarmee op.



Voor sommige vragen zal je de instellingen moeten bekijken van o.a. FreeRTOS in STM32CubeMX.
Bijkomend kan je dit ook raadplegen: https://arm-software.github.io/CMSIS_5/RTOS2/html/modules.html.


Let op: de invulvragen zijn hoofdlettergevoelig!

# oefeningen

1. Hoeveel tasks heeft dit voorbeeld?

antwoord: 3

2. Wordt de USART2 global interrupt opgevangen of niet?

antwoord:

- nee

3. Welke prioriteit geniet Usart2RxThread?

antwoord: osPriorityNormal

4. De HAL-functies hebben ook nood aan een 'timer tick'. Welke hardware timer wordt hiervoor gebruikt in dit voorbeeld? Geef de naam van de timer.

antwoord: TIM6

5. Hoeveel queues heeft dit voorbeeld?

antwoord: 0

6. De firmware maakt onderliggend gebruik van FreeRTOS. Welke versie van FreeRTOS wordt gebruikt?

antwoord: V10.3.1

7. De CMSIS RTOS V2 code maakt intensief gebruik van de SysTick timer om 'ticks' te genereren. Op welke frequentie 'tickt' de SysTick timer in dit voorbeeld?

antwoord: 1000 Hz


8.  In welke thread state komt een task terecht wanneer de functie osDelay() opgeroepen wordt?

antwoord: osThreadBlocked

9.  Welk datatype geeft de functie osKernelStart() terug?

antwoord: osStatus_t

10. Van welk type is Usart2TxThread_attributes?

antwoord: const osThreadAttr_t