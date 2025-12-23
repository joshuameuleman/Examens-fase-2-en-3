# Vragen en korte antwoorden (Nederlands)

## Hoofdstuk 1 – Intuition of artificial intelligence

1. Waarom is er geen unanimiteit over de definitie van kunstmatige intelligentie?
   - Antwoord: Omdat "intelligentie" meerdere dimensies heeft (adaptatie, leren, redeneren, autonomie) en verschillende vakgebieden verschillende criteria en doelen hanteren.

2. Wat is het verschil tussen kwantitatieve data en kwalitatieve data? Geef voorbeelden.
   - Antwoord: Kwantitatief = numerieke meetwaarden (bv. temperatuur, aantal sales). Kwalitatief = beschrijvende informatie (bv. tekstfeedback, categorieën zoals "goed").

3. Wat is het verschil tussen data, informatie en kennis?
   - Antwoord: Data = ruwe feiten; Informatie = data met context of verwerking; Kennis = geïnternaliseerde en toepasbare informatie gecombineerd met ervaring.

4. Wat is een algoritme? Wat is een AI-algoritme? Wat zijn de componenten van een algoritme?
   - Antwoord: Algoritme = reeks stappen om een taak uit te voeren. AI-algoritme = algoritme dat leert of voorspelt op basis van data. Componenten: invoer, representatie/toestand, bewerkingsstappen, evaluatiefunctie (loss/fitness), parameters, stopconditie.

5. Noem enkele categorieën problemen die met (AI-)algoritmen opgelost worden.
   - Antwoord: Zoek- en planningsproblemen, optimalisatie, classificatie/voorspelling, clustering, reinforcement learning/beleidssynthese.

6. Wat is het verschil tussen een lokale beste oplossing en een globale beste oplossing?
   - Antwoord: Een lokale beste is optimaal binnen een deelgebied van de zoekruimte; de globale beste is het beste over de gehele ruimte.

7. Wat is het verschil tussen superintelligentie, algemene intelligentie en smalle intelligentie?
   - Antwoord: Smalle AI = gespecialiseerd in één taak; Algemene AI = brede, menselijke-achtige transfercapaciteit; Superintelligentie = hypothetisch ver boven menselijke prestaties.

8. Wat is de relatie tussen biology-inspired algorithms, machine learning, deep learning en search algorithms?
   - Antwoord: Ze vullen elkaar aan: search-algoritmen zoeken in toestandsruimtes; biology-inspired (evolutionair, swarm) gebruiken populaties/agents; ML leert patronen uit data; deep learning is ML met diepe netwerken.

9. Welke drie vormen van "learning" vallen onder machine learning?
   - Antwoord: Supervised learning (leren uit gelabelde voorbeelden), unsupervised learning (structuur ontdekken in ongelabelde data), reinforcement learning (leren via beloning/straffen).


## Hoofdstuk 2 – Search fundamentals

1. Wat is een datastructuur? Geef voorbeelden.
   - Antwoord: Een manier om data te organiseren/opslaan voor efficiënte bewerkingen. Voorbeelden: array, linked list, stack, queue, tree, graph.

2. Leg uit: graph, vertex/node, edge.
   - Antwoord: Graph = verzameling knopen en verbindingen. Vertex/node = element/knop. Edge = verbinding tussen twee knopen (gericht of ongericht).

3. Gegeven een graaf: wat zijn de array of edges, incidence matrix en adjacency matrix?
   - Antwoord: Array of edges = lijst met paren (u,v). Incidence matrix = rijen knopen, kolommen edges; aangeven welke knoop bij welke edge hoort. Adjacency matrix = n×n matrix met 1 als er een verbinding is tussen i en j.

4. Leg uit: een boom is een verbonden acyclische graaf.
   - Antwoord: Een tree is verbonden (er is een pad tussen alle knopen) en bevat geen cycli; dus precies n-1 edges voor n knopen.

