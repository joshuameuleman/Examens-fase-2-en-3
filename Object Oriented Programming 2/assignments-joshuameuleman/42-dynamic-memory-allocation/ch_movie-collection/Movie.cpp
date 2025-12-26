#include "Movie.h"

Movie::Movie(const std::string& director_, const std::string& title_, const std::string& genre_, int duration_)
    : director(director_), title(title_), genre(genre_), duration(duration_), next(nullptr) {}

void Movie::print() const {
    std::cout << "Title: " << title << "\n";
    std::cout << "Director: " << director << "\n";
    std::cout << "Genre: " << genre << "\n";
    std::cout << "Duration: " << duration << " minutes" << "\n";
}
