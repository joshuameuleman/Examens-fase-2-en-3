**ML Infrastructure — Gedetailleerde code-uitleg (belangrijkste scripts)**

Bestandspaden in repo: `250924-mlops-workshops/ml-infrastructure`

Doel: korte, examengerichte uitleg van belangrijke scripts zodat je ze snel kunt lezen, uitleggen en beantwoorden.

---

**`data_utils.py`**
- Doel: dataset loading, preprocessing en dataloader-voorbereiding.
- Belangrijkste functies:
  - `load_dataset(path)`: leest ruwe data (csv/images), voert normalisatie en transformaties uit.
  - `create_dataloader(dataset, batch_size, shuffle)`: pakt dataset en retourneert PyTorch (of vergelijkbare) DataLoader met collate-functie.
- Control flow:
  1. bestands- of map-invoer valideren
  2. per-item preprocessing (resize, normalize, augmentaties)
  3. dataset object en DataLoader teruggeven
- Concepten: batching, shuffling, seed voor determinisme, collate-functies, verschil tussen training/validation transforms.
- Mogelijke examenvragen:
  - "Wat doet de collate-functie en waarom heb je die nodig bij variabele-lengte items?"
  - "Welke stappen zijn essentieel om reproductie van resultaten te waarborgen in het dataloadingproces?"

---

**`model_utils.py`**
- Doel: model-architectuur-definitie en helper functies voor laden/saven van weights.
- Belangrijkste items:
  - `build_model(config)`: bouwt en initialiseert het netwerk volgens config (layers, activations, initialization).
  - `load_checkpoint(path, model, optimizer=None)`: laadt gewichten en (optioneel) optimizer state.
  - `save_checkpoint(path, model, optimizer, epoch)`: persistente opslag voor herstel.
- Control flow:
  1. config-parsing → model-instantie
  2. (optioneel) load checkpoint
  3. return model
- Concepten: weight initialization, state_dict, device mapping (`map_location`), training vs eval modes (`model.train()` vs `model.eval()`).
- Mogelijke examenvragen:
  - "Waarom gebruik je `state_dict()` i.p.v. `torch.save(model)` direct?"
  - "Wanneer en waarom roep je `model.eval()` aan tijdens inference?"

---

**`train_utils.py` / `run_training.py`**
- Doel: training loop, metrics logging en saving checkpoints.
- Belangrijke stappen in de training loop:
  1. dataset en dataloaders opzetten
  2. model naar device verplaatsen
  3. optimizer + scheduler initialiseren
  4. epoch-loop: forward → loss → backward → optimizer.step()
  5. validation en logging (loss, accuracy, eventueel early stopping)
  6. checkpointing en (optioneel) upload artifact
- Concepten: gradient accumulation, mixed precision (AMP), learning rate schedulers, gradient clipping, batchnorm/dropout gedrag tijdens train/eval.
- Mogelijke examenvragen:
  - "Leg het verschil uit tussen optimizer.zero_grad() en backward(), en waarom de volgorde belangrijk is."
  - "Wat is het nut van een LR scheduler en wanneer update je deze?"

---

**`model.pth` (artifact)**
- Doel: gepickelde gewichten. Kenmerken om te bespreken: grootte, afhankelijkheden (PyTorch versie), device mapping.
- Mogelijke examenvragen:
  - "Waarom kan een checkpoint die op GPU is getraind niet zomaar op CPU geladen worden zonder `map_location`?"

---

**`backend.py` (FastAPI)**
- Doel: model serving endpoint(s) voor inference.
- Belangrijke onderdelen:
  - App init: `app = FastAPI()`
  - Endpoint(s): `@app.post('/predict')` met pydantic request model
  - Model loading op startup event (`@app.on_event('startup')`) en caching van model-object
  - Request handling: input validatie → preprocess → model(input) → postprocess → response
- Concepten: async vs sync endpoints, thread-safety van modellen, batching aanvragen, timeouts en error handling.
- Mogelijke examenvragen:
  - "Waarom laad je het model tijdens `startup` i.p.v. bij elke request?"
  - "Wat moet je aanpassen als je meerdere gelijktijdige requests wilt kunnen verwerken?"

---

**`frontend.py`**
- Doel: eenvoudige client (CLI / Flask / andere) die HTTP-aanroepen maakt naar backend。
- Belangrijk: request format (JSON, multipart/form-data voor images), retry logic, UI-ervaring (sync vs async).
- Mogelijke examenvragen:
  - "Welke content-type header gebruik je voor het versturen van images via HTTP en waarom?"

---

**`s3_utils.py` / `compose-minio.yml`**
- Doel: upload/download van model artifacts naar S3 of MinIO.
- Belangrijk: credentials via env-variabelen, object keys en versies, streamen van data i.p.v. volledige geheugenbuffers.
- Concepten: presigned URLs, consistentie, beperkte bandbreedte en multipart upload.
- Mogelijke examenvragen:
  - "Waarom moet je credentials nooit hardcoden en welke alternatieven zijn er?"
  - "Wat is een multipart upload en wanneer gebruik je die?"

---

**`Dockerfile` & `docker-compose.yml`**
- Doel: containerisatie van backend/frontend en lokale integratie.
- Bespreek:
  - lagen en caching: reduceer rebuilds door afhankelijkheden eerst te installeren
  - exposeports, healthchecks, volumes en environment variables
  - compose services: afhankelijkheden (bv. backend wacht op MinIO)
- Mogelijke examenvragen:
  - "Waarom moet je zoveel mogelijk kleine lagen hebben voor performance?"
  - "Hoe stuur je een geheime waarde door naar een container op veilige wijze?"

---

**`test_dataloader.py` / CI (`checks.yml`)**
- Doel: unit tests en GitHub Actions configuratie voor PR-checks.
- Praatpunten: wat test je (shape, types, edge-cases), fixtures, mocking I/O, en test-runner config.
- Mogelijke examenvragen:
  - "Waarom is het belangrijk dat je dataloader tests uitvoert in PR-checks?"

---

Kort instructie-voorbeeld voor examenantwoorden
- Vraag: "Leg in 90 seconden uit wat `backend.py` doet." → Antwoordstructuur:
  1. Doel van bestand (model serving)
  2. Startup: model laden en resources initialiseren
  3. Endpoints: input → preprocess → model → postprocess → response
  4. Belangrijke concepten: model.eval(), concurrency en error handling


Als je wil, maak ik nu dezelfde gedetailleerde `.md`-uitleg voor de `edge-deployment` en `generative-ai` mappen (elk sleutel-bestand met 3–5 mogelijke examenvragen).