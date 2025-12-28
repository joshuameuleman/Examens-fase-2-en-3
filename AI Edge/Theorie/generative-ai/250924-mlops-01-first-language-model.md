**`01-first-language-model` — Uitleg en examenvragen**

Locatie: `250924-mlops-workshops/generative-ai/01-first-language-model/README.md`

Korte omschrijving
- Introductie tot basisprincipes van taalmodellen: tokenisatie, logits, softmax, en eenvoudige inference.

Belangrijke onderdelen
- Tokenizer usage: text → token ids → attention mask
- Model.forward: input_ids, attention_mask → logits → softmax → predicted tokens
- Decoding: greedy vs beam search vs sampling (temperature/top-k/top-p)

Control flow (hoog niveau)
1. Preprocess: text → tokens
2. Model inference: logits genereren
3. Decode: logits → tokens → text
4. Postprocess: strip special tokens, detokenize

Code snippet (verwacht patroon)

```python
inputs = tokenizer(prompt, return_tensors="pt")
with torch.no_grad():
    outputs = model.generate(**inputs, max_length=100, temperature=0.8)
result = tokenizer.decode(outputs[0], skip_special_tokens=True)
```

Annotated snippet (regel-voor-regel)

```
# 1. inputs = tokenizer(prompt, return_tensors="pt")
#    - tokenizes text to input_ids tensor and attention_mask; returns batched tensors.
# 2. with torch.no_grad():
#    - disables gradient tracking for inference to save memory/compute.
# 3. outputs = model.generate(**inputs, max_length=100, temperature=0.8)
#    - autoregressively generate tokens until max_length or EOS; `temperature` scales logits before softmax for sampling.
# 4. result = tokenizer.decode(outputs[0], skip_special_tokens=True)
#    - convert token ids back to string and remove special tokens like <pad>/<eos>.
```

Exam hint: when asked to explain `temperature`, say: it scales logits -> softmax; temperature <1 sharpens distribution (more greedy), >1 flattens (more diverse).

Concepten om te beheersen
- Waarom tokenizers belangrijk zijn (vocab size, OOV handling)
- Effect van temperature en nucleus sampling op output-diversiteit
- Context length en kosten (compute & memory)

Mogelijke examenvragen
- "Leg het verschil uit tussen greedy decoding en nucleus sampling." 
- "Wat doet de attention mask en waarom is die nodig?"
- "Waarom kan een langere context length leiden tot hogere latency en meer geheugenverbruik?"