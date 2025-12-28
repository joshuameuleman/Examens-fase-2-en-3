**Generative AI — Samenvatting van oefeningen en code**

Locatie: `250924-mlops-workshops/generative-ai`

Hoofdonderdelen en notebooks:
- `01-first-language-model/`: basisprincipes van taalmodellen en inference.
- `02-storytelling-assistant/`: opzet van een assistant voor verhaalcreatie; prompt design en conversatiegeschiedenis.
- `03-add-input-image/`: multimodale prompts met afbeeldingen; beeldpreprocessing en feature-extractors.
- `04-multi-part-stories/` en oplossing: state management voor langere verhalen en het combineren van prompts over meerdere stappen.
- `05-generated-images/` en oplossing: image-generation notebooks — API-calls, sampling, en seeding.
- `06-simple-gradio-app/` en oplossing: bouw van eenvoudige Gradio-apps (`06a`..`06d`) voor text-to-text, image-gen en chat met geschiedenis.
- `07-interactive-app/` en oplossing: interactieve notebooks en gebruikersflow.
- `08-other-modalities/`: audio-transcription, text-to-speech, music generation, document answering, grounding (DINO).

Concepten om te beheersen:
- Prompt engineering, chat-context, system/user messages
- Tokenization, temperature, sampling vs deterministic decoding
- Multimodale pipeline: image/audio preprocessing en model I/O
- Quick deployment of notebook demos with Gradio

Studietips: open elk notebook en volg de cellen; wees in staat uit te leggen welke input preprocessing gebeurt, welke model-API's worden aangeroepen, en hoe outputs worden gepostprocessed of weergegeven in de UI.
