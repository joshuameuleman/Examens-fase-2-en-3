# Examenmateriaal Praktijk - React

Bronnen: `Individueele opdrachten`, `klassikale_Oefeningen`, `Oef uit de les`, slides hoofdstuk 1-9 en `Master React in 5 days.pdf`.

Doel: dit document is bedoeld voor het open-boek programmeerdeel zonder internet. Gebruik het als snelle zoek- en kopieerbasis voor typische React-oefeningen.

## 0. Examenstrategie

Bij een oefening "from scratch":

1. Maak of open project.
2. Verwijder overbodige startercode.
3. Bepaal de state.
4. Bouw eerst werkende basis-UI.
5. Voeg handlers toe.
6. Voeg validatie toe.
7. Toon lijsten met `map`.
8. Gebruik stabiele `key`.
9. Splits pas daarna in componenten.
10. Test alle acties manueel.

Bij een bestaand project uitbreiden:

1. Lees eerst `App`, componentenmap en hooksmap.
2. Zoek waar de hoofdstate zit.
3. Zoek welke props naar child components gaan.
4. Voeg nieuwe functionaliteit toe op dezelfde manier als de bestaande code.
5. Verander geen projectstructuur als dat niet nodig is.

## 1. Projecten Starten

### Create React App

```bash
npm install
npm start
```

Typisch op `http://localhost:3000`.

### Vite React

```bash
npm install
npm run dev
```

Typisch op `http://localhost:5173`.

### PWA met Vite

```bash
npm install
npm run dev
npm run build
npm run preview
```

Gebruik `npm run preview` om service worker en manifest realistischer te testen.

### React Native / Expo

```bash
npm install
npm run android
```

Of:

```bash
npm run web
```

## 2. Basiscomponent

```jsx
function MyComponent() {
  return (
    <div>
      <h1>Titel</h1>
    </div>
  );
}

export default MyComponent;
```

Importeren:

```jsx
import MyComponent from "./MyComponent";
```

Gebruiken:

```jsx
<MyComponent />
```

## 3. Props

```jsx
function Greeting({ name, age }) {
  return (
    <p>
      {name} is {age} jaar.
    </p>
  );
}
```

```jsx
<Greeting name="Kurt" age={22} />
```

Belangrijk:

- Props zijn read-only in de child.
- Data aanpassen gebeurt meestal in de parent via state.
- Geef functies door als props wanneer een child iets in parent-state moet wijzigen.

## 4. useState

```jsx
import { useState } from "react";

function Counter() {
  const [count, setCount] = useState(0);

  function increment() {
    setCount((count) => count + 1);
  }

  return <button onClick={increment}>{count}</button>;
}
```

Gebruik functionele update wanneer de nieuwe waarde afhangt van de vorige waarde:

```jsx
setCount((count) => count + 1);
```

Niet doen:

```jsx
count++;
setCount(count + 1);
setCount(count + 1);
```

## 5. Events

### Click

```jsx
function handleClick() {
  console.log("clicked");
}

return <button onClick={handleClick}>Klik</button>;
```

Niet:

```jsx
<button onClick={handleClick()}>Klik</button>
```

### Met parameter

```jsx
<button onClick={() => removeItem(item.id)}>Remove</button>
```

### Form submit

Gebaseerd op de ticketreservatie-opdracht.

```jsx
function handleSubmit(event) {
  event.preventDefault();

  const trimmedName = visitorName.trim();
  const ticketCountNumber = Number(ticketCountInput);

  if (trimmedName === "") {
    setStatus({ kind: "error", message: "Vul uw naam in." });
    return;
  }

  if (!Number.isInteger(ticketCountNumber) || ticketCountNumber <= 0) {
    setStatus({ kind: "error", message: "Aantal moet positief geheel getal zijn." });
    return;
  }

  setStatus({ kind: "success", message: "Gelukt." });
}
```

## 6. Controlled Inputs

```jsx
function NameInput() {
  const [name, setName] = useState("");

  return (
    <input
      value={name}
      onChange={(event) => setName(event.target.value)}
    />
  );
}
```

