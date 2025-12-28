# IoT Devices – Volledige Examensamenvatting

Deze samenvatting bevat **de volledige leerstof** die nodig is om te slagen voor:

- **Deel 1: theorie-examen** (open vragen, gesloten boek)
- **Deel 2: praktisch programmeerexamen** (HAL, STM32CubeMX, Keil)

De uitleg is bewust **uitgebreid en verhalend**, omdat bij open vragen verwacht wordt
dat je **principes helder kan uitleggen**, niet enkel definities kan opsommen.

---

## Hoofdstuk 1 – Inleiding, Microcontrollers en HAL

### Doel van de cursus
Deze cursus bouwt verder op het vak *Microcontrollers* en focust op:

- STM32L476RG microcontroller
- Programmeren in **C**
- Gebruik van de **HAL-bibliotheken**
- Efficiënte IO via **polling, interrupts en DMA**
- Communicatie via **UART, I²C, SPI en WiFi**
- Introductie tot **RTOS**

Een **microcontroller** is een volledig klein computersysteem op één chip:

- CPU (Cortex‑M4 in de STM32L476RG)
- Flashgeheugen (programma)
- RAM (data)
- Peripherals: timers, ADC, UART, I²C, SPI, GPIO, …

In embedded systemen is er meestal **geen besturingssysteem zoals Windows**, maar draait jouw C‑programma rechtstreeks op de hardware. Daardoor moet jij zelf:

- IO configureren (pinnen, snelheden, pull‑ups, …)
- Peripherals initialiseren (UART, timers, ADC, …)
- De flow van het programma bepalen (superloop, interrupts, RTOS)

---

### CMSIS versus HAL

#### CMSIS (Cortex Microcontroller Software Interface Standard)
Bij CMSIS programmeer je rechtstreeks op **register-niveau**.  
Dit levert **zeer efficiënte en snelle code**, maar maakt de software sterk
afhankelijk van het exacte microcontrollertype.

#### HAL (Hardware Abstraction Layer)
HAL vormt een **abstractielaag boven CMSIS** en verbergt hardware-details.
Dit maakt de code:

- Leesbaarder
- Onderhoudsvriendelijker
- Eenvoudiger te migreren naar andere STM32-microcontrollers

Nadeel: iets minder efficiënt dan registerprogrammering.

> **Examenvraag**  
> Leg het verschil uit tussen CMSIS en HAL en geef een situatie waarin HAL een betere keuze is.

**Praktisch voorbeeld**  
Stel dat je een GPIO‑pin als output wil instellen:

- Met CMSIS moet je zelf in de referentiemanual opzoeken **welk register** en **welke bits** je moet aanpassen (bv. `MODER`, `OTYPER`, `PUPDR` …) en met bitmaskers werken.
- Met HAL gebruik je een **struct** (`GPIO_InitTypeDef`) en een functie zoals `HAL_GPIO_Init()`; CubeMX genereert die code automatisch.

HAL is dus ideaal voor **snelle ontwikkeling, leesbaarheid en foutreductie**. CMSIS is bruikbaar als je **maximale performantie** en **volledige controle** nodig hebt (bv. in een tijdkritische ISR of bij zeer beperkte geheugenruimte).

**Afbeelding**: lagenmodel CMSIS–HAL–User Code  
**PDF p. ±10–11**

---

## Hoofdstuk 2 – C-taal (Embedded focus)

### C-strings
In C bestaat een string uit een **array van karakters** die eindigt op een
**nulkarakter (`\0`)**.

Gebruik:
- UART-communicatie
- `printf()`-uitvoer

Een string zoals `"TEST"` wordt in het geheugen opgeslagen als:

- `{'T', 'E', 'S', 'T', '\0'}` → totale lengte = 5 karakters

Het **nulkarakter** geeft aan waar de string eindigt. Functies zoals `strlen()` of `printf()` lopen de array af **tot ze `\0` tegenkomen**. Staat er geen `\0`, dan leest de functie verder in het geheugen → **onvoorspelbaar gedrag (undefined behavior)**.

Veelgebruikte functies (uit `string.h`):

- `strlen(s)` – lengte van de string (zonder `\0`)
- `strcpy(dst, src)` – string kopiëren
- `strcat(dst, src)` – strings aan elkaar plakken
- `strcmp(a, b)` – strings vergelijken

In embedded context moet je **voorzichtig zijn met geheugen**:

- Vermijd te grote buffers op de stack
- Let op dat je altijd voldoende ruimte voorziet voor **alle karakters + `\0`**

