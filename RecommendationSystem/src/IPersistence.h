 // Shape.h
#ifndef IPERSISTENCE_H
#define IPERSISTENCE_H
#include <vector>

#include "movie.h"
#include "user.h"

class IPersistence {
public:
    virtual void Save(std::vector<Movie> &movies, std::vector<User> &users) = 0;
    virtual void Load(std::vector<Movie> &movies, std::vector<User> &users) = 0;
};

#endif