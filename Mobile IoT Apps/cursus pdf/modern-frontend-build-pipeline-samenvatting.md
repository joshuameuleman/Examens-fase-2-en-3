# Modern Frontend Build Pipeline – leersamenvatting (examengericht)

Dit is een zelfstandige samenvatting over **moderne frontend build pipelines** (zoals je die tegenkomt bij Angular/React apps). Focus: **begrippen**, **pipeline-stappen**, **waarom je dit doet**, en **typische examen-/interviewvragen**.

## 1) Het grote plaatje

Een build pipeline zet je project om van “developer-friendly source” naar “browser-friendly output”.

- **Input**: TypeScript/ESNext, JSX/TSX, SCSS, assets (images/fonts), configuratie.
- **Output**: geoptimaliseerde JS/CSS bundles (vaak meerdere chunks), assets, en (optioneel) source maps.
- **Twee modi**:
  - **Dev**: snelle rebuilds, duidelijke errors, meestal ruimere source maps.
  - **Prod**: maximale performance: minify, tree-shake, split, compress.

## 2) Kernbegrippen (die je zeker moet kunnen uitleggen)

### 2.1 Transpilation
**Transpilen** = syntax omzetten naar een versie die browsers begrijpen.

- Voorbeelden:
  - TypeScript → JavaScript (types verdwijnen volledig)
  - JSX → JavaScript functie-calls
  - Modern JS (ES202x) → oudere JS syntax (indien nodig)
- Tools: Babel, TypeScript compiler, esbuild, swc.

Verschil met “type checking”:
- Transpilation kan slagen terwijl type checking faalt (afhankelijk van setup).

### 2.2 Bundling
**Bundlen** = je imports volgen en samenpakken in 1 of meerdere output-bestanden.

- Waarom:
  - Dependency graph analyseren
  - Optimalisaties mogelijk maken (tree-shaking, splitting)
  - Minder/efficiëntere requests (historisch belangrijk; nog steeds relevant)
- Tools: webpack, Vite (gebruikt Rollup voor build), Rollup, Parcel.

### 2.3 Minification
**Minify** = code kleiner maken zonder gedrag te veranderen.

- Voorbeelden:
  - whitespace verwijderen
  - variabelen verkorten
  - simpele code transforms
- Tools: Terser, esbuild, swc.

### 2.4 Tree-shaking / Dead Code Elimination
**Tree-shaking** = ongebruikte exports verwijderen op basis van de import/export-structuur.

- Werkt best met **ES Modules** (`import`/`export`).
- Kan mislopen bij:
  - modules met **side effects** (code die meteen bij import iets doet)
  - “barrel files” of dynamische import patterns

### 2.5 Code splitting & lazy loading
**Code splitting** = output opsplitsen in meerdere chunks.

- Doel: kleinere initiële download → sneller eerste scherm.
- Typische triggers:
  - dynamische import (`import('...')`)
  - route-based splitting (Angular routes / React router patterns)

### 2.6 Dev server & HMR
- **Dev server**: serveert lokaal, rebuilds, proxy naar backend.
- **HMR (Hot Module Replacement)**: vervangen van modules zonder volledige reload.

### 2.7 Source maps
**Source maps** mappen de output (minified/transpiled) terug naar je originele source.

- Pro: debugging wordt realistisch.
- Con: kan groot zijn; kan (afhankelijk van config) source price geven in productie.

## 3) De pipeline als stappenplan

Je kan een typische pipeline als deze flow uitleggen:

1. **Resolve & parse**: bundler leest entrypoints en volgt imports.
2. **Loaders/plugins**: transpile TS/JSX, compile SCSS → CSS, asset processing.
3. **Optimize**:
   - tree-shake
   - minify
   - split chunks
4. **Emit**: schrijf output naar `dist/`.
5. **Serve** (dev) of **deploy** (prod).

## 4) CSS/SCSS in de pipeline

- SCSS wordt meestal gecompileerd naar CSS (Sass).
- Vaak met:
  - autoprefixer (vendor prefixes)
  - CSS minification
  - (soms) CSS modules of component-scoped styles

Wat je moet kunnen duiden:
- Globale styles vs component styles.
- Waarom preprocessors nuttig zijn (variables, mixins, nesting).

## 5) Assets (images/fonts)

- Pipeline kan assets:
  - kopiëren naar output
  - fingerprints/hashes geven (cache busting)
  - comprimeren
  - inline’en (kleine assets) afhankelijk van config

## 6) Environments & configuratie

- **Environment variables** (dev/prod) sturen:
  - API base URL
  - feature flags
  - logging levels
- Angular heeft typisch verschillende build configs; Vite gebruikt `.env`-varianten.

Belangrijk concept: **build-time** config ≠ **runtime** config.

## 7) Performance & caching (must-know)

- **Caching**: browsers cachen assets agressief.
- **Cache busting**: content-hash in filenames (`app.3f2a1c.js`).
- **CDN**: statische assets wereldwijd sneller.

## 8) Quality gates (CI/CD)

Een “professionele” pipeline is niet alleen bundlen:

- Lint (ESLint)
- Format (Prettier)
- Type-check
- Tests (unit/integration)
- Build + artifact
- Deploy

## 9) Typische examenvragen (met korte antwoorden)

- Wat is het verschil tussen transpilation en bundling?
  - Transpilation zet syntax om; bundling volgt imports en maakt output bundles.

- Wat is tree-shaking en wanneer werkt het niet goed?
  - Ongebruikte exports verwijderen; lastig bij side effects en niet-ESM patterns.

- Waarom code splitting?
  - Kleinere initial load, sneller eerste render; laad rest pas als nodig.

- Waarom source maps in dev wel en soms niet in prod?
  - Dev: debugging. Prod: size/security trade-offs.

- Wat doet HMR?
  - Module vervangen zonder full reload, sneller itereren.

## 10) Mini-spiekbrief

- Transpile: TS/JSX → JS
- Bundle: imports → (meerdere) bundles
- Optimize: tree-shake, split, minify
- Serve dev: dev server + HMR
- Ship prod: hashes + compress + CDN
