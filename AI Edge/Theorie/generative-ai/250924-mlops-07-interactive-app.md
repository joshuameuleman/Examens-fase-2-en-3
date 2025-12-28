**`07-interactive-app` — Uitleg en examenvragen**

Locatie: `250924-mlops-workshops/generative-ai/07-interactive-app/interactive-story.ipynb`

Korte omschrijving
- Interactieve notebook die gebruikers input combineert met model prompts om verhaallijnen te maken en iteratief te verfijnen.

Belangrijke onderdelen
- State management between cells / callbacks
- Prompt-chaining: output van model A als input voor model B
- Simple UI controls inside notebooks (widgets)

Control flow
1. User provides seed story or choices
2. Notebook builds prompt segments and calls model(s)
3. Model outputs worden getoond en kunnen aangepast door gebruiker
4. Iteratief verdere prompts genereren

Code snippet (prompt chaining)

```python
scene = generate_text(scene_prompt)
character_prompt = f"Given the scene: {scene}, write dialog for character X"
dialog = generate_text(character_prompt)
```

Concepten om te beheersen
- Prompt engineering for multi-step pipelines
- Latency and UX considerations for notebook demos
- Using small models locally vs remote APIs for responsiveness

Mogelijke examenvragen
- "Wat is prompt-chaining en wanneer gebruik je het?"
- "Hoe balanceer je model-call kosten en interactieve UX in notebooks?"
- "Noem twee manieren om state in een notebook-demo persistent te maken."