5. Leg de boomterminologie uit: root, parent, sibling, descendent, ancestor, leaf, goal, path, cost, degree, depth.
   - Antwoord: Root = beginknoop; parent = ouder van een knoop; sibling = knopen met dezelfde ouder; descendant = afstammeling; ancestor = voorouder; leaf = bladknoop zonder kinderen; goal = doelknoop; path = pad; cost = som van edgegewichten; degree = aantal buren/children; depth = afstand tot root.

6. Leg Breadth-First Search (BFS) uit en welke datastructuur wordt gebruikt.
   - Antwoord: BFS doorzoekt niveau voor niveau, gebruikt een queue (FIFO), en vindt het kortste pad in ongewogen grafen.

7. Toepassing van BFS op een zoekboom: procedure kort.
   - Antwoord: Plaats root in queue; herhaaldelijk pop front, visiteer kinderen en push ze; stop bij vinden van doel.

8. Leg Depth-First Search (DFS) uit en welke datastructuur wordt gebruikt.
   - Antwoord: DFS gaat zo diep mogelijk langs een pad (stack of recursie), backtrackt bij doodlopende paden; gebruikt LIFO.

9. Toepassing van DFS op een zoekboom: procedure kort.
   - Antwoord: Start bij root, volg steeds het eerst gekozen kind naar beneden; als geen kinderen, backtrack en probeer volgende kind; stop bij doel.


## Hoofdstuk 3 – Intelligent search

1. Wat is een heuristiek?
   - Antwoord: Een geschatte regel of functie die de geschatte resterende kosten naar het doel inschat (h functie) en zo zoekrichting leidt.

2. Waarom kunnen heuristieken de efficiëntie van zoekproblemen verbeteren?
   - Antwoord: Ze sturen de zoekprocedure naar veelbelovende gebieden waardoor minder knopen geëxploreerd hoeven worden.

3. Geef voorbeelden van heuristieken.
   - Antwoord: Euclidische afstand in ruimtelijke zoekproblemen, manhattan distance, aantal misplaatste tegels in 8-puzzle.

4. Hoe werkt het A* algoritme?
   - Antwoord: A* gebruikt f(n)=g(n)+h(n) (g: kosten tot nu, h: geschatte resterende kosten) en kiest telkens de knoop met kleinste f.

5. Hoe wordt de costfunctie bepaald?
   - Antwoord: g berekent werkelijke kosten van start naar huidige knoop; h wordt gekozen als consistente/optimistische heuristiek afhankelijk van probleem.

6. Min-max adversarial search: hoe werkt het?
   - Antwoord: Min-max evalueert spelbomen door bladscores terug te propageren; max-niveau kiest maximale uitkomst, min-niveau kiest minimale uitkomst.

7. Alpha-beta pruning: wat is alpha en beta en waarom efficiënter?
   - Antwoord: Alpha = beste reeds gevonden waarde voor max, Beta = beste voor min; pruning slaat takken over die geen betere waarde kunnen opleveren, wat veel rekenwerk bespaart.


## Hoofdstuk 4 – Evolutionary algorithms

1. Beschrijf kort de levenscyclus van een genetisch algoritme.
   - Antwoord: Initialiseer populatie → evalueer fitness → selecteer ouders → crossover/mutatie → vorm nieuwe populatie → herhaal tot stopconditie.

2. Hoe zorgen crossover en mutatie voor diversiteit?
   - Antwoord: Crossover combineert genen van ouders; mutatie introduceert willekeurige variatie, waardoor nieuwe gebieden van zoekruimte verkend worden.

3. Geef voorbeelden van crossover en mutatie.
   - Antwoord: Single-point crossover, uniform crossover; bitflip-mutatie, boundary- of arithmetic-mutatie voor reële waarden.

4. Noem vijf parameters van een genetisch algoritme en hun effect.
   - Antwoord: populatiegrootte (meer exploratie), mutatierate (meer variatie), crossoverrate (mate van recombinatie), selectie-intensiteit (hoe snel betere individuen domineren), aantal generaties/stopcriterium.

5. Wat is een fitness-functie en waarom is de keuze cruciaal?
   - Antwoord: Fitness meet kwaliteit van oplossingen; verkeerde fitness leidt tot ongewenste optimalisatie-doelen en slechte prestaties.


