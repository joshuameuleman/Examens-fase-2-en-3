#- Naam: Joshua Meuleman

#- Datum: 14/11/2025

#- Python Programming - Oefening 1


# Oefening: nested for-lussen die het product van i en j berekenen en afdrukken

def main():
	
	for i in range(1, 6):  # outer loop: 1 t/m 5
		for j in range(1, 6):  # inner loop: 1 t/m 5
			x = i * j  # bereken product
			print(f"i={i}, j={j} -> x={x}")


if __name__ == "__main__":
	main()

