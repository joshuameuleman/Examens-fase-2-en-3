#- Naam: Joshua Meuleman

#- Datum: 14/11/2025

#- Data Analysis - Oefening 1
import os # dit import is nodig om het pad van de script te bepalen
import sys # dit import is nodig om sys.exit te gebruiken

try:
	import pandas as pd
	import numpy as np
	from scipy import stats
	import matplotlib.pyplot as plt
except Exception as e:
	print("Benodigde packages ontbreken. Installeer: pandas, scipy, matplotlib")
	print("Fout:", e)
	sys.exit(1)


def main():
	# locate data.csv in the same folder as this script
	script_dir = os.path.dirname(__file__)
	csv_path = os.path.join(script_dir, 'data.csv')

	if not os.path.isfile(csv_path):
		print(f"Kan bestand niet vinden: {csv_path}")
		return

	df = pd.read_csv(csv_path)

	# Select the first two numeric columns as x and y
	numeric = df.select_dtypes(include=[np.number])
	if numeric.shape[1] < 2:
		print("CSV bevat niet minstens twee numerieke kolommen voor x en y.")
		print("Gevonden kolommen:", list(df.columns))
		return

	x = numeric.iloc[:, 0].values
	y = numeric.iloc[:, 1].values

	# perform linear regression
	res = stats.linregress(x, y)
	slope = res.slope
	intercept = res.intercept
	r_value = res.rvalue
	p_value = res.pvalue
	slope_stderr = res.stderr

	# residual standard deviation (standaardafwijking van de residuen)
	y_pred = intercept + slope * x
	n = len(y)
	if n > 2:
		resid = y - y_pred
		resid_std = np.sqrt(np.sum(resid**2) / (n - 2))
	else:
		resid_std = float('nan')

	# Print requested values
	print(f"Snijpunt met de Y-as (intercept): {intercept}")
	print(f"Helling van de rechte (slope): {slope}")
	print(f"Standaard afwijking (residuen): {resid_std}")
	print(f"Standaardfout van de helling (stderr): {slope_stderr}")
	print(f"R-waarde: {r_value}, P-waarde: {p_value}")

	# Plot data points and regression line
	plt.figure(figsize=(8, 5))
	plt.scatter(x, y, label='Datapunten')
	xs = np.linspace(np.min(x), np.max(x), 200)
	ys = intercept + slope * xs
	plt.plot(xs, ys, color='red', label='Regressielijn')
	plt.xlabel(numeric.columns[0])
	plt.ylabel(numeric.columns[1])
	plt.title('Lineaire regressie')
	plt.legend()
	plt.grid(True)
	plt.tight_layout()
	plt.show()


if __name__ == '__main__':
	main()

