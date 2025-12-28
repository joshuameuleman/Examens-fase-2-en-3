**`backend.py` (FastAPI) — Uitleg en examenvragen**

Locatie: `250924-mlops-workshops/ml-infrastructure/04-backend-with-fastapi/backend.py`

Korte omschrijving
- Model serving API met FastAPI: model wordt geladen bij startup en er zijn endpoints voor class names, random validation images en predict.

Belangrijke onderdelen
- Global preload
  - `class_names = get_classes()`
  - `model = load_model(num_classes=len(class_names))` en `model.eval()`
- `val_dataset = GroceryDataset(VAL_CSV, transform=None)` voor raw images
- Endpoints
  - `GET /class-names` — (TODO) moet `{"classes": [...]}` retourneren
  - `GET /random-image` — retourneert een random JPEG uit de validation set
  - `POST /predict` — accepteert `UploadFile`, converteert naar PIL Image, apply `transform`, voert model inference uit en retourneert predicted class

Implementatie-tip (missende functie)
- `get_class_names()` implementatie voorbeeld:

```python
@app.get("/class-names")
def get_class_names():
    return {"classes": list(class_names.values())}
```

Control flow van `POST /predict`
1. `UploadFile` gelezen (await file.read())
2. `PIL.Image.open` + `.convert('RGB')`
3. `transform(image).unsqueeze(0)` → tensor met batch-dim
4. `with torch.no_grad(): output = model(input_tensor.to(DEVICE))`
5. `predicted_idx = torch.argmax(output, dim=1)` → map naar class name
6. Return JSON met `prediction`

Concepten om te beheersen
- Waarom het model bij startup geladen wordt (startup latency vs per-request overhead)
- Thread-safety: PyTorch en meerdere workers/uvicorn workers — model delen tussen processen vs threads
- Input validatie en foutcodes (400 bij ongeldige image)
- StreamingResponse usage voor binaire data (images)

Mogelijke examenvragen
- "Waarom is `model.eval()` noodzakelijk voor inference?"
- "Leg uit waarom je `torch.no_grad()` gebruikt in de predict-route."
- "Wat verandert er als je meerdere Uvicorn workers gebruikt?"

Annotated `POST /predict` (regel-voor-regel)

```
async def predict(file: UploadFile = File(...)):
  # 1. image_data = await file.read()
  #    - lees ruwe bytes uit UploadFile (async).
  # 2. image = Image.open(BytesIO(image_data)).convert("RGB")
  #    - decodeer bytes naar PIL.Image en forceer RGB kanalen.
  # 3. input_tensor = transform(image).unsqueeze(0)
  #    - pas preprocess transforms toe (resize, ToTensor, Normalize) en voeg batch-dim toe.
  # 4. with torch.no_grad(): output = model(input_tensor.to(DEVICE))
  #    - zet no_grad om GPU memory te besparen en voorkomen dat autograd graph gebouwd wordt.
  # 5. _, predicted_idx = torch.max(output, 1)
  #    - vind index van hoogste logit per sample.
  # 6. predicted_class = class_names[predicted_idx.item()]
  #    - map index naar string via class_names dict.
  # 7. return {"prediction": predicted_class}
```

Exam tip antwoorden (kort):
- `model.eval()` schakelt dropout uit en zorgt dat BatchNorm gebruikt wordt met running stats — essentieel voor stabiele inference.
- `torch.no_grad()` voorkomt allocatie van gradients en verkleint memory/compute tijdens inference.
- Bij meerdere Uvicorn workers draait elk worker een apart process met eigen model copy; zorg dat memory en model load times geoptimaliseerd zijn en gebruik eventueel shared model servers voor schaal.
