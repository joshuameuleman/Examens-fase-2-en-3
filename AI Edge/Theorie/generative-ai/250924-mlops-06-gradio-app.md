**`06-simple-gradio-app` — Uitleg en examenvragen**

Locatie: `250924-mlops-workshops/generative-ai/06-simple-gradio-app/` (06a..06d notebooks)

Korte omschrijving
- Demonstraties van eenvoudige Gradio-apps: text-to-text LLM, image generation, vision-to-text, chatbot met geschiedenis.

Belangrijke onderdelen
- Gradio interfaces: `gr.Interface` / `gr.Blocks`
- Input handlers: text inputs, image uploads, sliders for temperature
- State management for chat (maintaining conversation history)
- Backend calls to model.generate or image APIs

Control flow (example — chatbot with history)
1. User inputs text → append to history
2. Build prompt (system + history + user)
3. Call model.generate with prompt
4. Append model reply to history and return updated UI

Code snippet (chat history pattern)

```python
history = []

def respond(user_message):
    history.append({"role": "user", "content": user_message})
    prompt = build_prompt(history)
    reply = generate_text(prompt)
    history.append({"role": "assistant", "content": reply})
    return reply, history
```

Concepten om te beheersen
- Stateless vs stateful apps (where to store history)
- Latency implications of synchronous blocking calls
- Securing API keys when deploying (server-side calls vs client)

Mogelijke examenvragen
- "Hoe bewaar je conversatiegeschiedenis veilig in een Gradio-app?"
- "Waarom kun je model-calls niet direct vanaf de browser doen als je een geheime API-key gebruikt?"
- "Leg uit hoe je streaming responses (token-by-token) in Gradio zou integreren."