# Building ML Infrastructure — Samenvatting (Nederlands)

## Course overview
Deze cursus behandelt hoe je machine learning-projecten van prototype (notebooks) naar productie brengt: refactoren van code, model serving, containerisatie, orkestratie, opslag, CI/CD en data-orchestration.

## Hoofdstukken (kort)
- 1. From Notebooks to Production Code — waarom notebooks niet schalen, refactor naar `*.py` modules, tests en `requirements.txt`.
- 2. Model Deployment and Serving — communicatieprotocollen (REST, gRPC, WebSockets, MQTT), voorbeelden met FastAPI en authenticatie (JWT, OAuth2, mTLS).
- 3. Containers and Virtual Machines — verschil VM vs container, Dockerfiles, image layering en caching, best practices (pin versies).
- 4. Container Orchestration — Docker Compose voor lokaal; Kubernetes voor productie (deployments, PVCs, probes, rollbacks).
- 5. Infrastructure Management — IaaS/PaaS/SaaS, managed Kubernetes, serverless containers, Infrastructure as Code (Terraform, GitOps).
- 6. Scalable Storage — object storage (S3), aanbevolen formaten, versiebeheer, DVC/LakeFS voor datasetversies.
- 7. CI/CD for ML — waarom CI/CD nodig is voor ML, GitHub Actions voorbeelden, secrets en workflow triggers.
- 8. Data Pipelines & Orchestration — DAGs, Airflow, Dagster, Prefect en rolverdeling tussen CI/CD en data-orchestration.

## Belangrijke kernbegrippen en examenkansen
- Notebooks als "thin wrappers": logica in `data.py`, `model.py`, `train_model.py`, notebooks alleen voor visualisatie.
- Docker best practices: pin base images en dependencies, gebruik caching door `COPY requirements.txt` vóór `COPY . .`.
- Model serving: REST (simpel, breed ondersteund), gRPC (high-performance, typed), WebSockets/MQTT voor streaming of IoT.
- FastAPI: voorbeelden van routes, Pydantic-modellen en automatische Swagger UI (`/docs`).
- Orkestratie: wanneer Docker Compose volstaat vs wanneer Kubernetes nodig is; basis Kubernetes YAML-structuur (Deployment, Service, PVC).
- IaC en GitOps: Terraform, Argo CD/Flux; waarom dit repetitieve, reviewbare infrastructuur mogelijk maakt.
- Storage & versiebeheer: verschil tussen object storage en dataset-versioning tools (DVC, LakeFS).
- CI/CD: triggers (`push`, `pull_request`), jobs/runners, caching en secrets; voorbeeld GitHub Actions-workflow voor tests en builds.
- Data orchestration: DAG concept, Airflow & Prefect voorbeelden, wanneer welke tool kiezen.

## Praktische tips voor het examen (code lezen)
- Leg uit waarom code uit notebooks naar modules is verplaatst (testbaarheid, hergebruik).
- Kun je een Dockerfile of GitHub Actions-workflow interpreteren? Leg stappen en caching uit.
- Wees vertrouwd met eenvoudige FastAPI- en ONNX/ONNX Runtime-codevoorbeelden (hoe een endpoint input valideert en doorstuurt naar een model).

---
Bron: samengevoegd en vertaald uit de cursuspagina "Building ML Infrastructure" (mlops4ecm.be).

## Uitgebreide codevoorbeelden en uitleg per hoofdstuk

### 1) From Notebooks to Production Code — voorbeeld en uitleg
Voorbeeld: refactor van notebook naar modulair project.

data.py
```
import pandas as pd

def load_data(path="data.csv"):
		df = pd.read_csv(path)
		X = df[["feature1","feature2"]]
		y = df["target"]
		return X, y
```
Antwoord / Uitleg (data.py):
- `import pandas as pd` — importeert de pandas library en geeft het alias `pd`.
- `def load_data(path="data.csv"):` — definieert een functie met een optioneel pad-argument.
- `df = pd.read_csv(path)` — leest een CSV-bestand in een DataFrame (`df`).
- `X = df[["feature1","feature2"]]` — selecteert twee kolommen als features (input voor model).
- `y = df["target"]` — selecteert de target-kolom (labels).
- `return X, y` — geeft features en labels terug; handig voor training/inferentie.

model.py
```
from sklearn.linear_model import LinearRegression
import joblib

def train_model(X, y):
		m = LinearRegression()
		m.fit(X, y)
		return m

def save_model(model, path="model.joblib"):
		joblib.dump(model, path)

def load_model(path="model.joblib"):
		return joblib.load(path)
```
Antwoord / Uitleg (model.py):
- `from sklearn.linear_model import LinearRegression` — importeert het lineaire regressiemodel.
- `import joblib` — module om Python-objecten snel te serialiseren (sparen/laden).
- `train_model(X, y)` — maakt een `LinearRegression`-object, traint het met `fit`, en retourneert het getrainde model.
- `save_model(model, path)` — schrijft het model naar schijf (`model.joblib`) zodat het later hergebruikt kan worden.
- `load_model(path)` — laadt een eerder opgeslagen model terug in het geheugen.

