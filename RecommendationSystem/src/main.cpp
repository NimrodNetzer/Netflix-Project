
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "user.h"
#include "movie.h"
#include "recommendAlgo.h"

int main() {
    // Create movies (IDs from 100 to 116 as per your data)
    Movie movie100(100);
    Movie movie101(101);
    Movie movie102(102);
    Movie movie103(103);
    Movie movie104(104);
    Movie movie105(105);
    Movie movie106(106);
    Movie movie107(107);
    Movie movie108(108);
    Movie movie109(109);
    Movie movie110(110);
    Movie movie111(111);
    Movie movie112(112);
    Movie movie113(113);
    Movie movie114(114);
    Movie movie115(115);
    Movie movie116(116);

    // Create users and assign movies based on your input data
    User user1(1);
    user1.addMovieWatched(movie100);
    user1.addMovieWatched(movie101);
    user1.addMovieWatched(movie102);
    user1.addMovieWatched(movie103);

    User user2(2);
    user2.addMovieWatched(movie101);
    user2.addMovieWatched(movie102);
    user2.addMovieWatched(movie104);
    user2.addMovieWatched(movie105);
    user2.addMovieWatched(movie106);

    User user3(3);
    user3.addMovieWatched(movie100);
    user3.addMovieWatched(movie104);
    user3.addMovieWatched(movie105);
    user3.addMovieWatched(movie107);
    user3.addMovieWatched(movie108);

    User user4(4);
    user4.addMovieWatched(movie101);
    user4.addMovieWatched(movie105);
    user4.addMovieWatched(movie106);
    user4.addMovieWatched(movie107);
    user4.addMovieWatched(movie109);
    user4.addMovieWatched(movie110);

    User user5(5);
    user5.addMovieWatched(movie100);
    user5.addMovieWatched(movie102);
    user5.addMovieWatched(movie103);
    user5.addMovieWatched(movie105);
    user5.addMovieWatched(movie108);
    user5.addMovieWatched(movie111);

    User user6(6);
    user6.addMovieWatched(movie100);
    user6.addMovieWatched(movie103);
    user6.addMovieWatched(movie104);
    user6.addMovieWatched(movie110);
    user6.addMovieWatched(movie111);
    user6.addMovieWatched(movie112);
    user6.addMovieWatched(movie113);

    User user7(7);
    user7.addMovieWatched(movie102);
    user7.addMovieWatched(movie105);
    user7.addMovieWatched(movie106);
    user7.addMovieWatched(movie107);
    user7.addMovieWatched(movie109);
    user7.addMovieWatched(movie110);

    User user8(8);
    user8.addMovieWatched(movie101);
    user8.addMovieWatched(movie104);
    user8.addMovieWatched(movie105);
    user8.addMovieWatched(movie106);
    user8.addMovieWatched(movie109);
    user8.addMovieWatched(movie111);
    user8.addMovieWatched(movie114);

    User user9(9);
    user9.addMovieWatched(movie100);
    user9.addMovieWatched(movie103);
    user9.addMovieWatched(movie105);
    user9.addMovieWatched(movie107);
    user9.addMovieWatched(movie112);
    user9.addMovieWatched(movie113);
    user9.addMovieWatched(movie115);

    User user10(10);
    user10.addMovieWatched(movie100);
    user10.addMovieWatched(movie102);
    user10.addMovieWatched(movie105);
    user10.addMovieWatched(movie106);
    user10.addMovieWatched(movie107);
    user10.addMovieWatched(movie109);
    user10.addMovieWatched(movie110);
    user10.addMovieWatched(movie116);

    // Create a vector and add users to it
    std::vector<User> users = {user1, user2, user3, user4, user5, user6, user7, user8, user9, user10};
    std::vector<Movie> movies = {movie100, movie101, movie102, movie103, movie104, movie105, movie106,
                                 movie107, movie108, movie109, movie110, movie111, movie112, movie113,
                                 movie114, movie115, movie116};


    std::vector<int> sortedMap =
            combineAndCalculateMoviesRelevance(users, movies, user1, movie104);

    // Print using a range-based for loop
    for (size_t i = 0; i < sortedMap.size(); ++i) {
        std::cout << sortedMap[i];
        if (i < sortedMap.size() - 1) {
            std::cout << ", "; // Add a comma except after the last element
        }
    }

    return 0;
}

