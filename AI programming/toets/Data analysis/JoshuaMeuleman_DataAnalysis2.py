#- Naam: Joshua Meuleman

#- Datum: 14/11/2025

#- Data Analysis - Oefening 2



import re
import sys
from pathlib import Path

import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as mtick
import requests


def find_year_and_population(df):
	# Probeer kolom te vinden met jaren
	year_col = None
	pop_col = None
	for col in df.columns:
		name = str(col)
		# heuristiek 1: kolomnaam bevat 'year'
		if 'year' in name.lower():
			year_col = col
			break
	# heuristiek 2: als geen kolomnaam 'year' bevat, zoek kolom met jaarachtige waarden
	if year_col is None:
		for col in df.columns:
			try:
				vals = pd.to_numeric(df[col], errors='coerce')
				# veel volledige jaren tussen 1000 en 2100
				if vals.notna().sum() > 0 and vals.dropna().between(1000, 2100).sum() / max(1, vals.notna().sum()) > 0.6:
					year_col = col
					break
			except Exception:
				continue

	# Zoek een populatiekolom: voorkeur voor kolomnamen met 'pop' of 'population'
	for col in df.columns:
		name = str(col).lower()
		if 'popul' in name or 'population' in name or 'population' in name:
			pop_col = col
			break

	# Als nog niet gevonden, kies eerste numerieke kolom anders dan year
	if pop_col is None:
		for col in df.columns:
			if col == year_col:
				continue
			try:
				vals = pd.to_numeric(df[col].astype(str).str.replace(r"\[.*?\]", "", regex=True).str.replace(',', ''), errors='coerce')
				if vals.notna().sum() > 0:
					pop_col = col
					break
			except Exception:
				continue

	return year_col, pop_col


def clean_numeric_series(s):
	# verwijder voetnoot markers en komma's en mogelijke tekst
	s = s.astype(str).str.replace(r"\[.*?\]", "", regex=True)
	s = s.str.replace(',', '')
	# haal numerieke deel (inclusief decimalen)
	nums = s.str.extract(r'([0-9,.]+)')[0]
	return pd.to_numeric(nums, errors='coerce')


def main():
	url = 'https://en.wikipedia.org/wiki/World_population'
	print('Lezen van:', url)

	try:
		# Haal de pagina op met een browser-like User-Agent om 403 Forbidden te vermijden
		headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64)'}
		resp = requests.get(url, headers=headers, timeout=15)
		resp.raise_for_status()
		html = resp.text
		# Parse HTML vanuit de tekst met lxml (geen BeautifulSoup)
		tables = pd.read_html(html, flavor='lxml')
	except requests.exceptions.HTTPError as e:
		print('HTTP-fout bij ophalen pagina:', e)
		print('Mogelijk blokkeert de site scraping. Probeer later of wijzig User-Agent.')
		sys.exit(1)
	except Exception as e:
		print('Fout bij lezen van HTML-tabel of ophalen pagina:', e)
		print('Zorg dat packages geïnstalleerd zijn: pip install lxml requests')
		sys.exit(1)

	print(f'Gevonden tabellen: {len(tables)}')

	target_df = None
	target_year_col = None
	target_pop_col = None

	# probeer tabel te vinden met 'Global annual population growth' door te zoeken naar 'Year' en 'Population'
	for i, df in enumerate(tables):
		yc, pc = find_year_and_population(df)
		if yc is None or pc is None:
			continue
		# extra check: bevat jaar 2023 of recente jaren
		cleaned_years = clean_numeric_series(df[yc])
		if cleaned_years.dropna().astype(int).between(1900, 2100).any():
			target_df = df.copy()
			target_year_col = yc
			target_pop_col = pc
			print(f'Gekozen tabel index {i} met kolommen: year={yc} pop={pc}')
			break

	if target_df is None:
		print('Kon geen geschikte tabel vinden. Probeer handmatig te inspecteren.')
		sys.exit(1)

	# Schoonmaken en opmaken
	years = clean_numeric_series(target_df[target_year_col]).astype('Int64')
	pops = clean_numeric_series(target_df[target_pop_col])

	df_clean = pd.DataFrame({'year': years, 'population': pops}).dropna()
	df_clean['year'] = df_clean['year'].astype(int)

	# Sorteren
	df_clean = df_clean.sort_values('year')

	# Als population lijkt te zijn uitgedrukt in miljarden of percentages, we kunnen dat niet automatisch herkennen altijd
	# Print wat info en plot
	print('\nVoorbeeld rijen:')
	print(df_clean.tail(10))

	# Plot
	fig, ax = plt.subplots(figsize=(10, 6))
	ax.plot(df_clean['year'], df_clean['population'], marker='o', linestyle='-')
	ax.set_xlabel('Jaar')
	ax.set_ylabel('Bevolking (aantal)')
	ax.set_title('Wereldbevolking per jaar (geëxtraheerd van Wikipedia)')
	ax.grid(True, linestyle='--', alpha=0.5)

	# probeer grote getallen mooi te formatteren
	ax.yaxis.set_major_formatter(mtick.StrMethodFormatter('{x:,.0f}'))

	out_file = Path('world_population_by_year.png')
	fig.tight_layout()
	fig.savefig(out_file)
	print(f'Plot opgeslagen als: {out_file.resolve()}')

	# Toon waarde voor 2023 of laatst beschikbare jaar
	wanted_year = 2023
	if wanted_year in df_clean['year'].values:
		val = df_clean.loc[df_clean['year'] == wanted_year, 'population'].iloc[0]
		print(f'Bevolking in {wanted_year}: {val:,.0f}')
	else:
		last_year = int(df_clean['year'].max())
		val = df_clean.loc[df_clean['year'] == last_year, 'population'].iloc[0]
		print(f'2023 niet gevonden; laatst beschikbare jaar: {last_year} met bevolking {val:,.0f}')

	# Laat plot zien (gebruik interactief venster als beschikbaar)
	try:
		plt.show()
	except Exception:
		print('Kan plot niet weergeven in deze omgeving; plot is opgeslagen op schijf.')


if __name__ == '__main__':
	main()

