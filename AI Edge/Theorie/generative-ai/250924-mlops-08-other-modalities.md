**`08-other-modalities` — Uitleg en examenvragen**

Locatie: `250924-mlops-workshops/generative-ai/08-other-modalities/`

Korte omschrijving
- Notebooks voor audio transcription, text-to-speech, music generation, document question-answering en grounding (DINO).

Belangrijke onderdelen
- Audio transcription: audio preprocessing (sampling rate, mel spectrograms) en ASR model inference
- Text-to-speech: vocoder usage, waveform generation and playback
- Document QA: chunking long documents, embeddings + retriever + reader pattern (RAG)
- Vision grounding: object detection + grounding models integration

Control flow voorbeelden
- Audio transcription: read WAV → resample → feature extract → model.transcribe → decode
- Document QA: split doc → encode chunks → retrieve top-k → pass to reader for final answer

Concepten om te beheersen
- RAG pattern: retrieval + generation
- Chunking strategies and overlap to retain context
- Trade-offs for on-device audio models vs cloud APIs

Mogelijke examenvragen
- "Leg het RAG-patroon uit en waarom het nuttig is voor lange documenten."
- "Waarom gebruik je overlap bij chunking en wat is de trade-off?"
- "Wat moet je checken bij het voorbehandelen van audio voor ASR?"