# Guide de test — moteur LLM / RAG

> Comment tester le pipeline HL7 → FHIR → RAG, avec les **prompts qui marchent**
> et ceux qui échouent (et pourquoi). À jour des correctifs du 2026-06-15.

L'API ai-engine écoute sur `http://127.0.0.1:8000` **uniquement avec la stack dev**
(`make dev`, port loopback). En prod (`make up`), aucun port direct n'est publié :
passe par l'UI ou par `https://localhost:8443/ai/*` avec un cookie de session valide.
Fichiers de test : `simple.hl7`, `intermediate.hl7`, `complex.hl7` (ce dossier).

---

## 0. Si tu obtiens encore « I do not have this information in the records. »

Dans l'ordre, les 3 causes possibles :

1. **Question trop vague** → utilise les prompts « ✅ qui marchent » plus bas.
   « Donne-moi des infos sur X » échoue souvent sur les petits modèles ; pose une
   question **précise** (« quels sont les résultats de labo de X ? »).
2. **Base pas (ré)indexée** après un changement de code → refais l'étape 1 (reset)
   puis l'étape 2 (ingestion).
3. **Anglais > français** : `all-minilm` est surtout anglais. En cas de doute, teste
   d'abord la même question **en anglais** pour isoler le problème.

---

## 1. (Ré)initialiser la base vectorielle

À faire après tout changement de code RAG, ou si la base contient de vieux doublons.
Le plus simple :

```bash
make purge-ai      # vide ChromaDB + redémarre ai-engine (collection vide recréée)
```

> ⚠️ Le redémarrage est indispensable : supprimer la collection sans relancer le
> service le laisse avec un handle périmé (« Collection [...] does not exist »).
> C'est pour ça que `make purge-ai` enchaîne purge **puis** restart.

## 2. Ingérer les 3 messages HL7 (HL7 → FHIR + indexation)

```bash
cd hl7_tests
for f in simple intermediate complex; do
  HL7=$(python3 -c "import json;print(json.dumps(open('$f.hl7').read()))")
  curl -s -X POST http://127.0.0.1:8000/ai/convert \
    -H 'Content-Type: application/json' -d "{\"hl7\": $HL7}" >/dev/null
done
```

Vérifier le nombre de documents (doit valoir **3**, même si on réimporte plusieurs
fois — grâce à la déduplication par `sha256`) :

```bash
docker compose exec -T ai-engine python3 -c \
  "import chromadb; print(chromadb.PersistentClient(path='/app/db/chroma').get_collection('medical_records').count())"
```

## 3. Inspecter ce qui est réellement indexé (debug)

```bash
docker compose exec -T ai-engine python3 -c "
from app.services.vector_store import vector_store
r = vector_store.query('Jane Smith lab results')
for doc in r['documents'][0]:
    print(' *', doc[:160])
"
```

---

## 4. Prompts de test (`POST /ai/rag`)

Gabarit :

```bash
curl -s -X POST http://127.0.0.1:8000/ai/rag \
  -H 'Content-Type: application/json' \
  -d '{"question":"VOTRE QUESTION ICI"}' | python3 -m json.tool
```

### ✅ Qui marchent (questions précises)

| Langue | Prompt                                             | Résultat attendu                                               |
| ------ | -------------------------------------------------- | -------------------------------------------------------------- |
| EN     | `What lab results does Jane Smith have?`           | WBC 7.5, RBC 4.8, HGB 13.5 g/dL, HCT 40.5 %, Glucose 105 mg/dL |
| EN     | `What information do you have on Jane Smith?`      | Nom, sexe, date de naissance (+ labos selon le modèle)         |
| EN     | `What is Jane Smith's glucose level?`              | 105 mg/dL                                                      |
| FR     | `Quels sont les résultats de labo de Jane Smith ?` | la liste des 5 résultats                                       |
| FR     | `Quel est le taux de glucose de Jane Smith ?`      | 105 mg/dL                                                      |
| EN     | `What lab results does John Doe have?`             | les résultats de John Doe (≠ ceux de Jane)                     |

### ✅ Cas « refus correct » (le refus est attendu ici)

| Prompt                                             | Résultat attendu                                                    |
| -------------------------------------------------- | ------------------------------------------------------------------- |
| `Donne-moi des infos sur Bob Martin`               | « I do not have this information in the records. » (patient absent) |
| `Quelle est la tension artérielle de Jane Smith ?` | refus / pas trouvé (donnée absente du dossier)                      |

### ⚠️ Qui peuvent échouer sur petit modèle (limite connue)

| Prompt                                           | Pourquoi                                                                                                                                                                                          |
| ------------------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Donne-moi des infos sur Jane Smith` (vague, FR) | Le 1ᵉʳ doc récupéré est le résumé « identité seule » (message de commande) ; un petit modèle le lit, n'y voit pas de labo et s'arrête. Reformuler en question précise, ou passer à `llama3.2:1b`. |

---

## 5. Choix du modèle

Le LLM par défaut est **`smollm2:135m`** (270 Mo — pour tenir sur une machine 42 à
l'espace disque limité). Pour des réponses nettement meilleures, lancer avec
`llama3.2:1b` (1.3 Go) :

```bash
make ... LLM=normal      # via Makefile_test : LLM=normal => llama3.2:1b
# ou directement :
LLM_MODEL=llama3.2:1b docker compose up -d ai-engine ollama
```

Vérifier le modèle actif dans le conteneur :

```bash
docker compose exec -T ai-engine python3 -c \
  "from app.services.ollama_client import ollama_client; print(ollama_client.model)"
```

> Note : `temperature=0.0` est forcée partout (réponses déterministes, sans
> créativité — important en contexte médical).

---

## 6. Autres endpoints à tester

```bash
# Chat LLM direct (sans dossiers)
curl -s -X POST http://127.0.0.1:8000/ai/chat \
  -H 'Content-Type: application/json' \
  -d '{"message":"What is a FHIR bundle?","history":[]}' | python3 -m json.tool

# RAG en streaming (Server-Sent Events)
curl -N -s -X POST http://127.0.0.1:8000/ai/rag/stream \
  -H 'Content-Type: application/json' \
  -d '{"question":"What lab results does Jane Smith have?"}'
```
