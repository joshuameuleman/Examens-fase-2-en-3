Open oefenvragen — Generative AI

1) Leg uit wat elke stap doet in dit generatiesnippet en waarom `temperature` invloed heeft:
```python
inputs = tokenizer(prompt, return_tensors='pt')
outputs = model.generate(**inputs, max_length=100, temperature=0.9)
text = tokenizer.decode(outputs[0], skip_special_tokens=True)
```

2) Geef drie verschillen tussen greedy decoding, beam search en nucleus sampling en wanneer je elk gebruikt.

3) Bekijk dit Gradio-chatpatroon en leg uit hoe je conversatiegeschiedenis veilig en schaalbaar zou bewaren:
```python
history = []
def respond(msg):
    history.append(('user', msg))
    res = generate(build_prompt(history))
    history.append(('assistant', res))
    return res
```

4) Beschrijf de RAG-pipeline: welke componenten zijn er, welke fouten kunnen optreden bij retrieval, en hoe test je de kwaliteit.

5) Voor image-generation: leg uit wat `guidance_scale` doet en welke trade-offs er zijn bij het verhogen van deze waarde.

6) Geef een korte checklist van wat je controleert als een notebook-demo op jouw machine andere outputs produceert dan in de cursusoplossing.

7) Leg uit waarom tokenization fouten (wrong tokenizer) slecht uitpakken voor model-inference; hoe detecteer en corrigeer je dit.

8) Beschrijf drie manieren om latency in een interactieve notebook-demo te verminderen zonder de gebruikerservaring te schaden.

9) Leg uit hoe je streaming token-output (token-by-token) kunt implementeren en welke UX-issues dit kan oplossen.

10) Noem ethische checks die je inbouwt in een image- of text-generation pipeline (2–3 items) en hoe je ze technisch toepast.

Antwoorden (kort)

1) Stap-uitleg snippet: tokenizer -> model.generate -> decode. `temperature` beïnvloedt softmax logits scaling: hogere temperature → meer probabilistische sampling.

2) Greedy vs beam vs nucleus: Greedy is snel/deterministisch, beam zoekt top-k hypotheses (meer quality) en nucleus sampling kiest uit top-p mass voor diversiteit.

3) Conversatiegeschiedenis schaalbaar bewaren: gebruik server-side session store (Redis) met size limits and TTL; niet in-memory per-process voor schaal.

4) RAG-pipeline: encoder (embeddings) → vector DB (FAISS/Annoy) → retriever (top-k) → reader (LLM). Errors: bad chunks, mismatch embedding model. Test met holdout QA pairs and retrieval metrics (recall@k).

5) `guidance_scale` (classifier-free guidance): hogere waarde dwingt model closer to prompt but reduces diversity; technisch mix van unconditional and conditional scores.

6) Notebook-demo mismatch checklist: seed, model version, tokenizer, dependencies, and preprocessing (normalization, resizing).

7) Wrong tokenizer effects: token IDs mismatch leading to wrong embeddings; detect via inconsistent token lengths/unknown tokens; fix by using same tokenizer version and vocab.

8) Latency tips: caching partial results, asynchronous calls, smaller local model for interactive steps.

9) Streaming token-output: use model.generate with streaming API or step-by-step decode loop; UX: show incremental output, handle edits and partial tokens.

10) Ethical checks: content filter (toxicity/NSFW classifier), rate limits and user reporting; enforce via post-generation classifiers and blocklists.