> **Examenvraag**  
> Waarom is het nulkarakter (`\0`) noodzakelijk bij C-strings?

**Afbeelding**: string in geheugen  
**PDF p. ±37–38**

---

### Pointers en structs
- Pointer = adres van een variabele
- HAL gebruikt pointers naar structs
- Void pointers laten generiek gebruik toe

> **Belangrijk**  
> Pointers moet je **begrijpen**, niet memoriseren.

Een pointer **bewaar het geheugenadres** van een variabele:

- `int x = 5;`
- `int *px = &x;` → `px` bevat het adres van `x`
- `*px` geeft de **waarde** waarnaar de pointer wijst (hier 5)

In embedded C gebruik je pointers om:

- Functies een variabele **by reference** te laten aanpassen
- Grote structs **niet te kopiëren**, maar enkel het adres door te geven
- Hardware‑registers te benaderen via **pointers naar vaste adressen**

Voorbeeld uit HAL:

- `UART_HandleTypeDef huart2;`
- Functies zoals `HAL_UART_Transmit(&huart2, ...)` verwachten een **pointer naar de struct**.

Een `void *` pointer is een **generieke pointer** zonder type; de HAL gebruikt dit om bv. in callbacks één generieke functie te kunnen schrijven die met verschillende types peripherals kan werken. Voor gebruik moet je deze casten naar het juiste type.

**Afbeelding**: pointers naar structs  
**PDF p. ±41–42**

---

## Hoofdstuk 3 – GPIO en Basis IO

### GPIO-concepten
- Input vs output
- Pull-up en pull-down
- Actief hoog / actief laag

```c
HAL_GPIO_ReadPin();
HAL_GPIO_WritePin();
```

> **Examenvraag**  
> Wat is het verschil tussen een pull-up en een pull-down weerstand?

**Pull-up / pull-down**  
Een ingangspin mag **nooit zweven** (onbepaald niveau), want dan kan ruis of lekstroom een willekeurige waarde veroorzaken. Een pull‑weerstand zorgt voor een **standaardniveau** wanneer de knop/schakelaar **niet actief** is:

- Pull‑up: pin wordt standaard naar **logisch 1 (VCC)** getrokken
- Pull‑down: pin wordt standaard naar **logisch 0 (GND)** getrokken

Bij een knop aan GND gebruik je typisch een **pull-up**: ongedrukt = 1, gedrukt = 0. Dit is elektrisch robuust en wordt vaak gecombineerd met een **actief lage logica** (0 = actief).

**Actief hoog / actief laag**  
Bij **actief hoog** wordt een functie geactiveerd door een **hoog** signaal (1).  
Bij **actief laag** wordt een functie geactiveerd door een **laag** signaal (0), vaak aangeduid met een streepje of `N` in de naam (bv. `RESET_N`).

**Afbeelding**: GPIO-instellingen in CubeMX  
**PDF p. ±19–20**

---

## Hoofdstuk 4 – IO-transfers

### Polling
De CPU controleert continu of data beschikbaar is.

- Voordeel: eenvoudig
- Nadeel: CPU-geblokkeerd

Bij polling heb je meestal een **oneindige superloop**:

```c
while (1) {
	if (data_available()) {
		handle_data();
	}
}
```

Zolang er geen data is, doet de CPU **niets nuttigs**. Dit is acceptabel voor **zeer eenvoudige applicaties**, maar in complexe systemen wil je dat de CPU **andere taken** kan uitvoeren terwijl ze wacht op IO.

**Afbeelding**: polling schema  
**PDF p. ±4–5**

---

### Interrupts
De peripheral verwittigt de CPU wanneer nodig.

- NVIC configuratie
- Interrupt handlers

> **Examenvraag**  
> Waarom zijn interrupts efficiënter dan polling?

Bij een interrupt kan de CPU **andere code uitvoeren of in sleep gaan** totdat een gebeurtenis optreedt (bv. timer overflow, ontvangen UART‑byte, druk op een knop). Wanneer de gebeurtenis optreedt:

1. De CPU onderbreekt de huidige taak
2. Voert de **ISR (Interrupt Service Routine)** uit
3. Keert terug naar de vorige taak

Belangrijke begrippen:

- **NVIC** (Nested Vectored Interrupt Controller) beheert prioriteiten van interrupts
- Hogere prioriteit → kan een lagere prioriteit onderbreken
- In een ISR moet je **zo weinig mogelijk werk** doen (snel klaar zijn) en langere verwerking doorschuiven naar de main‑loop of een RTOS‑taak.

