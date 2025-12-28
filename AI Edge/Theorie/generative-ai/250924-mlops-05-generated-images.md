**`05-generated-images` — Uitleg en examenvragen**

Locatie: `250924-mlops-workshops/generative-ai/05-generated-images/` (notebooks en oplossingen)

Korte omschrijving
- Image-generation notebooks: pipeline voor prompt → model call → image sampling → postprocessing and display.

Belangrijke onderdelen
- Prompt formatting for image models (text + optional conditioning)
- Sampling parameters: seed, guidance_scale, steps
- Image postprocessing: denormalize, convert to PIL, save/show

Control flow
1. Build prompt (possibly with negative prompts)
2. Call image-generation API (local model or remote service)
3. Receive image tensors → postprocess → show/save

Code snippet (conceptueel)

```python
images = image_model.generate(prompt=prompt, num_images=1, seed=42, guidance_scale=7.5)
pil = to_pil(images[0])
pil.save("out.png")
```

Concepten om te beheersen
- Determinisme via seed; reproducibility
- Trade-offs: higher guidance_scale = more faithful to prompt but less diversity
- Ethics and filtering (NSFW checks) when generating images

Mogelijke examenvragen
- "Wat doet `guidance_scale` bij classifier-free guidance?"
- "Waarom is het nuttig om een seed te gebruiken bij experiments?"
- "Hoe zou je batch-generate images efficiënt op GPU doen?"