Voor number input: bewaar de input vaak eerst als string, valideer pas bij submit.

```jsx
const [ticketCountInput, setTicketCountInput] = useState("");
const ticketCountNumber = Number(ticketCountInput);
```

## 7. Input Beperken Tot Cijfers

Uit `Oef uit de les/Chapter 3/input_field_allow_digits`.

```jsx
function keydown(event) {
  if (["Backspace", "Delete", "ArrowLeft", "ArrowRight", "Tab"].includes(event.key)) {
    return;
  }

  if (event.key < "0" || event.key > "9") {
    event.preventDefault();
  }
}

return <input type="text" onKeyDown={keydown} />;
```

## 8. Focus Met useRef

Uit ticketreservatie, input focus en smart-home editable text.

```jsx
import { useEffect, useRef } from "react";

function Form() {
  const inputRef = useRef(null);

  useEffect(() => {
    inputRef.current?.focus();
  }, []);

  return <input ref={inputRef} />;
}
```

Bij edit-modus:

```jsx
useEffect(() => {
  if (isEditing) inputRef.current?.focus();
}, [isEditing]);
```

## 9. Lijsten Tonen

```jsx
function Items({ items }) {
  return (
    <ul>
      {items.map((item) => (
        <li key={item.id}>{item.name}</li>
      ))}
    </ul>
  );
}
```

Stabiele `key` is cruciaal. Gebruik liever `id` dan index.

## 10. Array State Aanpassen

### Toevoegen

```jsx
setItems((items) => [...items, newItem]);
```

### Verwijderen

```jsx
setItems((items) => items.filter((item) => item.id !== id));
```

### Wijzigen

```jsx
setItems((items) =>
  items.map((item) =>
    item.id === id ? { ...item, name: newName } : item
  )
);
```

### Nested array wijzigen

Gebaseerd op smart-home opdracht: installatie bevat toestellen.

```jsx
setInstallations((current) =>
  current.map((installation) => {
    if (installation.id !== installationId) return installation;

    return {
      ...installation,
      devices: installation.devices.map((device) =>
        device.id === deviceId ? { ...device, name: nextName } : device
      ),
    };
  })
);
```

### Nested item toevoegen

```jsx
setInstallations((current) =>
  current.map((installation) =>
    installation.id === installationId
      ? { ...installation, devices: [...installation.devices, newDevice] }
      : installation
  )
);
```

## 11. Unieke IDs

```jsx
function newId() {
  if (typeof crypto !== "undefined" && crypto.randomUUID) {
    return crypto.randomUUID();
  }

  return `${Date.now()}-${Math.random().toString(16).slice(2)}`;
}
```

Gebruik die id voor `key` en bewerkingen.

## 12. Validatiepatroon

Gebaseerd op ticketreservatie.

```jsx
const [status, setStatus] = useState({ kind: "idle", message: "" });

function validate() {
  if (name.trim() === "") {
    setStatus({ kind: "error", message: "Naam is verplicht." });
    return false;
  }

  if (amount === "" || !Number.isInteger(Number(amount))) {
    setStatus({ kind: "error", message: "Aantal moet een geheel getal zijn." });
    return false;
  }

  return true;
}
```

Tonen:

```jsx
<p className={`status ${status.kind}`}>{status.message}</p>
```

## 13. Afgeleide Waarden Met useMemo

Gebruik wanneer een waarde berekend wordt uit state.

```jsx
const remainingTickets = useMemo(() => {
  return Math.max(0, AVAILABLE_TICKETS - reservedTotal);
}, [AVAILABLE_TICKETS, reservedTotal]);
```

Filtering:

```jsx
const visibleInstallations = useMemo(() => {
  if (selectedInstallationId === "all") return installations;
  return installations.filter((item) => item.id === selectedInstallationId);
}, [installations, selectedInstallationId]);
```

## 14. useEffect

### Eerste render

```jsx
useEffect(() => {
  console.log("component geladen");
}, []);
```

### Wanneer waarde verandert

