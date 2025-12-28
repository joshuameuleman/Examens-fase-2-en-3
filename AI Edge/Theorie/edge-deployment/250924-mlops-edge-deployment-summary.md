**Edge Deployment — Samenvatting van oefeningen en code**

Locatie: `250924-mlops-workshops/edge-deployment`

Belangrijkste onderdelen:
- `README.md`: overkoepelende uitleg van edge deployment-oefeningen.
- `05-explore-whisper/`:
  - `01-record-audio-app.py`: eenvoudige audio-opname en I/O; leer audio capture, formaten, en persistente opslag.
  - `02-whisper-huggingface.py`: laadt een Whisper-model (Hugging Face) en voert transcriptie uit; bestudeer model loading, tokenizers, en batching.
  - `03-export-encoder-decoder.py`: code om modelcomponenten te exporteren (bv. TorchScript/ONNX) voor deployment; belangrijk: serialisatie, input/output-interfaces en compatibiliteit.
  - `requirements.txt`: afhankelijkheden en runtimes.

Concepten om te beheersen voor het examen:
- Audio I/O (sampling rate, wav formaat)
- Model inference stappen: preprocess → model.forward → postprocess
- Model export en deployment formats (TorchScript, ONNX)
- Het verschil tussen training-time en inference-time code

Studietips: lees elk script en wees in staat om te beschrijven waarom en hoe de audio data verwerkt wordt, welke model-API's worden aangeroepen, en welke aanpassingen nodig zijn om op een edge device te draaien.
