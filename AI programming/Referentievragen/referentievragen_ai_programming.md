# Referentievragen — AI Programming

# chapter 1
 
Opdracht: beantwoord de referentievragen (Chapter 1 — *Intuition of artificial intelligence*) met behulp van **Grokking: Artificial Intelligence Algorithms**. Antwoorden zijn beknopt en gericht op leerstof.

---

## 1) Waarom is er geen unanimiteit over de definitie van artificial intelligence?
AI is een ambigu begrip: filosofen, psychologen, wetenschappers en ingenieurs hanteren verschillende perspectieven op wat "intelligentie" is. In de literatuur wordt daarom vaak gesproken over **AI-likeness**: systemen die intelligente eigenschappen vertonen (autonomie, adaptatie, perceptie, leren). Omdat intelligentie meerdere dimensies heeft (aanpassingsvermogen, redeneren, verbeelding, enz.) bestaat er geen eenduidige, universele definitie.

## 2) Wat is het verschil tussen kwantitatieve data en kwalitatieve data? Geef concrete voorbeelden.
- **Kwantitatieve data**: numerieke, meetbare waarden. Voorbeelden: temperatuur (°C), aantal verkopen, leeftijd in jaren, afstand in meters.
- **Kwalitatieve data**: observaties of meningen die niet puur numeriek zijn. Voorbeelden: de geur van een bloem, categorieën zoals "goed" of "slecht", tekstuele feedback van gebruikers.

## 3) Wat is het verschil tussen data, informatie en kennis?
- **Data**: ruwe feiten en metingen (losse waarden). Bijvoorbeeld: individuele afstanden afgelegd per stap in een doolhof.
- **Informatie**: data met context of bewerking die inzicht geeft (bijv. de totale afgelegde afstand of het gemiddelde).
- **Kennis**: geïnternaliseerde informatie gecombineerd met ervaring en begrip, bruikbaar om beslissingen te nemen of nieuwe problemen te benaderen.

## 4) Wat is een algoritme? Wat is een AI-algoritme? Wat zijn de componenten van een algoritme?
- **Algoritme**: een eindige reeks van regels/instructies die, gegeven invoer, een gewenste uitvoer produceert.
- **AI-algoritme**: een algoritme dat data gebruikt om gedrag te produceren dat als intelligent wordt beschouwd (leren, voorspellen, optimaliseren, plannen).
- **Belangrijke componenten**: invoer (data), toestanden/repræsentatie, bewerkingsstappen (operaties), beslissingslogica (heuristieken/fitness/regels), terminatieconditie en uitvoer. Voor sommige AI-methodes komen nog parameters bij (bijv. leersnelheid, populatiegrootte) of een beoordelingsfunctie (loss/fitness).

## 5) Noem enkele categorieën problemen die met (AI-)algoritmen opgelost worden.
- **Zoekproblemen / planning** (bv. kortste pad, routeplanning)
- **Optimalisatieproblemen** (bv. pakproblemen, TSP-achtige taken)
- **Voorspelling en classificatie** (supervised learning)
- **Clustering / patroonontdekking** (unsupervised learning)
- **Reinforcement learning / beslissingsproblemen** (agenten in dynamische omgevingen)
- **Deterministische vs. stochastische modellen** (altijd hetzelfde resultaat vs. probabilistische uitkomsten)

## 6) Wat is het verschil tussen een lokale beste oplossing en een globale beste oplossing?
- **Lokale beste**: beste oplossing binnen een beperkte regio van de zoekruimte.
- **Globale beste**: beste oplossing in de gehele zoekruimte.
Voorbeeld: het beste restaurant in jouw buurt (lokaal) is niet noodzakelijk het beste restaurant in het hele land (globaal).

## 7) Wat is het verschil tussen superintelligentie, algemene intelligentie en smalle (narrow) intelligentie?
- **Narrow intelligence**: systemen die gespecialiseerd zijn in één taak of domein (bv. beeldherkenning, spamfilter).
- **General intelligence**: menselijke-achtige breedte van leer- en transfervermogen: dezelfde kennis toepassen in nieuwe, diverse contexten.
- **Superintelligence**: hypothetische stap voorbij menselijke capaciteit, ver boven menselijke prestaties — grotendeels speculatief.