```jsx
useEffect(() => {
  console.log("city changed", city);
}, [city]);
```

### Timer Met Cleanup

```jsx
useEffect(() => {
  const timer = setInterval(() => {
    setCount((count) => count + 1);
  }, 1000);

  return () => clearInterval(timer);
}, []);
```

### Automatisch verwijderen na tijd

Gebaseerd op smart-home opdracht.

```jsx
useEffect(() => {
  const interval = setInterval(() => {
    const now = Date.now();

    setInstallations((current) =>
      current.map((installation) => ({
        ...installation,
        devices: installation.devices.filter((device) => {
          if (!device.installed) return true;
          if (!device.installedAt) return true;
          return now - device.installedAt <= 60000;
        }),
      }))
    );
  }, 1000);

  return () => clearInterval(interval);
}, [setInstallations]);
```

## 15. Fetch Hook

Eenvoudig patroon uit `use_fetch`.

```jsx
import { useEffect, useState } from "react";

function useFetch(url) {
  const [data, setData] = useState("");
  const [error, setError] = useState("");

  useEffect(() => {
    fetch(url)
      .then((res) => res.text())
      .then((data) => setData(data.toString()))
      .catch((err) => setError(err.toString()));
  }, [url]);

  return [data, error];
}
```

Verbeterd patroon met status en cleanup, gebaseerd op `useWeather`.

```jsx
function useWeather(city) {
  const [state, setState] = useState({
    status: "loading",
    data: null,
    error: null,
  });

  useEffect(() => {
    if (!city) {
      setState({ status: "error", data: null, error: new Error("No city") });
      return;
    }

    const controller = new AbortController();
    setState({ status: "loading", data: null, error: null });

    fetch(`http://goweather.xyz/weather/${encodeURIComponent(city)}`, {
      signal: controller.signal,
    })
      .then((res) => {
        if (!res.ok) throw new Error(`HTTP ${res.status}`);
        return res.json();
      })
      .then((json) => {
        setState({
          status: "success",
          data: {
            temperature: json?.temperature ?? "",
            description: json?.description ?? "",
          },
          error: null,
        });
      })
      .catch((err) => {
        if (err?.name === "AbortError") return;
        setState({ status: "error", data: null, error: err });
      });

    return () => controller.abort();
  }, [city]);

  return state;
}
```

Tonen:

```jsx
{weather.status === "loading" && <p>Laden...</p>}
{weather.status === "error" && <p>Kan gegevens niet laden.</p>}
{weather.status === "success" && (
  <p>{weather.data.temperature} {weather.data.description}</p>
)}
```

## 16. localStorage Hook

Gebaseerd op smart-home opdracht.

```jsx
import { useEffect, useState } from "react";

function useLocalStorageState(key, initialValue) {
  const [state, setState] = useState(() => {
    try {
      const raw = localStorage.getItem(key);
      if (raw === null) return initialValue;
      return JSON.parse(raw);
    } catch {
      return initialValue;
    }
  });

  useEffect(() => {
    try {
      localStorage.setItem(key, JSON.stringify(state));
    } catch {
      // storage kan vol of geblokkeerd zijn
    }
  }, [key, state]);

  return [state, setState];
}
```

Gebruik:

```jsx
const [installations, setInstallations] = useLocalStorageState(
  "smart-home-installations",
  []
);
```

## 17. Editable Text Component

Gebaseerd op smart-home `EditableText`.

```jsx
function EditableText({ value, onCommit }) {
  const [isEditing, setIsEditing] = useState(false);
  const [draft, setDraft] = useState(value);
  const inputRef = useRef(null);

  useEffect(() => {
    if (!isEditing) setDraft(value);
  }, [value, isEditing]);

  useEffect(() => {
    if (isEditing) inputRef.current?.focus();
  }, [isEditing]);

  function commit() {
    const next = draft.trim();
    if (next.length === 0) {
      setDraft(value);
      setIsEditing(false);
      return;
    }

    if (next !== value) onCommit(next);
    setIsEditing(false);
  }

  if (isEditing) {
    return (
      <input
        ref={inputRef}
        value={draft}
        onChange={(e) => setDraft(e.target.value)}
        onBlur={commit}
        onKeyDown={(e) => {
          if (e.key === "Enter") commit();
          if (e.key === "Escape") setIsEditing(false);
        }}
      />
    );
  }

  return (
    <span onDoubleClick={() => setIsEditing(true)}>
      {value}
    </span>
  );
}
```

## 18. Filter Met Select

```jsx
const [selectedId, setSelectedId] = useState("all");

