Inhoud van toets
Vraag 
Download het codevoorbeeld UART2 – DMA en los onderstaande vragen daarmee op.



Let op: de invulvragen zijn hoofdlettergevoelig!


Vraag 1

De tweede parameter die meegegeven moet worden aan HAL_UART_Receive_DMA() moet van het type pointer naar een uint8_t zijn. Hoe komt het dan dat je een verwijzing naar een uint8_t array daar mag meegeven?

Antwoord:
In C “degradeert” (decays) de naam van een array automatisch naar een pointer naar het eerste element. Een `uint8_t buf[...];` kan dus als `uint8_t*` doorgegeven worden omdat `buf` het adres van `buf[0]` voorstelt.

Vraag 2

Schrijf volledig voluit: UART RX DMA

antwoord:
Universal Asynchronous Receiver/Transmitter Receive Direct Memory Access

Vraag 3

Wat zit er als waarde in NUMBER_OF_BYTES_TO_RECEIVE?

antwoord:
10

Vraag 4

Hoeveel parameters heeft de functie HAL_UART_Receive_DMA()?
 
Antwoord:
3 (namelijk: `UART_HandleTypeDef *huart`, `uint8_t *pData`, `uint16_t Size`).

Vraag 5

Opmerking: om de volgende vragen op te kunnen lossen hoef je niet noodzakelijk te beschikken over het Nucleo-L476RG bordje (het mag natuurlijk wel) ...



Stel dat we de voorbeeldcode inladen op onze Nucleo-L476RG en een breakpoint plaatsen bij de functieaanroep HAL_DMA_IRQHandler(&hdma_usart2_rx) in het bestand stm32l4xx_it.c, dat zal ongeveer op lijn 209 zijn.

We starten vervolgens de Debug Session op, dat kan er ongeveer zo uitzien:

Code:
void DMA1_Channel6_IRQHandler(void)
{

    Hal_DMA_IRQHandler(&hdma_usart2_rx)

}

Als we karakters versturen vanuit Putty naar het Nucleo-bord zal normaalgezien het programma halt houden na het verzenden van 5 karakters. Dat is precies in de helft van het totaal aantal te verwachten bytes via DMA. Dat komt omdat de HAL-bibliotheek de Half Transfer Interrupt Enable hoog zet in de DMA controller. Dat zorgt er dus voor dat je ook na 5 bytes reeds in break mode gaat.

[text](../../../../../Downloads/STM32L4x6.SFR)

Je merkt dat de vlag/bit DMAR aangevinkt staat.

Zoek op in STM32L476RG Reference manual.pdf (te vinden op Toledo onder Documentatie > Datasheets > Datasheets STM32L476RG) wat die DMAR betekent. Noteer alles voluit.

Je merkt dat de vlag/bit DMAR aangevinkt staat.

Zoek op in STM32L476RG Reference manual.pdf (te vinden op Toledo onder Documentatie > Datasheets > Datasheets STM32L476RG) wat die DMAR betekent. Noteer alles voluit.

Antwoord:
DMAR = DMA enable receiver. Dit is de DMAR-bit in register USART_CR3. Wanneer deze bit = 1, wordt DMA-ontvangst ingeschakeld en genereert de USART een DMA‑request voor de ontvanger (bij RXNE=1) zodat ontvangen data uit RDR via DMA naar het geheugen gekopieerd wordt. Bij 0 is DMA voor ontvangst uitgeschakeld.

Vraag 6

We gebruiken DMA controller 1, maar welk kanaal daarvan gebruiken we om data te ontvangen van USART2?

Antwoord:
DMA1 Channel 6 (DMA1_Channel6)

Vraag 7

De DMA controller weet hoeveel bytes ontvangen moeten worden omdat dat getal bewaard wordt in het register DMA->CNDTRx (lees eens na in STM32L476RG Reference manual.pdf op p. 355).

Stel dat we nu alle breakpoints verwijderen en één breakpoint plaatsen bij de start van de hoofdlus in main.c (ongeveer lijn 117). We resetten vervolgens het programma/microcontroller.



Als we vervolgens via View > System Viewer > DMA > DMA1 onderstaand scherm opvragen, zal een DMA->CNDTRx register een niet-nulwaarde bevatten (meer bepaald de waarde 0x0000000A).

Er zijn verschillende registers met die naam, enkel de x verschilt:

Onder welk register zal je de waarde 0x0000000A aantreffen? Gebruik het antwoord uit de vorige vraag om het juiste register te vinden.

A: CNDTR7
B: CNDTR6
C: CNDTR5
D: CNDTR3
E: CNDTR2
F: CNDTR4
G: CNDTR1

Antwoord :
B: CNDTR6