**`requirements.txt` — Dependencies and rationale**

Locatie: `250924-mlops-workshops/edge-deployment/05-explore-whisper/requirements.txt`

Korte omschrijving
- Beschrijving van typische dependencies en waarom ze nodig zijn voor de Whisper/Audio workflow.

Meestal voorkomende packages
- `torch`, `torchaudio` — model runtime en audio ops
- `transformers` — model wrappers en processors
- `sounddevice` of `pyaudio` — audio capture
- `scipy` — I/O (wav), signal processing
- `onnxruntime` of `torchscript` runtime — inference op edge

Rationale en aandachtspunten
- Versiecompatibiliteit tussen `torch` en CUDA/onnxruntime
- Op edge devices kun je kiezen voor lichtere runtimes (onnxruntime, tflite)
- Beperk libraries die veel native bindings vereisen op constrained devices

Mogelijke examenvragen
- "Waarom wil je `onnxruntime` gebruiken op sommige edge devices?"
- "Wat is een risico van het installeren van grote C-extension packages op een Raspberry Pi?"
- "Hoe controleer je dat je geïnstalleerde runtime GPU ondersteunt?"