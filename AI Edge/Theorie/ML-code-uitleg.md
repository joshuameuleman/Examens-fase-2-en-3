# ML — Code-uitleg (startbestand)

Dit bestand verzamelt uitleg van belangrijke codefragmenten en oefeningen uit de Git-repo `250924-mlops-workshops`. Ik ga de repo analyseren en per oefening de volgende gegevens toevoegen:

- Bestandslocatie en korte beschrijving
- Belangrijkste functies en wat ze doen (stap-voor-stap)
- Welke concepten uit de cursus gebruikt worden (CI/CD, Docker, ONNX, quantization, etc.)
- Mogelijke examenvragen en korte modelantwoorden

Volgende stap: ik doorzoek de lokale repo `250924-mlops-workshops` en vul hieronder een lijst met gevonden oefeningen in. Daarna vul ik per oefening de code-uitleg.

### Status
- Repo inspectie: nog te doen
- Eerste oefening uitgewerkt: nog te doen

## Oefeningen: `ml-infrastructure` — overzicht en code-uitleg

Ik werk hier kort en duidelijk de belangrijkste bestanden uit zodat je ze met de hand kunt bestuderen.

### 02 - Refactor the notebook (oplossing)

- `data_utils.py` (belangrijkste punten)
	- `DATA_DIR`, `CLASSES_CSV`, `TRAIN_CSV`, `VAL_CSV`: paden naar dataset en indexbestanden.
	- `GroceryDataset(Dataset)`: PyTorch `Dataset`-implementatie.
		- `__init__`: leest CSV in, zet kolomnamen en bewaart transform-functie.
		- `__len__`: retourneert datasetgrootte.
		- `__getitem__`: bouwt pad naar afbeelding, laadt met PIL, haalt coarse label op, past transform toe en retourneert `(image, label)`.
	- `transform`: Compose van `Resize(224,224)`, `ToTensor()` en `Normalize(...)` — de standaard preprocessing voor pretrained modellen.
	- `get_classes()`: leest `classes.csv`, zet coarse class id als index en geeft dict terug {int: name}.
	- `get_loaders(batch_size)`: bouwt `GroceryDataset` voor train/val en geeft `DataLoader` objecten terug.

	Handmatige studiepunten (wat te kunnen uitleggen op papier):
	- Waarom `transform` nodig is voor pretrained nets (shape & normalisatie).
	- Verschil tussen `fine_label` en `coarse_label` en waarom coarse gebruikt wordt.

- `model_utils.py`
	- `create_model(num_classes)`: laadt `mobilenet_v3_small` met pretrained weights en vervangt de laatste classifier-laag (`model.classifier[3]`) met een `nn.Linear` met `num_classes` output. Verplaatst model naar `DEVICE`.
	- `save_model(model, path)`: `torch.save(model.state_dict(), path)` — slaat alleen gewichten op (aanbevolen voor deployment).
	- `load_model(num_classes, path)`: maakt model aan met `create_model` en laadt `state_dict` vanuit bestand.

	Belangrijk: weet waarom we `state_dict` sparen ipv hele model (portabiliteit, minder afhankelijkheden).

- `train_utils.py`
	- `train_model(model, dataloader, epochs, lr)`:
		- Maakt loss (`CrossEntropyLoss`) en optimizer (`Adam`).
		- Per epoch: zet model in train-mode, iter leer batches, push input & labels naar `DEVICE`, `optimizer.zero_grad()`, `outputs = model(images)`, `loss.backward()`, `optimizer.step()`.
		- Print gemiddelde loss per epoch.
	- `evaluate_model(model, dataloader)`: zet model in eval-mode, iter zonder grads, bereken `predicted = torch.max(outputs, 1)`, tel `correct` en `total`, return accuracy.

	Studiepunten: leg de purpose van `model.train()` vs `model.eval()`, en waarom `torch.no_grad()` gebruikt wordt bij evaluatie.

- `run_training.py`
	- CLI wrapper: `argparse` definieert `--batch-size`, `--epochs`, `--learning-rate`, `--output`.
	- Stappen in `main()`:
		1. `classes = get_classes()` — bepaal aantal classes.
		2. `train_loader, val_loader = get_loaders(...)` — krijg DataLoaders.
		3. `model = create_model(len(classes))` — bouw model.
		4. `train_model(...)` — run training loop.
		5. `accuracy = evaluate_model(...)` — print validation accuracy.
		6. `save_model(model, args.output)` — sla op.

	Studietip: op papier beschrijven wat elke stap voor effect heeft (data → model → training → evaluatie → persist).

### 04 - Backend with FastAPI

- `backend.py` (oefening)
	- Top: importeer FastAPI, helper libs, laad `class_names = get_classes()` en `model = load_model(...)` — deze worden éénmaal bij opstart geladen (performance win).
	- `val_dataset = GroceryDataset(VAL_CSV, transform=None)` — dataset zonder preprocessing zodat raw afbeeldingen kunnen worden teruggegeven via `/random-image`.
	- Endpoint `GET /class-names` — TODO in oefening: moet `{"classes": [...]}` teruggeven; implementatie vraag: converteer `class_names` dict naar lijst gesorteerd op key.
	- Endpoint `GET /random-image` — kiest willekeurige index, laadt PIL image, streamt als JPEG terug (`StreamingResponse`).
	- Endpoint `POST /predict` — accepteert `UploadFile`, leest bytes, converteert naar PIL Image, past `transform` toe om input tensor te maken, `model(input_tensor.to(DEVICE))`, `torch.max` om predicted index te bepalen, map naar class name en return JSON met `prediction`.

	Handig om op papier te kunnen schrijven:
	- Waarom model en classname bij opstart laden (latency vs memory).
	- Hoe input-validatie en foutafhandeling voor uploads werkt (try/except + 400 response).

### 05 - Connect the frontend

- `frontend.py` (Dash app)
	- `API_URL = "http://localhost:8000"` — verwacht FastAPI backend lokaal.
	- `get_random_image()` — TODO: moet een GET request sturen naar `/random-image` en `response.content` returnen (raw bytes).
	- `predict_image(image_bytes)` — stuurt image bytes als multipart `files={'file': ('image.jpg', image_bytes, 'image/jpeg')}` naar backend `/predict` en retourneert `response.json()['prediction']`.
	- `update_output(n_clicks)` — bij knopdruk: roept `get_random_image()`, dan `predict_image()`, encodeert bytes naar base64 om in browser te tonen en toont voorspelling.

	Op papier: schrijf het request/response pad uit: frontend -> GET /random-image -> bytes; frontend -> POST /predict (multipart) -> JSON response.

---
Volgende stap: wil je dat ik deze uitleg regel-voor-regel uitschrijf per bronbestand (dus echt iedere regel commentaar klaar om met de hand te leren), of is dit compacte, stapgerichte format genoeg? Ik kan nu doorgaan en de `ML-code-uitleg.md` automatisch aanvullen met regel-voor-regel toelichtingen per bestand als je dat wil.


---
 (Dit bestand wordt automatisch aangevuld zodra de repo-analyse voltooid is.)
