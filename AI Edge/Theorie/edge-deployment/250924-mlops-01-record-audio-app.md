**`01-record-audio-app.py` — Uitleg en examenvragen**

Locatie: `250924-mlops-workshops/edge-deployment/05-explore-whisper/01-record-audio-app.py`

Korte omschrijving
- Eenvoudige audio opname-app: opent microfoon input, neemt sample frames op en slaat naar bestand (wav).

Belangrijke onderdelen
- Audio capture libraries (sounddevice, pyaudio)
- Parameters: sample rate, channels, dtype, chunk size
- Opslaan: WAV bestandsformat (bits per sample, headers)

Control flow
1. Configureer opname (sr, duration)
2. Start opname stream, verzamel buffers
3. Converteer naar juiste numpy dtype en schrijf naar wav bestand

Code snippet (verwacht patroon)

```python
import sounddevice as sd
from scipy.io.wavfile import write
sr = 16000
duration = 5
rec = sd.rec(int(duration*sr), samplerate=sr, channels=1)
sd.wait()
write('out.wav', sr, rec)
```

Concepten om te beheersen
- Waarom juiste sampling rate en bit depth belangrijk zijn voor ASR
- Latency en buffer-grootte trade-offs voor realtime capture
- File format metadata (sample rate, channels)

Mogelijke examenvragen
- "Waarom kies je 16 kHz of 16-bit PCM voor veel ASR workflows?"
- "Wat gebeurt er als je de sample rate mismatched tussen opname en model input?"
- "Hoe minimaliseer je capture-latency op een edge device?"