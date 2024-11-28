#ifndef FILEPERSISTENCE_H
#define FILEPERSISTENCE_H
#include <vector>
#include "movie.h"
#include "user.h"
#include "IPersistence.h"


class FilePersistence : public IPersistence {
    private:
        std::string folderName;
    public:
        FilePersistence(std::string folderName) : folderName(folderName) {} ;
        void Save(std::vector<Movie> &movies, std::vector<User> &users);
        void Load(std::vector<Movie> &movies, std::vector<User> &users);
};



#endif
