#include <iostream>
#include <vector>
#include "user.h"

int main() {

    // Create a list of users
    std::vector<User> users;

    // Create some example users
    User user1(2);
    user1.addMovieWatched(Movie(103));
    user1.addMovieWatched(Movie(106));

    User user2(4);
    user2.addMovieWatched(Movie(110));

    // Add users to the list
    users.push_back(user1);
    users.push_back(user2);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
