#ifndef FILEPERSISTENCE_H
#define FILEPERSISTENCE_H
#include <vector>
#include "Movie.h"
#include "User.h"
#include "IPersistence.h"

// Object for persisting users and movies to files
class FilePersistence : public IPersistence {
    private:
        // the folder which is used to save and load the files.
        std::string folderName;
    public:
        FilePersistence(std::string folderName) : folderName(folderName) {} ;
        // Gets vectors of movies and users in the system and saves them to files.
        void Save(std::vector<Movie> &movies, std::vector<User> &users) override;
        // Receives two vector references to movies vector and users vector and loads the data into them.
        void Load(std::vector<Movie> &movies, std::vector<User> &users) override;
};



#endif