const visibleItems = useMemo(() => {
  if (selectedId === "all") return items;
  return items.filter((item) => item.id === selectedId);
}, [items, selectedId]);
```

```jsx
<select value={selectedId} onChange={(e) => setSelectedId(e.target.value)}>
  <option value="all">Alles</option>
  {items.map((item) => (
    <option key={item.id} value={item.id}>
      {item.name}
    </option>
  ))}
</select>
```

## 19. useContext

Gebruik wanneer veel nested components dezelfde state/functie nodig hebben.

```jsx
import { createContext, useContext, useState } from "react";

const TotalContext = createContext();

function App() {
  const [total, setTotal] = useState(0);

  return (
    <TotalContext.Provider value={[total, setTotal]}>
      <Counter />
      <Counter />
      <b>Total: {total}</b>
    </TotalContext.Provider>
  );
}

function Counter() {
  const [total, setTotal] = useContext(TotalContext);
  const [value, setValue] = useState(0);

  function increment() {
    setValue((value) => value + 1);
    setTotal((total) => total + 1);
  }

  return <button onClick={increment}>{value}</button>;
}
```

## 20. useReducer

Gebruik wanneer state via acties wijzigt.

```jsx
function reducer(state, action) {
  if (action.type === "INCR") {
    return { ...state, value: state.value + action.value };
  }

  if (action.type === "DECR") {
    return { ...state, value: state.value - action.value };
  }

  return state;
}

function Counter() {
  const [state, dispatch] = useReducer(reducer, { value: 0 });

  return (
    <>
      <button onClick={() => dispatch({ type: "INCR", value: 10 })}>+10</button>
      <button onClick={() => dispatch({ type: "DECR", value: 10 })}>-10</button>
      <span>{state.value}</span>
    </>
  );
}
```

Let op: return altijd een nieuw object.

```jsx
return { ...state };
```

Niet:

```jsx
return state;
```

## 21. Custom Hooks

### useCounterMax

```jsx
function useCounterMax(max) {
  const [value, setValue] = useState(0);

  function incr() {
    if (value < max) setValue(value + 1);
  }

  function decr() {
    setValue(value - 1);
  }

  let error = "";
  if (value >= max) error = `Maximum (${max}) bereikt`;

  return [value, incr, decr, error];
}
```

### usePreviousState

```jsx
function usePreviousState(state) {
  const ref = useRef();
  const oldValue = ref.current;
  ref.current = state;
  return oldValue;
}
```

## 22. Routing

Gebaseerd op `Oef uit de les/Chapter 7/react_routes`.

Installatie:

```bash
npm install react-router-dom
```

Basis:

```jsx
import { BrowserRouter, Routes, Route, Link, NavLink } from "react-router-dom";

function App() {
  return (
    <BrowserRouter>
      <nav>
        <NavLink to="/">Home</NavLink>
        <Link to="/about">About</Link>
      </nav>

      <Routes>
        <Route path="/" element={<Home />} />
        <Route path="/about" element={<About />} />
      </Routes>
    </BrowserRouter>
  );
}
```

### Nested routes

```jsx
import { Link, Outlet } from "react-router-dom";

function Products() {
  return (
    <div>
      <Link to="/products/car">Cars</Link>
      <Link to="/products/bike">Bikes</Link>
      <Outlet />
    </div>
  );
}
```

```jsx
<Route path="/products" element={<Products />}>
  <Route path="car" element={<CarProducts />} />
  <Route path="bike" element={<BikeProducts />} />
</Route>
```

### URL parameter

```jsx
<Route path="/customer/:firstname" element={<Info />} />
```

```jsx
import { useParams } from "react-router-dom";

