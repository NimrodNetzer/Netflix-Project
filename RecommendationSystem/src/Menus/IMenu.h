#ifndef IMENU_H
#define IMENU_H

#include <string>   // For std::string
#include <vector>   // For std::vector

// Abstract base class that defines the interface for a menu system
class IMenu {
public:
    virtual ~IMenu() = default;  // Virtual destructor for proper cleanup in derived classes

    // Pure virtual function for getting the next command from the user input
    virtual int nextCommand() = 0;

    // Pure virtual function for displaying a logic error message (404 Not Found)
    virtual void displayLogicError(const std::string& message) = 0;

    // Pure virtual function for displaying a bad request error message (400 Bad Request)
    virtual void displayBadRequestError(const std::string& message) = 0;

    // Pure virtual function to get the last user input as a string
    virtual const std::string& getLastInput() const = 0;

    // Pure virtual function to display a message to the user
    virtual void displayMessage(const std::string& message) = 0;

    // Pure virtual function to display a list of movie IDs
    virtual void displayMovieList(const std::vector<int>& movies) = 0;
};

#endif // IMENU_H
