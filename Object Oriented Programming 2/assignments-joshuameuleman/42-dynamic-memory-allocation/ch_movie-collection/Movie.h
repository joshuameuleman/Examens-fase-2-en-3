#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <iostream>

class Movie {
public:
    std::string director;
    std::string title;
    std::string genre;
    int duration; // minutes
    Movie* next;

    Movie(const std::string& director_, const std::string& title_, const std::string& genre_, int duration_);
    ~Movie() = default;

    void print() const;
};

#endif // MOVIE_H