function Info() {
  const { firstname } = useParams();
  return <h1>Hello, {firstname}!</h1>;
}
```

### Query parameter

```jsx
import { useSearchParams } from "react-router-dom";

function Info() {
  const [searchParams] = useSearchParams();
  const firstname = searchParams.get("firstname");
  return <h1>Hello, {firstname}!</h1>;
}
```

## 23. PWA Config

Gebaseerd op `Oef uit de les/Chapter 8/my-react-pwa-app`.

```jsx
import { VitePWA } from "vite-plugin-pwa";
import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";

export default defineConfig({
  plugins: [
    react(),
    VitePWA({
      registerType: "prompt",
      injectRegister: false,
      manifest: {
        name: "my-react-pwa-app",
        short_name: "my-react-pwa-app",
        start_url: "/",
        display: "fullscreen",
        theme_color: "#ffffff",
      },
      workbox: {
        globPatterns: ["**/*.{js,css,html,svg,png,ico}"],
        cleanupOutdatedCaches: true,
        clientsClaim: true,
      },
    }),
  ],
});
```

Controleer bij PWA:

- staat `vite-plugin-pwa` in dependencies/devDependencies;
- staat `VitePWA(...)` in `vite.config.js`;
- manifest bevat `name`, `short_name`, `start_url`, `display`, icons/theme;
- service worker test je na `npm run build` + `npm run preview`.

## 24. React Native Basis

React Native gebruikt geen HTML.

Web:

```jsx
<div>
  <p>Hello</p>
  <button onClick={click}>Click</button>
</div>
```

React Native:

```jsx
import { View, Text, Button, Alert } from "react-native";

function App() {
  return (
    <View>
      <Text>Hello</Text>
      <Button title="Click" onPress={() => Alert.alert("Hello")} />
    </View>
  );
}
```

Timer:

```jsx
function Counter() {
  const [count, setCount] = useState(0);

  useEffect(() => {
    const timer = setInterval(() => {
      setCount((count) => count + 1);
    }, 1000);

    return () => clearInterval(timer);
  }, []);

  return <Text>The counter is set to: {count}</Text>;
}
```

Styles:

```jsx
const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: "flex-start",
    alignItems: "flex-start",
    backgroundColor: "#f5f5f5",
  },
});
```

## 25. React Native Versie Van Webpatronen

### TextInput

```jsx
<TextInput
  value={value}
  onChangeText={setValue}
  onBlur={commit}
  onSubmitEditing={commit}
  returnKeyType="done"
/>
```

### Pressable

```jsx
<Pressable onPress={handlePress}>
  <Text>Nieuwe installatie</Text>
</Pressable>
```

### Switch

```jsx
<Switch value={device.installed} onValueChange={onToggleInstalled} />
```

### Long press in plaats van double click

```jsx
<Pressable onLongPress={() => setIsEditing(true)}>
  <Text>{value}</Text>