## 8) Wat is de relatie tussen biology-inspired algorithms, machine learning, deep learning en search algorithms?
Deze categorieën overlappen en vullen elkaar aan:
- **Search-algoritmen** (oudere, fundamentele technieken) zoeken naar paden of plannen in een ruimte; nuttig voor planning en spelbomen.
- **Biology-inspired algorithms** (bv. evolutionaire algoritmen, swarm intelligence) gebruiken natuur-geïnspireerde mechanismen (selectie, populaties, agents) om complexe optimalisatieproblemen aan te pakken.
- **Machine learning** gebruikt statistische methodes om patronen uit data te leren (supervised, unsupervised, reinforcement).
- **Deep learning** is een subveld van ML dat gebruikmaakt van diepe neurale netwerken voor taken zoals beeld- en spraakherkenning.
Samen vormen ze een gereedschapskist: sommige problemen vragen expliciete zoektocht/planning, andere vragen leren uit data of het zoeken naar goede oplossingen via evolutionaire/swarm-methodes.

## 9) Welke drie vormen van 'learning' vallen onder machine learning en leg ze kort uit?
- **Supervised learning**: leren met gelabelde voorbeelden; doel is voorspellen of classificeren (regressie/klassificatie).
- **Unsupervised learning**: ontdekken van structuur/patronen in ongelabelde data (clustering, dimensiereductie).
- **Reinforcement learning**: leren door beloning en straf in een omgeving; een agent leert een beleid dat cumulatieve beloning maximaliseert.

---

*Document gebaseerd op hoofdstuk 1 van* **Grokking: Artificial Intelligence Algorithms**.

# chapter 2

# Referentievragen AI Programming

## Hoofdstuk 1 – Inleiding (samenvatting eerder toegevoegd)

*(Hier staat reeds de inhoud van hoofdstuk 1 zoals eerder opgesteld.)*

---

## Hoofdstuk 2 – Datastructuren en Zoekalgoritmen

### 1. Wat is een datastructuur? Geef voorbeelden.

Een **datastructuur** is een manier om data te organiseren, op te slaan en efficiënt te manipuleren.
**Voorbeelden:**

* **Array** – vaste grootte, indexeerbare elementen.
* **Lijst** (linked list) – dynamisch, verbonden knopen.
* **Stack** – LIFO-principe (Last In, First Out).
* **Queue** – FIFO-principe (First In, First Out).
* **Graph** – knopen en verbindingen.
* **Tree** – hiërarchische structuur.

---

### 2. Verklaring van grafen-terminologie

* **Graph**: verzameling van **vertices (knopen/nodes)** en **edges (verbindingen)**.
* **Vertex/Node**: een enkel punt/object in de graaf.
* **Edge**: verbinding tussen twee nodes (gericht of ongericht).

---

### 3. Representatie van een graaf

* **Array of Edges**: lijst van alle verbindingen als paren (u, v).
* **Incidence Matrix**: matrix met rijen = knopen, kolommen = edges; waarde geeft aan of een edge aan een node is verbonden.
* **Adjacency Matrix**: vierkante matrix waarin cel (i,j) aangeeft of er een verbinding is tussen knoop i en knoop j.

---

### 4. Een boom is een verbonden acyclische graaf

Een **tree** is een graaf die:

* **Verbonden** is → er bestaat een pad tussen elke 2 knopen.
* **Acyclisch** is → bevat geen cycli.

---

### 5. Boom-terminologie

* **Root node**: startpunt van de boom.
* **Parent node**: knoop die een andere knoop ‘heeft’.
* **Sibling nodes**: knopen met dezelfde ouder.
* **Descendent**: knoop bereikbaar via een pad vanaf een ouder.
* **Ancestor**: knoop die op het pad naar de root ligt.
* **Leaf node**: knoop zonder kinderen.
* **Goal node**: de te vinden oplossing/knoop.
* **Path**: opeenvolging van knopen en edges.
* **Cost**: som van gewichten van de edges in een pad.
* **Degree**: aantal kinderen dat een knoop heeft.
* **Depth**: afstand (aantal edges) van de root tot een knoop.

---

### 6. Breadth-First Search (BFS)

* **Beschrijving**: doorzoekt de boom/graaf niveau per niveau (eerst alle knopen van diepte d voordat diepte d+1).
* **Gebruikte datastructuur**: **Queue (FIFO)**.

---

### 7. BFS – Oefening

**Gegeven een zoekboom**:

* Start bij de root, plaats in de queue.
* Haal telkens de eerste knoop uit de queue.
* Voeg alle kinderen toe aan de queue.
* Herhaal tot de goal node wordt gevonden of de queue leeg is.

---

### 8. Depth-First Search (DFS)

* **Beschrijving**: doorzoekt de boom/graaf zo diep mogelijk langs één pad, keert terug bij doodlopend pad.
* **Gebruikte datastructuur**: **Stack (LIFO)** of recursieve functie-aanroepen.

---

### 9. DFS – Oefening

**Gegeven een zoekboom**:

* Start bij de root, plaats in de stack.
* Haal bovenste knoop uit de stack.
* Voeg alle kinderen toe (volgorde bepaalt zoekrichting).
* Herhaal tot de goal node wordt gevonden of de stack leeg is.


