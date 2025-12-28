**`02-whisper-huggingface.py` — Uitleg en examenvragen**

Locatie: `250924-mlops-workshops/edge-deployment/05-explore-whisper/02-whisper-huggingface.py`

Korte omschrijving
- Script dat een Whisper-model laadt via Hugging Face en audio transcribeert naar tekst.

Belangrijke onderdelen
- Model loading: `from transformers import WhisperForConditionalGeneration, WhisperProcessor` of Hugging Face `pipeline("automatic-speech-recognition")`
- Preprocessing: resampling audio, normalisatie, feature extraction (log-mels)
- Inference: model.generate / model.forward → logits → decode tokens

Control flow
1. Load audio file → resample to model sr
2. Preprocess via processor (feature extract)
3. Run model inference (with torch.no_grad())
4. Decode output tokens to text

Code snippet (conceptueel)

```python
from transformers import pipeline
asr = pipeline("automatic-speech-recognition", model="openai/whisper-small")
res = asr("out.wav")
print(res['text'])
```

Annotated snippet (regel-voor-regel)

```
# 1. from transformers import pipeline
#    - convenience factory that wires tokenizer + processor + model.
# 2. asr = pipeline("automatic-speech-recognition", model="openai/whisper-small")
#    - loads model + processor; processor handles resampling/feature extraction when possible.
# 3. res = asr("out.wav")
#    - pipeline reads file, preprocesses audio, runs model.generate/infer, and decodes tokens to text.
# 4. print(res['text'])
#    - prints the transcription string from pipeline output.
```

Exam hint: If asked why resampling matters, say: processor expects model sample rate; mismatch yields wrong spectrogram alignment and bad transcriptions.

Concepten om te beheersen
- Waarom resampling en correct padding belangrijk zijn
- Beam search of greedy decoding voor ASR outputs
- Model export/quantization opties voor edge (int8, float16)

Mogelijke examenvragen
- "Wat doet de Whisper processor bij preprocessing?"
- "Waarom kun je voordeel halen uit quantization op edge devices?"
- "Noem twee manieren om latency te verminderen bij ASR inference."