Uitleg: zo wordt elke functie herbruikbaar en testbaar. Notebooks blijven `thin wrappers` voor visualisatie en exploratie.

### 2) Model Deployment en Serving — FastAPI voorbeeld + uitleg
FastAPI endpoint dat input valideert met Pydantic en een model gebruikt:

main.py
```
from fastapi import FastAPI
from pydantic import BaseModel
import joblib

app = FastAPI()
model = joblib.load("model.joblib")

class Input(BaseModel):
		feature1: float
		feature2: float

@app.post("/predict")
def predict(inp: Input):
		x = [[inp.feature1, inp.feature2]]
		pred = model.predict(x).tolist()
		return {"prediction": pred}
```
Antwoord / Uitleg (FastAPI `main.py`):
- `from fastapi import FastAPI` — importeert FastAPI-applicatieklasse.
- `from pydantic import BaseModel` — voor declaratieve input-validatie en type-checking.
- `model = joblib.load("model.joblib")` — laadt het getrainde model in geheugen bij opstart.
- `class Input(BaseModel): ...` — definieert het JSON-schema dat de `/predict` endpoint verwacht.
- `@app.post("/predict")` — registreert een POST-route `/predict`.
- `def predict(inp: Input):` — FastAPI parseert en valideert JSON body naar `inp` van type `Input`.
- `x = [[...]]` — zet de features in de vorm die scikit-learn verwacht (2D array).
- `pred = model.predict(x).tolist()` — vraag voorspelling op en zet het resultaat om naar een JSON-serialiseerbare lijst.
- `return {"prediction": pred}` — geeft JSON antwoord terug met de voorspelling.

Uitleg: Pydantic zorgt voor input-validatie; `uvicorn`/`fastapi run` exposeert `/docs` (Swagger) automatisch.

Examenvraag: leg uit welke beveiligings- en schaaloverwegingen relevant zijn bij het openstellen van dit endpoint (authenticatie, rate-limiting, batching).

### 3) Containers — Dockerfile voorbeeld en best practices
Dockerfile:

```
FROM python:3.11-slim
WORKDIR /app
COPY requirements.txt ./
RUN pip install -r requirements.txt
COPY . .
CMD ["uvicorn", "main:app", "--host", "0.0.0.0", "--port", "8000"]
```
Antwoord / Uitleg (Dockerfile):
- `FROM python:3.11-slim` — basisimage met Python 3.11 (lichte variant).
- `WORKDIR /app` — stelt de werkmap binnen de container in.
- `COPY requirements.txt ./` — kopieert alleen dependency-lijst eerst (caching voordeel).
- `RUN pip install -r requirements.txt` — installeert Python-dependencies binnen image.
- `COPY . .` — kopieert resten van de projectbestanden naar de image.
- `CMD [...]` — standaardcommando dat de app start (Uvicorn server voor FastAPI).

Uitleg en tips:
- Plaats `COPY requirements.txt` vóór `COPY . .` voor betere layer caching.
- Pin Python- en packageversies in `requirements.txt` voor reproduceerbaarheid.
- Gebruik `-e` om environment variables te injecteren en `-v` voor mounts tijdens ontwikkeling.

### 4) Container Orchestration — Docker Compose & Kubernetes voorbeeld
Docker Compose (kort):

```
version: '3.8'
services:
	backend:
		build: ./backend
		ports:
			- "8000:8000"
		environment:
			- DATABASE_URL=postgres://user:pass@db:5432/app
	db:
		image: postgres:15
		environment:
			- POSTGRES_PASSWORD=pass
```
Antwoord / Uitleg (Docker Compose):
- `version: '3.8'` — Compose bestandsversie.
- `services:` — lijst van services die Compose start.
- `backend: build: ./backend` — bouwt een image uit de `./backend` map.
- `ports: - "8000:8000"` — map hostpoort 8000 naar containerpoort 8000.
- `environment:` — injecteert environment-variabelen (bv. database connectiestring).
- `db: image: postgres:15` — start een Postgres-container als service; deze is bereikbaar onder hostname `db` in het netwerk.

Kubernetes Deployment example (fragment):

```
apiVersion: apps/v1
kind: Deployment
metadata:
	name: backend
spec:
	replicas: 2
	selector:
		matchLabels:
			app: backend
	template:
		metadata:
			labels:
				app: backend
		spec:
			containers:
			- name: backend
				image: myregistry/ml-backend:1.0
				ports:
				- containerPort: 8000
				readinessProbe:
					httpGet:
						path: /health
						port: 8000

Antwoord / Uitleg (Kubernetes Deployment fragment):
- `apiVersion`, `kind`, `metadata` — standaard YAML metadata om Kubernetes resource te identificeren.
- `replicas: 2` — wil twee exemplaren (pods) van de applicatie draaien voor redundantie.
- `selector` en `template` — koppelen Deployment aan de pods en labels.
- `containers:` — specificeert container-image en poort binnen de pod.
- `readinessProbe` — Kubernetes checkt `/health` en markeert pod 'ready' alleen als probe slaagt; voorkomt verkeer naar niet-klaar pods.

```

