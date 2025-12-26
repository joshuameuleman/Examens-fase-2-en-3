#ifndef MOVIE_COLLECTION_H
#define MOVIE_COLLECTION_H

#include "Movie.h"
#include <string>

class MovieCollection {
public:
    explicit MovieCollection(const std::string& name_ = "");
    ~MovieCollection();

    // non-copyable to avoid double-free issues
    MovieCollection(const MovieCollection&) = delete;
    MovieCollection& operator=(const MovieCollection&) = delete;

    void addMovie(const std::string& director, const std::string& title, const std::string& genre, int duration);
    bool removeMovie(const std::string& director, const std::string& title);

    void showFirstMovie();
    void showNextMovie();
    void showMovies() const;

    void clearMovies();

private:
    std::string name;
    Movie* head;
    Movie* current; // pointer used by showFirst/showNext
};

#endif // MOVIE_COLLECTION_H
