Download het codevoorbeeld SPI - DMA - APA102C en los onderstaande vragen daarmee op.

Je zal ook nog extra documenten nodig hebben, zoals de datasheet van de APA102C LED (zie Toledo onder Documentatie/Datasheets externe modules).



Let op: de invulvragen zijn hoofdlettergevoelig!

Waarom is de code opgesteld zodat eerst de data voor blauw, dan groen en dan rood verzonden wordt?

ANTWOORD:
Omdat de APA102C in zijn protocol per LED verwacht dat na de helderheidsbyte eerst de blauwe, dan de groene en tenslotte de rode kleurbyte gestuurd worden (B, G, R). De code volgt dus het datasheet-vereiste byte-order.

Hoeveel bytes worden per cyclus verstuurd via DMA in deze code?

antwoord:
20 bytes. Berekening: 4 start-bytes + (NUMBER_OF_APA102C_LEDS * 4 bytes per LED) + 4 end-bytes = 4 + 3*4 + 4 = 20.



Wanneer de LED’s aangestuurd worden via SPI, geef je ook mee wat de standaardhelderheid is, momenteel is dit 4. Als we dit nu veranderen naar bv. 20, welke "helderheidspercentage" zullen we bekomen op onze LED's (rond af op 1 cijfer na de komma)?

antwoord:
Ongeveer 64,5%. Uitleg: de APA102C gebruikt een 5-bit globale helderheid (0–31). 20/31 * 100 ≈ 64,516% → afgerond 64,5%.

Als we die 20 nemen als waarde, wat wordt dan de uiteindelijke waarde die als byte verstuurd wordt over SPI? Noteer het in hexadecimale vorm.

antwoord:
0xF4. (Omdat de code `brightness | 0xE0` schrijft; 20 decimal = 0x14 → 0xE0 | 0x14 = 0xF4.)



Wanneer precies wordt de functie HAL_SPI_TxCpltCallback() aangeroepen?

antwoord:
Deze callback wordt aangeroepen wanneer de SPI-transmissie via DMA volledig afgerond is — dus nadat de DMA-transfer complete (TC) interrupt is verwerkt en alle bytes daadwerkelijk door de SPI-peripheral zijn verzonden. De HAL roept de callback aan vanuit de interrupt-context van de DMA/SPI.

In het bestand apa102c.c wordt het keyword extern gebruikt. Leg uit waarom dat hier zo is.

antwoord:
Omdat de array `source` in een ander bronbestand gedefinieerd is (in `main.c`). Met `extern` wordt de declaratie hier geplaatst zodat `apa102c.c` naar diezelfde array kan verwijzen zonder nogmaals geheugen ervoor te reserveren.

Hoeveel variabelen zitten verwerkt in de struct van het type APA102C? 

antwoord:
4 variabelen: `brightness`, `red`, `green` en `blue`.