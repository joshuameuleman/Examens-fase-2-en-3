Open oefenvragen — Edge Deployment

1) Leg uit wat er kan misgaan als je audio niet naar de verwachte sample rate resampled vóór model-inference. Geef een stappenplan om dit te debuggen.

2) Bekijk dit opnamevoorbeeld en beschrijf hoe je latency en dropouts minimaliseert op een Raspberry Pi:
```python
rec = sd.rec(int(duration*sr), samplerate=sr, channels=1)
sd.wait()
write('out.wav', sr, rec)
```

3) Leg in detail uit het verschil tussen `torch.jit.trace` en `torch.jit.script` en geef een voorbeeld wanneer tracing faalt.

4) Beschrijf de rol van `dynamic_axes` bij ONNX-export en geef een concreet voorbeeld van wanneer je dat nodig hebt.

5) Geef de stappen om een Whisper-model te quantizen voor ARM CPU (wat controleer je na quantization?).

6) Leg uit hoe je een geëxporteerd model valideert op gelijkheid met het origineel (testcases, tolerantie, random seeds).

7) Geef drie problemen die optreden bij het installeren van grote native-deps op edge devices en hoe je ze oplost.

8) Beschrijf welke runtime (TorchScript, ONNXRuntime, TFLite) je kiest voor een gegeven edge-usecase en waarom.

9) Leg uit hoe je streaming ASR (online transcription) anders implementeert dan batch ASR.

10) Beschrijf welke metrics je monitort na deployment van een on-device model en hoe je regressies detecteert.

Antwoorden (kort)

1) Debug sample rate: mismatch leidt tot wrong spectrograms; debug met: (a) print sample rates after load, (b) resample explicitly with torchaudio or librosa, (c) validate on known audio examples.

2) Latency/dropouts minimisatie: gebruik smaller buffer sizes, realtime priority for audio thread, avoid heavy Python ops on capture path, stream processing rather than full-file write.

3) `trace` vs `script`: trace registreert executed ops for given input shapes — faalt on input-dependent Python control-flow; script compiles Python code to TorchScript IR.

4) `dynamic_axes` voorbeeld: ONNX with variable `seq_len` for ASR inputs so model accepts varying-length spectrograms at inference.

5) Quantize Whisper for ARM: post-training static quantization or dynamic quantization; verify Per-layer output and WER on validation set after quantization.

6) Validate exported model equality: run fixed test set (deterministic seed), compare outputs with tolerance (e.g., L2 or exact for int8-aware ops), check shape and types.

7) Native-deps problems: incompatible binary wheels, long compile times, missing cross-compile toolchain — solve with prebuilt wheels, docker buildx, or use lightweight runtimes.

8) Runtime choice: TorchScript for PyTorch-centric flows, ONNXRuntime for cross-framework speed and optimizer support, TFLite for very small/ARM devices — choose by supported ops and perf.

9) Streaming ASR: incremental feature extraction + chunked inference with overlapping context and stateful encoder; differs from batch where entire audio is processed at once.

10) Post-deploy metrics: latency p95, memory, CPU usage, accuracy/WER, error rates; detect regressions via baselining and alerts on drift of metrics beyond thresholds.
