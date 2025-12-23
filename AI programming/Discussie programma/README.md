# Discussie programma - Hoe run ik de scripts

Deze map bevat vier kleine Python-demo's die datastructuren laten zien:

- `array_program.py` - demo van een Python list (array)
- `linked_list_program.py` - eenvoudige singly linked list implementatie
- `queue_program.py` - demo van een FIFO queue met `collections.deque`
- `stack_program.py` - demo van een LIFO stack met een Python list

Stappen om de scripts te runnen (Windows PowerShell):

1. Zorg dat je Python 3.8+ hebt geïnstalleerd. Je kunt dit controleren met:

```powershell
python --version
```

2. Open PowerShell in deze map (`Discussie programma`). Bijvoorbeeld in Verkenner: Shift + rechtermuisklik -> "Open PowerShell-venster hier".

3. Run één script met:

```powershell
python .\array_program.py
python .\linked_list_program.py
python .\queue_program.py
python .\stack_program.py
```

Voorbeelden met eigen aantal elementen:

```powershell
# Precies 3 elementen
python .\array_program.py --count 3

# Gebruik een bereik 2..6
python .\stack_program.py --min 2 --max 6

# Run alle scripts met run_all (let op: run_all gebruikt de scripts zoals ze zijn;
# je kunt individuele scripts ook apart runnen met --count)
python .\run_all.py
```

NumPy voorbeeld:

```powershell
# Gebruik NumPy voor de array-output (vereist numpy geïnstalleerd)
python .\array_program.py --count 5 --use-numpy
```

Let op: `array_program.py` is nu volledig herschreven en vereist NumPy.
Installeer NumPy met:

```powershell
python -m pip install numpy
```

Run het script:

```powershell
python .\array_program.py --count 5
# of: interactive
python .\array_program.py
```

Opmerking: de andere demo scripts (`linked_list_program.py`, `queue_program.py`, `stack_program.py`) gebruiken nu ook NumPy om waarden te genereren.

Voorbeeld:

```powershell
python .\linked_list_program.py --count 5
python .\queue_program.py --count 6
python .\stack_program.py --count 4
```

4. (Optioneel) Run alle scripts na elkaar met:

```powershell
python .\run_all.py
```

Veelvoorkomende problemen:
- Als `python` niet gevonden wordt: controleer of Python in je PATH staat of gebruik het volledige pad naar `python.exe`.
- Als modules ontbreken: deze scripts gebruiken alleen de Python-standaardbibliotheek.

Heb je specifieke wensen (bijv. extra argumenten of output naar een bestand)? Laat het weten.
