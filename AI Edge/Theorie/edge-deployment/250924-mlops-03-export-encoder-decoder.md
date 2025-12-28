**`03-export-encoder-decoder.py` — Uitleg en examenvragen**

Locatie: `250924-mlops-workshops/edge-deployment/05-explore-whisper/03-export-encoder-decoder.py`

Korte omschrijving
- Script om modelcomponenten (encoder/decoder) te exporteren naar portable formats (TorchScript, ONNX) voor deployment op edge devices.

Belangrijke onderdelen
- Trace vs script: `torch.jit.trace` vs `torch.jit.script`
- ONNX export: `torch.onnx.export(model, dummy_input, out_path, opset_version=...)`
- Input/output signatures: maak expliciete shapes en dtypes voor compatibiliteit

Control flow
1. Laad getraind model in eval-mode
2. Bouw dummy inputs met correcte shapes en device
3. Export naar TorchScript of ONNX met juiste flags (example: dynamic axes voor variabele lengtes)

Code snippet (TorchScript voorbeeld)

```python
model.eval()
dummy = torch.randn(1, 80, 300)  # example spectrogram shape
traced = torch.jit.trace(model.encoder, dummy)
traced.save('encoder.pt')
```

Concepten om te beheersen
- Dynamic axes in ONNX voor sequenties
- Waarom je model in `eval()` moet zetten voor export
- Compatibiliteitsproblemen tussen opset versions en runtimes

Mogelijke examenvragen
- "Wat is het verschil tussen `torch.jit.trace` en `torch.jit.script`?"
- "Waarom moeten dummy inputs de juiste dtypes en shapes hebben bij export?"
- "Wanneer gebruik je ONNX i.p.v. TorchScript?"