## Hoofdstuk 5 – Advanced evolutionary approaches

1. Selectiemechanismen: roulette, rank, tournament, elitism — korte bespreking.
   - Antwoord: Roulette: kansen proportioneel aan fitness (kan te veel variatie geven); Rank: op rang gebaseerd (vermindert dominantie); Tournament: kies beste uit random subset (eenvoudig en effectief); Elitism: bewaar topindividuen (zorgt dat beste oplossingen niet verloren gaan).

2. Mutatiemechanismen: boundary, arithmetic, etc.
   - Antwoord: Boundary mutation zet genen naar grenswaarden; arithmetic mutation past numerieke genen aan met kleine wijziging; keuze hangt af van encoding.

3. Tree encoding en tree crossover (kort).
   - Antwoord: Tree encoding gebruikt boomstructuren voor representatie (bv. expressies); tree crossover ruilt subtrees tussen ouders (veel gebruikt in genetic programming).


## Hoofdstuk 6 – Swarm intelligence

1. Wat is swarm intelligence?
   - Antwoord: Gedrag waarbij eenvoudige agents met lokale regels samenwerken en zo emergente, slimme oplossingen produceren (bv. mieren, vogels).

2. Waarom wordt de analogie met mieren gebruikt in ant colony algorithms?
   - Antwoord: Mieren leggen pheromonensporen en versterken goede paden; dat mechanisme inspireert probabilistische paden en positieve feedback in algoritmes.

3. Hoofdstappen van het ant colony optimization-algoritme (kort).
   - Antwoord: Initialiseer pheromonen → laat vele mieren tours maken volgens pheromone + heuristiek → evalueer oplossingen → update pheromonen (verdampt + versterk beste paden) → herhaal.

4. Wiskundige formule voor doelselectie (kort):
   - Antwoord: P(i→j) = (τ_ij^α * η_ij^β) / Σ_k (τ_ik^α * η_ik^β), waarbij τ pheromone is, η heuristiek (bv. 1/distance), α en β regelen gewicht.

5. Hoe wordt de beste oplossing uiteindelijk bepaald?
   - Antwoord: Door de beste tour (hoogste fitness/laagste kosten) gevonden door mieren in iteraties; pheromonenkracht leidt tot convergentie.

6. Stopcriteria voor het algoritme.
   - Antwoord: Vast aantal iteraties, stagnatie van beste oplossing, of tijd-/RU-limiet.


## Hoofdstuk 7 – Swarm intelligence: Particles (PSO)

1. Wat betekenen Alignment, Cohesion en Separation in vogelzwermen?
   - Antwoord: Alignment = afstemmen richting met buren; Cohesion = naar gemiddelde positie van buren bewegen; Separation = botsingen vermijden.

2. Beschrijf kort de PSO-levenscyclus en positie-update.
   - Antwoord: Initialiseer deeltjes (posities/snelheden), evalueer fitness, update persoonlijke en globale best, update snelheid: v = inertia*v + c1*r1*(pbest-pos) + c2*r2*(gbest-pos), update positie: pos += v; herhaal.

3. Hoe wordt de beste oplossing bepaald?
   - Antwoord: Elke deeltje houdt zijn persoonlijke beste bij (pbest); de swarm houdt het globale beste (gbest); gbest bepaalt het eindresultaat.

4. Stopcriteria voor PSO.
   - Antwoord: Vast aantal iteraties, stagnatie van gbest, of behaalde fitness-drempel.

5. Wat is de functie van inertia, cognitive en social components?
   - Antwoord: Inertia = behoud van momentum/exploratie; Cognitive = trek naar eigen beste (lokale exploitatie); Social = trek naar groepsbeste (gedeelde kennis).


---

Bestand aangemaakt: `Referentievragen/questions_nl_and_answers.md` — wil je dat ik nu dit bestand compacter maak (bullet-opschoning), of alle antwoorden uitbreid met voorbeelden en formules?