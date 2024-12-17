 #ifndef IPERSISTENCE_H
#define IPERSISTENCE_H
#include <vector>

#include "../objects/Movie.h"
#include "../objects/User.h"

 // This interface defines methods for saving and loading users and movies data to/from persistent storage (e.g., file, database).
class IPersistence {
    public:
        // save to the storage
        virtual void Save() = 0;
        // load from the storage
        virtual void Load() = 0;
};

#endif