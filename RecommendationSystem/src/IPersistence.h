 #ifndef IPERSISTENCE_H
#define IPERSISTENCE_H
#include <vector>

#include "movie.h"
#include "user.h"

// This interface defines methods for saving and loading users and movies data to/from persistent storage (e.g., file, database).
class IPersistence {
    public:
        // save to the storage
        virtual void Save(std::vector<Movie> &movies, std::vector<User> &users) = 0;
        // load from the storage
        virtual void Load(std::vector<Movie> &movies, std::vector<User> &users) = 0;
};

#endif