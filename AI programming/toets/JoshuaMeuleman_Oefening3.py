#- Naam: Joshua Meuleman

#- Datum: 14/11/2025

#- Python Programming - Oefening 3


def add(a, b):
	return a + b


def main():
	# Concrete waarden kiezen
	x = 7
	y = 5

	# Functie aanroepen
	result = add(x, y)
	print(result)

	# Verifiëren of het resultaat correct is
	expected = x + y
	if result == expected:
		print('Verificatie: correct')
	else:
		print(f'Verificatie: fout (resultaat {result}, verwacht {expected})')


if __name__ == '__main__':
	main()




