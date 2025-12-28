**`run_training.py` — Uitleg en examenvragen**

Locatie: `250924-mlops-workshops/ml-infrastructure/02-refactor-the-notebook/run_training.py`

Korte omschrijving
- Script om een model te trainen: parse arguments (batch-size, epochs, lr, output), laad data en model, train en sla checkpoint op.

Verwachte training flow (pseudocode)

```python
train_loader, val_loader = get_loaders(batch_size=args.batch_size)
model = create_model(num_classes)
optimizer = torch.optim.Adam(model.parameters(), lr=args.learning_rate)
criterion = torch.nn.CrossEntropyLoss()
for epoch in range(args.epochs):
    model.train()
    for images, labels in train_loader:
        images, labels = images.to(DEVICE), labels.to(DEVICE)
        optimizer.zero_grad()
        outputs = model(images)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()
    # run validation, print metrics, optionally save checkpoint
save_model(model, path=args.output)
```

Concepten om te beheersen
- Volgorde: `optimizer.zero_grad()` → `loss.backward()` → `optimizer.step()`
- Waarom `model.train()` en `model.eval()` nodig zijn
- Checkpointing: wat opslaan (model state, optimizer state, epoch)
- Early stopping, LR schedulers, mixed precision (AMP) als efficiency-opties

Mogelijke examenvragen
- "Leg uit waarom je `optimizer.zero_grad()` vóór `loss.backward()` moet aanroepen."
- "Wat sla je idealiter op in een checkpoint zodat je training kunt hervatten?"

Annotated training loop (regel-voor-regel)

1) `train_loader, val_loader = get_loaders(...)` — zet data pipelines klaar; `train_loader` yieldt batches (images, labels).
2) `model = create_model(num_classes)` — bouwt en initialiseerd netwerk op CPU/GPU.
3) `optimizer = torch.optim.Adam(...)` — houdt param-groepen en learning rate.
4) `criterion = torch.nn.CrossEntropyLoss()` — loss voor classificatie (logits → target indices).
5) `for epoch in ...` — outer loop over epochepochs.
6) `model.train()` — zet layers in training mode (dropout aan, BatchNorm updaten).
7) `for images, labels in train_loader:` — per-batch: `images` shape [B, C, H, W], `labels` shape [B].
8) `images, labels = images.to(DEVICE), labels.to(DEVICE)` — verplaats naar GPU indien beschikbaar, belangrijk voor performance.
9) `optimizer.zero_grad()` — reset gradients; moet vóór `loss.backward()` zodat oude grads niet opstapelen.
10) `outputs = model(images)` — forward pass, produceert logits shape [B, num_classes].
11) `loss = criterion(outputs, labels)` — bereken scalar loss.
12) `loss.backward()` — backpropagate; gradients worden in `.grad` attributen van parameters gezet.
13) `optimizer.step()` — update parameters op basis van gradients en optimizer state.
14) (optional) validation loop: `model.eval()` + `torch.no_grad()` run to compute metrics.
15) `save_model(...)` — bewaar `state_dict()` en eventueel optimizer state.

Kort antwoord op checklist vraag (optimizer.zero_grad): moet vóór backward om oude gradients te wissen; anders accumulatie.