**Afbeelding**: interrupt flow  
**PDF p. ±7–10**

---

### DMA (Direct Memory Access)
Data wordt rechtstreeks naar het geheugen geschreven.

- CPU enkel interrupt bij voltooiing
- Zeer efficiënt

> **Examenvraag**  
> Vergelijk DMA met polling en interrupts.

DMA is ideaal voor **grote of continue datastromen** (bv. ADC‑samples, seriële data, audio).  
Zonder DMA moet de CPU **elke byte** zelf uit een register lezen/schrijven. Met DMA configureer je eens:

- Bronadres (bv. peripheral register)
- Doeladres (bv. buffer in RAM)
- Aantal transfers
- Eventueel **circular mode** (continu in een ringbuffer schrijven)

Daarna kan de CPU **andere zaken doen**, terwijl de DMA‑controller de data verplaatst. Enkel bij **half‑vol** of **vol buffer** krijg je een interrupt.

**Afbeelding**: DMA + bus matrix  
**PDF p. ±13–15**

---

## Hoofdstuk 5 – Timers en PWM

### Timers
- Prescaler
- Counter
- Input Capture

Een timer telt op (of af) met een bepaalde **tijdsresolutie**. De ingangsklok (bv. 80 MHz) wordt eerst gedeeld door de **prescaler**, daarna telt de **counter** door tot een bepaalde **auto‑reload waarde (ARR)**.

Formule (in eenvoudige vorm):

- `timer_freq = f_clk / (prescaler + 1)`
- `update_freq = timer_freq / (ARR + 1)`

Door prescaler en ARR te kiezen, stel je de **frequentie** in waarop de timer overloopt (en dus een interrupt of event kan genereren). Met **Input Capture** kun je tijdstippen van inkomende signalen meten (bv. pulsbreedte of periode van een signaal).

**Afbeelding**: timer clock schema  
**PDF p. ±36**

---

### PWM
Gebruikt voor servo’s en motoren.

- Duty cycle
- Frequentie

> **Examenvraag**  
> Hoe stuur je een servo aan met PWM?

Bij PWM blijft de **frequentie** meestal vast, en verander je de **duty cycle** (percentage "hoog" binnen één periode). De gemiddelde spanning over de belasting is ongeveer:

- `Vgemiddeld ≈ duty_cycle * VCC`

Voor een standaard RC‑servo:

- Frequentie ≈ 50 Hz (periode 20 ms)
- Pulsbreedte ≈ 1 ms → uiterste hoek links
- Pulsbreedte ≈ 2 ms → uiterste hoek rechts

Je gebruikt dus een timer‑kanaal in PWM‑mode en stelt de **compare‑waarde** zó in dat de gewenste pulsbreedte ontstaat.

**Afbeelding**: PWM-signaal  
**PDF p. ±37**

---

## Hoofdstuk 6 – I²C

### I²C-bus
- SDA & SCL
- Open drain
- Pull-up weerstanden

I²C is een **seri ële, synchrone bus** met één of meerdere masters en meerdere slaves.  
Omdat de lijnen **open‑drain** zijn, kunnen meerdere toestellen de bus delen zonder dat ze elkaar kortsluiten:

- Iedereen kan enkel naar **laag** trekken
- Pull‑up weerstanden trekken de lijn naar **hoog** als niemand actief is

Elke slave heeft een **uniek adres** (7‑ of 10‑bit). De master spreekt een specifieke slave aan door dat adres in het adresframe te plaatsen.

**Afbeelding**: I²C bus  
**PDF p. ±6–7**

---

### I²C-communicatie
- Start
- Address + R/W
- ACK/NACK
- Stop

> **Examenvraag**  
> Waarom moet je bij I²C-lezen eerst schrijven?

Typisch I²C‑scenario met een sensor of geheugenchip:

1. Master stuurt **Start**
2. Master stuurt **slave‑adres + Write‑bit**
3. Master stuurt het **registeradres** binnen de slave (bv. "temperatuurregister")
4. Master stuurt **herstart (Repeated Start)**
5. Master stuurt **slave‑adres + Read‑bit**
6. Slave stuurt de gevraagde data

Je "schrijft" dus eerst **welk register** je wil lezen, daarna doe je een leesoperatie. Zonder die eerste schrijffase weet de slave niet **welke interne locatie** je bedoelt.

**Afbeelding**: I²C timingdiagram  
**PDF p. ±9–12**

---

