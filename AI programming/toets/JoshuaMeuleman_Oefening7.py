#- Naam: Joshua Meuleman

#- Datum: 14/11/2025

#- Python Programming - Oefening 7

import pandas as pd
import os

data = {
	'Name': ['Tony', 'Robert', 'John', 'Alice'],
	'Age': [18, 24, 19, 21],
}

df = pd.DataFrame(data)

print(df)

csv_path = 'test.csv'
df.to_csv(csv_path, index=False)

print(f"Saved DataFrame to: {os.path.abspath(csv_path)}")