Uitleg: Compose is handig lokaal; Kubernetes voegt features toe voor schaal, health checks, persistent volumes en rollbacks.

### 5) Scalable Storage — S3 voorbeeld met boto3
Upload voorbeeld:

```
import boto3

s3 = boto3.client('s3')
def upload_model(path, bucket, key):
		s3.upload_file(path, bucket, key)
```
Antwoord / Uitleg (S3 upload met boto3):
- `import boto3` — AWS SDK voor Python.
- `s3 = boto3.client('s3')` — maakt een client-verbinding naar S3 API.
- `upload_model(path, bucket, key)` — wrapper-functie die een lokaal bestand (`path`) uploadt naar S3-bucket onder `key` (objectnaam).
- Security tip: gebruik IAM-rollen of `AWS_ACCESS_KEY_ID`/`AWS_SECRET_ACCESS_KEY` via environment variables of CI secrets; commit nooit sleutels.

Uitleg: gebruik server-side encryption en versiebeheer (S3 versioning) voor auditability; bewaar metadata (experiment-id, commit-hash).

### 6) CI/CD voor ML — GitHub Actions voorbeeld
.github/workflows/test.yml
```
name: CI
on: [push, pull_request]
jobs:
	test:
		runs-on: ubuntu-latest
		steps:
			- uses: actions/checkout@v4
			- uses: actions/setup-python@v5
				with: {python-version: '3.11'}
			- run: pip install -r requirements.txt
			- run: pytest -q
```
Antwoord / Uitleg (GitHub Actions workflow):
- `name: CI` — naam van de workflow.
- `on: [push, pull_request]` — triggers: start workflow bij push of PR.
- `jobs:` — definieert taken; `test` draait op `ubuntu-latest` runner.
- `actions/checkout@v4` — checkt repository-code uit zodat runner ermee kan werken.
- `actions/setup-python@v5` — installeert Python op runner.
- `pip install -r requirements.txt` — installeer dependencies.
- `pytest -q` — voert tests uit; fouten leiden tot mislukte job en blokkeren merge indien als required ingesteld.

Uitleg: triggers (`push`, `pull_request`) zorgen voor automatische checks; gebruik `secrets` voor credentials en `actions/cache` voor dependency caching.

### 7) Data Pipelines & Orchestration — eenvoudig Airflow DAG voorbeeld
```
from airflow.decorators import dag, task
from datetime import datetime

@dag(start_date=datetime(2025,1,1), schedule='@daily', catchup=False)
def pipeline():
		@task
		def extract():
				return 'data'

		@task
		def transform(data):
				return data + '_clean'

		@task
		def load(data):
				print('loaded', data)

		load(transform(extract()))

dag = pipeline()
```
Antwoord / Uitleg (Airflow DAG):
- `@dag(...)` — declareert een DAG met startdatum en schema (`@daily`). `catchup=False` voorkomt inhalen van oude runs.
- `@task` — decorator waarmee een functie een Airflow-task wordt.
- `extract()` — haalt data op (hier dummy return 'data').
- `transform(data)` — verwerkt of transformeert data.
- `load(data)` — laadt/gebruikt de verwerkte data; in productiescenario schrijft dit naar DB of upload naar storage.
- `load(transform(extract()))` — schakelt taken aan elkaar; Airflow maakt een taakgraph met deze afhankelijkheden.

Uitleg: DAGs modelleren afhankelijkheden; Airflow is geschikt voor geplande, traceerbare ETL‑werkflows.

## Extra informatie: Begrippenlijst (kort)
- Notebook: interactief document (Jupyter) voor exploratie, maar minder geschikt voor productie wegens merge- en testproblemen.
- Container image: read-only snapshot van filesystem + app; container = draaiende instantie.
- Orkestratie: beheer van meerdere containers (scheduling, networking, health checks).
- IaC (Infrastructure as Code): declaratieve definitie van infrastructuur (Terraform, CloudFormation).
- CI/CD: geautomatiseerde testen, bouwen en deployen (GitHub Actions, GitLab CI).
- Quantization: verkleinen van numerieke precisie (FP32→INT8) voor snellere, kleinere modellen — let op calibratie en accuracy impact.
- ONNX: interoperabel modelformaat om modellen tussen frameworks en runtimes te verplaatsen.

---
Als je wilt, vul ik nu in `ML-code-uitleg.md` concrete oefeningen uit de lokale repo `250924-mlops-workshops` in met stap-voor-stap code-uitleg en examenvragen.

