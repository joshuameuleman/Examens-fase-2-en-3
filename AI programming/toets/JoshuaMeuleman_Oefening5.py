#- Naam: Joshua Meuleman

#- Datum: 14/11/2025

#- Python Programming - Oefening 5
import numpy as np
import matplotlib.pyplot as plt


def plot_sine():
	# Aantal punten
	n = 100
	# step size
	step = 0.01

	# Maak array [0, 1, ..., 99] en schaal met step zodat waarden lopen van 0 t.e.m. 0.99
	x = np.arange(n) * step

	# Bereken argument van de sinus: 2*pi*x + 0.01
	arg = 2 * np.pi * x + 0.01

	# Bereken y = sin(arg)
	y = np.sin(arg)

	# Plotten
	plt.figure(figsize=(8, 4))
	plt.plot(x, y, marker='o', linestyle='-', color='tab:blue')
	plt.xlabel('X')
	plt.ylabel('Y = sin(2πx + 0.01)')
	plt.title('Sinusfunctie')
	plt.grid(True)

	# Save de plot naar bestand en print bevestiging
	out_file = 'sine_plot.png'
	plt.tight_layout()
	plt.savefig(out_file)
	print(f"Plot opgeslagen naar: {out_file}")


if __name__ == '__main__':
	plot_sine()

