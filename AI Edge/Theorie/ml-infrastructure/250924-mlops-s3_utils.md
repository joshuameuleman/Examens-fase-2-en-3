**`s3_utils.py` — Uitleg en examenvragen**

Locatie: `250924-mlops-workshops/ml-infrastructure/08-deploy-model-from-s3/backend/s3_utils.py`

Korte omschrijving
- Helper functies om te praten met een S3-compatible storage (MinIO): client-creation, upload en download van artifact-bestanden.

Belangrijke onderdelen
- Environment variables: `MINIO_ROOT_USER`, `MINIO_ROOT_PASSWORD`, `MINIO_ENDPOINT_URL`, `MINIO_BUCKET`
- `create_s3_client()` maakt een `boto3.client(...)` met `endpoint_url` en credentials
- `upload_to_s3(file_path)` en `download_from_s3(file_path)` verzorgen transfer

Implementatie-tip: eenvoudige `upload_to_s3`

```python
def upload_to_s3(file_path):
    bucket = MINIO_BUCKET
    object_name = os.path.basename(file_path)
    s3 = create_s3_client()
    s3.upload_file(file_path, bucket, object_name)
    print(f"Uploaded {file_path} => s3://{bucket}/{object_name}")
```

Concepten om te beheersen
- Credentials: nooit hardcoden — gebruik env vars of secret managers
- Presigned URLs voor tijdelijke upload/download zonder credentials
- Multipart uploads voor grote bestanden en resilience
- Endpoint URL en S3-compatibility (MinIO vs AWS S3 differences)

Mogelijke examenvragen
- "Waarom gebruik je `endpoint_url` bij MinIO en wat gebeurt er als je het weglaat?"
- "Wat is een presigned URL en wanneer gebruik je die?"
- "Hoe kun je uploaden robuuster maken voor grote model-bestanden?"