#- Naam: Joshua Meuleman

#- Datum: 14/11/2025

#- Python Programming - Oefening 4
def maxarray(arr):
	"""Return het maximum in een array (lijst).

	Werkt voor negatieve waarden en controleert op lege lijsten.
	"""
	if not arr:
		raise ValueError("Array is empty")
	maximum = arr[0]
	for value in arr[1:]:
		if value > maximum:
			maximum = value
	return maximum


if __name__ == "__main__":
	# Voorbeeldarray om te testen
	array = [3, 7, 2, 9, 5]

	# Bereken maximum met onze functie
	result = maxarray(array)
	print(f"Maximum: {result}")

	# Verifieer het resultaat tegen de ingebouwde max-functie
	assert result == max(array), f"Verificatie mislukt: {result} != {max(array)}"
	print("Verificatie OK: resultaat komt overeen met ingebouwde max()")