## Hoofdstuk 7 – SPI

### SPI-basis
- MOSI / MISO / SCK / CS
- Full-duplex

SPI is een **snelle, synchrone seriële bus** met een duidelijke master‑slave structuur:

- Master genereert de klok (`SCK`)
- Data gaat van master naar slave via **MOSI** (Master Out Slave In)
- Data gaat van slave naar master via **MISO** (Master In Slave Out)
- Elke slave heeft een aparte **chip select (CS / NSS)**

In tegenstelling tot I²C heeft SPI **geen adressen** op de bus; de master kiest een slave door zijn CS‑lijn laag te maken.

**Afbeelding**: SPI bus  
**PDF p. ±3–6**

---

### CPOL en CPHA
Bepalen wanneer data gesampled wordt.

> **Examenvraag**  
> Wat doen CPOL en CPHA?

Met **CPOL** (Clock POLarity) bepaal je wat het **rustniveau** van de klok is (hoog of laag).  
Met **CPHA** (Clock PHAse) bepaal je **op welke flank** (opgaande of neergaande) data wordt gesampled en op welke flank data verandert.

Master en slave moeten **exact dezelfde combinatie** van CPOL/CPHA gebruiken, anders wordt data op het verkeerde moment gelezen en krijg je foute bits.

**Afbeelding**: SPI timing  
**PDF p. ±13–15**

---

## Hoofdstuk 8 – UART

- TX / RX
- Baudrate
- Asynchroon

UART is een **asynchrone seriële communicatie** zonder gedeelde kloklijn. In plaats daarvan spreken zender en ontvanger **baudrate, aantal databits, pariteit en stopbits** vooraf af (bv. `115200 8N1`).

Een typisch UART‑frame bevat:

- 1 startbit (laag)
- 5–9 databits (LSB eerst)
- Optioneel 1 pariteitsbit
- 1 of 2 stopbits (hoog)

Omdat er geen kloklijn is, gebruikt de ontvanger zijn **eigen klok** en samplet hij de lijn op vaste tijdsintervallen. Als de baudrates te veel afwijken, gaat de sampling uit fase en ontstaan bitfouten.

UART wordt vaak gebruikt voor:

- Debug‑output (`printf` via een seriële terminal)
- Communicatie met modules (bv. GPS, Bluetooth, WiFi‑modems)

**Afbeelding**: UART frame  
**PDF p. ±11**

---

## Hoofdstuk 9 – WiFi (ESP32-C3)

- UART communicatie
- AT-commando’s
- ESP32 verzorgt netwerkstack

De STM32 fungeert hier als **host‑microcontroller** en de ESP32‑C3 als **WiFi‑modem**.  
Via UART stuurt de STM32 **AT‑commando’s** (tekstcommando’s) naar de ESP32, zoals:

- Verbinden met een access point
- Openen van een TCP/UDP‑verbinding
- Versturen/ontvangen van data

De volledige **TCP/IP‑stack en WiFi‑authenticatie** draait op de ESP32. Zo moet je op de STM32 geen complex netwerkprotocol implementeren, enkel de juiste commando’s sturen en antwoorden verwerken.

---

## Hoofdstuk 10 – RTOS

### Wat is een RTOS?
- Taken
- Scheduling
- Deterministisch gedrag

> **Examenvraag**  
> Waarom gebruik je een RTOS?

Zonder RTOS schrijf je meestal een **superloop** met veel `if`‑structuren en flags om verschillende functies om de beurt uit te voeren. Dit wordt snel onoverzichtelijk wanneer:

- Je veel verschillende periodieke taken hebt (sensor lezen, communicatie, logging, …)
- Sommige taken **snelle responstijd** vereisen

Een **RTOS (Real‑Time Operating System)** laat je toe om:

- Meerdere **taken (threads)** te definiëren
- Elke taak een **prioriteit** en eventueel een **periode** te geven
- Synchronisatie te doen via **queues, semaforen, mutexen**

Het RTOS‑scheduler beslist **welke taak wanneer draait**, rekening houdend met prioriteiten. Zo kun je garanderen dat kritieke taken **binnen een voorspelbare tijd** worden uitgevoerd (deterministisch gedrag).

Je gebruikt een RTOS wanneer de applicatie:

- Complex genoeg is met meerdere gelijktijdige activiteiten
- Strikte timing‑eisen heeft
- Op een gestructureerde manier moet kunnen groeien en onderhouden worden

**Afbeelding**: RTOS scheduling  
**PDF p. ±31–32**
