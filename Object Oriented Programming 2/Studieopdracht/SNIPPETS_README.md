Waar zet je dit snippets-bestand?

1) Workspace (aanbevolen voor dit project)
- Plaats het bestand `cpp_project.code-snippets` in de map `.vscode` in je project root:

  .vscode/cpp_project.code-snippets

- VS Code leest workspace snippets automatisch voor het project. Om een snippet te gebruiken: open een `.cpp`/`.h` bestand, typ de `prefix` (bijv. `weapon-h`) en druk `Tab`.

2) Globale (user) snippets
- Open de Command Palette (Ctrl+Shift+P) -> `Preferences: Configure User Snippets` -> kies `cpp.json` en plak de gewenste snippet-inhoud daar.
- Global snippets zijn beschikbaar in elk project.

Hoe gebruik je de snippets
- Open een C++ bestand (.cpp/.h).
- Typ de prefix (bijv. `weapon-h`) en druk Tab. Je kunt door de placeholders navigeren met Tab.

Extra tips
- De snippets in deze workspace bevatten tabstops zoals `${1:name}` zodat je snel de juiste velden invult.
- Als je de snippet wilt aanpassen: open `.vscode/cpp_project.code-snippets` en bewerk de JSON.

Als je wil, kan ik:
- extra, kleinere snippets toevoegen (bijv. for-loop, class boilerplate, unique_ptr), of
- de bestaande snippets exporteren naar je VS Code user snippets (als je dat wilt).