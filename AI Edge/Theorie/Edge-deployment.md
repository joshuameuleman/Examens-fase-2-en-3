# Edge AI Deployment — Samenvatting (Nederlands)

## Course overview
Deze cursus behandelt technieken om ML-modellen efficiënt en betrouwbaar op edge-apparaten te draaien: hardwarekeuze, modeloptimalisatie (quantization, pruning, distillation), export naar ONNX, inference runtimes (ONNX Runtime, TensorRT) en geavanceerde workflow-tools.

## Belangrijke thema's

- Introductie tot Edge AI: motivaties (latency, bandbreedte, privacy, betrouwbaarheid) en wanneer edge gepast is.
- Hardware-overzicht: MCUs (TinyML), single-board computers, embedded GPUs, NPUs, externe accelerators (Hailo), FPGAs, IPCs en PLCs — plus tooling/SDK-ecosystemen.
- Modeloptimalisatie: post-training quantization (PTQ), quantization-aware training (QAT), pruning (gestructureerd & ongestructureerd), sparsity (2:4), operator fusion en graph-level optimalisaties.
- Lightweight modellen: architecturen en ontwerpprincipes voor beeld-, audio- en time-series-taken op het edge.
- Export & interoperabiliteit: ONNX-formaat (opset, protobuf), inspectie met `onnx` API en Netron, veelvoorkomende export-pitfalls (tracing vs scripting, dynamic_axes, eval mode).
- Efficiënte inference: ONNX Runtime — execution providers (CPU, CUDA, TensorRT, OpenVINO), quantize_dynamic/quantize_static voorbeelden en provider selectie.
- High-performance: TensorRT engine-builds, tactic selection, workspace sizing, FP16/INT8, geheugenbeheer en uitvoering met pycuda.
- Geavanceerde optimalisaties: Model Optimizer workflows, QAT, structured pruning, en fine-tuning workflows voor productie-inference.

## Praktische aandachtspunten voor examen

- Leg uit waarom quantization snelheid en geheugen verbetert, en benoem trade-offs (accurateiteitsverlies, calibratie dataset). 
- Ken de verschillen tussen PTQ en QAT en wanneer je welke gebruikt.
- Wees in staat ONNX-exportopties te interpreteren (`dynamic_axes`, `do_constant_folding`) en foutbronnen te herkennen (in-place ops, device mismatch).
- Beschrijf TensorRT-buildstappen en waarom runtime memory/engine-serialisatie belangrijk is.

---
Bron: samengevoegd en vertaald uit de cursuspagina "Edge AI Deployment" (mlops4ecm.be).

