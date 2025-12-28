Open oefenvragen — ML Infrastructure

1) Lees en leg uit wat er fout is en waarom:
```python
for images, labels in train_loader:
    outputs = model(images)
    loss = criterion(outputs, labels)
    loss.backward()
    optimizer.zero_grad()
    optimizer.step()
```

2) Leg uit het verschil tussen `model.train()` en `model.eval()` en noem twee concrete effecten op layers.

3) Geef de stappen en redenatie om een `DataLoader` te debuggen die af en toe verkeerde labels retourneert.

4) Beschrijf wat er wordt opgeslagen in een checkpoint waarmee je training exact kunt hervatten (noem velden en types).

5) Analyseer dit FastAPI-fragment en beschrijf threading/worker-issues die kunnen optreden:
```python
model = load_model(...)
@app.post('/predict')
def predict(image: bytes):
    tensor = transform(image)
    out = model(tensor)
    return {'pred': out.argmax().item()}
```

6) Schrijf kort hoe je een dataloader unit-test opzet om shape en types te verifiëren.

7) Leg uit waarom je `torch.save(model.state_dict())` verkiest boven `torch.save(model)` in productie.

8) Beschrijf hoe je model artifacts veilig naar MinIO uploadt in een CI-pijplijn zonder credentials te lekken.

9) Geef drie performance-tips om een CPU-only inference container kleiner en sneller te maken.

10) Verklaar het nut van `map_location` bij `torch.load` en geef een foutvoorbeeld wanneer het ontbreekt.

Antwoorden (kort)

1) Fout in loop: `optimizer.zero_grad()` moet vóór `loss.backward()`; huidige volgorde leidt tot accumulatie van eerdere gradients.

2) `model.train()` activeert training-specifieke lagen (dropout, BatchNorm update); `model.eval()` schakelt dropout uit en zorgt dat BatchNorm gebruikt wordt met opgeslagen running stats.

3) Debug stappen voor dataloader met verkeerde labels: (a) visueel inspecteer een batch (images + labels), (b) controleer CSV/indexing en label parsing, (c) bevestig consistent shuffling/seed, (d) schrijf unit-test voor paar voorbeelden.

4) Checkpoint velden voor hervatten: `model.state_dict()` (dict), `optimizer.state_dict()` (dict), `epoch` (int), `rng_states` (optioneel, dict van random.getstate()/torch.get_rng_state()), eventueel scheduler state.

5) FastAPI fragment threading-issues: als je meerdere uvicorn workers gebruikt draait elk proces zijn eigen model; bij threads kunnen race conditions optreden als model mutable state wordt bewerkt (BatchNorm running stats) — bewaar model in read-only mode (`eval()` + `no_grad()`), of zorg voor per-request kopie als nodig.

6) Dataloader unit-test: maak fixture met klein CSV/sample images; assert shapes (batch, C, H, W), dtype (`torch.float32`), and label dtypes; test edge-cases (empty, corrupted file) met mocks.

7) `state_dict()` voordeel: portable, onafhankelijk van class-definities en minder afhankelijk van path/namespace issues; `torch.save(model)` picklet gehele object en kan version/namespace-sensitive zijn.

8) Veilig uploaden naar MinIO in CI: gebruik CI secrets (environment variables), gebruik ephemeral credentials, upload artifact met authenticated step, verwijder lokale secrets uit logs, en beperk bucket policy.

9) CPU-only performance tips: (a) gebruik smaller precision (float16) of quantization, (b) fuse ops en gebruik ONNXRuntime met OpenMP tuned, (c) verminder model size of batch parallelisme.

10) `map_location` nut: converteert tensors naar het juiste device bij laden; voorbeeld fout: attempt to deserialize object on CUDA device when CUDA is not available -> RuntimeError als checkpoint GPU tensors bevat en je op CPU probeert te laden zonder `map_location='cpu'`.
