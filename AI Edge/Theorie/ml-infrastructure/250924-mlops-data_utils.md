**`data_utils.py` — Uitleg en examenvragen**

Locatie: `250924-mlops-workshops/ml-infrastructure/02-refactor-the-notebook/data_utils.py`

Korte omschrijving
- Verantwoordelijk voor: inlezen van dataset, preprocessing per item, en het aanmaken van `DataLoader`-objecten voor training en validatie.

Belangrijke functies / classes (verwachte implementatie)
- `get_classes()`
  - Leest label-definities (bv. CSV of JSON) en retourneert een mapping {int: class_name}.
- `GroceryDataset` (Dataset subclass, verwacht)
  - `__init__(csv_path, transform=None)`: bewaart rij-data en transform
  - `__len__()`: aantal voorbeelden
  - `__getitem__(idx)`: laadt image via `PIL.Image.open`, past `transform` toe en retourneert (image, label)
- `get_loaders(batch_size=32)`
  - Bouwt `train` en `val` dataset-instanties
  - Maakt `DataLoader`-objecten met `shuffle=True` voor training en `shuffle=False` voor validatie

Control flow (hoog niveau)
1. Labels/class-namen inladen (`get_classes`)
2. CSV of map met bestandsnamen en labels inlezen
3. Transform-definities (resize, ToTensor, Normalize, augmentaties) bepalen
4. Dataset-object(en) aanmaken
5. `DataLoader` teruggeven

Concepten om te beheersen
- `torch.utils.data.Dataset` vs `DataLoader`
- Transforms: normalisatie, augmentatie en waarom train/val verschillen
- Collate-functies bij variabele-lengte inputs
- Determinisme: seeding, `shuffle`, `num_workers` en pin_memory

Kort code-voorbeeld (verwacht patroon)

```python
from torch.utils.data import DataLoader
from torchvision import transforms

def get_loaders(batch_size=32):
    transform_train = transforms.Compose([...])
    transform_val = transforms.Compose([...])

    train_ds = GroceryDataset("train.csv", transform=transform_train)
    val_ds = GroceryDataset("val.csv", transform=transform_val)

    train_loader = DataLoader(train_ds, batch_size=batch_size, shuffle=True, num_workers=4)
    val_loader = DataLoader(val_ds, batch_size=batch_size, shuffle=False, num_workers=4)
    return train_loader, val_loader
```

Annotated `get_loaders` verklaring

```
def get_loaders(batch_size=32):
  # 1. define transforms for train/val: train may include augmentations (random crop/flip)
  #    while val uses deterministic transforms (center crop, resize, normalize).
  transform_train = transforms.Compose([...])
  transform_val = transforms.Compose([...])

  # 2. create Dataset objects that lazily load samples on __getitem__
  train_ds = GroceryDataset("train.csv", transform=transform_train)
  val_ds = GroceryDataset("val.csv", transform=transform_val)

  # 3. DataLoader wraps datasets and manages batching and parallel workers
  #    - shuffle=True for training for randomization
  #    - num_workers > 0 uses subprocesses to load batches in parallel
  train_loader = DataLoader(train_ds, batch_size=batch_size, shuffle=True, num_workers=4, pin_memory=True)
  val_loader = DataLoader(val_ds, batch_size=batch_size, shuffle=False, num_workers=4, pin_memory=True)
  return train_loader, val_loader
```

Exam hints:
- Controleer dat `GroceryDataset.__getitem__` altijd `PIL.Image` -> `transform` -> `tensor` returnt en labels als ints.
- Als batches variabele sequenties bevatten, implementeer een `collate_fn` die paddt naar max length binnen de batch.

Mogelijke examenvragen
- "Wat is het verschil tussen `Dataset` en `DataLoader`?"
- "Waarom gebruik je andere transforms voor training en validatie?"
- "Leg uit wat `num_workers` doet en welke trade-offs er zijn."

Waarom dit belangrijk
- Data pipeline bugs veroorzaken vaak slechte training of nondeterministisch gedrag — examenvragen richten zich vaak op het correct lezen en verklaren van preprocessing en batching.