</Pressable>
```

## 26. Checklist Voor Een CRUD-achtige Oefening

Voorbeeld: task list, ticketreservatie, smart-home installaties.

State:

```jsx
const [items, setItems] = useState([]);
const [isAdding, setIsAdding] = useState(false);
const [selectedId, setSelectedId] = useState("all");
const [status, setStatus] = useState({ kind: "idle", message: "" });
```

Objectvorm:

```jsx
{
  id: newId(),
  name: "Item",
  completed: false,
  createdAt: new Date().toISOString()
}
```

Nodige functies:

- `addItem(name)`;
- `updateItem(id, fields)`;
- `removeItem(id)`;
- `toggleItem(id)`;
- `validateInput()`;
- `clearForm()`;
- `filterItems()`.

## 27. Veelgemaakte Fouten

### Handler direct uitvoeren

Fout:

```jsx
onClick={save()}
```

Goed:

```jsx
onClick={save}
onClick={() => save(id)}
```

### State muteren

Fout:

```jsx
items.push(item);
setItems(items);
```

Goed:

```jsx
setItems((items) => [...items, item]);
```

### Object muteren

Fout:

```jsx
item.name = "Nieuw";
return item;
```

Beter:

```jsx
return item.id === id ? { ...item, name: "Nieuw" } : item;
```

### Effect zonder cleanup

Fout:

```jsx
useEffect(() => {
  setInterval(tick, 1000);
}, []);
```

Goed:

```jsx
useEffect(() => {
  const timer = setInterval(tick, 1000);
  return () => clearInterval(timer);
}, []);
```

### Oneindige renderlus

Risico:

```jsx
useEffect(() => {
  setCount(count + 1);
});
```

Gebruik dependency array en denk na wanneer de effect moet draaien.

### Verkeerde key

Risico bij verwijderbare lijst:

```jsx
key={index}
```

Gebruik:

```jsx
key={item.id}
```

## 28. Zoekindex In Jouw Mappen

Handige voorbeelden:

- Formulier + validatie + history: `Individueele opdrachten/1-ticketreservatie-joshuameuleman/individuele-opdracht-1/src`.
- Smart-home nested arrays + localStorage + fetch hook + editable text: `Individueele opdrachten/2-smart-home-installatiebeheer-joshuameuleman/react-web-app/src`.
- React Native variant smart-home: `Individueele opdrachten/2-smart-home-installatiebeheer-joshuameuleman/react-native`.
- Basiscomponent + props + timer: `Oef uit de les/Chapter 1`.
- JSX conditions, loops en styling: `Oef uit de les/Chapter 2`.
- Events, inputs, focus en timers: `Oef uit de les/Chapter 3`.
- Hooks: `Oef uit de les/Chapter 4`.
- Router: `Oef uit de les/Chapter 7/react_routes`.
- PWA: `Oef uit de les/Chapter 8/my-react-pwa-app`.
- React Native/Expo: `Oef uit de les/Chapter 9/my-react-native-app`.

## 29. Mini-Sjabloon Voor Een Nieuwe Oefening

```jsx
import { useMemo, useRef, useState } from "react";
import "./App.css";

function newId() {
  return `${Date.now()}-${Math.random().toString(16).slice(2)}`;
}

function App() {
  const inputRef = useRef(null);
  const [items, setItems] = useState([]);
  const [text, setText] = useState("");
  const [filter, setFilter] = useState("all");
  const [status, setStatus] = useState({ kind: "idle", message: "" });

  const visibleItems = useMemo(() => {
    if (filter === "all") return items;
    return items.filter((item) => item.category === filter);
  }, [items, filter]);

  function addItem(event) {
    event.preventDefault();

    const name = text.trim();
    if (name === "") {
      setStatus({ kind: "error", message: "Naam is verplicht." });
      inputRef.current?.focus();
      return;
    }

    setItems((items) => [
      { id: newId(), name, completed: false },
      ...items,
    ]);
    setText("");
    setStatus({ kind: "success", message: "Toegevoegd." });
    inputRef.current?.focus();
  }

  function toggleItem(id) {
    setItems((items) =>
      items.map((item) =>
        item.id === id ? { ...item, completed: !item.completed } : item
      )
    );
  }

  function removeItem(id) {
    setItems((items) => items.filter((item) => item.id !== id));
  }

  return (
    <main className="app">
      <form onSubmit={addItem}>
        <input
          ref={inputRef}
          value={text}
          onChange={(event) => setText(event.target.value)}
        />
        <button type="submit">Toevoegen</button>
      </form>

      <p className={status.kind}>{status.message}</p>

      <select value={filter} onChange={(event) => setFilter(event.target.value)}>
        <option value="all">Alles</option>
      </select>

      <ul>
        {visibleItems.map((item) => (
          <li key={item.id}>
            <label>
              <input
                type="checkbox"
                checked={item.completed}
                onChange={() => toggleItem(item.id)}
              />
              {item.name}
            </label>
            <button type="button" onClick={() => removeItem(item.id)}>
              Remove
            </button>
          </li>
        ))}
      </ul>
    </main>
  );
}

export default App;
```
