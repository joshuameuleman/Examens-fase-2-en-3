**`model_utils.py` — Uitleg en examenvragen**

Locatie: `250924-mlops-workshops/ml-infrastructure/02-refactor-the-notebook/model_utils.py`

Korte omschrijving
- Bouwt modelarchitectuur (pretrained backbone + custom classifier), en bevat helpers om checkpoints te laden en op te slaan.

Belangrijke functies
- `create_model(num_classes)`
  - Laadt een pretrained `MobileNetV3` (of andere backbone)
  - Vervangt de classifier / final layer met `nn.Linear` passend bij `num_classes`
  - Initieert eventueel weights voor classifier
- `save_model(model, path)`
  - Roept `torch.save(model.state_dict(), path)` aan (voorkeur voor state_dict)
- `load_model(num_classes, path)`
  - Maakt een model met `create_model(num_classes)` en laadt `state_dict` met `map_location` indien nodig

Control flow
1. Config / num_classes ophalen
2. `create_model` aanroepen → model klaar
3. (optioneel) `load_model` met checkpoint voor inference

Concepten om te beheersen
- `state_dict()` vs `torch.save(model)` en waarom `state_dict` aanbevolen is
- Device mapping: `map_location=torch.device('cpu')` bij laden op CPU
- `model.train()` vs `model.eval()` en waarom dat matter
- Fine-tuning vs feature-extraction (welke lagen trainbaar maken)

Korte code-voorbeeld (verwachte implementatie)

```python
from torchvision.models import mobilenet_v3_small, MobileNet_V3_Small_Weights
import torch.nn as nn
import torch

def create_model(num_classes):
    weights = MobileNet_V3_Small_Weights.DEFAULT
    model = mobilenet_v3_small(weights=weights)
    in_features = model.classifier[3].in_features
    model.classifier[3] = nn.Linear(in_features, num_classes)
    return model

def save_model(model, path="model.pth"):
    torch.save(model.state_dict(), path)

def load_model(num_classes, path="model.pth"):
    model = create_model(num_classes)
    model.load_state_dict(torch.load(path, map_location=torch.device('cpu')))
    return model
```

Mogelijke examenvragen
- "Waarom is `state_dict()` vaak beter voor portability?"
- "Wat gebeurt er als je `model.eval()` vergeet tijdens inference?"
- "Wanneer zou je alleen de classifier trainen i.p.v. het hele netwerk?"