#- Naam: Joshua Meuleman

#- Datum: 14/11/2025

#- Python Programming - Oefening 6

import numpy as np
import matplotlib.pyplot as plt


def main():
	# Maak x-waarden van -pi tot +pi
	x = np.linspace(-np.pi, np.pi, 400)

	# Bereken sinus en cosinus
	y_sin = np.sin(x)
	y_cos = np.cos(x)

	# Maak de figuur en plot beide functies
	plt.figure(figsize=(8, 5))
	plt.plot(x, y_sin, label='sin(x)', color='tab:blue', linewidth=2)
	plt.plot(x, y_cos, label='cos(x)', color='tab:orange', linewidth=2)

	# Assen, titel en legenda
	plt.axhline(0, color='black', linewidth=0.8, alpha=0.6)
	plt.axvline(0, color='black', linewidth=0.8, alpha=0.6)
	plt.xlabel('x (rad)')
	plt.ylabel('y')
	plt.title('Sinus en Cosinus op [-π, +π]')
	plt.legend()
	plt.grid(True, linestyle='--', alpha=0.5)

	# Toon de figuur
	plt.tight_layout()
	plt.show()


if __name__ == '__main__':
	main()