#include "MovieCollection.h"
#include <iostream>

int main() {
    MovieCollection collection("My movies");

    collection.addMovie("Christopher Nolan", "Inception", "Sci-Fi", 148);
    collection.addMovie("Peter Jackson", "The Lord of the Rings: The Fellowship of the Ring", "Fantasy", 178);
    collection.addMovie("Hayao Miyazaki", "Spirited Away", "Animation", 125);
    collection.addMovie("Greta Gerwig", "Little Women", "Drama", 135);

    std::cout << "All movies after adding:\n";
    collection.showMovies();

    std::cout << "\nShow first movie:\n";
    collection.showFirstMovie();

    std::cout << "\nShow next movie:\n";
    collection.showNextMovie();

    std::cout << "\nRemoving 'Inception' by Christopher Nolan...\n";
    bool removed = collection.removeMovie("Christopher Nolan", "Inception");
    std::cout << (removed ? "Removed.\n" : "Not found.\n");

    std::cout << "\nAll movies after removal:\n";
    collection.showMovies();

    std::cout << "\nClearing collection (done automatically by destructor)\n";
    // explicit clear is optional: collection.clearMovies();

    return 0;
}
