**Edge Deployment README — Uitleg en examenvragen**

Locatie: `250924-mlops-workshops/edge-deployment/README.md`

Korte omschrijving
- Overzicht van edge deployment-oefeningen: opnemen van audio, lokale inferentie met Whisper, model export en optimalisaties voor edge.

Belangrijke punten
- Workflow: data capture → preprocessing → model inference → export/optimize
- Deployment targets: Raspberry Pi, Jetson, ARM-based devices
- Optimalisaties: quantization, pruning, operator fusion, model sharding

Concepten om te beheersen
- Welke optimalisaties goed werken op CPU vs GPU
- Betekenis van operator fusion en waarom het runtime-beïnvloedt
- Cross-compilation en runtime afhankelijkheden (libtorch, ONNXRuntime)

Mogelijke examenvragen
- "Noem drie optimalisaties om een model kleiner en sneller te maken voor edge deployment." 
- "Wat zijn typische bottlenecks bij on-device ASR?"
- "Hoe test je of een geëxporteerd model produceert hetzelfde resultaat als het originele model?"