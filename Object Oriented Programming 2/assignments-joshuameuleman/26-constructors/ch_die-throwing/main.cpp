// main.cpp
#include <iostream>
#include "Die.h"

int main() {
	Die d6; 
	std::cout << "Rolling a 6-sided die 5 times:\n";
	for (int i = 0; i < 5; ++i) {
		std::cout << d6.roll() << (i+1<5 ? ' ' : '\n');
	}

	Die d20(20);
	std::cout << "Rolling a 20-sided die 5 times:\n";
	for (int i = 0; i < 5; ++i) {
		std::cout << d20.roll() << (i+1<5 ? ' ' : '\n');
	}

	return 0;
}
